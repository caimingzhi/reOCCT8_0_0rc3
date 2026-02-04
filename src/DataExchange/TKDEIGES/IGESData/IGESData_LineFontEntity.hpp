#pragma once


#include <Standard.hpp>

#include <IGESData_IGESEntity.hpp>

//! defines required type for LineFont in directory part
//! an effective LineFont entity must inherits it
class IGESData_LineFontEntity : public IGESData_IGESEntity
{

public:
  DEFINE_STANDARD_RTTIEXT(IGESData_LineFontEntity, IGESData_IGESEntity)
};

