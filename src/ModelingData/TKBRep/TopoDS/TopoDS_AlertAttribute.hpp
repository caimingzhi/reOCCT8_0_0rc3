#pragma once

#include <Message_AttributeStream.hpp>
#include <Message_Messenger.hpp>
#include <Message_Report.hpp>
#include <TCollection_AsciiString.hpp>

#include <TopoDS_Shape.hpp>

class Message_Messenger;

class TopoDS_AlertAttribute : public Message_AttributeStream
{
  DEFINE_STANDARD_RTTIEXT(TopoDS_AlertAttribute, Message_AttributeStream)
public:
  Standard_EXPORT TopoDS_AlertAttribute(
    const TopoDS_Shape&            theShape,
    const TCollection_AsciiString& theName = TCollection_AsciiString::EmptyString());

  const TopoDS_Shape& GetShape() const { return myShape; }

public:
  Standard_EXPORT static void Send(const occ::handle<Message_Messenger>& theMessenger,
                                   const TopoDS_Shape&                   theShape);

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

private:
  TopoDS_Shape myShape;
};

inline const occ::handle<Message_Messenger>& operator<<(
  const occ::handle<Message_Messenger>& theMessenger,
  const TopoDS_Shape&                   theShape)
{
  TopoDS_AlertAttribute::Send(theMessenger, theShape);
  return theMessenger;
}
