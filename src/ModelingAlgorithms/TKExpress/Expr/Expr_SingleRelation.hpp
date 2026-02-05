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
  //! Defines the first member of the relation
  Standard_EXPORT void SetFirstMember(const occ::handle<Expr_GeneralExpression>& exp);

  //! Defines the second member of the relation
  Standard_EXPORT void SetSecondMember(const occ::handle<Expr_GeneralExpression>& exp);

  //! Returns the first member of the relation
  Standard_EXPORT occ::handle<Expr_GeneralExpression> FirstMember() const;

  //! Returns the second member of the relation
  Standard_EXPORT occ::handle<Expr_GeneralExpression> SecondMember() const;

  //! Tests if <me> is linear between its NamedUnknowns.
  Standard_EXPORT bool IsLinear() const override;

  //! Returns the number of relations contained in <me>.
  Standard_EXPORT int NbOfSubRelations() const override;

  //! Returns the number of SingleRelations contained in
  //! <me> (Always 1).
  Standard_EXPORT int NbOfSingleRelations() const override;

  //! Returns the relation denoted by <index> in <me>.
  //! An exception is raised if index is out of range.
  Standard_EXPORT occ::handle<Expr_GeneralRelation> SubRelation(const int index) const override;

  //! Tests if <me> contains <exp>.
  Standard_EXPORT bool Contains(const occ::handle<Expr_GeneralExpression>& exp) const override;

  //! Replaces all occurrences of <var> with <with> in <me>.
  Standard_EXPORT void Replace(const occ::handle<Expr_NamedUnknown>&      var,
                               const occ::handle<Expr_GeneralExpression>& with) override;

  DEFINE_STANDARD_RTTIEXT(Expr_SingleRelation, Expr_GeneralRelation)

private:
  occ::handle<Expr_GeneralExpression> myFirstMember;
  occ::handle<Expr_GeneralExpression> mySecondMember;
};
