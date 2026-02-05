#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IFSelect_Selection.hpp>
class IFSelect_SelectionIterator;

//! A SelectControl kind Selection works with two input Selections
//! in a dissymmetric way : the Main Input which gives an input
//! list of Entities, to be processed, and the Second Input which
//! gives another list, to be used to filter the main input.
//!
//! e.g. : SelectDiff retains the items of the Main Input which
//! are not in the Control Input (which acts as Diff Input)
//! or a specific selection which retains Entities from the Main
//! Input if and only if they are concerned by an entity from
//! the Control Input (such as Views in IGES, etc...)
//!
//! The way RootResult and Label are produced are at charge of
//! each sub-class
class IFSelect_SelectControl : public IFSelect_Selection
{

public:
  //! Returns the Main Input Selection
  Standard_EXPORT occ::handle<IFSelect_Selection> MainInput() const;

  //! Returns True if a Control Input is defined
  //! Thus, Result can be computed differently if there is a
  //! Control Input or if there is none
  Standard_EXPORT bool HasSecondInput() const;

  //! Returns the Control Input Selection, or a Null Handle
  Standard_EXPORT occ::handle<IFSelect_Selection> SecondInput() const;

  //! Sets a Selection to be the Main Input
  Standard_EXPORT void SetMainInput(const occ::handle<IFSelect_Selection>& sel);

  //! Sets a Selection to be the Control Input
  Standard_EXPORT void SetSecondInput(const occ::handle<IFSelect_Selection>& sel);

  //! Puts in an Iterator the Selections from which "me" depends
  //! That is to say, the list of Input Selections
  Standard_EXPORT void FillIterator(IFSelect_SelectionIterator& iter) const override;

  DEFINE_STANDARD_RTTIEXT(IFSelect_SelectControl, IFSelect_Selection)

private:
  occ::handle<IFSelect_Selection> themain;
  occ::handle<IFSelect_Selection> thesecond;
};
