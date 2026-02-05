#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <IGESData_IGESEntity.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <IGESData_SingleParentEntity.hpp>
class IGESData_IGESEntity;

//! defines SingleParent, Type <402> Form <9>
//! in package IGESBasic
//! It defines a logical structure of one independent
//! (parent) entity and one or more subordinate (children)
//! entities
class IGESBasic_SingleParent : public IGESData_SingleParentEntity
{

public:
  Standard_EXPORT IGESBasic_SingleParent();

  //! This method is used to set the fields of the class
  //! SingleParent
  //! - nbParentEntities : Indicates number of Parents, always = 1
  //! - aParentEntity    : Used to hold the Parent Entity
  //! - allChildren      : Used to hold the children
  Standard_EXPORT void Init(
    const int                                                                 nbParentEntities,
    const occ::handle<IGESData_IGESEntity>&                                   aParentEntity,
    const occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>& allChildren);

  //! returns the number of Parent Entities, which should be 1
  Standard_EXPORT int NbParentEntities() const;

  //! Returns the Parent Entity (inherited method)
  Standard_EXPORT occ::handle<IGESData_IGESEntity> SingleParent() const override;

  //! returns the number of children of the Parent
  Standard_EXPORT int NbChildren() const override;

  //! returns the specific child as indicated by Index
  //! raises exception if Index <= 0 or Index > NbChildren()
  Standard_EXPORT occ::handle<IGESData_IGESEntity> Child(const int Index) const override;

  DEFINE_STANDARD_RTTIEXT(IGESBasic_SingleParent, IGESData_SingleParentEntity)

private:
  int                                                                theNbParentEntities;
  occ::handle<IGESData_IGESEntity>                                   theParentEntity;
  occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>> theChildren;
};
