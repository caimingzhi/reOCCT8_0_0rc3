#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <Expr_GeneralFunction.hpp>
#include <Standard_Real.hpp>
#include <NCollection_Array1.hpp>
class Expr_GeneralExpression;
class Expr_NamedUnknown;
class TCollection_AsciiString;

class Expr_FunctionDerivative : public Expr_GeneralFunction
{

public:
  //! Creates a FunctionDerivative of degree <deg> relative
  //! to the <withX> variable.
  //! Raises OutOfRange if <deg> lower or equal to zero.
  Standard_EXPORT Expr_FunctionDerivative(const occ::handle<Expr_GeneralFunction>& func,
                                          const occ::handle<Expr_NamedUnknown>&    withX,
                                          const int                                deg);

  //! Returns the number of variables of <me>.
  Standard_EXPORT int NbOfVariables() const override;

  //! Returns the variable denoted by <index> in <me>.
  //! Raises OutOfRange if <index> greater than
  //! NbOfVariables of <me>.
  Standard_EXPORT occ::handle<Expr_NamedUnknown> Variable(const int index) const override;

  //! Computes the value of <me> with the given variables.
  //! Raises DimensionMismatch if Length(vars) is different from
  //! Length(values).
  Standard_EXPORT double Evaluate(const NCollection_Array1<occ::handle<Expr_NamedUnknown>>& vars,
                                  const NCollection_Array1<double>& values) const override;

  //! Returns a copy of <me> with the same form.
  Standard_EXPORT occ::handle<Expr_GeneralFunction> Copy() const override;

  //! Returns Derivative of <me> for variable <var>.
  Standard_EXPORT occ::handle<Expr_GeneralFunction> Derivative(
    const occ::handle<Expr_NamedUnknown>& var) const override;

  //! Returns Derivative of <me> for variable <var> with
  //! degree <deg>.
  Standard_EXPORT occ::handle<Expr_GeneralFunction> Derivative(
    const occ::handle<Expr_NamedUnknown>& var,
    const int                             deg) const override;

  //! Tests if <me> and <func> are similar functions (same
  //! name and same used expression).
  Standard_EXPORT bool IsIdentical(const occ::handle<Expr_GeneralFunction>& func) const override;

  //! Tests if <me> is linear on variable on range <index>
  Standard_EXPORT bool IsLinearOnVariable(const int index) const override;

  //! Returns the function of which <me> is the derivative.
  Standard_EXPORT occ::handle<Expr_GeneralFunction> Function() const;

  //! Returns the degree of derivation of <me>.
  Standard_EXPORT int Degree() const;

  //! Returns the derivation variable of <me>.
  Standard_EXPORT occ::handle<Expr_NamedUnknown> DerivVariable() const;

  Standard_EXPORT TCollection_AsciiString GetStringName() const override;

  Standard_EXPORT occ::handle<Expr_GeneralExpression> Expression() const;

  Standard_EXPORT void UpdateExpression();

  friend class Expr_NamedFunction;

  DEFINE_STANDARD_RTTIEXT(Expr_FunctionDerivative, Expr_GeneralFunction)

private:
  occ::handle<Expr_GeneralFunction>   myFunction;
  occ::handle<Expr_GeneralExpression> myExp;
  occ::handle<Expr_NamedUnknown>      myDerivate;
  int                                 myDegree;
};

