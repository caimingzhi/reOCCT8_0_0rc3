#include <PrsDim_EqualDistanceRelation.hpp>

#include <PrsDim.hpp>
#include <PrsDim_LengthDimension.hpp>
#include <Bnd_Box.hpp>
#include <BRep_Tool.hpp>
#include <BRepAdaptor_Curve.hpp>
#include <BRepBuilderAPI_MakeVertex.hpp>
#include <DsgPrs_EqualDistancePresentation.hpp>
#include <ElCLib.hpp>
#include <Geom_Circle.hpp>
#include <Geom_Line.hpp>
#include <Geom_Plane.hpp>
#include <GeomAPI_ProjectPointOnCurve.hpp>
#include <gp_Lin.hpp>
#include <gp_Pnt.hpp>
#include <Precision.hpp>
#include <Prs3d_ArrowAspect.hpp>
#include <Prs3d_DimensionAspect.hpp>
#include <Prs3d_Drawer.hpp>
#include <Prs3d_Presentation.hpp>
#include <Select3D_SensitiveBox.hpp>
#include <Select3D_SensitivePoly.hpp>
#include <Select3D_SensitiveSegment.hpp>
#include <SelectMgr_EntityOwner.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDS_Vertex.hpp>

IMPLEMENT_STANDARD_RTTIEXT(PrsDim_EqualDistanceRelation, PrsDim_Relation)

PrsDim_EqualDistanceRelation::PrsDim_EqualDistanceRelation(const TopoDS_Shape&            aShape1,
                                                           const TopoDS_Shape&            aShape2,
                                                           const TopoDS_Shape&            aShape3,
                                                           const TopoDS_Shape&            aShape4,
                                                           const occ::handle<Geom_Plane>& aPlane)

{
  myFShape = aShape1;
  mySShape = aShape2;
  myShape3 = aShape3;
  myShape4 = aShape4;
  myPlane  = aPlane;

  myArrowSize = 3.0;
  mySymbolPrs = DsgPrs_AS_BOTHAR;
}

