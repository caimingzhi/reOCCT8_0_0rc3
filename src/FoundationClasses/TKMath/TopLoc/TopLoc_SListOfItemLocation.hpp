#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Macro.hpp>
class TopLoc_SListNodeOfItemLocation;
class TopLoc_ItemLocation;

//! An SListOfItemLocation is a LISP like list of Items.
//! An SListOfItemLocation is:
//! . Empty.
//! . Or it has a Value and a Tail which is an other SListOfItemLocation.
//!
//! The Tail of an empty list is an empty list.
//! SListOfItemLocation are shared. It means that they can be
//! modified through other lists.
//! SListOfItemLocation may be used as Iterators. They have Next,
//! More, and value methods. To iterate on the content
//! of the list S just do.
//!
//! SListOfItemLocation Iterator;
//! for (Iterator = S; Iterator.More(); Iterator.Next())
//! X = Iterator.Value();
class TopLoc_SListOfItemLocation
{
public:
  DEFINE_STANDARD_ALLOC

  //! Creates an empty List.
  TopLoc_SListOfItemLocation() = default;

  //! Creates a List with <anItem> as value and <aTail> as tail.
  Standard_EXPORT TopLoc_SListOfItemLocation(const TopLoc_ItemLocation&        anItem,
                                             const TopLoc_SListOfItemLocation& aTail);

  //! Creates a list from an other one. The lists are shared.
  TopLoc_SListOfItemLocation(const TopLoc_SListOfItemLocation& Other)

    = default;

  //! Sets a list from an other one. The lists are
  //! shared. The list itself is returned.
  Standard_EXPORT TopLoc_SListOfItemLocation& Assign(const TopLoc_SListOfItemLocation& Other);

  //! Assignment
  TopLoc_SListOfItemLocation& operator=(const TopLoc_SListOfItemLocation& Other)
  {
    return Assign(Other);
  }

  //! Move constructor
  TopLoc_SListOfItemLocation(TopLoc_SListOfItemLocation&& theOther) noexcept
      : myNode(std::move(theOther.myNode))
  {
  }

  //! Move operator
  TopLoc_SListOfItemLocation& operator=(TopLoc_SListOfItemLocation&& theOther) noexcept
  {
    myNode = std::move(theOther.myNode);
    return *this;
  }

  //! Return true if this list is empty
  bool IsEmpty() const { return myNode.IsNull(); }

  //! Sets the list to be empty.
  void Clear() { myNode.Nullify(); }

  //! Destructor
  ~TopLoc_SListOfItemLocation() { Clear(); }

  //! Returns the current value of the list. An error is
  //! raised if the list is empty.
  Standard_EXPORT const TopLoc_ItemLocation& Value() const;

  //! Returns the current tail of the list. On an empty
  //! list the tail is the list itself.
  Standard_EXPORT const TopLoc_SListOfItemLocation& Tail() const;

  //! Replaces the list by a list with <anItem> as Value
  //! and the list <me> as tail.
  void Construct(const TopLoc_ItemLocation& anItem)
  {
    Assign(TopLoc_SListOfItemLocation(anItem, *this));
  }

  //! Replaces the list <me> by its tail.
  void ToTail() { Assign(Tail()); }

  //! Returns True if the iterator has a current value.
  //! This is !IsEmpty()
  bool More() const { return !IsEmpty(); }

  //! Moves the iterator to the next object in the list.
  //! If the iterator is empty it will stay empty. This is ToTail()
  void Next() { ToTail(); }

private:
  occ::handle<TopLoc_SListNodeOfItemLocation> myNode;
};
