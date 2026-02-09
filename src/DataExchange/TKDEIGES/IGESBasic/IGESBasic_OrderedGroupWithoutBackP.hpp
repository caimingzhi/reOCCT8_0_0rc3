#pragma once

#include <Standard.hpp>

#include <IGESBasic_Group.hpp>

class IGESBasic_OrderedGroupWithoutBackP : public IGESBasic_Group
{

public:
  Standard_EXPORT IGESBasic_OrderedGroupWithoutBackP();

  DEFINE_STANDARD_RTTIEXT(IGESBasic_OrderedGroupWithoutBackP, IGESBasic_Group)
};
