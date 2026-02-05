#include <ExprIntrp.hpp>
#include <ExprIntrp_Generator.hpp>
#include <ExprIntrp_SyntaxError.hpp>
#include <ExprIntrp_yaccanal.hpp>
#include <ExprIntrp_yaccintrf.hpp>
#include <Standard_ErrorHandler.hpp>
#include <TCollection_AsciiString.hpp>

static TCollection_AsciiString ExprIntrp_thestring;

bool ExprIntrp::Parse(const occ::handle<ExprIntrp_Generator>& gen,
                      const TCollection_AsciiString&          str)
{
  ExprIntrp_Recept.SetMaster(gen);
  if (str.Length() == 0)
    return false;
  ExprIntrp_thestring = str;
  ExprIntrp_start_string(ExprIntrp_thestring.ToCString());

  int kerror = 1;

  {
    try
    {
      OCC_CATCH_SIGNALS
      while (kerror != 0)
      {
        kerror = ExprIntrpparse();
      }
      ExprIntrp_stop_string();
      return true;
    }
    catch (Standard_Failure const&)
    {
    }
  }
  ExprIntrp_stop_string();
  return false;
}
