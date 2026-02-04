#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <IFSelect_Selection.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
class IFSelect_Selection;

//! Defines an Iterator on a list of Selections
class IFSelect_SelectionIterator
{
public:
  DEFINE_STANDARD_ALLOC

  //! Creates an empty iterator, ready to be filled
  Standard_EXPORT IFSelect_SelectionIterator();

  //! Creates an iterator from a Selection : it lists the Selections
  //! from which <sel> depends (given by its method FillIterator)
  Standard_EXPORT IFSelect_SelectionIterator(const occ::handle<IFSelect_Selection>& sel);

  //! Adds to an iterator the content of another one
  //! (each selection is present only once in the result)
  Standard_EXPORT void AddFromIter(IFSelect_SelectionIterator& iter);

  //! Adds a Selection to an iterator (if not yet noted)
  Standard_EXPORT void AddItem(const occ::handle<IFSelect_Selection>& sel);

  //! Adds a list of Selections to an iterator (this list comes
  //! from the description of a Selection or a Dispatch, etc...)
  Standard_EXPORT void AddList(const NCollection_Sequence<occ::handle<IFSelect_Selection>>& list);

  //! Returns True if there are more Selections to get
  Standard_EXPORT bool More() const;

  //! Sets iterator to the next item
  Standard_EXPORT void Next();

  //! Returns the current Selection being iterated
  //! Error if count of Selection has been passed
  Standard_EXPORT const occ::handle<IFSelect_Selection>& Value() const;

private:
  int                                                                 thecurr;
  occ::handle<NCollection_HSequence<occ::handle<IFSelect_Selection>>> thelist;
};

