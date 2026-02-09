#pragma once

#include <Standard.hpp>

#include <IGESData_IGESEntity.hpp>
#include <Standard_Integer.hpp>

class IGESData_SingleParentEntity : public IGESData_IGESEntity
{

public:
  Standard_EXPORT virtual occ::handle<IGESData_IGESEntity> SingleParent() const = 0;

  Standard_EXPORT virtual int NbChildren() const = 0;

  Standard_EXPORT virtual occ::handle<IGESData_IGESEntity> Child(const int num) const = 0;

  DEFINE_STANDARD_RTTIEXT(IGESData_SingleParentEntity, IGESData_IGESEntity)
};
