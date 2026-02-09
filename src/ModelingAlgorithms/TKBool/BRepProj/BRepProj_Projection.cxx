

#include <Bnd_Box.hpp>
#include <BRepAlgoAPI_Section.hpp>
#include <BRepBndLib.hpp>
#include <BRepFill_Generator.hpp>
#include <BRepLib_MakeVertex.hpp>
#include <BRepLib_MakeWire.hpp>
#include <BRepProj_Projection.hpp>
#include <BRepSweep_Prism.hpp>
#include <BRepTools_Modifier.hpp>
#include <BRepTools_TrsfModification.hpp>
#include <gp_Dir.hpp>
#include <gp_Pnt.hpp>
#include <gp_Trsf.hpp>
#include <gp_Vec.hpp>
#include <Precision.hpp>
#include <ShapeAnalysis_FreeBounds.hpp>
#include <Standard_ConstructionError.hpp>
#include <Standard_NullObject.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Shape.hpp>

static double DistanceOut(const TopoDS_Shape& S1, const TopoDS_Shape& S2)
{
  Bnd_Box BBox1, BBox2;
  BRepBndLib::Add(S1, BBox1);
  BRepBndLib::Add(S2, BBox2);
  return BBox1.Distance(BBox2);
}

static double DistanceIn(const TopoDS_Shape& S1, const TopoDS_Shape& S2)
{
  Bnd_Box LBBox, SBBox;
  BRepBndLib::Add(S1, SBBox);
  BRepBndLib::Add(S2, LBBox);

  double LXmin, LYmin, LZmin, LXmax, LYmax, LZmax, SXmin, SYmin, SZmin, SXmax, SYmax, SZmax;
  SBBox.Get(SXmin, SYmin, SZmin, SXmax, SYmax, SZmax);
  LBBox.Get(LXmin, LYmin, LZmin, LXmax, LYmax, LZmax);

  gp_XYZ Lmin(LXmin, LYmin, LZmin), Lmax(LXmax, LYmax, LZmax);
  gp_XYZ Smin(SXmin, SYmin, SZmin), Smax(SXmax, SYmax, SZmax);
  Lmax.Subtract(Lmin);
  Smax.Subtract(Smin);
  return Lmax.Modulus() + Smax.Modulus() + DistanceOut(S1, S2);
}

void BRepProj_Projection::BuildSection(const TopoDS_Shape& theShape, const TopoDS_Shape& theTool)
{
  myIsDone = false;
  mySection.Nullify();
  myShape.Nullify();
  myItr = 0;

  TopoDS_Shape aShape;
  if (theShape.ShapeType() == TopAbs_FACE || theShape.ShapeType() == TopAbs_SHELL
      || theShape.ShapeType() == TopAbs_SOLID || theShape.ShapeType() == TopAbs_COMPSOLID)
    aShape = theShape;
  else if (theShape.ShapeType() == TopAbs_COMPOUND)
  {
    TopoDS_Compound C;
    BRep_Builder    B;
    TopExp_Explorer exp(theShape, TopAbs_FACE);
    for (; exp.More(); exp.Next())
    {
      if (C.IsNull())
        B.MakeCompound(C);
      B.Add(C, exp.Current());
    }
    aShape = C;
  }
  if (aShape.IsNull())
    throw Standard_ConstructionError(__FILE__ ": target shape has no faces");

  BRepAlgoAPI_Section aSectionTool(aShape, theTool, false);
  aSectionTool.Approximation(true);
  aSectionTool.ComputePCurveOn1(true);
  aSectionTool.ComputePCurveOn2(true);

  aSectionTool.SetUseOBB(true);
  aSectionTool.Build();

  if (!aSectionTool.IsDone())
    return;

  occ::handle<NCollection_HSequence<TopoDS_Shape>> anEdges =
    new NCollection_HSequence<TopoDS_Shape>;
  TopExp_Explorer exp(aSectionTool.Shape(), TopAbs_EDGE);
  for (; exp.More(); exp.Next())
    anEdges->Append(exp.Current());

  if (anEdges->Length() <= 0)
    return;

  ShapeAnalysis_FreeBounds::ConnectEdgesToWires(anEdges, Precision::Confusion(), true, mySection);
  myIsDone = (!mySection.IsNull() && mySection->Length() > 0);

  if (myIsDone)
  {
    BRep_Builder B;
    B.MakeCompound(myShape);
    for (int i = 1; i <= mySection->Length(); i++)
      B.Add(myShape, mySection->Value(i));

    myItr = 1;
  }
}

