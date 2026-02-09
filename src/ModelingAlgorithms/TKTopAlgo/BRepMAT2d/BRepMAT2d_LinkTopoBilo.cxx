#include <BRepMAT2d_BisectingLocus.hpp>
#include <BRepMAT2d_Explorer.hpp>
#include <BRepMAT2d_LinkTopoBilo.hpp>
#include <BRepTools_WireExplorer.hpp>
#include <Geom2d_CartesianPoint.hpp>
#include <Geom2d_Geometry.hpp>
#include <MAT_BasicElt.hpp>
#include <MAT_Graph.hpp>
#include <NCollection_Sequence.hpp>
#include <Standard_ConstructionError.hpp>
#include <Standard_Type.hpp>
#include <Geom2d_Curve.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_DataMap.hpp>
#include <TopAbs.hpp>
#include <TopExp.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDS_Vertex.hpp>
#include <TopoDS_Wire.hpp>

BRepMAT2d_LinkTopoBilo::BRepMAT2d_LinkTopoBilo()
    : current(0),
      isEmpty(true)
{
}

BRepMAT2d_LinkTopoBilo::BRepMAT2d_LinkTopoBilo(const BRepMAT2d_Explorer&       Explo,
                                               const BRepMAT2d_BisectingLocus& BiLo)
{
  Perform(Explo, BiLo);
}

void BRepMAT2d_LinkTopoBilo::Perform(const BRepMAT2d_Explorer&       Explo,
                                     const BRepMAT2d_BisectingLocus& BiLo)
{
  myMap.Clear();
  myBEShape.Clear();

  TopoDS_Shape S          = Explo.Shape();
  int          IndContour = 1;

  if (S.ShapeType() == TopAbs_FACE)
  {
    TopExp_Explorer Exp(S, TopAbs_WIRE);

    while (Exp.More())
    {
      LinkToWire(TopoDS::Wire(Exp.Current()), Explo, IndContour, BiLo);
      Exp.Next();
      IndContour++;
    }
  }
  else
  {
    throw Standard_ConstructionError("BRepMAT2d_LinkTopoBilo::Perform");
  }
}

void BRepMAT2d_LinkTopoBilo::Init(const TopoDS_Shape& S)
{
  isEmpty = false;
  current = 1;
  if (myMap.IsBound(S))
    myKey = S;
  else
    isEmpty = true;
}

bool BRepMAT2d_LinkTopoBilo::More()
{
  if (isEmpty)
    return false;
  return (current <= myMap(myKey).Length());
}

void BRepMAT2d_LinkTopoBilo::Next()
{
  current++;
}

occ::handle<MAT_BasicElt> BRepMAT2d_LinkTopoBilo::Value() const
{
  return myMap(myKey).Value(current);
}

TopoDS_Shape BRepMAT2d_LinkTopoBilo::GeneratingShape(const occ::handle<MAT_BasicElt>& BE) const
{
  return myBEShape(BE);
}

static void LinkToContour(const BRepMAT2d_Explorer&       Explo,
                          const int                       IndC,
                          const BRepMAT2d_BisectingLocus& BiLo,
                          NCollection_DataMap<int, int>&  Link);

void BRepMAT2d_LinkTopoBilo::LinkToWire(const TopoDS_Wire&              W,
                                        const BRepMAT2d_Explorer&       Explo,
                                        const int                       IndC,
                                        const BRepMAT2d_BisectingLocus& BiLo)
{
  BRepTools_WireExplorer                          TheExp(W);
  int                                             KC;
  TopoDS_Vertex                                   VF, VL;
  TopoDS_Shape                                    S;
  occ::handle<MAT_BasicElt>                       BE;
  occ::handle<Standard_Type>                      Type;
  NCollection_Sequence<TopoDS_Shape>              TopoSeq;
  NCollection_Sequence<occ::handle<MAT_BasicElt>> EmptySeq;

  NCollection_DataMap<int, int>::Iterator Ite;
  NCollection_DataMap<int, int>           LinkBECont;

  for (; TheExp.More(); TheExp.Next())
  {
    TopoSeq.Append(TheExp.Current());
  }

  LinkToContour(Explo, IndC, BiLo, LinkBECont);

  for (Ite.Initialize(LinkBECont); Ite.More(); Ite.Next())
  {
    BE   = BiLo.Graph()->BasicElt(Ite.Key());
    Type = BiLo.GeomElt(BE)->DynamicType();
    KC   = Ite.Value();
    S    = TopoSeq.Value(std::abs(KC));

    if (Type == STANDARD_TYPE(Geom2d_CartesianPoint))
    {
      if (S.Orientation() == TopAbs_REVERSED)
      {
        TopExp::Vertices(TopoDS::Edge(S), VL, VF);
      }
      else
      {
        TopExp::Vertices(TopoDS::Edge(S), VF, VL);
      }
      if (KC > 0)
        S = VL;
      else
        S = VF;
    }
    if (!myMap.IsBound(S))
    {
      myMap.Bind(S, EmptySeq);
    }
    myMap(S).Append(BE);

    if (KC < 0)
      myBEShape.Bind(BE, S.Oriented(TopAbs::Reverse(S.Orientation())));
    else
      myBEShape.Bind(BE, S);
  }
}

void LinkToContour(const BRepMAT2d_Explorer&       Explo,
                   const int                       IndC,
                   const BRepMAT2d_BisectingLocus& BiLo,
                   NCollection_DataMap<int, int>&  Link)
{
  occ::handle<MAT_BasicElt>    BE;
  occ::handle<Geom2d_Geometry> GeomBE;
  occ::handle<Standard_Type>   Type;
  bool                         DirectSense = true;
  bool                         LastPoint   = false;
  int                          NbSect, ISect;

  const NCollection_Sequence<occ::handle<Geom2d_Curve>>& Cont = Explo.Contour(IndC);

  int IndOnCont     = 1;
  int PrecIndOnCont = -1;
  NbSect            = BiLo.NumberOfSections(IndC, 1);
  ISect             = 0;

  for (int i = 1; i <= BiLo.NumberOfElts(IndC); i++)
  {

    BE     = BiLo.BasicElt(IndC, i);
    GeomBE = BiLo.GeomElt(BE);
    Type   = GeomBE->DynamicType();

    if (Type != STANDARD_TYPE(Geom2d_CartesianPoint))
    {
      ISect++;

      if (DirectSense)
      {
        Link.Bind(BE->Index(), IndOnCont);
      }
      else
      {
        Link.Bind(BE->Index(), -IndOnCont);
      }
    }
    else
    {

      if (DirectSense || LastPoint)
      {
        Link.Bind(BE->Index(), PrecIndOnCont);
      }
      else
      {
        Link.Bind(BE->Index(), -PrecIndOnCont);
      }
    }

    PrecIndOnCont = IndOnCont;

    if (Type != STANDARD_TYPE(Geom2d_CartesianPoint) && ISect == NbSect)
    {
      if (IndOnCont < Cont.Length() && DirectSense)
      {
        IndOnCont++;
        NbSect = BiLo.NumberOfSections(IndC, IndOnCont);
        ISect  = 0;
      }
      else
      {

        if (!DirectSense)
        {
          IndOnCont--;
          if (IndOnCont != 0)
            NbSect = BiLo.NumberOfSections(IndC, IndOnCont);
          LastPoint = false;
        }
        else
        {
          LastPoint = true;
        }
        ISect       = 0;
        DirectSense = false;
      }
    }
  }
}
