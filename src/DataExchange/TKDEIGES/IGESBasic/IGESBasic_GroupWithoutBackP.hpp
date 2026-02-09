#pragma once

#include <Standard.hpp>

#include <IGESBasic_Group.hpp>

class IGESBasic_GroupWithoutBackP : public IGESBasic_Group
{

public:
  Standard_EXPORT IGESBasic_GroupWithoutBackP();

  DEFINE_STANDARD_RTTIEXT(IGESBasic_GroupWithoutBackP, IGESBasic_Group)
};
