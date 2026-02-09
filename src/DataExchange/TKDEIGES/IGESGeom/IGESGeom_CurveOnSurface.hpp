#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <IGESData_IGESEntity.hpp>

class IGESGeom_CurveOnSurface : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESGeom_CurveOnSurface();

  Standard_EXPORT void Init(const int                               aMode,
                            const occ::handle<IGESData_IGESEntity>& aSurface,
                            const occ::handle<IGESData_IGESEntity>& aCurveUV,
                            const occ::handle<IGESData_IGESEntity>& aCurve3D,
                            const int                               aPreference);

  Standard_EXPORT int CreationMode() const;

  Standard_EXPORT occ::handle<IGESData_IGESEntity> Surface() const;

  Standard_EXPORT occ::handle<IGESData_IGESEntity> CurveUV() const;

  Standard_EXPORT occ::handle<IGESData_IGESEntity> Curve3D() const;

  Standard_EXPORT int PreferenceMode() const;

  DEFINE_STANDARD_RTTIEXT(IGESGeom_CurveOnSurface, IGESData_IGESEntity)

private:
  int                              theCreationMode;
  occ::handle<IGESData_IGESEntity> theSurface;
  occ::handle<IGESData_IGESEntity> theCurveUV;
  occ::handle<IGESData_IGESEntity> theCurve3D;
  int                              thePreferenceMode;
};
