#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <ExprIntrp_Generator.hpp>
class Expr_GeneralRelation;
class TCollection_AsciiString;

//! Implements an interpreter for equations or system
//! of equations made of expressions of package Expr.
class ExprIntrp_GenRel : public ExprIntrp_Generator
{

public:
  Standard_EXPORT static occ::handle<ExprIntrp_GenRel> Create();

  //! Processes given string.
  Standard_EXPORT void Process(const TCollection_AsciiString& str);

  //! Returns false if any syntax error has occurred during
  //! process.
  Standard_EXPORT bool IsDone() const;

  //! Returns relation generated. Raises an exception if
  //! IsDone answers false.
  Standard_EXPORT occ::handle<Expr_GeneralRelation> Relation() const;

  DEFINE_STANDARD_RTTIEXT(ExprIntrp_GenRel, ExprIntrp_Generator)

private:
  //! Creates an empty generator
  Standard_EXPORT ExprIntrp_GenRel();

  bool                              done;
  occ::handle<Expr_GeneralRelation> myRelation;
};