BRepProj_Projection::BRepProj_Projection(const TopoDS_Shape& Wire,
                                         const TopoDS_Shape& Shape,
                                         const gp_Dir&       D)
    : myIsDone(false),
      myItr(0)
{

  Standard_NullObject_Raise_if((Wire.IsNull() || Shape.IsNull()), __FILE__ ": null input shape");
  if (Wire.ShapeType() != TopAbs_EDGE && Wire.ShapeType() != TopAbs_WIRE)
    throw Standard_ConstructionError(__FILE__ ": projected shape is neither wire nor edge");

  double mdis = DistanceIn(Wire, Shape);
  gp_Vec Vsup(D.XYZ() * 2 * mdis);
  gp_Vec Vinf(D.XYZ() * -mdis);

  gp_Trsf T;
  T.SetTranslation(Vinf);

  occ::handle<BRepTools_TrsfModification> Trsf = new BRepTools_TrsfModification(T);
  BRepTools_Modifier                      Modif(Wire, Trsf);
  const TopoDS_Shape&                     WireBase = Modif.ModifiedShape(Wire);

  BRepSweep_Prism CylSurf(WireBase, Vsup, false);

  BuildSection(Shape, CylSurf.Shape());
}

BRepProj_Projection::BRepProj_Projection(const TopoDS_Shape& Wire,
                                         const TopoDS_Shape& Shape,
                                         const gp_Pnt&       P)
    : myIsDone(false),
      myItr(0)
{

  Standard_NullObject_Raise_if((Wire.IsNull() || Shape.IsNull()), __FILE__ ": null input shape");
  if (Wire.ShapeType() != TopAbs_EDGE && Wire.ShapeType() != TopAbs_WIRE)
    throw Standard_ConstructionError(__FILE__ ": projected shape is neither wire nor edge");

  TopoDS_Wire aWire;
  if (Wire.ShapeType() == TopAbs_EDGE)
  {
    BRep_Builder BB;
    BB.MakeWire(aWire);
    BB.Add(aWire, Wire);
  }
  else
    aWire = TopoDS::Wire(Wire);

  double mdis = DistanceIn(Wire, Shape);

  TopExp_Explorer ExpWire;
  ExpWire.Init(aWire, TopAbs_VERTEX);

  gp_Pnt PC = BRep_Tool::Pnt(TopoDS::Vertex(ExpWire.Current()));

  double Scale = PC.Distance(P);
  if (std::abs(Scale) < Precision::Confusion())
    throw Standard_ConstructionError("Projection");
  Scale = 1. + mdis / Scale;

  gp_Trsf T;
  T.SetScale(P, Scale);
  occ::handle<BRepTools_TrsfModification> Tsca = new BRepTools_TrsfModification(T);
  BRepTools_Modifier                      ModifScale(aWire, Tsca);
  TopoDS_Shape                            ShapeGen1 = ModifScale.ModifiedShape(aWire);

  TopoDS_Vertex aVertex = BRepLib_MakeVertex(P);
  TopoDS_Edge   DegEdge;
  BRep_Builder  BB;
  BB.MakeEdge(DegEdge);
  BB.Add(DegEdge, aVertex.Oriented(TopAbs_FORWARD));
  BB.Add(DegEdge, aVertex.Oriented(TopAbs_REVERSED));
  BB.Degenerated(DegEdge, true);

  TopoDS_Wire DegWire;
  BB.MakeWire(DegWire);
  BB.Add(DegWire, DegEdge);
  DegWire.Closed(true);

  BRepFill_Generator RuledSurf;
  RuledSurf.AddWire(DegWire);
  RuledSurf.AddWire(TopoDS::Wire(ShapeGen1));
  RuledSurf.Perform();
  TopoDS_Shell SurfShell = RuledSurf.Shell();

  BuildSection(Shape, SurfShell);
}
