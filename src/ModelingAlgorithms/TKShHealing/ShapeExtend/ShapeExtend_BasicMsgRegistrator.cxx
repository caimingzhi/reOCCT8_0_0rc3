#include <Message_Msg.hpp>
#include <ShapeExtend_BasicMsgRegistrator.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>
#include <TopoDS_Shape.hpp>

IMPLEMENT_STANDARD_RTTIEXT(ShapeExtend_BasicMsgRegistrator, Standard_Transient)

ShapeExtend_BasicMsgRegistrator::ShapeExtend_BasicMsgRegistrator() = default;

void ShapeExtend_BasicMsgRegistrator::Send(const occ::handle<Standard_Transient>&,
                                           const System::log::Message_Msg&,
                                           const Message_Gravity)
{
}

void ShapeExtend_BasicMsgRegistrator::Send(const TopoDS_Shape&,
                                           const System::log::Message_Msg&,
                                           const Message_Gravity)
{
}

void ShapeExtend_BasicMsgRegistrator::Send(const System::log::Message_Msg&    message,
                                           const Message_Gravity gravity)
{
  occ::handle<Standard_Transient> dummy;
  Send(dummy, message, gravity);
}
