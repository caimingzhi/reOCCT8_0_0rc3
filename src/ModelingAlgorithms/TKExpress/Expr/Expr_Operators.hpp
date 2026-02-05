#pragma once

#include <Expr_GeneralExpression.hpp>
#include <Expr_NumericValue.hpp>
#include <Expr_Sum.hpp>
#include <Expr_UnaryMinus.hpp>
#include <Expr_Difference.hpp>
#include <Expr_Product.hpp>
#include <Expr_Division.hpp>

Standard_EXPORT occ::handle<Expr_Sum> operator+(const occ::handle<Expr_GeneralExpression>& x,
                                                const occ::handle<Expr_GeneralExpression>& y);

Standard_EXPORT occ::handle<Expr_Sum> operator+(const double                               x,
                                                const occ::handle<Expr_GeneralExpression>& y);

Standard_EXPORT occ::handle<Expr_Sum> operator+(const occ::handle<Expr_GeneralExpression>& x,
                                                const double                               y);

Standard_EXPORT occ::handle<Expr_Difference> operator-(
  const occ::handle<Expr_GeneralExpression>& x,
  const occ::handle<Expr_GeneralExpression>& y);

Standard_EXPORT occ::handle<Expr_Difference> operator-(
  const double                               x,
  const occ::handle<Expr_GeneralExpression>& y);

Standard_EXPORT occ::handle<Expr_Difference> operator-(const occ::handle<Expr_GeneralExpression>& x,
                                                       const double y);

Standard_EXPORT occ::handle<Expr_UnaryMinus> operator-(
  const occ::handle<Expr_GeneralExpression>& x);

Standard_EXPORT occ::handle<Expr_Product> operator*(const occ::handle<Expr_GeneralExpression>& x,
                                                    const occ::handle<Expr_GeneralExpression>& y);

Standard_EXPORT occ::handle<Expr_Product> operator*(const double                               x,
                                                    const occ::handle<Expr_GeneralExpression>& y);

Standard_EXPORT occ::handle<Expr_Product> operator*(const occ::handle<Expr_GeneralExpression>& x,
                                                    const double                               y);

Standard_EXPORT occ::handle<Expr_Division> operator/(const occ::handle<Expr_GeneralExpression>& x,
                                                     const occ::handle<Expr_GeneralExpression>& y);

Standard_EXPORT occ::handle<Expr_Division> operator/(const double                               x,
                                                     const occ::handle<Expr_GeneralExpression>& y);

Standard_EXPORT occ::handle<Expr_Division> operator/(const occ::handle<Expr_GeneralExpression>& x,
                                                     const double                               y);
