#pragma once

#include <Standard.hpp>

#include <IGESData_IGESEntity.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Integer.hpp>

class IGESGeom_CompositeCurve : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESGeom_CompositeCurve();

  Standard_EXPORT void Init(
    const occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>& allEntities);

  Standard_EXPORT int NbCurves() const;

  Standard_EXPORT occ::handle<IGESData_IGESEntity> Curve(const int Index) const;

  DEFINE_STANDARD_RTTIEXT(IGESGeom_CompositeCurve, IGESData_IGESEntity)

private:
  occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>> theEntities;
};
