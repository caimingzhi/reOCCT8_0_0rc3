#include <Draw.hpp>

#include <Standard_ErrorHandler.hpp>
#include <Standard_Failure.hpp>

Standard_EXPORT const char* Draw_Eval(const char* theCommandStr)
{
  if (theCommandStr == nullptr)
  {
    return "Error: null command string";
  }
  try
  {
    OCC_CATCH_SIGNALS
    Draw_Interpretor& aCommands = Draw::GetInterpretor();
    aCommands.Eval(theCommandStr);
    std::cout << aCommands.Result() << std::endl;
    return aCommands.Result();
  }
  catch (Standard_Failure const& anException)
  {
    return anException.what();
  }
}
