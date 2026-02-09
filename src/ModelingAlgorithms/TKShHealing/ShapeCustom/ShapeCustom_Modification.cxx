

#include <Message_Msg.hpp>
#include <ShapeCustom_Modification.hpp>
#include <ShapeExtend_BasicMsgRegistrator.hpp>
#include <Standard_Type.hpp>
#include <TopoDS_Shape.hpp>

IMPLEMENT_STANDARD_RTTIEXT(ShapeCustom_Modification, BRepTools_Modification)

void ShapeCustom_Modification::SetMsgRegistrator(
  const occ::handle<ShapeExtend_BasicMsgRegistrator>& msgreg)
{
  myMsgReg = msgreg;
}

occ::handle<ShapeExtend_BasicMsgRegistrator> ShapeCustom_Modification::MsgRegistrator() const
{
  return myMsgReg;
}

void ShapeCustom_Modification::SendMsg(const TopoDS_Shape&   shape,
                                       const Message_Msg&    message,
                                       const Message_Gravity gravity) const
{
  if (!myMsgReg.IsNull())
    myMsgReg->Send(shape, message, gravity);
}
