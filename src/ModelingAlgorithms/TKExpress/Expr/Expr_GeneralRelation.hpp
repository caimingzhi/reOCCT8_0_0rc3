#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
#include <Standard_Integer.hpp>
class Expr_GeneralExpression;
class Expr_NamedUnknown;
class TCollection_AsciiString;

class Expr_GeneralRelation : public Standard_Transient
{

public:
  Standard_EXPORT virtual bool IsSatisfied() const = 0;

  Standard_EXPORT virtual bool IsLinear() const = 0;

  Standard_EXPORT virtual occ::handle<Expr_GeneralRelation> Simplified() const = 0;

  Standard_EXPORT virtual void Simplify() = 0;

  Standard_EXPORT virtual occ::handle<Expr_GeneralRelation> Copy() const = 0;

  Standard_EXPORT virtual int NbOfSubRelations() const = 0;

  Standard_EXPORT virtual int NbOfSingleRelations() const = 0;

  Standard_EXPORT virtual occ::handle<Expr_GeneralRelation> SubRelation(const int index) const = 0;

  Standard_EXPORT virtual bool Contains(const occ::handle<Expr_GeneralExpression>& exp) const = 0;

  Standard_EXPORT virtual void Replace(const occ::handle<Expr_NamedUnknown>&      var,
                                       const occ::handle<Expr_GeneralExpression>& with) = 0;

  Standard_EXPORT virtual TCollection_AsciiString String() const = 0;

  DEFINE_STANDARD_RTTIEXT(Expr_GeneralRelation, Standard_Transient)
};
