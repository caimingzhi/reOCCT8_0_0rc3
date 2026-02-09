#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <IGESData_IGESEntity.hpp>

class IGESGeom_RuledSurface : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESGeom_RuledSurface();

  Standard_EXPORT void Init(const occ::handle<IGESData_IGESEntity>& aCurve,
                            const occ::handle<IGESData_IGESEntity>& anotherCurve,
                            const int                               aDirFlag,
                            const int                               aDevFlag);

  Standard_EXPORT void SetRuledByParameter(const bool mode);

  Standard_EXPORT bool IsRuledByParameter() const;

  Standard_EXPORT occ::handle<IGESData_IGESEntity> FirstCurve() const;

  Standard_EXPORT occ::handle<IGESData_IGESEntity> SecondCurve() const;

  Standard_EXPORT int DirectionFlag() const;

  Standard_EXPORT bool IsDevelopable() const;

  DEFINE_STANDARD_RTTIEXT(IGESGeom_RuledSurface, IGESData_IGESEntity)

private:
  occ::handle<IGESData_IGESEntity> theCurve1;
  occ::handle<IGESData_IGESEntity> theCurve2;
  int                              theDirFlag;
  int                              theDevFlag;
};
