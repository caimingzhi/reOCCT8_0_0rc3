#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
#include <Message_Gravity.hpp>
class Message_Msg;
class TopoDS_Shape;

//! Abstract class that can be used for attaching messages
//! to the objects (e.g. shapes).
//! It is used by ShapeHealing algorithms to attach a message
//! describing encountered case (e.g. removing small edge from
//! a wire).
//!
//! The methods of this class are empty and redefined, for instance,
//! in the classes for Data Exchange processors for attaching
//! messages to interface file entities or CAS.CADE shapes.
class ShapeExtend_BasicMsgRegistrator : public Standard_Transient
{

public:
  //! Empty constructor.
  Standard_EXPORT ShapeExtend_BasicMsgRegistrator();

  //! Sends a message to be attached to the object.
  //! Object can be of any type interpreted by redefined MsgRegistrator.
  Standard_EXPORT virtual void Send(const occ::handle<Standard_Transient>& object,
                                    const Message_Msg&                     message,
                                    const Message_Gravity                  gravity);

  //! Sends a message to be attached to the shape.
  Standard_EXPORT virtual void Send(const TopoDS_Shape&   shape,
                                    const Message_Msg&    message,
                                    const Message_Gravity gravity);

  //! Calls Send method with Null Transient.
  Standard_EXPORT virtual void Send(const Message_Msg& message, const Message_Gravity gravity);

  DEFINE_STANDARD_RTTIEXT(ShapeExtend_BasicMsgRegistrator, Standard_Transient)
};

