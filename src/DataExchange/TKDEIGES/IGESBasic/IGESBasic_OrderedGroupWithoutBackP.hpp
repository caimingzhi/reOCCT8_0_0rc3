#pragma once


#include <Standard.hpp>

#include <IGESBasic_Group.hpp>

//! defines OrderedGroupWithoutBackP, Type <402> Form <15>
//! in package IGESBasic
//! Allows a collection of a set of entities to be
//! maintained as a single entity, but the group is
//! ordered and there are no back pointers.
//! It inherits from Group
class IGESBasic_OrderedGroupWithoutBackP : public IGESBasic_Group
{

public:
  Standard_EXPORT IGESBasic_OrderedGroupWithoutBackP();

  DEFINE_STANDARD_RTTIEXT(IGESBasic_OrderedGroupWithoutBackP, IGESBasic_Group)
};

