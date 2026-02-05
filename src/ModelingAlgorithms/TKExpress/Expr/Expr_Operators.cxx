#include <Expr_Operators.hpp>

occ::handle<Expr_Sum> operator+(const occ::handle<Expr_GeneralExpression>& x,
                                const occ::handle<Expr_GeneralExpression>& y)
{
  return new Expr_Sum(x, y);
}

occ::handle<Expr_Sum> operator+(const double x, const occ::handle<Expr_GeneralExpression>& y)
{
  occ::handle<Expr_NumericValue> nv = new Expr_NumericValue(x);
  return new Expr_Sum(nv, y);
}

occ::handle<Expr_Sum> operator+(const occ::handle<Expr_GeneralExpression>& x, const double y)
{
  return y + x;
}

occ::handle<Expr_Difference> operator-(const occ::handle<Expr_GeneralExpression>& x,
                                       const occ::handle<Expr_GeneralExpression>& y)
{
  return new Expr_Difference(x, y);
}

occ::handle<Expr_Difference> operator-(const double x, const occ::handle<Expr_GeneralExpression>& y)
{
  occ::handle<Expr_NumericValue> nv = new Expr_NumericValue(x);
  return new Expr_Difference(nv, y);
}

occ::handle<Expr_Difference> operator-(const occ::handle<Expr_GeneralExpression>& x, const double y)
{
  occ::handle<Expr_NumericValue> nv = new Expr_NumericValue(y);
  return new Expr_Difference(x, nv);
}

occ::handle<Expr_UnaryMinus> operator-(const occ::handle<Expr_GeneralExpression>& x)
{
  return new Expr_UnaryMinus(x);
}

occ::handle<Expr_Product> operator*(const occ::handle<Expr_GeneralExpression>& x,
                                    const occ::handle<Expr_GeneralExpression>& y)
{
  return new Expr_Product(x, y);
}

occ::handle<Expr_Product> operator*(const double x, const occ::handle<Expr_GeneralExpression>& y)
{
  occ::handle<Expr_NumericValue> nv = new Expr_NumericValue(x);
  return new Expr_Product(nv, y);
}

occ::handle<Expr_Product> operator*(const occ::handle<Expr_GeneralExpression>& x, const double y)
{
  return y * x;
}

occ::handle<Expr_Division> operator/(const occ::handle<Expr_GeneralExpression>& x,
                                     const occ::handle<Expr_GeneralExpression>& y)
{
  return new Expr_Division(x, y);
}

occ::handle<Expr_Division> operator/(const double x, const occ::handle<Expr_GeneralExpression>& y)
{
  occ::handle<Expr_NumericValue> nv = new Expr_NumericValue(x);
  return new Expr_Division(nv, y);
}

occ::handle<Expr_Division> operator/(const occ::handle<Expr_GeneralExpression>& x, const double y)
{
  occ::handle<Expr_NumericValue> nv = new Expr_NumericValue(y);
  return new Expr_Division(x, nv);
}
