#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Expr_UnaryExpression.hpp>
#include <NCollection_Array1.hpp>
class Expr_GeneralExpression;
class Expr_NamedUnknown;
class TCollection_AsciiString;

class Expr_Square : public Expr_UnaryExpression
{

public:
  //! Creates the square of <exp>.
  Standard_EXPORT Expr_Square(const occ::handle<Expr_GeneralExpression>& exp);

  //! Returns a GeneralExpression after a simplification
  //! of the arguments of <me>.
  Standard_EXPORT occ::handle<Expr_GeneralExpression> ShallowSimplified() const override;

  //! Returns a copy of <me> having the same unknowns and functions.
  Standard_EXPORT occ::handle<Expr_GeneralExpression> Copy() const override;

  //! Tests if <me> and <Other> define the same expression.
  //! This method does not include any simplification before
  //! testing.
  Standard_EXPORT bool IsIdentical(const occ::handle<Expr_GeneralExpression>& Other) const override;

  Standard_EXPORT bool IsLinear() const override;

  //! Returns the derivative on <X> unknown of <me>.
  Standard_EXPORT occ::handle<Expr_GeneralExpression> Derivative(
    const occ::handle<Expr_NamedUnknown>& X) const override;

  //! Returns the value of <me> (as a Real) by
  //! replacement of <vars> by <vals>.
  //! Raises NotEvaluable if <me> contains NamedUnknown not
  //! in <vars> or NumericError if result cannot be computed.
  Standard_EXPORT double Evaluate(const NCollection_Array1<occ::handle<Expr_NamedUnknown>>& vars,
                                  const NCollection_Array1<double>& vals) const override;

  //! returns a string representing <me> in a readable way.
  Standard_EXPORT TCollection_AsciiString String() const override;

  DEFINE_STANDARD_RTTIEXT(Expr_Square, Expr_UnaryExpression)
};