void PrsDim_EqualDistanceRelation::Compute(const occ::handle<PrsMgr_PresentationManager>&,
                                           const occ::handle<Prs3d_Presentation>& aPresentation,
                                           const int)
{
  gp_Pnt Position12 = myPosition, Position34 = myPosition;

  occ::handle<Prs3d_DimensionAspect> la  = myDrawer->DimensionAspect();
  occ::handle<Prs3d_ArrowAspect>     arr = la->ArrowAspect();
  arr->SetLength(myArrowSize);

  if (!myAutomaticPosition)
  {
    gp_Pnt aMiddle12((myPoint1.XYZ() + myPoint2.XYZ()) * 0.5);
    gp_Pnt aMiddle34((myPoint3.XYZ() + myPoint4.XYZ()) * 0.5);

    if (myPosition.Distance(aMiddle12) > myPosition.Distance(aMiddle34))
      Position12.SetXYZ((myPoint1.XYZ() + myPoint2.XYZ()) * 0.5);
    else
      Position34.SetXYZ((myPoint3.XYZ() + myPoint4.XYZ()) * 0.5);
  }

  if (myFShape.ShapeType() == TopAbs_EDGE && mySShape.ShapeType() == TopAbs_EDGE)
    PrsDim_EqualDistanceRelation::ComputeTwoEdgesLength(aPresentation,
                                                        myDrawer,
                                                        myArrowSize,
                                                        TopoDS::Edge(myFShape),
                                                        TopoDS::Edge(mySShape),
                                                        myPlane,
                                                        myAutomaticPosition,
                                                        myIsSetBndBox,
                                                        myBndBox,
                                                        Position12,
                                                        myAttachPoint1,
                                                        myAttachPoint2,
                                                        myPoint1,
                                                        myPoint2,
                                                        mySymbolPrs);

  else if (myFShape.ShapeType() == TopAbs_VERTEX && mySShape.ShapeType() == TopAbs_VERTEX)
    PrsDim_EqualDistanceRelation::ComputeTwoVerticesLength(aPresentation,
                                                           myDrawer,
                                                           myArrowSize,
                                                           TopoDS::Vertex(myFShape),
                                                           TopoDS::Vertex(mySShape),
                                                           myPlane,
                                                           myAutomaticPosition,
                                                           myIsSetBndBox,
                                                           myBndBox,
                                                           PrsDim_TypeOfDist_Unknown,
                                                           Position12,
                                                           myAttachPoint1,
                                                           myAttachPoint2,
                                                           myPoint1,
                                                           myPoint2,
                                                           mySymbolPrs);
  else
    PrsDim_EqualDistanceRelation::ComputeOneEdgeOneVertexLength(aPresentation,
                                                                myDrawer,
                                                                myArrowSize,
                                                                myFShape,
                                                                mySShape,
                                                                myPlane,
                                                                myAutomaticPosition,
                                                                myIsSetBndBox,
                                                                myBndBox,
                                                                Position12,
                                                                myAttachPoint1,
                                                                myAttachPoint2,
                                                                myPoint1,
                                                                myPoint2,
                                                                mySymbolPrs);

  if (myShape3.ShapeType() == TopAbs_EDGE && myShape4.ShapeType() == TopAbs_EDGE)
    PrsDim_EqualDistanceRelation::ComputeTwoEdgesLength(aPresentation,
                                                        myDrawer,
                                                        myArrowSize,
                                                        TopoDS::Edge(myShape3),
                                                        TopoDS::Edge(myShape4),
                                                        myPlane,
                                                        myAutomaticPosition,
                                                        myIsSetBndBox,
                                                        myBndBox,
                                                        Position34,
                                                        myAttachPoint3,
                                                        myAttachPoint4,
                                                        myPoint3,
                                                        myPoint4,
                                                        mySymbolPrs);

  else if (myShape3.ShapeType() == TopAbs_VERTEX && myShape4.ShapeType() == TopAbs_VERTEX)
    PrsDim_EqualDistanceRelation::ComputeTwoVerticesLength(aPresentation,
                                                           myDrawer,
                                                           myArrowSize,
                                                           TopoDS::Vertex(myShape3),
                                                           TopoDS::Vertex(myShape4),
                                                           myPlane,
                                                           myAutomaticPosition,
                                                           myIsSetBndBox,
                                                           myBndBox,
                                                           PrsDim_TypeOfDist_Unknown,
                                                           Position34,
                                                           myAttachPoint3,
                                                           myAttachPoint4,
                                                           myPoint3,
                                                           myPoint4,
                                                           mySymbolPrs);

  else
    PrsDim_EqualDistanceRelation::ComputeOneEdgeOneVertexLength(aPresentation,
                                                                myDrawer,
                                                                myArrowSize,
                                                                myShape3,
                                                                myShape4,
                                                                myPlane,
                                                                myAutomaticPosition,
                                                                myIsSetBndBox,
                                                                myBndBox,
                                                                Position34,
                                                                myAttachPoint3,
                                                                myAttachPoint4,
                                                                myPoint3,
                                                                myPoint4,
                                                                mySymbolPrs);

  DsgPrs_EqualDistancePresentation::Add(aPresentation,
                                        myDrawer,
                                        myPoint1,
                                        myPoint2,
                                        myPoint3,
                                        myPoint4,
                                        myPlane);
}

