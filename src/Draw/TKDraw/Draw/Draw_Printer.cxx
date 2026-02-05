#include <Draw_Printer.hpp>

#include <TCollection_AsciiString.hpp>
#include <TCollection_ExtendedString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Draw_Printer, Message_Printer)

//=================================================================================================

Draw_Printer::Draw_Printer(Draw_Interpretor& theTcl)
    : myTcl(&theTcl)
{
}

//=================================================================================================

void Draw_Printer::send(const TCollection_AsciiString& theString,
                        const Message_Gravity          theGravity) const
{
  if (myTcl == nullptr || theGravity < myTraceLevel)
  {
    return;
  }

  *myTcl << theString << "\n";
}
