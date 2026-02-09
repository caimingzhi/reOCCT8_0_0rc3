#include <PrsDim_DiameterDimension.hpp>

#include <PrsDim.hpp>
#include <BRepLib_MakeEdge.hpp>
#include <ElCLib.hpp>
#include <GeomAPI_IntCS.hpp>
#include <Geom_Circle.hpp>
#include <Geom_Plane.hpp>
#include <gce_MakeDir.hpp>

IMPLEMENT_STANDARD_RTTIEXT(PrsDim_DiameterDimension, PrsDim_Dimension)

namespace
{
  static const char16_t THE_DIAMETER_SYMBOL(0x00D8);
}

PrsDim_DiameterDimension::PrsDim_DiameterDimension(const gp_Circ& theCircle)
    : PrsDim_Dimension(PrsDim_KOD_DIAMETER)
{
  SetMeasuredGeometry(theCircle);
  SetSpecialSymbol(THE_DIAMETER_SYMBOL);
  SetDisplaySpecialSymbol(PrsDim_DisplaySpecialSymbol_Before);
  SetFlyout(0.0);
}

PrsDim_DiameterDimension::PrsDim_DiameterDimension(const gp_Circ& theCircle, const gp_Pln& thePlane)
    : PrsDim_Dimension(PrsDim_KOD_DIAMETER)
{
  SetCustomPlane(thePlane);
  SetMeasuredGeometry(theCircle);
  SetSpecialSymbol(THE_DIAMETER_SYMBOL);
  SetDisplaySpecialSymbol(PrsDim_DisplaySpecialSymbol_Before);
  SetFlyout(0.0);
}

PrsDim_DiameterDimension::PrsDim_DiameterDimension(const TopoDS_Shape& theShape)
    : PrsDim_Dimension(PrsDim_KOD_DIAMETER)
{
  SetMeasuredGeometry(theShape);
  SetSpecialSymbol(THE_DIAMETER_SYMBOL);
  SetDisplaySpecialSymbol(PrsDim_DisplaySpecialSymbol_Before);
  SetFlyout(0.0);
}

PrsDim_DiameterDimension::PrsDim_DiameterDimension(const TopoDS_Shape& theShape,
                                                   const gp_Pln&       thePlane)
    : PrsDim_Dimension(PrsDim_KOD_DIAMETER)
{
  SetCustomPlane(thePlane);
  SetMeasuredGeometry(theShape);
  SetSpecialSymbol(THE_DIAMETER_SYMBOL);
  SetDisplaySpecialSymbol(PrsDim_DisplaySpecialSymbol_Before);
  SetFlyout(0.0);
}

gp_Pnt PrsDim_DiameterDimension::AnchorPoint()
{
  if (!IsValid())
  {
    return gp::Origin();
  }

  return myAnchorPoint;
}

void PrsDim_DiameterDimension::SetMeasuredGeometry(const gp_Circ& theCircle)
{
  myCircle          = theCircle;
  myGeometryType    = GeometryType_Edge;
  myShape           = BRepLib_MakeEdge(theCircle);
  myAnchorPoint     = gp::Origin();
  myIsGeometryValid = IsValidCircle(myCircle);

  if (myIsGeometryValid && myIsPlaneCustom)
  {
    ComputeAnchorPoint();
  }
  else if (!myIsPlaneCustom)
  {
    ComputePlane();
    myAnchorPoint = ElCLib::Value(0.0, myCircle);
  }

  SetToUpdate();
}

void PrsDim_DiameterDimension::SetMeasuredGeometry(const TopoDS_Shape& theShape)
{
  gp_Pnt aDummyPnt(gp::Origin());
  bool   isClosed = false;

  myGeometryType    = GeometryType_UndefShapes;
  myShape           = theShape;
  myAnchorPoint     = gp::Origin();
  myIsGeometryValid = InitCircularDimension(theShape, myCircle, aDummyPnt, isClosed)
                      && IsValidCircle(myCircle) && isClosed;

  if (myIsGeometryValid && myIsPlaneCustom)
  {
    ComputeAnchorPoint();
  }
  else if (!myIsPlaneCustom)
  {
    ComputePlane();
    myAnchorPoint = ElCLib::Value(0.0, myCircle);
  }

  SetToUpdate();
}

bool PrsDim_DiameterDimension::CheckPlane(const gp_Pln& thePlane) const
{

  return thePlane.Contains(myCircle.Location(), Precision::Confusion());
}

void PrsDim_DiameterDimension::ComputePlane()
{
  if (!myIsGeometryValid)
  {
    return;
  }

  myPlane = gp_Pln(gp_Ax3(myCircle.Position()));
}

