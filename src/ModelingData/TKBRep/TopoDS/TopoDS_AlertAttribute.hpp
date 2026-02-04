#pragma once


#include <Message_AttributeStream.hpp>
#include <Message_Messenger.hpp>
#include <Message_Report.hpp>
#include <TCollection_AsciiString.hpp>

#include <TopoDS_Shape.hpp>

class Message_Messenger;

//! Alert attribute object storing TopoDS shape in its field
class TopoDS_AlertAttribute : public Message_AttributeStream
{
  DEFINE_STANDARD_RTTIEXT(TopoDS_AlertAttribute, Message_AttributeStream)
public:
  //! Constructor with shape argument
  Standard_EXPORT TopoDS_AlertAttribute(
    const TopoDS_Shape&            theShape,
    const TCollection_AsciiString& theName = TCollection_AsciiString::EmptyString());

  //! Returns contained shape
  const TopoDS_Shape& GetShape() const { return myShape; }

public:
  //! Push shape information into messenger
  Standard_EXPORT static void Send(const occ::handle<Message_Messenger>& theMessenger,
                                   const TopoDS_Shape&                   theShape);

  //! Dumps the content of me into the stream
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

