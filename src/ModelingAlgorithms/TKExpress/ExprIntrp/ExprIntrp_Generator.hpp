#pragma once

#include <Standard.hpp>

#include <Expr_NamedFunction.hpp>
#include <NCollection_Sequence.hpp>
#include <Expr_NamedExpression.hpp>
#include <Standard_Transient.hpp>
class Expr_NamedFunction;
class Expr_NamedExpression;
class TCollection_AsciiString;

class ExprIntrp_Generator : public Standard_Transient
{

public:
  Standard_EXPORT void Use(const occ::handle<Expr_NamedFunction>& func);

  Standard_EXPORT void Use(const occ::handle<Expr_NamedExpression>& named);

  Standard_EXPORT const NCollection_Sequence<occ::handle<Expr_NamedExpression>>& GetNamed() const;

  Standard_EXPORT const NCollection_Sequence<occ::handle<Expr_NamedFunction>>& GetFunctions() const;

  Standard_EXPORT occ::handle<Expr_NamedExpression> GetNamed(
    const TCollection_AsciiString& name) const;

  Standard_EXPORT occ::handle<Expr_NamedFunction> GetFunction(
    const TCollection_AsciiString& name) const;

  DEFINE_STANDARD_RTTIEXT(ExprIntrp_Generator, Standard_Transient)

protected:
  Standard_EXPORT ExprIntrp_Generator();

private:
  NCollection_Sequence<occ::handle<Expr_NamedFunction>>   myFunctions;
  NCollection_Sequence<occ::handle<Expr_NamedExpression>> myNamed;
};
