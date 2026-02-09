#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Expr_NamedUnknown.hpp>
#include <NCollection_IndexedMap.hpp>
#include <Standard_Integer.hpp>
class Expr_GeneralExpression;
class Expr_NamedUnknown;

class Expr_UnknownIterator
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Expr_UnknownIterator(const occ::handle<Expr_GeneralExpression>& exp);

  Standard_EXPORT bool More() const;

  Standard_EXPORT void Next();

  Standard_EXPORT occ::handle<Expr_NamedUnknown> Value() const;

private:
  Standard_EXPORT void Perform(const occ::handle<Expr_GeneralExpression>& exp);

  NCollection_IndexedMap<occ::handle<Expr_NamedUnknown>> myMap;
  int                                                    myCurrent;
};