void PrsDim_EqualDistanceRelation::ComputeSelection(
  const occ::handle<SelectMgr_Selection>& aSelection,
  const int)
{
  occ::handle<SelectMgr_EntityOwner>     own = new SelectMgr_EntityOwner(this, 7);
  occ::handle<Select3D_SensitiveSegment> seg;

  seg = new Select3D_SensitiveSegment(own, myPoint1, myPoint2);
  aSelection->Add(seg);

  seg = new Select3D_SensitiveSegment(own, myPoint3, myPoint4);
  aSelection->Add(seg);

  gp_Pnt Middle12((myPoint1.XYZ() + myPoint2.XYZ()) * 0.5),
    Middle34((myPoint3.XYZ() + myPoint4.XYZ()) * 0.5);
  seg = new Select3D_SensitiveSegment(own, Middle12, Middle34);
  aSelection->Add(seg);

  gp_Pnt                             Middle((Middle12.XYZ() + Middle34.XYZ()) * 0.5);
  double                             SmallDist = .001;
  occ::handle<Select3D_SensitiveBox> box       = new Select3D_SensitiveBox(own,
                                                                     Middle.X() - SmallDist,
                                                                     Middle.Y() - SmallDist,
                                                                     Middle.Z() - SmallDist,
                                                                     Middle.X() + SmallDist,
                                                                     Middle.Y() + SmallDist,
                                                                     Middle.Z() + SmallDist);
  aSelection->Add(box);

  if (myFShape.ShapeType() == TopAbs_EDGE)
  {
    BRepAdaptor_Curve aCurve(TopoDS::Edge(myFShape));
    if (aCurve.GetType() == GeomAbs_Line)
    {

      seg = new Select3D_SensitiveSegment(own, myAttachPoint1, myPoint1);
      aSelection->Add(seg);
    }
    else if (aCurve.GetType() == GeomAbs_Circle)
    {
      occ::handle<Geom_Circle> aCircle  = occ::down_cast<Geom_Circle>(aCurve.Curve().Curve());
      double                   FirstPar = ElCLib::Parameter(aCircle->Circ(), myAttachPoint1),
             LastPar                    = ElCLib::Parameter(aCircle->Circ(), myPoint1);
      if (LastPar < FirstPar)
        LastPar += M_PI * 2;
      occ::handle<Select3D_SensitivePoly> circ =
        new Select3D_SensitivePoly(own, aCircle->Circ(), FirstPar, LastPar);
      aSelection->Add(circ);
    }
  }
  else
  {
    seg = new Select3D_SensitiveSegment(own, myAttachPoint1, myPoint1);
    aSelection->Add(seg);
  }

  if (mySShape.ShapeType() == TopAbs_EDGE)
  {
    BRepAdaptor_Curve aCurve(TopoDS::Edge(mySShape));
    if (aCurve.GetType() == GeomAbs_Line)
    {

      seg = new Select3D_SensitiveSegment(own, myAttachPoint2, myPoint2);
      aSelection->Add(seg);
    }
    else if (aCurve.GetType() == GeomAbs_Circle)
    {
      occ::handle<Geom_Circle> aCircle  = occ::down_cast<Geom_Circle>(aCurve.Curve().Curve());
      double                   FirstPar = ElCLib::Parameter(aCircle->Circ(), myAttachPoint2),
             LastPar                    = ElCLib::Parameter(aCircle->Circ(), myPoint2);
      if (LastPar < FirstPar)
        LastPar += M_PI * 2;
      occ::handle<Select3D_SensitivePoly> circ =
        new Select3D_SensitivePoly(own, aCircle->Circ(), FirstPar, LastPar);
      aSelection->Add(circ);
    }
  }
  else
  {
    seg = new Select3D_SensitiveSegment(own, myAttachPoint2, myPoint2);
    aSelection->Add(seg);
  }

  if (myShape3.ShapeType() == TopAbs_EDGE)
  {
    BRepAdaptor_Curve aCurve(TopoDS::Edge(myShape3));
    if (aCurve.GetType() == GeomAbs_Line)
    {

      seg = new Select3D_SensitiveSegment(own, myAttachPoint3, myPoint3);
      aSelection->Add(seg);
    }
    else if (aCurve.GetType() == GeomAbs_Circle)
    {
      occ::handle<Geom_Circle> aCircle  = occ::down_cast<Geom_Circle>(aCurve.Curve().Curve());
      double                   FirstPar = ElCLib::Parameter(aCircle->Circ(), myAttachPoint3),
             LastPar                    = ElCLib::Parameter(aCircle->Circ(), myPoint3);
      if (LastPar < FirstPar)
        LastPar += M_PI * 2;
      occ::handle<Select3D_SensitivePoly> circ =
        new Select3D_SensitivePoly(own, aCircle->Circ(), FirstPar, LastPar);
      aSelection->Add(circ);
    }
    else
    {
      seg = new Select3D_SensitiveSegment(own, myAttachPoint3, myPoint3);
      aSelection->Add(seg);
    }
  }
  else
  {
    seg = new Select3D_SensitiveSegment(own, myAttachPoint3, myPoint3);
    aSelection->Add(seg);
  }

  if (myShape4.ShapeType() == TopAbs_EDGE)
  {
    BRepAdaptor_Curve aCurve(TopoDS::Edge(myShape4));
    if (aCurve.GetType() == GeomAbs_Line)
    {

      seg = new Select3D_SensitiveSegment(own, myAttachPoint4, myPoint4);
      aSelection->Add(seg);
    }
    else if (aCurve.GetType() == GeomAbs_Circle)
    {
      occ::handle<Geom_Circle> aCircle  = occ::down_cast<Geom_Circle>(aCurve.Curve().Curve());
      double                   FirstPar = ElCLib::Parameter(aCircle->Circ(), myAttachPoint4),
             LastPar                    = ElCLib::Parameter(aCircle->Circ(), myPoint4);
      if (LastPar < FirstPar)
        LastPar += M_PI * 2;
      occ::handle<Select3D_SensitivePoly> circ =
        new Select3D_SensitivePoly(own, aCircle->Circ(), FirstPar, LastPar);
      aSelection->Add(circ);
    }
  }
  else
  {
    seg = new Select3D_SensitiveSegment(own, myAttachPoint4, myPoint4);
    aSelection->Add(seg);
  }
}

