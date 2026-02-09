#include <gp_GTrsf.hpp>
#include <gp_XYZ.hpp>
#include <IGESData_TransfEntity.hpp>
#include <IGESDraw_View.hpp>
#include <IGESGeom_Plane.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESDraw_View, IGESData_ViewKindEntity)

IGESDraw_View::IGESDraw_View() = default;

void IGESDraw_View::Init(const int                          aViewNum,
                         const double                       aScale,
                         const occ::handle<IGESGeom_Plane>& aLeftPlane,
                         const occ::handle<IGESGeom_Plane>& aTopPlane,
                         const occ::handle<IGESGeom_Plane>& aRightPlane,
                         const occ::handle<IGESGeom_Plane>& aBottomPlane,
                         const occ::handle<IGESGeom_Plane>& aBackPlane,
                         const occ::handle<IGESGeom_Plane>& aFrontPlane)
{
  theViewNumber  = aViewNum;
  theScaleFactor = aScale;
  theLeftPlane   = aLeftPlane;
  theTopPlane    = aTopPlane;
  theRightPlane  = aRightPlane;
  theBottomPlane = aBottomPlane;
  theBackPlane   = aBackPlane;
  theFrontPlane  = aFrontPlane;
  InitTypeAndForm(410, 0);
}

bool IGESDraw_View::IsSingle() const
{
  return true;
}

int IGESDraw_View::NbViews() const
{
  return 1;
}

occ::handle<IGESData_ViewKindEntity> IGESDraw_View::ViewItem(const int) const
{
  return occ::down_cast<IGESData_ViewKindEntity>(This());
}

int IGESDraw_View::ViewNumber() const
{
  return theViewNumber;
}

double IGESDraw_View::ScaleFactor() const
{
  return theScaleFactor;
}

bool IGESDraw_View::HasLeftPlane() const
{
  return (!theLeftPlane.IsNull());
}

occ::handle<IGESGeom_Plane> IGESDraw_View::LeftPlane() const
{
  return theLeftPlane;
}

bool IGESDraw_View::HasTopPlane() const
{
  return (!theTopPlane.IsNull());
}

occ::handle<IGESGeom_Plane> IGESDraw_View::TopPlane() const
{
  return theTopPlane;
}

bool IGESDraw_View::HasRightPlane() const
{
  return (!theRightPlane.IsNull());
}

occ::handle<IGESGeom_Plane> IGESDraw_View::RightPlane() const
{
  return theRightPlane;
}

bool IGESDraw_View::HasBottomPlane() const
{
  return (!theBottomPlane.IsNull());
}

occ::handle<IGESGeom_Plane> IGESDraw_View::BottomPlane() const
{
  return theBottomPlane;
}

bool IGESDraw_View::HasBackPlane() const
{
  return (!theBackPlane.IsNull());
}

occ::handle<IGESGeom_Plane> IGESDraw_View::BackPlane() const
{
  return theBackPlane;
}

bool IGESDraw_View::HasFrontPlane() const
{
  return (!theFrontPlane.IsNull());
}

occ::handle<IGESGeom_Plane> IGESDraw_View::FrontPlane() const
{
  return theFrontPlane;
}

occ::handle<IGESData_TransfEntity> IGESDraw_View::ViewMatrix() const
{
  return (Transf());
}

gp_XYZ IGESDraw_View::ModelToView(const gp_XYZ& coords) const
{
  gp_XYZ tempCoords = coords;
  Location().Transforms(tempCoords);
  return (tempCoords);
}
