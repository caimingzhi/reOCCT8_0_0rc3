#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Expr_NamedExpression.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
class Expr_GeneralExpression;
class TCollection_AsciiString;

class Expr_NamedUnknown : public Expr_NamedExpression
{

public:
  Standard_EXPORT Expr_NamedUnknown(const TCollection_AsciiString& name);

  bool IsAssigned() const;

  Standard_EXPORT const occ::handle<Expr_GeneralExpression>& AssignedExpression() const;

  Standard_EXPORT void Assign(const occ::handle<Expr_GeneralExpression>& exp);

  void Deassign();

  Standard_EXPORT int NbSubExpressions() const override;

  Standard_EXPORT const occ::handle<Expr_GeneralExpression>& SubExpression(
    const int I) const override;

  Standard_EXPORT occ::handle<Expr_GeneralExpression> Simplified() const override;

  Standard_EXPORT occ::handle<Expr_GeneralExpression> ShallowSimplified() const override;

  Standard_EXPORT occ::handle<Expr_GeneralExpression> Copy() const override;

  Standard_EXPORT bool ContainsUnknowns() const override;

  Standard_EXPORT bool Contains(const occ::handle<Expr_GeneralExpression>& exp) const override;

  Standard_EXPORT bool IsLinear() const override;

  Standard_EXPORT occ::handle<Expr_GeneralExpression> Derivative(
    const occ::handle<Expr_NamedUnknown>& X) const override;

  Standard_EXPORT void Replace(const occ::handle<Expr_NamedUnknown>&      var,
                               const occ::handle<Expr_GeneralExpression>& with) override;

  Standard_EXPORT double Evaluate(const NCollection_Array1<occ::handle<Expr_NamedUnknown>>& vars,
                                  const NCollection_Array1<double>& vals) const override;

  DEFINE_STANDARD_RTTIEXT(Expr_NamedUnknown, Expr_NamedExpression)

private:
  occ::handle<Expr_GeneralExpression> myExpression;
};

inline bool Expr_NamedUnknown::IsAssigned() const
{
  return !(myExpression.IsNull());
}

inline void Expr_NamedUnknown::Deassign()
{
  myExpression.Nullify();
}

class Expr_NamedUnknown;
