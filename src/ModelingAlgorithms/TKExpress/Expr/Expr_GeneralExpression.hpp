#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
#include <Standard_Integer.hpp>
#include <Standard_Real.hpp>
#include <NCollection_Array1.hpp>
class Expr_NamedUnknown;
class TCollection_AsciiString;

class Expr_GeneralExpression : public Standard_Transient
{

public:
  Standard_EXPORT virtual int NbSubExpressions() const = 0;

  Standard_EXPORT virtual const occ::handle<Expr_GeneralExpression>& SubExpression(
    const int I) const = 0;

  Standard_EXPORT virtual occ::handle<Expr_GeneralExpression> Simplified() const = 0;

  Standard_EXPORT virtual occ::handle<Expr_GeneralExpression> ShallowSimplified() const = 0;

  Standard_EXPORT virtual occ::handle<Expr_GeneralExpression> Copy() const = 0;

  Standard_EXPORT virtual bool ContainsUnknowns() const = 0;

  Standard_EXPORT virtual bool Contains(const occ::handle<Expr_GeneralExpression>& exp) const = 0;

  Standard_EXPORT virtual bool IsLinear() const = 0;

  Standard_EXPORT virtual bool IsShareable() const;

  Standard_EXPORT virtual bool IsIdentical(
    const occ::handle<Expr_GeneralExpression>& Other) const = 0;

  Standard_EXPORT virtual occ::handle<Expr_GeneralExpression> Derivative(
    const occ::handle<Expr_NamedUnknown>& X) const = 0;

  Standard_EXPORT virtual occ::handle<Expr_GeneralExpression> NDerivative(
    const occ::handle<Expr_NamedUnknown>& X,
    const int                             N) const;

  Standard_EXPORT virtual void Replace(const occ::handle<Expr_NamedUnknown>&      var,
                                       const occ::handle<Expr_GeneralExpression>& with) = 0;

  Standard_EXPORT virtual double Evaluate(
    const NCollection_Array1<occ::handle<Expr_NamedUnknown>>& vars,
    const NCollection_Array1<double>&                         vals) const = 0;

  Standard_EXPORT double EvaluateNumeric() const;

  Standard_EXPORT virtual TCollection_AsciiString String() const = 0;

  DEFINE_STANDARD_RTTIEXT(Expr_GeneralExpression, Standard_Transient)
};
