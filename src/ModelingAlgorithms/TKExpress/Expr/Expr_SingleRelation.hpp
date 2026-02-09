#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Expr_GeneralRelation.hpp>
#include <Standard_Integer.hpp>
class Expr_GeneralExpression;
class Expr_NamedUnknown;

class Expr_SingleRelation : public Expr_GeneralRelation
{

public:
  Standard_EXPORT void SetFirstMember(const occ::handle<Expr_GeneralExpression>& exp);

  Standard_EXPORT void SetSecondMember(const occ::handle<Expr_GeneralExpression>& exp);

  Standard_EXPORT occ::handle<Expr_GeneralExpression> FirstMember() const;

  Standard_EXPORT occ::handle<Expr_GeneralExpression> SecondMember() const;

  Standard_EXPORT bool IsLinear() const override;

  Standard_EXPORT int NbOfSubRelations() const override;

  Standard_EXPORT int NbOfSingleRelations() const override;

  Standard_EXPORT occ::handle<Expr_GeneralRelation> SubRelation(const int index) const override;

  Standard_EXPORT bool Contains(const occ::handle<Expr_GeneralExpression>& exp) const override;

  Standard_EXPORT void Replace(const occ::handle<Expr_NamedUnknown>&      var,
                               const occ::handle<Expr_GeneralExpression>& with) override;

  DEFINE_STANDARD_RTTIEXT(Expr_SingleRelation, Expr_GeneralRelation)

private:
  occ::handle<Expr_GeneralExpression> myFirstMember;
  occ::handle<Expr_GeneralExpression> mySecondMember;
};
