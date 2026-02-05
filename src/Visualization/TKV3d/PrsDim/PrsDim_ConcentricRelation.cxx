#include <PrsDim_ConcentricRelation.hpp>

#include <PrsDim.hpp>
#include <BRepAdaptor_Curve.hpp>
#include <DsgPrs_ConcentricPresentation.hpp>
#include <Geom_Circle.hpp>
#include <Geom_Plane.hpp>
#include <gp_Ax1.hpp>
#include <gp_Ax2.hpp>
#include <gp_Dir.hpp>
#include <gp_Pln.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <Prs3d_Presentation.hpp>
#include <Select3D_SensitiveCircle.hpp>
#include <Select3D_SensitiveSegment.hpp>
#include <SelectMgr_EntityOwner.hpp>
#include <SelectMgr_Selection.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDS_Vertex.hpp>

IMPLEMENT_STANDARD_RTTIEXT(PrsDim_ConcentricRelation, PrsDim_Relation)

//=================================================================================================

PrsDim_ConcentricRelation::PrsDim_ConcentricRelation(const TopoDS_Shape&            aFShape,
                                                     const TopoDS_Shape&            aSShape,
                                                     const occ::handle<Geom_Plane>& aPlane)
{
  myFShape = aFShape;
  mySShape = aSShape;
  myPlane  = aPlane;
  myDir    = aPlane->Pln().Axis().Direction();
}

//=================================================================================================

void PrsDim_ConcentricRelation::Compute(const occ::handle<PrsMgr_PresentationManager>&,
                                        const occ::handle<Prs3d_Presentation>& aPresentation,
                                        const int)
{
  TopAbs_ShapeEnum type2(mySShape.ShapeType());
  aPresentation->SetInfiniteState(true);
  switch (myFShape.ShapeType())
  {
    case TopAbs_EDGE:
    {
      if (type2 == TopAbs_EDGE)
        ComputeTwoEdgesConcentric(aPresentation);
      else if (type2 == TopAbs_VERTEX)
        ComputeEdgeVertexConcentric(aPresentation);
    }
    break;

    case TopAbs_VERTEX:
    {
      if (type2 == TopAbs_VERTEX)
        ComputeTwoVerticesConcentric(aPresentation);
      else if (type2 == TopAbs_EDGE)
        ComputeEdgeVertexConcentric(aPresentation);
    }
    break;
    default:
    {
      return;
    }
  }
}

//=================================================================================================

void PrsDim_ConcentricRelation::ComputeEdgeVertexConcentric(
  const occ::handle<Prs3d_Presentation>& aPresentation)
{
  TopoDS_Edge   E;
  TopoDS_Vertex V;
  if (myFShape.ShapeType() == TopAbs_EDGE)
  {
    E = TopoDS::Edge(myFShape);
    V = TopoDS::Vertex(mySShape);
  }
  else
  {
    E = TopoDS::Edge(mySShape);
    V = TopoDS::Vertex(myFShape);
  }
  gp_Pnt                  p1, p2;
  occ::handle<Geom_Curve> C;
  occ::handle<Geom_Curve> extCurv;
  bool                    isInfinite;
  bool                    isOnPlanEdge, isOnPlanVertex;
  if (!PrsDim::ComputeGeometry(E, C, p1, p2, extCurv, isInfinite, isOnPlanEdge, myPlane))
    return;
  gp_Pnt P;
  PrsDim::ComputeGeometry(V, P, myPlane, isOnPlanVertex);

  occ::handle<Geom_Circle> CIRCLE(occ::down_cast<Geom_Circle>(C));
  myCenter = CIRCLE->Location();
  myRad    = std::min(CIRCLE->Radius() / 5., 15.);
  gp_Dir vec(p1.XYZ() - myCenter.XYZ());
  gp_Vec vectrans(vec);
  myPnt = myCenter.Translated(vectrans.Multiplied(myRad));
  DsgPrs_ConcentricPresentation::Add(aPresentation, myDrawer, myCenter, myRad, myDir, myPnt);
  if (!isOnPlanEdge)
    PrsDim::ComputeProjEdgePresentation(aPresentation, myDrawer, E, CIRCLE, p1, p2);
  if (!isOnPlanVertex)
    PrsDim::ComputeProjVertexPresentation(aPresentation, myDrawer, V, P);
}

//=================================================================================================

