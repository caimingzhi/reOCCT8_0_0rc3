#pragma once

#include <Standard.hpp>

#include <IGESData_IGESEntity.hpp>
class TCollection_HAsciiString;

class IGESData_NameEntity : public IGESData_IGESEntity
{

public:
  Standard_EXPORT virtual occ::handle<TCollection_HAsciiString> Value() const = 0;

  DEFINE_STANDARD_RTTIEXT(IGESData_NameEntity, IGESData_IGESEntity)
};
