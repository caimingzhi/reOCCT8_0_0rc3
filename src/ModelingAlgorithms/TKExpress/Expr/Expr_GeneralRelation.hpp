#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
#include <Standard_Integer.hpp>
class Expr_GeneralExpression;
class Expr_NamedUnknown;
class TCollection_AsciiString;

//! Defines the general purposes of any relation between
//! expressions.
class Expr_GeneralRelation : public Standard_Transient
{

public:
  //! Returns the current status of the relation
  Standard_EXPORT virtual bool IsSatisfied() const = 0;

  //! Tests if <me> is linear between its NamedUnknowns.
  Standard_EXPORT virtual bool IsLinear() const = 0;

  //! Returns a GeneralRelation after replacement of
  //! NamedUnknowns by an associated expression, and after
  //! values computation.
  Standard_EXPORT virtual occ::handle<Expr_GeneralRelation> Simplified() const = 0;

  //! Replaces NamedUnknowns by associated expressions,
  //! and computes values in <me>.
  Standard_EXPORT virtual void Simplify() = 0;

  //! Returns a copy of <me> having the same unknowns and
  //! functions.
  Standard_EXPORT virtual occ::handle<Expr_GeneralRelation> Copy() const = 0;

  //! Returns the number of relations contained in <me>.
  Standard_EXPORT virtual int NbOfSubRelations() const = 0;

  //! Returns the number of SingleRelations contained in
  //! <me>.
  Standard_EXPORT virtual int NbOfSingleRelations() const = 0;

  //! Returns the relation denoted by <index> in <me>.
  //! An exception is raised if <index> is out of range.
  Standard_EXPORT virtual occ::handle<Expr_GeneralRelation> SubRelation(const int index) const = 0;

  //! Tests if <exp> contains <var>.
  Standard_EXPORT virtual bool Contains(const occ::handle<Expr_GeneralExpression>& exp) const = 0;

  //! Replaces all occurrences of <var> with <with> in <me>.
  Standard_EXPORT virtual void Replace(const occ::handle<Expr_NamedUnknown>&      var,
                                       const occ::handle<Expr_GeneralExpression>& with) = 0;

  //! returns a string representing <me> in a readable way.
  Standard_EXPORT virtual TCollection_AsciiString String() const = 0;

  DEFINE_STANDARD_RTTIEXT(Expr_GeneralRelation, Standard_Transient)
};

