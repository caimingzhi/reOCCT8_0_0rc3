#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IFSelect_SelectCombine.hpp>
class Interface_EntityIterator;
class Interface_Graph;
class TCollection_AsciiString;

//! A SelectIntersection filters the Entities issued from several
//! other Selections as Intersection of results : "AND" operator
class IFSelect_SelectIntersection : public IFSelect_SelectCombine
{

public:
  //! Creates an empty SelectIntersection
  Standard_EXPORT IFSelect_SelectIntersection();

  //! Returns the list of selected Entities, which is the common part
  //! of results from all input selections. Uniqueness is guaranteed.
  Standard_EXPORT Interface_EntityIterator RootResult(const Interface_Graph& G) const override;

  //! Returns a text defining the criterium : "Intersection (AND)"
  Standard_EXPORT TCollection_AsciiString Label() const override;

  DEFINE_STANDARD_RTTIEXT(IFSelect_SelectIntersection, IFSelect_SelectCombine)
};