void PrsDim_EqualDistanceRelation::ComputeTwoEdgesLength(
  const occ::handle<Prs3d_Presentation>& aPresentation,
  const occ::handle<Prs3d_Drawer>&       aDrawer,
  const double                           ArrowSize,
  const TopoDS_Edge&                     FirstEdge,
  const TopoDS_Edge&                     SecondEdge,
  const occ::handle<Geom_Plane>&         Plane,
  const bool                             AutomaticPos,
  const bool                             IsSetBndBox,
  const Bnd_Box&                         BndBox,
  gp_Pnt&                                Position,
  gp_Pnt&                                FirstAttach,
  gp_Pnt&                                SecondAttach,
  gp_Pnt&                                FirstExtreme,
  gp_Pnt&                                SecondExtreme,
  DsgPrs_ArrowSide&                      SymbolPrs)
{
  gp_Dir            DirAttach;
  BRepAdaptor_Curve cu1(FirstEdge);
  BRepAdaptor_Curve cu2(SecondEdge);

  occ::handle<Geom_Curve> geom1, geom2;
  gp_Pnt                  ptat11, ptat12, ptat21, ptat22;

  bool                    isInfinite1(false), isInfinite2(false);
  occ::handle<Geom_Curve> extCurv;
  double                  arrsize = ArrowSize;
  double                  Val     = 0.;
  bool                    isInPlane1, isInPlane2;

  if (!PrsDim::ComputeGeometry(FirstEdge,
                               geom1,
                               ptat11,
                               ptat12,
                               extCurv,
                               isInfinite1,
                               isInPlane1,
                               Plane))
    return;
  if (!PrsDim::ComputeGeometry(SecondEdge,
                               geom2,
                               ptat21,
                               ptat22,
                               extCurv,
                               isInfinite2,
                               isInPlane2,
                               Plane))
    return;

  aPresentation->SetInfiniteState(isInfinite1 || isInfinite2);

  if (cu1.GetType() == GeomAbs_Line && cu2.GetType() == GeomAbs_Line)
  {
    occ::handle<Geom_Line> geom_lin1(occ::down_cast<Geom_Line>(geom1));
    occ::handle<Geom_Line> geom_lin2(occ::down_cast<Geom_Line>(geom2));
    const gp_Lin&          l1 = geom_lin1->Lin();
    const gp_Lin&          l2 = geom_lin2->Lin();

    Val = l1.Distance(l2);

    DirAttach = l1.Direction();

    if (AutomaticPos)
    {

      gp_Pnt curpos;
      double par1 = 0., par2 = 0.;
      if (!(isInfinite1 || isInfinite2))
      {
        par1 = ElCLib::Parameter(l1, ptat11);
        par2 = ElCLib::Parameter(l1, ptat21);
        if (par1 < par2)
        {
          gp_Pnt p2 = ElCLib::Value(ElCLib::Parameter(l2, ptat11), l2);
          curpos.SetXYZ((ptat11.XYZ() + p2.XYZ()) * 0.5);
        }
        else
        {
          gp_Pnt p2 = ElCLib::Value(par2, l1);
          curpos.SetXYZ((ptat21.XYZ() + p2.XYZ()) * 0.5);
        }
      }
      else if (!isInfinite1)
      {
        par2      = ElCLib::Parameter(l1, ptat21);
        gp_Pnt p2 = ElCLib::Value(par2, l1);
        curpos.SetXYZ((ptat21.XYZ() + p2.XYZ()) / 2.);
      }
      else if (!isInfinite2)
      {
        gp_Pnt p2 = ElCLib::Value(ElCLib::Parameter(l2, ptat11), l2);
        curpos.SetXYZ((ptat11.XYZ() + p2.XYZ()) * 0.5);
      }
      else
        curpos.SetXYZ((l1.Location().XYZ() + l2.Location().XYZ()) * 0.5);

      gp_Vec offset(DirAttach);
      offset = offset * ArrowSize * (-10.);
      curpos.Translate(offset);
      Position = curpos;
    }
    else
    {
      Position = PrsDim::ProjectPointOnPlane(Position, Plane->Pln());
    }

    if (!isInfinite1)
    {
      if (Position.Distance(ptat11) > Position.Distance(ptat12))
        FirstAttach = ptat12;
      else
        FirstAttach = ptat11;
    }
    else
    {
      FirstAttach = ElCLib::Value(ElCLib::Parameter(l1, Position), l1);
    }

    if (!isInfinite2)
    {
      if (Position.Distance(ptat21) > Position.Distance(ptat22))
        SecondAttach = ptat22;
      else
        SecondAttach = ptat21;
    }
    else
    {
      SecondAttach = ElCLib::Value(ElCLib::Parameter(l2, Position), l2);
    }

    constexpr double confusion(Precision::Confusion());
    if (arrsize < confusion)
      arrsize = Val * 0.1;
    if (std::abs(Val) <= confusion)
    {
      arrsize = 0.;
    }

    occ::handle<Prs3d_DimensionAspect> la  = aDrawer->DimensionAspect();
    occ::handle<Prs3d_ArrowAspect>     arr = la->ArrowAspect();
    arr->SetLength(arrsize);
    arr = la->ArrowAspect();
    arr->SetLength(arrsize);

    if (AutomaticPos && IsSetBndBox)
      Position = PrsDim::TranslatePointToBound(Position, DirAttach, BndBox);

    DsgPrs_EqualDistancePresentation::AddInterval(aPresentation,
                                                  aDrawer,
                                                  FirstAttach,
                                                  SecondAttach,
                                                  DirAttach,
                                                  Position,
                                                  SymbolPrs,
                                                  FirstExtreme,
                                                  SecondExtreme);
  }
  if (cu1.GetType() == GeomAbs_Circle && cu2.GetType() == GeomAbs_Circle)
  {

    occ::handle<Geom_Circle> aCir1(occ::down_cast<Geom_Circle>(geom1));
    occ::handle<Geom_Circle> aCir2(occ::down_cast<Geom_Circle>(geom2));
    gp_Circ                  aCirc1 = aCir1->Circ();
    gp_Circ                  aCirc2 = aCir2->Circ();

    constexpr double aTol = Precision::Confusion();
    if (aCirc2.Axis().IsOpposite(aCirc1.Axis(), aTol)
        || aCirc2.XAxis().IsOpposite(aCirc1.XAxis(), aTol)
        || aCirc2.YAxis().IsOpposite(aCirc1.YAxis(), aTol))
    {
      aCirc2.SetPosition(aCirc1.Position());
      aCirc2.SetAxis(aCirc1.Axis());
    }

    if (AutomaticPos)
    {
      double par1 = 0, par2 = 0;
      gp_Pln aPln = Plane->Pln();

      gp_Pnt PrPnt12 = PrsDim::ProjectPointOnPlane(ptat12, aPln);
      gp_Pnt PrPnt22 = PrsDim::ProjectPointOnPlane(ptat22, aPln);

      gp_Pnt PrCenter = PrsDim::ProjectPointOnPlane(aCirc1.Location(), aPln);

      gp_Dir XDir = aPln.XAxis().Direction();
      gp_Dir YDir = aPln.YAxis().Direction();

      if (PrPnt12.Distance(PrCenter) > Precision::Confusion())
      {
        gp_Dir aDir1(PrPnt12.XYZ() - PrCenter.XYZ());
        double anAngle = aDir1.Angle(XDir);
        if (aDir1.Dot(YDir) < 0)
          anAngle = 2 * M_PI - anAngle;
        par1 = anAngle;
      }

      if (PrPnt22.Distance(PrCenter) > Precision::Confusion())
      {
        gp_Dir aDir2(PrPnt22.XYZ() - PrCenter.XYZ());
        double anAngle = aDir2.Angle(XDir);
        if (aDir2.Dot(YDir) < 0)
          anAngle = 2 * M_PI - anAngle;
        par2 = anAngle;
      }

      if (par1 > par2)
      {
        FirstExtreme  = ptat12;
        double aPar1  = ElCLib::Parameter(aCirc2, ptat12);
        SecondExtreme = ElCLib::Value(aPar1, aCirc2);
      }
      else
      {
        double aPar2  = ElCLib::Parameter(aCirc1, ptat22);
        FirstExtreme  = ElCLib::Value(aPar2, aCirc1);
        SecondExtreme = ptat22;
      }
    }
    else
    {
      double pospar = ElCLib::Parameter(aCirc1, Position);
      FirstExtreme  = ElCLib::Value(pospar, aCirc1);
      pospar        = ElCLib::Parameter(aCirc2, Position);
      SecondExtreme = ElCLib::Value(pospar, aCirc2);
    }

    DsgPrs_EqualDistancePresentation::AddIntervalBetweenTwoArcs(aPresentation,
                                                                aDrawer,
                                                                aCirc1,
                                                                aCirc2,
                                                                ptat12,
                                                                FirstExtreme,
                                                                ptat22,
                                                                SecondExtreme,
                                                                SymbolPrs);

    FirstAttach  = ptat12;
    SecondAttach = ptat22;
    Position.SetXYZ((FirstAttach.XYZ() + SecondAttach.XYZ()) * 0.5);
  }

  if (arrsize < Precision::Confusion())
    arrsize = Val * 0.1;
  if (std::abs(Val) <= Precision::Confusion())
  {
    arrsize = 0.;
  }

  if (!isInPlane1)
  {
    PrsDim::ComputeProjEdgePresentation(aPresentation, aDrawer, FirstEdge, geom1, ptat11, ptat12);
  }
  if (!isInPlane2)
  {
    PrsDim::ComputeProjEdgePresentation(aPresentation, aDrawer, SecondEdge, geom2, ptat21, ptat22);
  }
}

