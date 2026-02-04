#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IFSelect_SelectAnyList.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class Interface_EntityIterator;

//! A SelectInList kind Selection selects a List of an Entity,
//! which is composed of single Entities
//! To know the list on which to work, SelectInList has two
//! deferred methods : NbItems (inherited from SelectAnyList) and
//! ListedEntity (which gives an item as an Entity) which must be
//! defined to get a List in an Entity of the required Type (and
//! consider that list is empty if Entity has not required Type)
//!
//! As for SelectAnyList, if a type of Entity defines several
//! lists, a given sub-class of SelectInList is attached on one
class IFSelect_SelectInList : public IFSelect_SelectAnyList
{

public:
  //! Returns an Entity, given its rank in the list
  Standard_EXPORT virtual occ::handle<Standard_Transient> ListedEntity(
    const int                              num,
    const occ::handle<Standard_Transient>& ent) const = 0;

  //! Puts into the result, the sub-entities of the list, from n1 to
  //! n2 included. Remark that adequation with Entity's type and
  //! length of list has already been made at this stage
  //! Called by RootResult; calls ListedEntity (see below)
  Standard_EXPORT void FillResult(const int                              n1,
                                  const int                              n2,
                                  const occ::handle<Standard_Transient>& ent,
                                  Interface_EntityIterator&              result) const override;

  DEFINE_STANDARD_RTTIEXT(IFSelect_SelectInList, IFSelect_SelectAnyList)
};

