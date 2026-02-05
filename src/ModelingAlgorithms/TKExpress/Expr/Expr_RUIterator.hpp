#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Expr_NamedUnknown.hpp>
#include <NCollection_IndexedMap.hpp>
#include <Standard_Integer.hpp>
class Expr_GeneralRelation;
class Expr_NamedUnknown;

//! Iterates on NamedUnknowns in a GeneralRelation.
class Expr_RUIterator
{
public:
  DEFINE_STANDARD_ALLOC

  //! Creates an iterator on every NamedUnknown contained in
  //! <rel>.
  Standard_EXPORT Expr_RUIterator(const occ::handle<Expr_GeneralRelation>& rel);

  //! Returns False if on other unknown remains.
  Standard_EXPORT bool More() const;

  Standard_EXPORT void Next();

  //! Returns current NamedUnknown.
  //! Raises exception if no more unknowns remain.
  Standard_EXPORT occ::handle<Expr_NamedUnknown> Value() const;

private:
  NCollection_IndexedMap<occ::handle<Expr_NamedUnknown>> myMap;
  int                                                    myCurrent;
};