void PrsDim_EqualDistanceRelation::ComputeTwoVerticesLength(
  const occ::handle<Prs3d_Presentation>& aPresentation,
  const occ::handle<Prs3d_Drawer>&       aDrawer,
  const double                           ArrowSize,
  const TopoDS_Vertex&                   FirstVertex,
  const TopoDS_Vertex&                   SecondVertex,
  const occ::handle<Geom_Plane>&         Plane,
  const bool                             AutomaticPos,
  const bool                             IsSetBndBox,
  const Bnd_Box&                         BndBox,
  const PrsDim_TypeOfDist                TypeDist,
  gp_Pnt&                                Position,
  gp_Pnt&                                FirstAttach,
  gp_Pnt&                                SecondAttach,
  gp_Pnt&                                FirstExtreme,
  gp_Pnt&                                SecondExtreme,
  DsgPrs_ArrowSide&                      SymbolPrs)
{
  bool   isOnPlane1, isOnPlane2;
  gp_Dir DirAttach;
  PrsDim::ComputeGeometry(FirstVertex, FirstAttach, Plane, isOnPlane1);
  PrsDim::ComputeGeometry(SecondVertex, SecondAttach, Plane, isOnPlane2);

  constexpr double confusion(Precision::Confusion());
  bool             samePoint(FirstAttach.IsEqual(SecondAttach, confusion));

  if (TypeDist == PrsDim_TypeOfDist_Vertical)
    DirAttach = Plane->Pln().XAxis().Direction();
  else if (TypeDist == PrsDim_TypeOfDist_Horizontal)
    DirAttach = Plane->Pln().YAxis().Direction();
  else
  {
    if (!samePoint)
    {
      DirAttach.SetXYZ(SecondAttach.XYZ() - FirstAttach.XYZ());
      DirAttach.Rotate(Plane->Pln().Axis(), M_PI / 2.);
    }
  }

  if (AutomaticPos)
  {
    if (!samePoint)
    {
      gp_Pnt curpos((FirstAttach.XYZ() + SecondAttach.XYZ()) * 0.5);

      gp_Vec offset(DirAttach);
      offset = offset * ArrowSize * (-10.);
      curpos.Translate(offset);
      Position = curpos;
    }
    else
    {
      gp_Dir aDir = Plane->Pln().Axis().Direction();
      gp_Vec aVec(aDir.XYZ() * 10 * ArrowSize);

      Position = FirstAttach.Translated(aVec);
      Position = PrsDim::ProjectPointOnPlane(Position, Plane->Pln());
      DirAttach.SetXYZ(Position.XYZ() - FirstAttach.XYZ());
    }
  }
  else
  {
    Position = PrsDim::ProjectPointOnPlane(Position, Plane->Pln());
  }

  occ::handle<Prs3d_DimensionAspect> la  = aDrawer->DimensionAspect();
  occ::handle<Prs3d_ArrowAspect>     arr = la->ArrowAspect();
  arr->SetLength(ArrowSize);
  arr = la->ArrowAspect();
  arr->SetLength(ArrowSize);

  if (AutomaticPos && IsSetBndBox)
    Position = PrsDim::TranslatePointToBound(Position, DirAttach, BndBox);

  DsgPrs_EqualDistancePresentation::AddInterval(aPresentation,
                                                aDrawer,
                                                FirstAttach,
                                                SecondAttach,
                                                DirAttach,
                                                Position,
                                                SymbolPrs,
                                                FirstExtreme,
                                                SecondExtreme);

  if (!isOnPlane1)
    PrsDim::ComputeProjVertexPresentation(aPresentation, aDrawer, FirstVertex, FirstAttach);
  if (!isOnPlane2)
    PrsDim::ComputeProjVertexPresentation(aPresentation, aDrawer, SecondVertex, SecondAttach);
}

