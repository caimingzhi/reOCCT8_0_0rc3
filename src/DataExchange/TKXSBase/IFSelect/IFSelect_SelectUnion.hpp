#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IFSelect_SelectCombine.hpp>
class Interface_EntityIterator;
class Interface_Graph;
class TCollection_AsciiString;

//! A SelectUnion cumulates the Entities issued from several other
//! Selections (union of results : "OR" operator)
class IFSelect_SelectUnion : public IFSelect_SelectCombine
{

public:
  //! Creates an empty SelectUnion
  Standard_EXPORT IFSelect_SelectUnion();

  //! Returns the list of selected Entities, which is the addition
  //! result from all input selections. Uniqueness is guaranteed.
  Standard_EXPORT Interface_EntityIterator RootResult(const Interface_Graph& G) const override;

  //! Returns a text defining the criterium : "Union (OR)"
  Standard_EXPORT TCollection_AsciiString Label() const override;

  DEFINE_STANDARD_RTTIEXT(IFSelect_SelectUnion, IFSelect_SelectCombine)
};
