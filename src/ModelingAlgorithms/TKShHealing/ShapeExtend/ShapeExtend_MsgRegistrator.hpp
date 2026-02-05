#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
#include <Message_Msg.hpp>
#include <NCollection_List.hpp>
#include <NCollection_DataMap.hpp>
#include <TopoDS_Shape.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <ShapeExtend_BasicMsgRegistrator.hpp>
#include <Message_Gravity.hpp>
class Standard_Transient;
class Message_Msg;
class TopoDS_Shape;

//! Attaches messages to the objects (generic Transient or shape).
//! The objects of this class are transmitted to the Shape Healing
//! algorithms so that they could collect messages occurred during
//! processing.
//!
//! Messages are added to the Maps (stored as a field) that can be
//! used, for instance, by Data Exchange processors to attach those
//! messages to initial file entities.
class ShapeExtend_MsgRegistrator : public ShapeExtend_BasicMsgRegistrator
{

public:
  //! Creates an object.
  Standard_EXPORT ShapeExtend_MsgRegistrator();

  //! Sends a message to be attached to the object.
  //! If the object is in the map then the message is added to the
  //! list, otherwise the object is firstly added to the map.
  Standard_EXPORT void Send(const occ::handle<Standard_Transient>& object,
                            const Message_Msg&                     message,
                            const Message_Gravity                  gravity) override;

  //! Sends a message to be attached to the shape.
  //! If the shape is in the map then the message is added to the
  //! list, otherwise the shape is firstly added to the map.
  Standard_EXPORT void Send(const TopoDS_Shape&   shape,
                            const Message_Msg&    message,
                            const Message_Gravity gravity) override;

  //! Returns a Map of objects and message list
  const NCollection_DataMap<occ::handle<Standard_Transient>, NCollection_List<Message_Msg>>&
    MapTransient() const;

  //! Returns a Map of shapes and message list
  const NCollection_DataMap<TopoDS_Shape, NCollection_List<Message_Msg>, TopTools_ShapeMapHasher>&
    MapShape() const;

  DEFINE_STANDARD_RTTIEXT(ShapeExtend_MsgRegistrator, ShapeExtend_BasicMsgRegistrator)

private:
  NCollection_DataMap<occ::handle<Standard_Transient>, NCollection_List<Message_Msg>>
    myMapTransient;
  NCollection_DataMap<TopoDS_Shape, NCollection_List<Message_Msg>, TopTools_ShapeMapHasher>
    myMapShape;
};

#include <ShapeExtend_MsgRegistrator.hpp>

//=================================================================================================

inline const NCollection_DataMap<occ::handle<Standard_Transient>, NCollection_List<Message_Msg>>&
  ShapeExtend_MsgRegistrator::MapTransient() const
{
  return myMapTransient;
}

//=================================================================================================

inline const NCollection_DataMap<TopoDS_Shape,
                                 NCollection_List<Message_Msg>,
                                 TopTools_ShapeMapHasher>&
  ShapeExtend_MsgRegistrator::MapShape() const
{
  return myMapShape;
}
