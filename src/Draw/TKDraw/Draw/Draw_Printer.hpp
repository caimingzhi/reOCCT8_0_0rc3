#pragma once


#include <Message_Printer.hpp>
#include <Draw_Interpretor.hpp>

//! Implementation of Printer class with output
//! (Message_Messenge) directed to Draw_Interpretor
class Draw_Printer : public Message_Printer
{
  DEFINE_STANDARD_RTTIEXT(Draw_Printer, Message_Printer)
public:
  //! Creates a printer connected to the interpreter.
  Standard_EXPORT Draw_Printer(Draw_Interpretor& theTcl);

protected:
  //! Send a string message with specified trace level.
  Standard_EXPORT void send(const TCollection_AsciiString& theString,
                            const Message_Gravity          theGravity) const override;

private:
  Draw_Interpretor* myTcl;
};

