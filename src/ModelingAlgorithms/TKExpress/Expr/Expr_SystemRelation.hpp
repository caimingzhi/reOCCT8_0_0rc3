#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Expr_GeneralRelation.hpp>
#include <NCollection_Sequence.hpp>
#include <Standard_Integer.hpp>
class Expr_GeneralExpression;
class Expr_NamedUnknown;
class TCollection_AsciiString;

class Expr_SystemRelation : public Expr_GeneralRelation
{

public:
  Standard_EXPORT Expr_SystemRelation(const occ::handle<Expr_GeneralRelation>& relation);

  Standard_EXPORT void Add(const occ::handle<Expr_GeneralRelation>& relation);

  Standard_EXPORT void Remove(const occ::handle<Expr_GeneralRelation>& relation);

  Standard_EXPORT bool IsLinear() const override;

  Standard_EXPORT int NbOfSubRelations() const override;

  Standard_EXPORT int NbOfSingleRelations() const override;

  Standard_EXPORT occ::handle<Expr_GeneralRelation> SubRelation(const int index) const override;

  Standard_EXPORT bool IsSatisfied() const override;

  Standard_EXPORT occ::handle<Expr_GeneralRelation> Simplified() const override;

  Standard_EXPORT void Simplify() override;

  Standard_EXPORT occ::handle<Expr_GeneralRelation> Copy() const override;

  Standard_EXPORT bool Contains(const occ::handle<Expr_GeneralExpression>& exp) const override;

  Standard_EXPORT void Replace(const occ::handle<Expr_NamedUnknown>&      var,
                               const occ::handle<Expr_GeneralExpression>& with) override;

  Standard_EXPORT TCollection_AsciiString String() const override;

  DEFINE_STANDARD_RTTIEXT(Expr_SystemRelation, Expr_GeneralRelation)

private:
  NCollection_Sequence<occ::handle<Expr_GeneralRelation>> myRelations;
};
