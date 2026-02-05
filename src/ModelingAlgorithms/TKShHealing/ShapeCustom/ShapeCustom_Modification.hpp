#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <BRepTools_Modification.hpp>
#include <Message_Gravity.hpp>
class ShapeExtend_BasicMsgRegistrator;
class TopoDS_Shape;
class Message_Msg;

//! A base class of Modification's from ShapeCustom.
//! Implements message sending mechanism.
class ShapeCustom_Modification : public BRepTools_Modification
{

public:
  //! Sets message registrator
  Standard_EXPORT virtual void SetMsgRegistrator(
    const occ::handle<ShapeExtend_BasicMsgRegistrator>& msgreg);

  //! Returns message registrator
  Standard_EXPORT occ::handle<ShapeExtend_BasicMsgRegistrator> MsgRegistrator() const;

  //! Sends a message to be attached to the shape.
  //! Calls corresponding message of message registrator.
  Standard_EXPORT void SendMsg(const TopoDS_Shape&   shape,
                               const Message_Msg&    message,
                               const Message_Gravity gravity = Message_Info) const;

  DEFINE_STANDARD_RTTIEXT(ShapeCustom_Modification, BRepTools_Modification)

private:
  occ::handle<ShapeExtend_BasicMsgRegistrator> myMsgReg;
};
