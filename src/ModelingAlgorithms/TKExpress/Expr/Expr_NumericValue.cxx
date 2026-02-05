#include <Expr_GeneralExpression.hpp>
#include <Expr_NamedUnknown.hpp>
#include <Expr_NumericValue.hpp>
#include <Standard_OutOfRange.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

#include <cstdio>
IMPLEMENT_STANDARD_RTTIEXT(Expr_NumericValue, Expr_GeneralExpression)

Expr_NumericValue::Expr_NumericValue(const double val)
{
  myValue = val;
}

double Expr_NumericValue::GetValue() const
{
  return myValue;
}

void Expr_NumericValue::SetValue(const double val)
{
  myValue = val;
}

int Expr_NumericValue::NbSubExpressions() const
{
  return 0;
}

const occ::handle<Expr_GeneralExpression>& Expr_NumericValue::SubExpression(const int) const
{
  throw Standard_OutOfRange();
}

occ::handle<Expr_GeneralExpression> Expr_NumericValue::Simplified() const
{
  return Copy();
}

occ::handle<Expr_GeneralExpression> Expr_NumericValue::Copy() const
{
  return new Expr_NumericValue(myValue);
}

bool Expr_NumericValue::ContainsUnknowns() const
{
  return false;
}

bool Expr_NumericValue::Contains(const occ::handle<Expr_GeneralExpression>&) const
{
  return false;
}

bool Expr_NumericValue::IsIdentical(const occ::handle<Expr_GeneralExpression>& Other) const
{
  if (!Other->IsKind(STANDARD_TYPE(Expr_NumericValue)))
  {
    return false;
  }
  occ::handle<Expr_NumericValue> NVOther = occ::down_cast<Expr_NumericValue>(Other);
  return (myValue == NVOther->GetValue());
}

bool Expr_NumericValue::IsLinear() const
{
  return true;
}

occ::handle<Expr_GeneralExpression> Expr_NumericValue::Derivative(
  const occ::handle<Expr_NamedUnknown>&) const
{
  return new Expr_NumericValue(0.0);
}

occ::handle<Expr_GeneralExpression> Expr_NumericValue::NDerivative(
  const occ::handle<Expr_NamedUnknown>&,
  const int) const
{
  return new Expr_NumericValue(0.0);
}

void Expr_NumericValue::Replace(const occ::handle<Expr_NamedUnknown>&,
                                const occ::handle<Expr_GeneralExpression>&)
{
}

occ::handle<Expr_GeneralExpression> Expr_NumericValue::ShallowSimplified() const
{
  occ::handle<Expr_NumericValue> me = this;
  return me;
}

double Expr_NumericValue::Evaluate(const NCollection_Array1<occ::handle<Expr_NamedUnknown>>&,
                                   const NCollection_Array1<double>&) const
{
  return myValue;
}

TCollection_AsciiString Expr_NumericValue::String() const
{
  char val[100];
  Sprintf(val, "%g", myValue);
  return TCollection_AsciiString(val);
}
