#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Expr_GeneralExpression.hpp>
#include <Standard_Integer.hpp>
class Expr_NamedUnknown;

//! Defines all binary expressions. The order of the two
//! operands is significant.
class Expr_BinaryExpression : public Expr_GeneralExpression
{

public:
  const occ::handle<Expr_GeneralExpression>& FirstOperand() const;

  const occ::handle<Expr_GeneralExpression>& SecondOperand() const;

  //! Sets first operand of <me>
  //! Raises InvalidOperand if exp = me
  Standard_EXPORT void SetFirstOperand(const occ::handle<Expr_GeneralExpression>& exp);

  //! Sets second operand of <me>
  //! Raises InvalidOperand if <exp> contains <me>.
  Standard_EXPORT void SetSecondOperand(const occ::handle<Expr_GeneralExpression>& exp);

  //! returns the number of sub-expressions contained
  //! in <me> ( >= 0)
  Standard_EXPORT int NbSubExpressions() const override;

  //! returns the <I>-th sub-expression of <me>
  //! raises OutOfRange if <I> > NbSubExpressions(me)
  Standard_EXPORT const occ::handle<Expr_GeneralExpression>& SubExpression(
    const int I) const override;

  //! Does <me> contain NamedUnknown ?
  Standard_EXPORT bool ContainsUnknowns() const override;

  //! Tests if <me> contains <exp>.
  Standard_EXPORT bool Contains(const occ::handle<Expr_GeneralExpression>& exp) const override;

  //! Replaces all occurrences of <var> with <with> in <me>.
  //! Raises InvalidOperand if <with> contains <me>.
  Standard_EXPORT void Replace(const occ::handle<Expr_NamedUnknown>&      var,
                               const occ::handle<Expr_GeneralExpression>& with) override;

  //! Returns a GeneralExpression after replacement of
  //! NamedUnknowns by an associated expression and after
  //! values computation.
  Standard_EXPORT occ::handle<Expr_GeneralExpression> Simplified() const override;

  DEFINE_STANDARD_RTTIEXT(Expr_BinaryExpression, Expr_GeneralExpression)

protected:
  //! Sets first operand of <me>
  Standard_EXPORT void CreateFirstOperand(const occ::handle<Expr_GeneralExpression>& exp);

  //! Sets second operand of <me>
  //! Raises InvalidOperand if <exp> contains <me>.
  Standard_EXPORT void CreateSecondOperand(const occ::handle<Expr_GeneralExpression>& exp);

private:
  occ::handle<Expr_GeneralExpression> myFirstOperand;
  occ::handle<Expr_GeneralExpression> mySecondOperand;
};

inline const occ::handle<Expr_GeneralExpression>& Expr_BinaryExpression::FirstOperand() const
{
  return myFirstOperand;
}

inline const occ::handle<Expr_GeneralExpression>& Expr_BinaryExpression::SecondOperand() const
{
  return mySecondOperand;
}
