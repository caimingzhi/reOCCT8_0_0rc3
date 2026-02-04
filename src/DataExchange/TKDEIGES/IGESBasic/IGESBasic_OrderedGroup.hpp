#pragma once


#include <Standard.hpp>

#include <IGESBasic_Group.hpp>

//! defines OrderedGroup, Type <402> Form <14>
//! in package IGESBasic
//! this class defines an Ordered Group with back pointers
//! Allows a collection of a set of entities to be
//! maintained as a single entity, but the group is
//! ordered.
//! It inherits from Group
class IGESBasic_OrderedGroup : public IGESBasic_Group
{

public:
  Standard_EXPORT IGESBasic_OrderedGroup();

  DEFINE_STANDARD_RTTIEXT(IGESBasic_OrderedGroup, IGESBasic_Group)
};

