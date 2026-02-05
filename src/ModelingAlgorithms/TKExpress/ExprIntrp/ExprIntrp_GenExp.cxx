#include <Expr_GeneralExpression.hpp>
#include <ExprIntrp.hpp>
#include <ExprIntrp_GenExp.hpp>
#include <ExprIntrp_yaccanal.hpp>
#include <Standard_NoSuchObject.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(ExprIntrp_GenExp, ExprIntrp_Generator)

ExprIntrp_GenExp::ExprIntrp_GenExp()
{
  done = false;
}

occ::handle<ExprIntrp_GenExp> ExprIntrp_GenExp::Create()
{
  return new ExprIntrp_GenExp();
}

void ExprIntrp_GenExp::Process(const TCollection_AsciiString& str)
{
  occ::handle<ExprIntrp_GenExp> me = this;
  done                             = false;
  if (ExprIntrp::Parse(me, str))
  {
    if (!ExprIntrp_Recept.IsExpStackEmpty())
    {
      myExpression = ExprIntrp_Recept.Pop();
      done         = true;
    }
    else
    {
      myExpression.Nullify();
      done = true;
    }
  }
  else
  {
    myExpression.Nullify();
  }
}

bool ExprIntrp_GenExp::IsDone() const
{
  return done;
}

occ::handle<Expr_GeneralExpression> ExprIntrp_GenExp::Expression() const
{
  if (!done)
  {
    throw Standard_NoSuchObject();
  }
  return myExpression;
}
