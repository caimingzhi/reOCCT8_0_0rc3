#pragma once

#include <Standard.hpp>

#include <IGESData_IGESEntity.hpp>

//! defines required type for LabelDisplay in directory part
//! an effective LabelDisplay entity must inherits it
class IGESData_LabelDisplayEntity : public IGESData_IGESEntity
{

public:
  DEFINE_STANDARD_RTTIEXT(IGESData_LabelDisplayEntity, IGESData_IGESEntity)
};
