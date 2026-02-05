#include <PrsDim_RadiusDimension.hpp>

#include <PrsDim.hpp>
#include <BRepLib_MakeEdge.hpp>
#include <ElCLib.hpp>
#include <gce_MakeDir.hpp>

IMPLEMENT_STANDARD_RTTIEXT(PrsDim_RadiusDimension, PrsDim_Dimension)

namespace
{
  static const char16_t THE_RADIUS_SYMBOL('R');
}

//=================================================================================================

PrsDim_RadiusDimension::PrsDim_RadiusDimension(const gp_Circ& theCircle)
    : PrsDim_Dimension(PrsDim_KOD_RADIUS)
{
  SetMeasuredGeometry(theCircle);
  SetSpecialSymbol(THE_RADIUS_SYMBOL);
  SetDisplaySpecialSymbol(PrsDim_DisplaySpecialSymbol_Before);
  SetFlyout(0.0);
}

//=================================================================================================

PrsDim_RadiusDimension::PrsDim_RadiusDimension(const gp_Circ& theCircle,
                                               const gp_Pnt&  theAttachPoint)
    : PrsDim_Dimension(PrsDim_KOD_RADIUS)
{
  SetMeasuredGeometry(theCircle, theAttachPoint);
  SetSpecialSymbol(THE_RADIUS_SYMBOL);
  SetDisplaySpecialSymbol(PrsDim_DisplaySpecialSymbol_Before);
  SetFlyout(0.0);
}

//=================================================================================================

PrsDim_RadiusDimension::PrsDim_RadiusDimension(const TopoDS_Shape& theShape)
    : PrsDim_Dimension(PrsDim_KOD_RADIUS)
{
  SetMeasuredGeometry(theShape);
  SetSpecialSymbol(THE_RADIUS_SYMBOL);
  SetDisplaySpecialSymbol(PrsDim_DisplaySpecialSymbol_Before);
  SetFlyout(0.0);
}

//=================================================================================================

void PrsDim_RadiusDimension::SetMeasuredGeometry(const gp_Circ& theCircle,
                                                 const gp_Pnt&  theAnchorPoint,
                                                 const bool     theHasAnchor)
{
  myCircle          = theCircle;
  myGeometryType    = GeometryType_Edge;
  myShape           = BRepLib_MakeEdge(theCircle);
  myAnchorPoint     = theHasAnchor ? theAnchorPoint : ElCLib::Value(0, myCircle);
  myIsGeometryValid = IsValidCircle(myCircle) && IsValidAnchor(myCircle, myAnchorPoint);

  if (myIsGeometryValid)
  {
    ComputePlane();
  }

  SetToUpdate();
}

//=================================================================================================

void PrsDim_RadiusDimension::SetMeasuredGeometry(const TopoDS_Shape& theShape,
                                                 const gp_Pnt&       theAnchorPoint,
                                                 const bool          theHasAnchor)
{
  bool isClosed  = false;
  myShape        = theShape;
  myGeometryType = GeometryType_UndefShapes;
  myIsGeometryValid =
    InitCircularDimension(theShape, myCircle, myAnchorPoint, isClosed) && IsValidCircle(myCircle);
  if (theHasAnchor)
  {
    myAnchorPoint     = theAnchorPoint;
    myIsGeometryValid = myIsGeometryValid && IsValidAnchor(myCircle, myAnchorPoint);
  }

  if (myIsGeometryValid)
  {
    ComputePlane();
  }

  SetToUpdate();
}

//=================================================================================================

bool PrsDim_RadiusDimension::CheckPlane(const gp_Pln& thePlane) const
{
  // Check if anchor point and circle center point belong to plane.
  return thePlane.Contains(myAnchorPoint, Precision::Confusion())
         || thePlane.Contains(myCircle.Location(), Precision::Confusion());
}

//=================================================================================================

void PrsDim_RadiusDimension::ComputePlane()
{
  if (!myIsGeometryValid)
  {
    return;
  }

  gp_Dir aDimensionX = gce_MakeDir(myAnchorPoint, myCircle.Location());

  myPlane = gp_Pln(gp_Ax3(myCircle.Location(), myCircle.Axis().Direction(), aDimensionX));
}

//=================================================================================================

const TCollection_AsciiString& PrsDim_RadiusDimension::GetModelUnits() const
{
  return myDrawer->DimLengthModelUnits();
}

//=================================================================================================

const TCollection_AsciiString& PrsDim_RadiusDimension::GetDisplayUnits() const
{
  return myDrawer->DimLengthDisplayUnits();
}

//=================================================================================================

void PrsDim_RadiusDimension::SetModelUnits(const TCollection_AsciiString& theUnits)
{
  myDrawer->SetDimLengthModelUnits(theUnits);
}

//=================================================================================================

void PrsDim_RadiusDimension::SetDisplayUnits(const TCollection_AsciiString& theUnits)
{
  myDrawer->SetDimLengthDisplayUnits(theUnits);
}

//=================================================================================================

double PrsDim_RadiusDimension::ComputeValue() const
{
  if (!IsValid())
  {
    return 0.0;
  }

  return myCircle.Radius();
}

//=================================================================================================

void PrsDim_RadiusDimension::Compute(const occ::handle<PrsMgr_PresentationManager>&,
                                     const occ::handle<Prs3d_Presentation>& thePresentation,
                                     const int                              theMode)
{
  mySelectionGeom.Clear(theMode);
  if (!IsValid())
  {
    return;
  }

  DrawLinearDimension(thePresentation, theMode, myAnchorPoint, myCircle.Location(), true);
}

//=================================================================================================

bool PrsDim_RadiusDimension::IsValidCircle(const gp_Circ& theCircle) const
{
  return theCircle.Radius() > Precision::Confusion();
}

//=================================================================================================

bool PrsDim_RadiusDimension::IsValidAnchor(const gp_Circ& theCircle, const gp_Pnt& theAnchor) const
{
  gp_Pln aCirclePlane(theCircle.Location(), theCircle.Axis().Direction());
  double anAnchorDist = theAnchor.Distance(theCircle.Location());

  return anAnchorDist > Precision::Confusion()
         && aCirclePlane.Contains(theAnchor, Precision::Confusion());
}

//=================================================================================================

gp_Pnt PrsDim_RadiusDimension::GetTextPosition() const
{
  if (IsTextPositionCustom())
  {
    return myFixedTextPosition;
  }

  // Counts text position according to the dimension parameters
  return GetTextPositionForLinear(myAnchorPoint, myCircle.Location(), true);
}

//=================================================================================================

void PrsDim_RadiusDimension::SetTextPosition(const gp_Pnt& theTextPos)
{
  if (!myIsGeometryValid)
  {
    return;
  }

  myIsTextPositionFixed = true;
  myFixedTextPosition   = theTextPos;

  SetToUpdate();
}
