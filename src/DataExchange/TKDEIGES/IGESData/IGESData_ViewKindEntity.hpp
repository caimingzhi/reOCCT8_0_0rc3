#pragma once

#include <Standard.hpp>

#include <IGESData_IGESEntity.hpp>
#include <Standard_Integer.hpp>

class IGESData_ViewKindEntity : public IGESData_IGESEntity
{

public:
  Standard_EXPORT virtual bool IsSingle() const = 0;

  Standard_EXPORT virtual int NbViews() const = 0;

  Standard_EXPORT virtual occ::handle<IGESData_ViewKindEntity> ViewItem(const int num) const = 0;

  DEFINE_STANDARD_RTTIEXT(IGESData_ViewKindEntity, IGESData_IGESEntity)
};
