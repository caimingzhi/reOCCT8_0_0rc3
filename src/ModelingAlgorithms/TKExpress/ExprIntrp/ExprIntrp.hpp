#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>
class ExprIntrp_Generator;
class TCollection_AsciiString;

//! Describes an interpreter for GeneralExpressions,
//! GeneralFunctions, and GeneralRelations defined in
//! package Expr.
class ExprIntrp
{
public:
  DEFINE_STANDARD_ALLOC

private:
  Standard_EXPORT static bool Parse(const occ::handle<ExprIntrp_Generator>& gen,
                                    const TCollection_AsciiString&          str);

private:
  friend class ExprIntrp_GenExp;
  friend class ExprIntrp_GenFct;
  friend class ExprIntrp_GenRel;
};

