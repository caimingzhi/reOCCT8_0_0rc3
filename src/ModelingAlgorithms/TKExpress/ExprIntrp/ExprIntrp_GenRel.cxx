#include <Expr_GeneralRelation.hpp>
#include <ExprIntrp.hpp>
#include <ExprIntrp_GenRel.hpp>
#include <ExprIntrp_yaccanal.hpp>
#include <Standard_NoSuchObject.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(ExprIntrp_GenRel, ExprIntrp_Generator)

ExprIntrp_GenRel::ExprIntrp_GenRel()
{
  done = false;
}

occ::handle<ExprIntrp_GenRel> ExprIntrp_GenRel::Create()
{
  return new ExprIntrp_GenRel();
}

void ExprIntrp_GenRel::Process(const TCollection_AsciiString& str)
{
  occ::handle<ExprIntrp_GenRel> me = this;
  done                             = false;
  if (ExprIntrp::Parse(me, str))
  {
    if (!ExprIntrp_Recept.IsRelStackEmpty())
    {
      myRelation = ExprIntrp_Recept.PopRelation();
      done       = true;
    }
    else
    {
      myRelation.Nullify();
    }
  }
  else
  {
    myRelation.Nullify();
  }
}

bool ExprIntrp_GenRel::IsDone() const
{
  return done;
}

occ::handle<Expr_GeneralRelation> ExprIntrp_GenRel::Relation() const
{
  if (!done)
  {
    throw Standard_NoSuchObject();
  }
  return myRelation;
}
