#pragma once

#include <Standard.hpp>

#include <IGESBasic_Group.hpp>

class IGESBasic_OrderedGroup : public IGESBasic_Group
{

public:
  Standard_EXPORT IGESBasic_OrderedGroup();

  DEFINE_STANDARD_RTTIEXT(IGESBasic_OrderedGroup, IGESBasic_Group)
};
