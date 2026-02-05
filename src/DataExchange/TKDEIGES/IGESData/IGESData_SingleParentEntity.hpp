#pragma once

#include <Standard.hpp>

#include <IGESData_IGESEntity.hpp>
#include <Standard_Integer.hpp>

//! a SingleParentEntity is a kind of IGESEntity which can refer
//! to a (Single) Parent, from Associativities list of an Entity
//! a effective SingleParent definition entity must inherit it
class IGESData_SingleParentEntity : public IGESData_IGESEntity
{

public:
  //! Returns the parent designated by the Entity, if only one !
  Standard_EXPORT virtual occ::handle<IGESData_IGESEntity> SingleParent() const = 0;

  //! Returns the count of Entities designated as children
  Standard_EXPORT virtual int NbChildren() const = 0;

  //! Returns a Child given its rank
  Standard_EXPORT virtual occ::handle<IGESData_IGESEntity> Child(const int num) const = 0;

  DEFINE_STANDARD_RTTIEXT(IGESData_SingleParentEntity, IGESData_IGESEntity)
};
