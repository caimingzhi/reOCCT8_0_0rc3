#pragma once

#include <Message_Printer.hpp>
#include <Draw_Interpretor.hpp>

class Draw_Printer : public Message_Printer
{
  DEFINE_STANDARD_RTTIEXT(Draw_Printer, Message_Printer)
public:
  Standard_EXPORT Draw_Printer(Draw_Interpretor& theTcl);

protected:
  Standard_EXPORT void send(const TCollection_AsciiString& theString,
                            const Message_Gravity          theGravity) const override;

private:
  Draw_Interpretor* myTcl;
};
