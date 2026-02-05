#include <ExprIntrp_Generator.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(ExprIntrp_Generator, Standard_Transient)

#include <ExprIntrp_yaccanal.hpp>
ExprIntrp_Analysis ExprIntrp_Recept;

ExprIntrp_Generator::ExprIntrp_Generator() = default;

void ExprIntrp_Generator::Use(const occ::handle<Expr_NamedFunction>& func)
{
  myFunctions.Append(func);
}

void ExprIntrp_Generator::Use(const occ::handle<Expr_NamedExpression>& named)
{
  myNamed.Append(named);
}

const NCollection_Sequence<occ::handle<Expr_NamedFunction>>& ExprIntrp_Generator::GetFunctions()
  const
{
  return myFunctions;
}

const NCollection_Sequence<occ::handle<Expr_NamedExpression>>& ExprIntrp_Generator::GetNamed() const
{
  return myNamed;
}

occ::handle<Expr_NamedFunction> ExprIntrp_Generator::GetFunction(
  const TCollection_AsciiString& name) const
{
  for (int i = 1; i <= myFunctions.Length(); i++)
  {
    if (name == myFunctions(i)->GetName())
    {
      return myFunctions(i);
    }
  }
  occ::handle<Expr_NamedFunction> curfunc;
  return curfunc;
}

occ::handle<Expr_NamedExpression> ExprIntrp_Generator::GetNamed(
  const TCollection_AsciiString& name) const
{
  for (int i = 1; i <= myNamed.Length(); i++)
  {
    if (name == myNamed(i)->GetName())
    {
      return myNamed(i);
    }
  }
  occ::handle<Expr_NamedExpression> curexp;
  return curexp;
}
