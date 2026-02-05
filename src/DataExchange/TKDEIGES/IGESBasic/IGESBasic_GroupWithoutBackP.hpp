#pragma once

#include <Standard.hpp>

#include <IGESBasic_Group.hpp>

//! defines GroupWithoutBackP, Type <402> Form <7>
//! in package IGESBasic
//! this class defines a Group without back pointers
//!
//! It inherits from Group
class IGESBasic_GroupWithoutBackP : public IGESBasic_Group
{

public:
  Standard_EXPORT IGESBasic_GroupWithoutBackP();

  DEFINE_STANDARD_RTTIEXT(IGESBasic_GroupWithoutBackP, IGESBasic_Group)
};
