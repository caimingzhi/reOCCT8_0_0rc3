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
  Standard_EXPORT Expr_FunctionDerivative(const occ::handle<Expr_GeneralFunction>& func,
                                          const occ::handle<Expr_NamedUnknown>&    withX,
                                          const int                                deg);

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

  Standard_EXPORT occ::handle<Expr_GeneralFunction> Function() const;

  Standard_EXPORT int Degree() const;

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
