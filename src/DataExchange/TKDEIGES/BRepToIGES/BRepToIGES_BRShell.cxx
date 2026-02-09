#include <BRep_Builder.hpp>
#include <BRep_Tool.hpp>
#include <BRepBuilderAPI_Copy.hpp>
#include <BRepToIGES_BRShell.hpp>
#include <BRepToIGES_BRWire.hpp>
#include <BRepTools.hpp>
#include <Geom2d_Curve.hpp>
#include <Geom_ConicalSurface.hpp>
#include <Geom_CylindricalSurface.hpp>
#include <Geom_Plane.hpp>
#include <Geom_RectangularTrimmedSurface.hpp>
#include <Geom_Surface.hpp>
#include <GeomToIGES_GeomSurface.hpp>
#include <gp_Trsf.hpp>
#include <IGESBasic_Group.hpp>
#include <IGESData_IGESEntity.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <IGESGeom_TrimmedSurface.hpp>
#include <MoniTool_Macros.hpp>
#include <Message_ProgressScope.hpp>
#include <NCollection_IncAllocator.hpp>
#include <NCollection_Map.hpp>
#include <ShapeAlgo.hpp>
#include <ShapeAlgo_AlgoContainer.hpp>
#include <Standard_Transient.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <TopAbs_ShapeEnum.hpp>
#include <TopExp_Explorer.hpp>
#include <TopLoc_Location.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDS_Shell.hpp>
#include <TopoDS_Wire.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <Transfer_FinderProcess.hpp>

BRepToIGES_BRShell::BRepToIGES_BRShell() = default;

BRepToIGES_BRShell::BRepToIGES_BRShell(const BRepToIGES_BREntity& BR)
    : BRepToIGES_BREntity(BR)
{
}

occ::handle<IGESData_IGESEntity> BRepToIGES_BRShell ::TransferShell(
  const TopoDS_Shape&          start,
  const Message_ProgressRange& theProgress)
{
  occ::handle<IGESData_IGESEntity> res;

  if (start.IsNull())
    return res;

  if (start.ShapeType() == TopAbs_FACE)
  {
    TopoDS_Face F = TopoDS::Face(start);
    res           = TransferFace(F, theProgress);
  }
  else if (start.ShapeType() == TopAbs_SHELL)
  {
    TopoDS_Shell S = TopoDS::Shell(start);
    res            = TransferShell(S, theProgress);
  }
  else
  {
  }
  return res;
}