void PrsDim_ConcentricRelation::ComputeTwoVerticesConcentric(
  const occ::handle<Prs3d_Presentation>& aPresentation)
{
  TopoDS_Vertex V1, V2;
  V1 = TopoDS::Vertex(myFShape);
  V2 = TopoDS::Vertex(myFShape);
  bool   isOnPlanVertex1(true), isOnPlanVertex2(true);
  gp_Pnt P1, P2;
  PrsDim::ComputeGeometry(V1, P1, myPlane, isOnPlanVertex1);
  PrsDim::ComputeGeometry(V2, P2, myPlane, isOnPlanVertex2);
  myCenter = P1;
  myRad    = 15.;
  gp_Dir vec(myPlane->Pln().Position().XDirection());
  gp_Vec vectrans(vec);
  myPnt = myCenter.Translated(vectrans.Multiplied(myRad));
  DsgPrs_ConcentricPresentation::Add(aPresentation, myDrawer, myCenter, myRad, myDir, myPnt);
  if (!isOnPlanVertex1)
    PrsDim::ComputeProjVertexPresentation(aPresentation, myDrawer, V1, P1);
  if (!isOnPlanVertex2)
    PrsDim::ComputeProjVertexPresentation(aPresentation, myDrawer, V2, P2);
}

//=================================================================================================

void PrsDim_ConcentricRelation::ComputeTwoEdgesConcentric(
  const occ::handle<Prs3d_Presentation>& aPresentation)
{
  BRepAdaptor_Curve curv1(TopoDS::Edge(myFShape));
  BRepAdaptor_Curve curv2(TopoDS::Edge(mySShape));

  gp_Pnt                  ptat11, ptat12, ptat21, ptat22;
  occ::handle<Geom_Curve> geom1, geom2;
  bool                    isInfinite1, isInfinite2;
  occ::handle<Geom_Curve> extCurv;
  if (!PrsDim::ComputeGeometry(TopoDS::Edge(myFShape),
                               TopoDS::Edge(mySShape),
                               myExtShape,
                               geom1,
                               geom2,
                               ptat11,
                               ptat12,
                               ptat21,
                               ptat22,
                               extCurv,
                               isInfinite1,
                               isInfinite2,
                               myPlane))
  {
    return;
  }

  occ::handle<Geom_Circle> gcirc1(occ::down_cast<Geom_Circle>(geom1));
  occ::handle<Geom_Circle> gcirc2(occ::down_cast<Geom_Circle>(geom2));

  myCenter = gcirc1->Location();

  // choose the radius equal to 1/5 of the smallest radius of
  // 2 circles. Limit is imposed ( 0.02 by chance)
  double aRad1 = gcirc1->Radius();
  double aRad2 = gcirc2->Radius();
  myRad        = (aRad1 > aRad2) ? aRad2 : aRad1;
  myRad /= 5;
  if (myRad > 15.)
    myRad = 15.;

  // Calculate a point of circle of radius myRad
  gp_Dir vec(ptat11.XYZ() - myCenter.XYZ());
  gp_Vec vectrans(vec);
  myPnt = myCenter.Translated(vectrans.Multiplied(myRad));

  DsgPrs_ConcentricPresentation::Add(aPresentation, myDrawer, myCenter, myRad, myDir, myPnt);
  if ((myExtShape != 0) && !extCurv.IsNull())
  {
    gp_Pnt pf, pl;
    if (myExtShape == 1)
    {
      if (!isInfinite1)
      {
        pf = ptat11;
        pl = ptat12;
      }
      ComputeProjEdgePresentation(aPresentation, TopoDS::Edge(myFShape), gcirc1, pf, pl);
    }
    else
    {
      if (!isInfinite2)
      {
        pf = ptat21;
        pl = ptat22;
      }
      ComputeProjEdgePresentation(aPresentation, TopoDS::Edge(mySShape), gcirc2, pf, pl);
    }
  }
}

//=================================================================================================

void PrsDim_ConcentricRelation::ComputeSelection(const occ::handle<SelectMgr_Selection>& aSelection,
                                                 const int)
{
  occ::handle<SelectMgr_EntityOwner> anOwner = new SelectMgr_EntityOwner(this, 7);

  // Creation of 2 sensitive circles

  // the greater
  gp_Ax2                                anAx(myCenter, myDir);
  gp_Circ                               aCirc(anAx, myRad);
  occ::handle<Select3D_SensitiveCircle> sensit = new Select3D_SensitiveCircle(anOwner, aCirc);
  aSelection->Add(sensit);

  // the smaller
  aCirc.SetRadius(myRad / 2);
  sensit = new Select3D_SensitiveCircle(anOwner, aCirc);
  aSelection->Add(sensit);

  // Creation of 2 segments sensitive for the cross
  occ::handle<Select3D_SensitiveSegment> seg;
  gp_Pnt                                 otherPnt = myPnt.Mirrored(myCenter);
  seg = new Select3D_SensitiveSegment(anOwner, otherPnt, myPnt);
  aSelection->Add(seg);

  gp_Ax1 RotateAxis(myCenter, myDir);
  gp_Pnt FPnt = myCenter.Rotated(RotateAxis, M_PI_2);
  gp_Pnt SPnt = myCenter.Rotated(RotateAxis, -M_PI_2);
  seg         = new Select3D_SensitiveSegment(anOwner, FPnt, SPnt);
  aSelection->Add(seg);
}
