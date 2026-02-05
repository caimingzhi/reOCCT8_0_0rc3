#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IFSelect_Selection.hpp>
#include <NCollection_Sequence.hpp>
#include <Standard_Integer.hpp>
class IFSelect_SelectionIterator;

//! A SelectCombine type Selection defines algebraic operations
//! between results of several Selections
//! It is a deferred class : sub-classes will have to define
//! precise what operator is to be applied
class IFSelect_SelectCombine : public IFSelect_Selection
{

public:
  //! Returns the count of Input Selections
  Standard_EXPORT int NbInputs() const;

  //! Returns an Input Selection, given its rank in the list
  Standard_EXPORT occ::handle<IFSelect_Selection> Input(const int num) const;

  //! Returns the rank of an input Selection, 0 if not in the list.
  //! Most generally, its value is meaningless, except for testing
  //! the presence of an input Selection :
  //! - == 0  if <sel> is not an input for <me>
  //! - >  0  if <sel> is an input for <me>
  Standard_EXPORT int InputRank(const occ::handle<IFSelect_Selection>& sel) const;

  //! Adds a Selection to the filling list
  //! By default, adds it to the end of the list
  //! A Positive rank less then NbInputs gives an insertion rank
  //! (InsertBefore : the new <atnum>th item of the list is <sel>)
  Standard_EXPORT void Add(const occ::handle<IFSelect_Selection>& sel, const int atnum = 0);

  //! Removes an input Selection.
  //! Returns True if Done, False, if <sel> is not an input for <me>
  Standard_EXPORT bool Remove(const occ::handle<IFSelect_Selection>& sel);

  //! Removes an input Selection, given its rank in the list
  //! Returns True if Done, False if <num> is out of range
  Standard_EXPORT bool Remove(const int num);

  //! Puts in an Iterator the Selections from which "me" depends
  //! That is to say, the list of Input Selections
  Standard_EXPORT void FillIterator(IFSelect_SelectionIterator& iter) const override;

  DEFINE_STANDARD_RTTIEXT(IFSelect_SelectCombine, IFSelect_Selection)

protected:
  //! Defines an empty SelectCombine
  Standard_EXPORT IFSelect_SelectCombine();

  //! Returns always True, because RootResult gives a Unique list
  Standard_EXPORT bool HasUniqueResult() const override;

private:
  NCollection_Sequence<occ::handle<IFSelect_Selection>> thelist;
};
