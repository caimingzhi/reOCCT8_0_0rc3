#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
#include <Message_Gravity.hpp>
namespace System { namespace log {
class Message_Msg;
}} // namespace System::log

class TopoDS_Shape;

class ShapeExtend_BasicMsgRegistrator : public Standard_Transient
{

public:
  Standard_EXPORT ShapeExtend_BasicMsgRegistrator();

  Standard_EXPORT virtual void Send(const occ::handle<Standard_Transient>& object,
                                    const System::log::Message_Msg&                     message,
                                    const Message_Gravity                  gravity);

  Standard_EXPORT virtual void Send(const TopoDS_Shape&   shape,
                                    const System::log::Message_Msg&    message,
                                    const Message_Gravity gravity);

  Standard_EXPORT virtual void Send(const System::log::Message_Msg& message, const Message_Gravity gravity);

  DEFINE_STANDARD_RTTIEXT(ShapeExtend_BasicMsgRegistrator, Standard_Transient)
};
