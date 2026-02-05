#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IFSelect_Selection.hpp>
class IFSelect_SelectionIterator;

//! SelectBase works directly from an InterfaceModel : it is the
//! first base for other Selections.
class IFSelect_SelectBase : public IFSelect_Selection
{

public:
  //! Puts in an Iterator the Selections from which "me" depends
  //! This list is empty for all SelectBase type Selections
  Standard_EXPORT void FillIterator(IFSelect_SelectionIterator& iter) const override;

  DEFINE_STANDARD_RTTIEXT(IFSelect_SelectBase, IFSelect_Selection)
};
