#include <gp_GTrsf.hpp>
#include <gp_Pnt.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Vec.hpp>
#include <gp_XY.hpp>
#include <gp_XYZ.hpp>
#include <IGESData_TransfEntity.hpp>
#include <IGESDraw_PerspectiveView.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESDraw_PerspectiveView, IGESData_ViewKindEntity)

IGESDraw_PerspectiveView::IGESDraw_PerspectiveView() = default;

void IGESDraw_PerspectiveView::Init(const int     aViewNumber,
                                    const double  aScaleFactor,
                                    const gp_XYZ& aViewNormalVector,
                                    const gp_XYZ& aViewReferencePoint,
                                    const gp_XYZ& aCenterOfProjection,
                                    const gp_XYZ& aViewUpVector,
                                    const double  aViewPlaneDistance,
                                    const gp_XY&  aTopLeft,
                                    const gp_XY&  aBottomRight,
                                    const int     aDepthClip,
                                    const double  aBackPlaneDistance,
                                    const double  aFrontPlaneDistance)
{
  theViewNumber         = aViewNumber;
  theScaleFactor        = aScaleFactor;
  theViewNormalVector   = aViewNormalVector;
  theViewReferencePoint = aViewReferencePoint;
  theCenterOfProjection = aCenterOfProjection;
  theViewUpVector       = aViewUpVector;
  theViewPlaneDistance  = aViewPlaneDistance;
  theTopLeft            = aTopLeft;
  theBottomRight        = aBottomRight;
  theDepthClip          = aDepthClip;
  theBackPlaneDistance  = aBackPlaneDistance;
  theFrontPlaneDistance = aFrontPlaneDistance;
  InitTypeAndForm(410, 1);
}

bool IGESDraw_PerspectiveView::IsSingle() const
{
  return true;
}

int IGESDraw_PerspectiveView::NbViews() const
{
  return 1;
}

occ::handle<IGESData_ViewKindEntity> IGESDraw_PerspectiveView::ViewItem(const int) const
{
  return occ::down_cast<IGESData_ViewKindEntity>(This());
}

int IGESDraw_PerspectiveView::ViewNumber() const
{
  return theViewNumber;
}

double IGESDraw_PerspectiveView::ScaleFactor() const
{
  return theScaleFactor;
}

gp_Vec IGESDraw_PerspectiveView::ViewNormalVector() const
{
  gp_Vec tempRes(theViewNormalVector);
  return tempRes;
}

gp_Pnt IGESDraw_PerspectiveView::ViewReferencePoint() const
{
  gp_Pnt tempRes(theViewReferencePoint);
  return tempRes;
}

gp_Pnt IGESDraw_PerspectiveView::CenterOfProjection() const
{
  gp_Pnt tempRes(theCenterOfProjection);
  return tempRes;
}

gp_Vec IGESDraw_PerspectiveView::ViewUpVector() const
{
  gp_Vec tempRes(theViewUpVector);
  return tempRes;
}

double IGESDraw_PerspectiveView::ViewPlaneDistance() const
{
  return theViewPlaneDistance;
}

gp_Pnt2d IGESDraw_PerspectiveView::TopLeft() const
{
  gp_Pnt2d tempRes(theTopLeft);
  return tempRes;
}

gp_Pnt2d IGESDraw_PerspectiveView::BottomRight() const
{
  gp_Pnt2d tempRes(theBottomRight);
  return tempRes;
}

int IGESDraw_PerspectiveView::DepthClip() const
{
  return theDepthClip;
}

double IGESDraw_PerspectiveView::BackPlaneDistance() const
{
  return theBackPlaneDistance;
}

double IGESDraw_PerspectiveView::FrontPlaneDistance() const
{
  return theFrontPlaneDistance;
}

occ::handle<IGESData_TransfEntity> IGESDraw_PerspectiveView::ViewMatrix() const
{
  return (Transf());
}

gp_XYZ IGESDraw_PerspectiveView::ModelToView(const gp_XYZ& coords) const
{
  gp_XYZ tempCoords = coords;
  Location().Transforms(tempCoords);
  return (tempCoords);
}