occ::handle<IGESData_IGESEntity> BRepToIGES_BRShell ::TransferFace(const TopoDS_Face& start,
                                                                   const Message_ProgressRange&)
{
  occ::handle<IGESData_IGESEntity> res;

  if (start.IsNull())
  {
    return res;
  }

  TopoDS_Face aFace = start;

  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher> aShapeShapeMap;
  if (start.Orientation() == TopAbs_REVERSED)
  {
    BRepBuilderAPI_Copy aCopy;
    aCopy.Perform(aFace);

    BRep_Builder              B;
    TopLoc_Location           aLoc;
    occ::handle<Geom_Surface> aSurf = BRep_Tool::Surface(start, aLoc);
    while (aSurf->IsKind(STANDARD_TYPE(Geom_RectangularTrimmedSurface)))
    {

      occ::handle<Geom_RectangularTrimmedSurface> aTrimmedSurf =
        occ::down_cast<Geom_RectangularTrimmedSurface>(aSurf);
      aSurf = aTrimmedSurf->BasisSurface();
    }
    aSurf       = aSurf->UReversed();
    double aTol = BRep_Tool::Tolerance(start);
    B.MakeFace(aFace, aSurf, aLoc, aTol);

    B.NaturalRestriction(aFace, BRep_Tool::NaturalRestriction(start));

    TopoDS_Wire     anOuter = TopoDS::Wire(ShapeAlgo::AlgoContainer()->OuterWire(start));
    TopExp_Explorer ex;
    for (ex.Init(start, TopAbs_WIRE); ex.More(); ex.Next())
    {
      TopoDS_Wire W         = TopoDS::Wire(ex.Current());
      TopoDS_Wire aCopyWire = TopoDS::Wire(aCopy.ModifiedShape(W));
      aCopyWire             = TopoDS::Wire(aCopyWire.Oriented(W.Orientation()));
      if (!W.IsNull() && W.IsSame(anOuter))
      {
        B.Add(aFace, aCopyWire);
        aShapeShapeMap.Bind(aCopyWire, W);
        break;
      }
    }
    for (ex.Init(start, TopAbs_WIRE); ex.More(); ex.Next())
    {
      TopoDS_Wire W         = TopoDS::Wire(ex.Current());
      TopoDS_Wire aCopyWire = TopoDS::Wire(aCopy.ModifiedShape(W));
      aCopyWire             = TopoDS::Wire(aCopyWire.Oriented(W.Orientation()));
      if (!W.IsNull() && !W.IsSame(anOuter))
      {
        B.Add(aFace, aCopyWire);
        aShapeShapeMap.Bind(aCopyWire, W);
      }
    }

    double U1, U2, V1, V2;
    aSurf->Bounds(U1, U2, V1, V2);
    double    aCenter = 0.5 * (U1 + U2);
    gp_Trsf2d T;
    gp_Ax2d   axis(gp_Pnt2d(aCenter, V1), gp_Dir2d(gp_Dir2d::D::Y));
    T.SetMirror(axis);
    NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> aMap(101, new NCollection_IncAllocator);
    for (ex.Init(start, TopAbs_EDGE); ex.More(); ex.Next())
    {
      TopoDS_Edge anOrigEdge = TopoDS::Edge(ex.Current());
      TopoDS_Edge aCopyEdge  = TopoDS::Edge(aCopy.ModifiedShape(anOrigEdge));
      aCopyEdge              = TopoDS::Edge(aCopyEdge.Oriented(anOrigEdge.Orientation()));
      if (!aMap.Add(aCopyEdge))

        continue;
      double                    f, l;
      occ::handle<Geom2d_Curve> aCurve1, aCurve2;
      aCurve1 =
        BRep_Tool::CurveOnSurface(aCopyEdge, TopoDS::Face(aCopy.ModifiedShape(start)), f, l);
      aTol = BRep_Tool::Tolerance(aCopyEdge);
      if (!aCurve1.IsNull())
      {
        aCurve1 = occ::down_cast<Geom2d_Curve>(aCurve1->Transformed(T));
        if (BRepTools::IsReallyClosed(aCopyEdge, TopoDS::Face(aCopy.ModifiedShape(start))))
        {
          TopoDS_Edge revEdge = TopoDS::Edge(aCopyEdge.Reversed());
          aCurve2 =
            BRep_Tool::CurveOnSurface(revEdge, TopoDS::Face(aCopy.ModifiedShape(start)), f, l);
          if (!aCurve2.IsNull())
          {
            aCurve2 = occ::down_cast<Geom2d_Curve>(aCurve2->Transformed(T));
            if (aCopyEdge.Orientation() == TopAbs_FORWARD)
            {
              B.UpdateEdge(aCopyEdge, aCurve1, aCurve2, aFace, aTol);
            }
            else
            {
              B.UpdateEdge(aCopyEdge, aCurve2, aCurve1, aFace, aTol);
            }
          }
          else
          {
            B.UpdateEdge(aCopyEdge, aCurve1, aFace, aTol);
          }
        }
        else
        {
          B.UpdateEdge(aCopyEdge, aCurve1, aFace, aTol);
        }

        if (BRep_Tool::Degenerated(aCopyEdge))
        {
          B.Range(aCopyEdge, aFace, f, l);
        }
      }

      aShapeShapeMap.Bind(aCopyEdge, anOrigEdge);
    }
    aShapeShapeMap.Bind(start, aFace);
  }

  double                           Length = 1.;
  occ::handle<IGESData_IGESEntity> ISurf;

  occ::handle<Geom_Surface> Surf = BRep_Tool::Surface(aFace);

  if (!Surf.IsNull())
  {
    double U1, U2, V1, V2;

    BRepTools::UVBounds(aFace, U1, U2, V1, V2);
    GeomToIGES_GeomSurface GS;
    GS.SetModel(GetModel());
    ISurf = GS.TransferSurface(Surf, U1, U2, V1, V2);
    if (ISurf.IsNull())
    {
      AddWarning(start, "the basic surface is a null entity");
      return res;
    }
    Length = GS.Length();
  }

  BRepToIGES_BRWire                BW(*this);
  int                              Imode   = 0;
  int                              Iprefer = 0;
  occ::handle<IGESData_IGESEntity> ICurve2d;

  TopoDS_Wire                          Outer  = ShapeAlgo::AlgoContainer()->OuterWire(aFace);
  occ::handle<IGESGeom_CurveOnSurface> IOuter = new IGESGeom_CurveOnSurface;
  if (!Outer.IsNull())
  {
    occ::handle<IGESData_IGESEntity> ICurve3d =
      BW.TransferWire(Outer, aFace, aShapeShapeMap, ICurve2d, Length);
    if ((!ICurve3d.IsNull()) && (!ICurve2d.IsNull()))
      Iprefer = 3;
    if ((!ICurve3d.IsNull()) && (ICurve2d.IsNull()))
      Iprefer = 2;
    if ((ICurve3d.IsNull()) && (!ICurve2d.IsNull()))
      Iprefer = 1;
    IOuter->Init(Imode, ISurf, ICurve2d, ICurve3d, Iprefer);
  }

  TopExp_Explorer                                                     Ex;
  occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>> Seq =
    new NCollection_HSequence<occ::handle<Standard_Transient>>();

  for (Ex.Init(aFace, TopAbs_WIRE); Ex.More(); Ex.Next())
  {
    TopoDS_Wire                          W     = TopoDS::Wire(Ex.Current());
    occ::handle<IGESGeom_CurveOnSurface> Curve = new IGESGeom_CurveOnSurface;
    if (W.IsNull())
    {
      AddWarning(start, " an Wire is a null entity");
    }
    else if (!W.IsSame(Outer))
    {
      occ::handle<IGESData_IGESEntity> ICurve3d =
        BW.TransferWire(W, aFace, aShapeShapeMap, ICurve2d, Length);
      if ((!ICurve3d.IsNull()) && (!ICurve2d.IsNull()))
        Iprefer = 3;
      if ((!ICurve3d.IsNull()) && (ICurve2d.IsNull()))
        Iprefer = 2;
      if ((ICurve3d.IsNull()) && (!ICurve2d.IsNull()))
        Iprefer = 1;
      Curve->Init(Imode, ISurf, ICurve2d, ICurve3d, Iprefer);
      if (!Curve.IsNull())
        Seq->Append(Curve);
    }
  }

  for (Ex.Init(aFace, TopAbs_EDGE, TopAbs_WIRE); Ex.More(); Ex.Next())
  {
    TopoDS_Edge                          E     = TopoDS::Edge(Ex.Current());
    occ::handle<IGESGeom_CurveOnSurface> Curve = new IGESGeom_CurveOnSurface;
    if (E.IsNull())
    {
      AddWarning(start, " an Edge is a null entity");
    }
    else
    {
      occ::handle<IGESData_IGESEntity> ICurve3d = BW.TransferEdge(E, aShapeShapeMap, false);
      occ::handle<IGESData_IGESEntity> newICurve2d =
        BW.TransferEdge(E, aFace, aShapeShapeMap, Length, false);
      if ((!ICurve3d.IsNull()) && (!newICurve2d.IsNull()))
        Iprefer = 3;
      if ((!ICurve3d.IsNull()) && (newICurve2d.IsNull()))
        Iprefer = 2;
      if ((ICurve3d.IsNull()) && (!newICurve2d.IsNull()))
        Iprefer = 1;
      Curve->Init(Imode, ISurf, newICurve2d, ICurve3d, Iprefer);
      if (!Curve.IsNull())
        Seq->Append(Curve);
    }
  }

  int                                                                    nbent = Seq->Length();
  occ::handle<NCollection_HArray1<occ::handle<IGESGeom_CurveOnSurface>>> Tab;
  if (nbent >= 1)
  {
    Tab = new NCollection_HArray1<occ::handle<IGESGeom_CurveOnSurface>>(1, nbent);
    for (int itab = 1; itab <= nbent; itab++)
    {
      occ::handle<IGESGeom_CurveOnSurface> item =
        GetCasted(IGESGeom_CurveOnSurface, Seq->Value(itab));
      Tab->SetValue(itab, item);
    }
  }

  bool isWholeSurface = BRep_Tool::NaturalRestriction(start);
  if ((Surf->IsKind(STANDARD_TYPE(Geom_Plane))
       || Surf->IsKind(STANDARD_TYPE(Geom_CylindricalSurface))
       || Surf->IsKind(STANDARD_TYPE(Geom_ConicalSurface)))
      && !IOuter.IsNull())
    isWholeSurface = false;

  occ::handle<IGESGeom_TrimmedSurface> TrimmedSurf = new IGESGeom_TrimmedSurface;
  if (isWholeSurface)
  {

    TrimmedSurf->Init(ISurf, false, nullptr, Tab);
  }
  else
    TrimmedSurf->Init(ISurf, true, IOuter, Tab);

  res = TrimmedSurf;
  SetShapeResult(start, res);
  return res;
}

