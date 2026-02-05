#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TCollection_AsciiString.hpp>
#include <Expr_GeneralFunction.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
class Expr_GeneralExpression;
class Expr_NamedUnknown;

class Expr_NamedFunction : public Expr_GeneralFunction
{

public:
  //! Creates a function of given variables <vars> with name
  //! <name> defined by the expression <exp>.
  Standard_EXPORT Expr_NamedFunction(
    const TCollection_AsciiString&                            name,
    const occ::handle<Expr_GeneralExpression>&                exp,
    const NCollection_Array1<occ::handle<Expr_NamedUnknown>>& vars);

  //! Sets the name <newname> to <me>.
  Standard_EXPORT void SetName(const TCollection_AsciiString& newname);

  //! Returns the name assigned to <me>
  Standard_EXPORT TCollection_AsciiString GetName() const;

  //! Returns the number of variables of <me>.
  Standard_EXPORT int NbOfVariables() const override;

  //! Returns the variable denoted by <index> in <me>.
  //! Raises OutOfRange if <index> is greater than
  //! NbOfVariables of <me>, or less than or equal to zero.
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

  Standard_EXPORT TCollection_AsciiString GetStringName() const override;

  //! Returns equivalent expression of <me>.
  Standard_EXPORT occ::handle<Expr_GeneralExpression> Expression() const;

  //! Modifies expression of <me>.
  //! Warning: Beware of derivatives. See FunctionDerivative
  Standard_EXPORT void SetExpression(const occ::handle<Expr_GeneralExpression>& exp);

  DEFINE_STANDARD_RTTIEXT(Expr_NamedFunction, Expr_GeneralFunction)

private:
  TCollection_AsciiString                            myName;
  occ::handle<Expr_GeneralExpression>                myExp;
  NCollection_Array1<occ::handle<Expr_NamedUnknown>> myVariables;
};
