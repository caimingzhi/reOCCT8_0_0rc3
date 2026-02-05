#pragma once

#include <Standard.hpp>

#include <IGESData_IGESEntity.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;

//! defines Group, Type <402> Form <1>
//! in package IGESBasic
//! The Group Associativity allows a collection of a set
//! of entities to be maintained as a single, logical
//! entity
//!
//! Group, OrderedGroup, GroupWithoutBackP, OrderedGroupWithoutBackP
//! share the same definition (class Group), form number changes
//!
//! non Ordered, non WithoutBackP : form  1
//! non Ordered,     WithoutBackP : form  7
//! Ordered, non WithoutBackP : form 14
//! Ordered,     WithoutBackP : form 15
class IGESBasic_Group : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESBasic_Group();

  //! Creates a Group with a predefined count of items
  //! (which all start as null)
  Standard_EXPORT IGESBasic_Group(const int nb);

  //! This method is used to set the fields of the class Group
  //! - allEntities : Used to store pointers to members of
  //! the Group.
  Standard_EXPORT void Init(
    const occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>& allEntities);

  //! Sets a Group to be, or not to be Ordered (according mode)
  Standard_EXPORT void SetOrdered(const bool mode);

  //! Sets a Group to be, or not to be WithoutBackP
  Standard_EXPORT void SetWithoutBackP(const bool mode);

  //! Returns True if <me> is Ordered
  Standard_EXPORT bool IsOrdered() const;

  //! Returns True if <me> is WithoutBackP
  Standard_EXPORT bool IsWithoutBackP() const;

  //! Enforce a new value for the type and form
  Standard_EXPORT void SetUser(const int type, const int form);

  //! Changes the count of item
  //! If greater, new items are null
  //! If lower, old items are lost
  Standard_EXPORT void SetNb(const int nb);

  //! returns the number of IGESEntities in the Group
  Standard_EXPORT int NbEntities() const;

  //! returns the specific entity from the Group
  Standard_EXPORT occ::handle<IGESData_IGESEntity> Entity(const int Index) const;

  //! returns the specific entity from the Group
  Standard_EXPORT occ::handle<Standard_Transient> Value(const int Index) const;

  //! Sets a new value for item <Index>
  Standard_EXPORT void SetValue(const int Index, const occ::handle<IGESData_IGESEntity>& ent);

  DEFINE_STANDARD_RTTIEXT(IGESBasic_Group, IGESData_IGESEntity)

private:
  occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>> theEntities;
};
