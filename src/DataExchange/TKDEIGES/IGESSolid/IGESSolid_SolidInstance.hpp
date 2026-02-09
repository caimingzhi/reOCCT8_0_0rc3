#pragma once

#include <Standard.hpp>

#include <IGESData_IGESEntity.hpp>

class IGESSolid_SolidInstance : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESSolid_SolidInstance();

  Standard_EXPORT void Init(const occ::handle<IGESData_IGESEntity>& anEntity);

  Standard_EXPORT bool IsBrep() const;

  Standard_EXPORT void SetBrep(const bool brep);

  Standard_EXPORT occ::handle<IGESData_IGESEntity> Entity() const;

  DEFINE_STANDARD_RTTIEXT(IGESSolid_SolidInstance, IGESData_IGESEntity)

private:
  occ::handle<IGESData_IGESEntity> theEntity;
};
