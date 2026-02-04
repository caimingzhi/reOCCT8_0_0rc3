#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Expr_SingleRelation.hpp>
class Expr_GeneralExpression;
class Expr_GeneralRelation;
class TCollection_AsciiString;

class Expr_GreaterThan : public Expr_SingleRelation
{

public:
  //! Creates the relation <exp1> > <exp2>.
  Standard_EXPORT Expr_GreaterThan(const occ::handle<Expr_GeneralExpression>& exp1,
                                   const occ::handle<Expr_GeneralExpression>& exp2);

  Standard_EXPORT bool IsSatisfied() const override;

  //! Returns a GeneralRelation after replacement of
  //! NamedUnknowns by an associated expression, and after
  //! values computation.
  Standard_EXPORT occ::handle<Expr_GeneralRelation> Simplified() const override;

  //! Replaces NamedUnknowns by associated expressions,
  //! and computes values in <me>.
  Standard_EXPORT void Simplify() override;

  //! Returns a copy of <me> having the same unknowns and functions.
  Standard_EXPORT occ::handle<Expr_GeneralRelation> Copy() const override;

  //! returns a string representing <me> in a readable way.
  Standard_EXPORT TCollection_AsciiString String() const override;

  DEFINE_STANDARD_RTTIEXT(Expr_GreaterThan, Expr_SingleRelation)
};

