#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <BRepTools_Modification.hpp>
#include <Message_Gravity.hpp>
class ShapeExtend_BasicMsgRegistrator;
class TopoDS_Shape;
namespace System { namespace log {
class Message_Msg;
}} // namespace System::log


class ShapeCustom_Modification : public BRepTools_Modification
{

public:
  Standard_EXPORT virtual void SetMsgRegistrator(
    const occ::handle<ShapeExtend_BasicMsgRegistrator>& msgreg);

  Standard_EXPORT occ::handle<ShapeExtend_BasicMsgRegistrator> MsgRegistrator() const;

  Standard_EXPORT void SendMsg(const TopoDS_Shape&   shape,
                               const System::log::Message_Msg&    message,
                               const Message_Gravity gravity = Message_Info) const;

  DEFINE_STANDARD_RTTIEXT(ShapeCustom_Modification, BRepTools_Modification)

private:
  occ::handle<ShapeExtend_BasicMsgRegistrator> myMsgReg;
};
