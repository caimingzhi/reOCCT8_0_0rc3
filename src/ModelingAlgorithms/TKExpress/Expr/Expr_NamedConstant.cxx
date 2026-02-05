#include <Expr_GeneralExpression.hpp>
#include <Expr_NamedConstant.hpp>
#include <Expr_NamedUnknown.hpp>
#include <Expr_NumericValue.hpp>
#include <Standard_OutOfRange.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Expr_NamedConstant, Expr_NamedExpression)

Expr_NamedConstant::Expr_NamedConstant(const TCollection_AsciiString& name, const double value)
{
  SetName(name);
  myValue = value;
}

const occ::handle<Expr_GeneralExpression>& Expr_NamedConstant::SubExpression(const int) const
{
  throw Standard_OutOfRange();
}

occ::handle<Expr_GeneralExpression> Expr_NamedConstant::Simplified() const
{
  occ::handle<Expr_GeneralExpression> res = new Expr_NumericValue(myValue);
  return res;
}

occ::handle<Expr_GeneralExpression> Expr_NamedConstant::Copy() const
{
  return new Expr_NamedConstant(GetName(), myValue);
}

occ::handle<Expr_GeneralExpression> Expr_NamedConstant::Derivative(
  const occ::handle<Expr_NamedUnknown>&) const
{
  occ::handle<Expr_GeneralExpression> aNumVal = new Expr_NumericValue(0.0);
  return aNumVal;
}

occ::handle<Expr_GeneralExpression> Expr_NamedConstant::NDerivative(
  const occ::handle<Expr_NamedUnknown>&,
  const int) const
{
  return new Expr_NumericValue(0.0);
}

occ::handle<Expr_GeneralExpression> Expr_NamedConstant::ShallowSimplified() const
{
  occ::handle<Expr_GeneralExpression> res = new Expr_NumericValue(myValue);
  return res;
}

double Expr_NamedConstant::Evaluate(const NCollection_Array1<occ::handle<Expr_NamedUnknown>>&,
                                    const NCollection_Array1<double>&) const
{
  return myValue;
}

int Expr_NamedConstant::NbSubExpressions() const
{
  return 0;
}

bool Expr_NamedConstant::ContainsUnknowns() const
{
  return false;
}

bool Expr_NamedConstant::Contains(const occ::handle<Expr_GeneralExpression>&) const
{
  return false;
}

bool Expr_NamedConstant::IsLinear() const
{
  return true;
}

void Expr_NamedConstant::Replace(const occ::handle<Expr_NamedUnknown>&,
                                 const occ::handle<Expr_GeneralExpression>&)
{
}
