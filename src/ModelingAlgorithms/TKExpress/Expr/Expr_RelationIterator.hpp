#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Expr_SingleRelation.hpp>
#include <NCollection_Array1.hpp>
#include <Standard_Integer.hpp>
#include <Standard_Boolean.hpp>
class Expr_GeneralRelation;
class Expr_SingleRelation;

class Expr_RelationIterator
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Expr_RelationIterator(const occ::handle<Expr_GeneralRelation>& rel);

  Standard_EXPORT bool More() const;

  Standard_EXPORT void Next();

  Standard_EXPORT occ::handle<Expr_SingleRelation> Value() const;

private:
  NCollection_Array1<occ::handle<Expr_SingleRelation>> myRelation;
  int                                                  current;
};
