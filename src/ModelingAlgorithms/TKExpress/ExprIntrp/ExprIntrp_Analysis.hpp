#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Expr_GeneralExpression.hpp>
#include <NCollection_List.hpp>
#include <Expr_GeneralRelation.hpp>
#include <Expr_GeneralFunction.hpp>
#include <TCollection_AsciiString.hpp>
#include <Standard_Integer.hpp>
#include <Expr_NamedFunction.hpp>
#include <NCollection_Sequence.hpp>
#include <Expr_NamedExpression.hpp>
class ExprIntrp_Generator;
class Expr_GeneralExpression;
class Expr_GeneralRelation;
class TCollection_AsciiString;
class Expr_GeneralFunction;
class Expr_NamedFunction;
class Expr_NamedExpression;

class ExprIntrp_Analysis
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT ExprIntrp_Analysis();

  Standard_EXPORT void SetMaster(const occ::handle<ExprIntrp_Generator>& agen);

  Standard_EXPORT void Push(const occ::handle<Expr_GeneralExpression>& exp);

  Standard_EXPORT void PushRelation(const occ::handle<Expr_GeneralRelation>& rel);

  Standard_EXPORT void PushName(const TCollection_AsciiString& name);

  Standard_EXPORT void PushValue(const int degree);

  Standard_EXPORT void PushFunction(const occ::handle<Expr_GeneralFunction>& func);

  Standard_EXPORT occ::handle<Expr_GeneralExpression> Pop();

  Standard_EXPORT occ::handle<Expr_GeneralRelation> PopRelation();

  Standard_EXPORT TCollection_AsciiString PopName();

  Standard_EXPORT int PopValue();

  Standard_EXPORT occ::handle<Expr_GeneralFunction> PopFunction();

  Standard_EXPORT bool IsExpStackEmpty() const;

  Standard_EXPORT bool IsRelStackEmpty() const;

  Standard_EXPORT void ResetAll();

  Standard_EXPORT void Use(const occ::handle<Expr_NamedFunction>& func);

  Standard_EXPORT void Use(const occ::handle<Expr_NamedExpression>& named);

  Standard_EXPORT occ::handle<Expr_NamedExpression> GetNamed(const TCollection_AsciiString& name);

  Standard_EXPORT occ::handle<Expr_NamedFunction> GetFunction(const TCollection_AsciiString& name);

private:
  NCollection_List<occ::handle<Expr_GeneralExpression>>   myGEStack;
  NCollection_List<occ::handle<Expr_GeneralRelation>>     myGRStack;
  NCollection_List<occ::handle<Expr_GeneralFunction>>     myGFStack;
  NCollection_List<TCollection_AsciiString>               myNameStack;
  NCollection_List<int>                                   myValueStack;
  NCollection_Sequence<occ::handle<Expr_NamedFunction>>   myFunctions;
  NCollection_Sequence<occ::handle<Expr_NamedExpression>> myNamed;
  occ::handle<ExprIntrp_Generator>                        myMaster;
};
