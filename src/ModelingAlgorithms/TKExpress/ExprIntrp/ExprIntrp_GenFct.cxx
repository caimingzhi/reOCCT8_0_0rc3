#include <ExprIntrp.hpp>
#include <ExprIntrp_GenFct.hpp>
#include <ExprIntrp_yaccanal.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(ExprIntrp_GenFct, ExprIntrp_Generator)

ExprIntrp_GenFct::ExprIntrp_GenFct()
{
  done = false;
}

occ::handle<ExprIntrp_GenFct> ExprIntrp_GenFct::Create()
{
  return new ExprIntrp_GenFct();
}

void ExprIntrp_GenFct::Process(const TCollection_AsciiString& str)
{
  occ::handle<ExprIntrp_GenFct> me = this;
  done                             = ExprIntrp::Parse(me, str);
}

bool ExprIntrp_GenFct::IsDone() const
{
  return done;
}