occ::handle<IGESData_IGESEntity> BRepToIGES_BRShell::TransferShell(
  const TopoDS_Shell&          start,
  const Message_ProgressRange& theProgress)
{
  occ::handle<IGESData_IGESEntity> res;
  if (start.IsNull())
    return res;

  TopExp_Explorer                                                     Ex;
  occ::handle<IGESBasic_Group>                                        IGroup = new IGESBasic_Group;
  occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>> Seq =
    new NCollection_HSequence<occ::handle<Standard_Transient>>();
  occ::handle<IGESData_IGESEntity> IFace;

  int nbshapes = 0;
  for (Ex.Init(start, TopAbs_FACE); Ex.More(); Ex.Next())
    nbshapes++;
  Message_ProgressScope aPS(theProgress, nullptr, nbshapes);
  for (Ex.Init(start, TopAbs_FACE); Ex.More() && aPS.More(); Ex.Next())
  {
    Message_ProgressRange aRange = aPS.Next();
    TopoDS_Face           F      = TopoDS::Face(Ex.Current());
    if (F.IsNull())
    {
      AddWarning(start, " a Face is a null entity");
    }
    else
    {
      IFace = TransferFace(F, aRange);
      if (!IFace.IsNull())
        Seq->Append(IFace);
    }
  }

  int                                                                nbfaces = Seq->Length();
  occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>> Tab;
  if (nbfaces >= 1)
  {
    Tab = new NCollection_HArray1<occ::handle<IGESData_IGESEntity>>(1, nbfaces);
    for (int itab = 1; itab <= nbfaces; itab++)
    {
      occ::handle<IGESData_IGESEntity> item = GetCasted(IGESData_IGESEntity, Seq->Value(itab));
      Tab->SetValue(itab, item);
    }
  }

  if (nbfaces == 1)
  {
    res = IFace;
  }
  else
  {
    IGroup->Init(Tab);
    res = IGroup;
  }

  SetShapeResult(start, res);

  return res;
}
