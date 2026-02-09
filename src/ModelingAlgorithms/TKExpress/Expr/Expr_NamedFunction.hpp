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
  Standard_EXPORT Expr_NamedFunction(
    const TCollection_AsciiString&                            name,
    const occ::handle<Expr_GeneralExpression>&                exp,
    const NCollection_Array1<occ::handle<Expr_NamedUnknown>>& vars);

  Standard_EXPORT void SetName(const TCollection_AsciiString& newname);

  Standard_EXPORT TCollection_AsciiString GetName() const;

  Standard_EXPORT int NbOfVariables() const override;

  Standard_EXPORT occ::handle<Expr_NamedUnknown> Variable(const int index) const override;

  Standard_EXPORT double Evaluate(const NCollection_Array1<occ::handle<Expr_NamedUnknown>>& vars,
                                  const NCollection_Array1<double>& values) const override;

  Standard_EXPORT occ::handle<Expr_GeneralFunction> Copy() const override;

  Standard_EXPORT occ::handle<Expr_GeneralFunction> Derivative(
    const occ::handle<Expr_NamedUnknown>& var) const override;

  Standard_EXPORT occ::handle<Expr_GeneralFunction> Derivative(
    const occ::handle<Expr_NamedUnknown>& var,
    const int                             deg) const override;

  Standard_EXPORT bool IsIdentical(const occ::handle<Expr_GeneralFunction>& func) const override;

  Standard_EXPORT bool IsLinearOnVariable(const int index) const override;

  Standard_EXPORT TCollection_AsciiString GetStringName() const override;

  Standard_EXPORT occ::handle<Expr_GeneralExpression> Expression() const;

  Standard_EXPORT void SetExpression(const occ::handle<Expr_GeneralExpression>& exp);

  DEFINE_STANDARD_RTTIEXT(Expr_NamedFunction, Expr_GeneralFunction)

private:
  TCollection_AsciiString                            myName;
  occ::handle<Expr_GeneralExpression>                myExp;
  NCollection_Array1<occ::handle<Expr_NamedUnknown>> myVariables;
};