void PrsDim_DiameterDimension::ComputeAnchorPoint()
{

  occ::handle<Geom_Circle> aCircle = new Geom_Circle(myCircle);
  occ::handle<Geom_Plane>  aPlane  = new Geom_Plane(myPlane);
  GeomAPI_IntCS            anIntersector(aCircle, aPlane);
  if (!anIntersector.IsDone())
  {
    myIsGeometryValid = false;
    return;
  }

  if (anIntersector.NbPoints() != 2)
  {
    myAnchorPoint     = ElCLib::Value(0.0, myCircle);
    myIsGeometryValid = true;
    return;
  }

  gp_Pnt aFirstPoint  = anIntersector.Point(1);
  gp_Pnt aSecondPoint = anIntersector.Point(2);

  gp_Dir aFirstDir = gce_MakeDir(aFirstPoint, myCircle.Location());
  gp_Dir aDir      = myPlane.Axis().Direction() ^ aFirstDir;
  myAnchorPoint =
    (gp_Vec(aDir) * gp_Vec(myCircle.Position().Direction()) > 0.0) ? aFirstPoint : aSecondPoint;
}

const TCollection_AsciiString& PrsDim_DiameterDimension::GetModelUnits() const
{
  return myDrawer->DimLengthModelUnits();
}

const TCollection_AsciiString& PrsDim_DiameterDimension::GetDisplayUnits() const
{
  return myDrawer->DimLengthDisplayUnits();
}

void PrsDim_DiameterDimension::SetModelUnits(const TCollection_AsciiString& theUnits)
{
  myDrawer->SetDimLengthModelUnits(theUnits);
}

void PrsDim_DiameterDimension::SetDisplayUnits(const TCollection_AsciiString& theUnits)
{
  myDrawer->SetDimLengthDisplayUnits(theUnits);
}

double PrsDim_DiameterDimension::ComputeValue() const
{
  if (!IsValid())
  {
    return 0.0;
  }

  return myCircle.Radius() * 2.0;
}

void PrsDim_DiameterDimension::Compute(const occ::handle<PrsMgr_PresentationManager>&,
                                       const occ::handle<Prs3d_Presentation>& thePresentation,
                                       const int                              theMode)
{
  mySelectionGeom.Clear(theMode);

  if (!IsValid())
  {
    return;
  }

  gp_Pnt aFirstPnt(gp::Origin());
  gp_Pnt aSecondPnt(gp::Origin());
  ComputeSidePoints(myCircle, aFirstPnt, aSecondPnt);

  DrawLinearDimension(thePresentation, theMode, aFirstPnt, aSecondPnt);
}

void PrsDim_DiameterDimension::ComputeFlyoutSelection(
  const occ::handle<SelectMgr_Selection>&   theSelection,
  const occ::handle<SelectMgr_EntityOwner>& theEntityOwner)
{
  if (!IsValid())
  {
    return;
  }

  gp_Pnt aFirstPnt(gp::Origin());
  gp_Pnt aSecondPnt(gp::Origin());
  ComputeSidePoints(myCircle, aFirstPnt, aSecondPnt);

  ComputeLinearFlyouts(theSelection, theEntityOwner, aFirstPnt, aSecondPnt);
}

void PrsDim_DiameterDimension::ComputeSidePoints(const gp_Circ& theCircle,
                                                 gp_Pnt&        theFirstPnt,
                                                 gp_Pnt&        theSecondPnt)
{
  theFirstPnt = AnchorPoint();

  gp_Vec aRadiusVector(theCircle.Location(), theFirstPnt);
  theSecondPnt = theCircle.Location().Translated(-aRadiusVector);
}

bool PrsDim_DiameterDimension::IsValidCircle(const gp_Circ& theCircle) const
{
  return (theCircle.Radius() * 2.0) > Precision::Confusion();
}

bool PrsDim_DiameterDimension::IsValidAnchor(const gp_Circ& theCircle,
                                             const gp_Pnt&  theAnchor) const
{
  gp_Pln aCirclePlane(theCircle.Location(), theCircle.Axis().Direction());
  double anAnchorDist = theAnchor.Distance(theCircle.Location());
  double aRadius      = myCircle.Radius();

  return std::abs(anAnchorDist - aRadius) > Precision::Confusion()
         && aCirclePlane.Contains(theAnchor, Precision::Confusion());
}

gp_Pnt PrsDim_DiameterDimension::GetTextPosition() const
{
  if (IsTextPositionCustom())
  {
    return myFixedTextPosition;
  }

  return GetTextPositionForLinear(myAnchorPoint, myCircle.Location());
}

void PrsDim_DiameterDimension::SetTextPosition(const gp_Pnt& theTextPos)
{
  if (!IsValid())
  {
    return;
  }

  myIsTextPositionFixed = true;
  myFixedTextPosition   = theTextPos;

  SetToUpdate();
}
