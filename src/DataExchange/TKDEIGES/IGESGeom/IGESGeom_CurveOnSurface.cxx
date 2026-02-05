#include <IGESGeom_CurveOnSurface.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESGeom_CurveOnSurface, IGESData_IGESEntity)

IGESGeom_CurveOnSurface::IGESGeom_CurveOnSurface() = default;

void IGESGeom_CurveOnSurface::Init(const int                               aMode,
                                   const occ::handle<IGESData_IGESEntity>& aSurface,
                                   const occ::handle<IGESData_IGESEntity>& aCurveUV,
                                   const occ::handle<IGESData_IGESEntity>& aCurve3D,
                                   const int                               aPreference)
{
  theCreationMode   = aMode;
  theSurface        = aSurface;
  theCurveUV        = aCurveUV;
  theCurve3D        = aCurve3D;
  thePreferenceMode = aPreference;
  InitTypeAndForm(142, 0);
}

int IGESGeom_CurveOnSurface::CreationMode() const
{
  return theCreationMode;
}

occ::handle<IGESData_IGESEntity> IGESGeom_CurveOnSurface::Surface() const
{
  return theSurface;
}

occ::handle<IGESData_IGESEntity> IGESGeom_CurveOnSurface::CurveUV() const
{
  return theCurveUV;
}

occ::handle<IGESData_IGESEntity> IGESGeom_CurveOnSurface::Curve3D() const
{
  return theCurve3D;
}

int IGESGeom_CurveOnSurface::PreferenceMode() const
{
  return thePreferenceMode;
}
