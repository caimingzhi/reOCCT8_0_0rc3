#pragma once

#include <Standard.hpp>

#include <IGESData_IGESEntity.hpp>

//! defines required type for Color in directory part
//! an effective Color entity must inherits it
class IGESData_ColorEntity : public IGESData_IGESEntity
{

public:
  DEFINE_STANDARD_RTTIEXT(IGESData_ColorEntity, IGESData_IGESEntity)
};
