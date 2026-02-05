#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IFSelect_SelectBase.hpp>
#include <Standard_Transient.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class Interface_CopyControl;
class IFSelect_Transformer;
class Interface_EntityIterator;
class Interface_Graph;
class TCollection_AsciiString;

//! This type of Selection is intended to describe a direct
//! selection without an explicit criterium, for instance the
//! result of picking viewed entities on a graphic screen
//!
//! It can also be used to provide a list as internal alternate
//! input : this use implies to clear the list once queried
class IFSelect_SelectPointed : public IFSelect_SelectBase
{

public:
  //! Creates a SelectPointed
  Standard_EXPORT IFSelect_SelectPointed();

  //! Clears the list of selected items
  //! Also says the list is unset
  //! All Add* methods and SetList say the list is set
  Standard_EXPORT void Clear();

  //! Tells if the list has been set. Even if empty
  Standard_EXPORT bool IsSet() const;

  //! As SetList but with only one entity
  //! If <ent> is Null, the list is said as being set but is empty
  Standard_EXPORT void SetEntity(const occ::handle<Standard_Transient>& item);

  //! Sets a given list to define the list of selected items
  //! <list> can be empty or null : in this case, the list is said
  //! as being set, but it is empty
  //!
  //! To use it as an alternate input, one shot :
  //! - SetList or SetEntity to define the input list
  //! - RootResult to get it
  //! - then Clear to drop it
  Standard_EXPORT void SetList(
    const occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>>& list);

  //! Adds an item. Returns True if Done, False if <item> is already
  //! in the selected list
  Standard_EXPORT bool Add(const occ::handle<Standard_Transient>& item);

  //! Removes an item. Returns True if Done, False if <item> was not
  //! in the selected list
  Standard_EXPORT bool Remove(const occ::handle<Standard_Transient>& item);

  //! Toggles status of an item : adds it if not pointed or removes
  //! it if already pointed. Returns the new status (Pointed or not)
  Standard_EXPORT bool Toggle(const occ::handle<Standard_Transient>& item);

  //! Adds all the items defined in a list. Returns True if at least
  //! one item has been added, False else
  Standard_EXPORT bool AddList(
    const occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>>& list);

  //! Removes all the items defined in a list. Returns True if at
  //! least one item has been removed, False else
  Standard_EXPORT bool RemoveList(
    const occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>>& list);

  //! Toggles status of all the items defined in a list : adds it if
  //! not pointed or removes it if already pointed.
  Standard_EXPORT bool ToggleList(
    const occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>>& list);

  //! Returns the rank of an item in the selected list, or 0.
  Standard_EXPORT int Rank(const occ::handle<Standard_Transient>& item) const;

  //! Returns the count of selected items
  Standard_EXPORT int NbItems() const;

  //! Returns an item given its rank, or a Null Handle
  Standard_EXPORT occ::handle<Standard_Transient> Item(const int num) const;

  //! Rebuilds the selected list. Any selected entity which has a
  //! bound result is replaced by this result, else it is removed.
  Standard_EXPORT void Update(const occ::handle<Interface_CopyControl>& control);

  //! Rebuilds the selected list, by querying a Transformer
  //! (same principle as from a CopyControl)
  Standard_EXPORT void Update(const occ::handle<IFSelect_Transformer>& trf);

  //! Returns the list of selected items. Only the selected entities
  //! which are present in the graph are given (this result assures
  //! uniqueness).
  Standard_EXPORT Interface_EntityIterator RootResult(const Interface_Graph& G) const override;

  //! Returns a text which identifies the type of selection made.
  //! It is "Pointed Entities"
  Standard_EXPORT TCollection_AsciiString Label() const override;

  DEFINE_STANDARD_RTTIEXT(IFSelect_SelectPointed, IFSelect_SelectBase)

private:
  bool                                                  theset;
  NCollection_Sequence<occ::handle<Standard_Transient>> theitems;
};