void PrsDim_EqualDistanceRelation::ComputeOneEdgeOneVertexLength(
  const occ::handle<Prs3d_Presentation>& aPresentation,
  const occ::handle<Prs3d_Drawer>&       aDrawer,
  const double                           ArrowSize,
  const TopoDS_Shape&                    FirstShape,
  const TopoDS_Shape&                    SecondShape,
  const occ::handle<Geom_Plane>&         Plane,
  const bool                             AutomaticPos,
  const bool                             IsSetBndBox,
  const Bnd_Box&                         BndBox,
  gp_Pnt&                                Position,
  gp_Pnt&                                FirstAttach,
  gp_Pnt&                                SecondAttach,
  gp_Pnt&                                FirstExtreme,
  gp_Pnt&                                SecondExtreme,
  DsgPrs_ArrowSide&                      SymbolPrs)
{
  TopoDS_Vertex thevertex;
  TopoDS_Edge   theedge;

  gp_Pnt                  ptonedge1, ptonedge2;
  occ::handle<Geom_Curve> aCurve;
  occ::handle<Geom_Curve> extCurv;
  bool                    isInfinite;
  double                  Val;
  bool                    isOnPlanEdge, isOnPlanVertex;
  int                     edgenum;

  if (FirstShape.ShapeType() == TopAbs_VERTEX)
  {
    thevertex = TopoDS::Vertex(FirstShape);
    theedge   = TopoDS::Edge(SecondShape);
    edgenum   = 2;
  }
  else
  {
    thevertex = TopoDS::Vertex(SecondShape);
    theedge   = TopoDS::Edge(FirstShape);
    edgenum   = 1;
  }
  if (!PrsDim::ComputeGeometry(theedge,
                               aCurve,
                               ptonedge1,
                               ptonedge2,
                               extCurv,
                               isInfinite,
                               isOnPlanEdge,
                               Plane))
    return;
  aPresentation->SetInfiniteState(isInfinite);
  PrsDim::ComputeGeometry(thevertex, FirstAttach, Plane, isOnPlanVertex);

  if (aCurve->IsInstance(STANDARD_TYPE(Geom_Line)))
  {
    occ::handle<Geom_Line> geom_lin(occ::down_cast<Geom_Line>(aCurve));
    const gp_Lin&          l = geom_lin->Lin();

    Val = l.Distance(FirstAttach);

    gp_Dir DirAttach = l.Direction();

    double arrsize = ArrowSize;
    if (std::abs(Val) <= Precision::Confusion())
    {
      arrsize = 0.;
    }

    if (AutomaticPos)
    {
      gp_Pnt p = ElCLib::Value(ElCLib::Parameter(l, FirstAttach), l);
      gp_Pnt curpos((FirstAttach.XYZ() + p.XYZ()) * 0.5);

      gp_Vec offset(DirAttach);
      offset = offset * ArrowSize * (-10.);
      curpos.Translate(offset);
      Position = curpos;
    }
    else
    {
      Position = PrsDim::ProjectPointOnPlane(Position, Plane->Pln());
    }

    if (!isInfinite)
    {
      if (Position.Distance(ptonedge1) > Position.Distance(ptonedge2))
        SecondAttach = ptonedge2;
      else
        SecondAttach = ptonedge1;
    }
    else
    {
      SecondAttach = ElCLib::Value(ElCLib::Parameter(l, Position), l);
    }

    occ::handle<Prs3d_DimensionAspect> la  = aDrawer->DimensionAspect();
    occ::handle<Prs3d_ArrowAspect>     arr = la->ArrowAspect();
    arr->SetLength(arrsize);
    arr = la->ArrowAspect();
    arr->SetLength(arrsize);

    if (AutomaticPos && IsSetBndBox)
      Position = PrsDim::TranslatePointToBound(Position, DirAttach, BndBox);
    DsgPrs_EqualDistancePresentation::AddInterval(aPresentation,
                                                  aDrawer,
                                                  FirstAttach,
                                                  SecondAttach,
                                                  DirAttach,
                                                  Position,
                                                  SymbolPrs,
                                                  FirstExtreme,
                                                  SecondExtreme);
  }
  if (aCurve->IsInstance(STANDARD_TYPE(Geom_Circle)))
  {
    gp_Circ aCirc1 = (occ::down_cast<Geom_Circle>(aCurve))->Circ();
    gp_Circ aCirc2(aCirc1);
    aCirc2.SetRadius(0);
    if (AutomaticPos)
    {
      SecondAttach = ptonedge2;
      Position.SetXYZ((SecondAttach.XYZ() + aCirc1.Location().XYZ()) * 0.5);
    }
    else
    {
      double aPar  = ElCLib::Parameter(aCirc1, Position);
      SecondAttach = ElCLib::Value(aPar, aCirc1);
    }

    occ::handle<Geom_Circle> aCurve2 = new Geom_Circle(aCirc2);
    DsgPrs_EqualDistancePresentation::AddIntervalBetweenTwoArcs(aPresentation,
                                                                aDrawer,
                                                                aCirc1,
                                                                aCirc2,
                                                                ptonedge2,
                                                                SecondAttach,
                                                                FirstAttach,
                                                                FirstAttach,
                                                                SymbolPrs);

    if (edgenum == 1)
    {
      FirstExtreme  = SecondAttach;
      SecondExtreme = FirstAttach;
      SecondAttach  = FirstAttach;
      FirstAttach   = ptonedge2;
    }
    else
    {
      FirstExtreme  = FirstAttach;
      SecondExtreme = SecondAttach;
      SecondAttach  = ptonedge2;
    }
  }

  Val = FirstAttach.Distance(SecondAttach);

  if (!isOnPlanEdge)
  {
    PrsDim::ComputeProjEdgePresentation(aPresentation,
                                        aDrawer,
                                        theedge,
                                        aCurve,
                                        ptonedge1,
                                        ptonedge2);
  }
  if (!isOnPlanVertex)
  {
    PrsDim::ComputeProjVertexPresentation(aPresentation, aDrawer, thevertex, FirstAttach);
  }
}
