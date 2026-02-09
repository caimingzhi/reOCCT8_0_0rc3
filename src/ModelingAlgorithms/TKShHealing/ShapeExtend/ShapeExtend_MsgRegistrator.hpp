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

class ShapeExtend_MsgRegistrator : public ShapeExtend_BasicMsgRegistrator
{

public:
  Standard_EXPORT ShapeExtend_MsgRegistrator();

  Standard_EXPORT void Send(const occ::handle<Standard_Transient>& object,
                            const Message_Msg&                     message,
                            const Message_Gravity                  gravity) override;

  Standard_EXPORT void Send(const TopoDS_Shape&   shape,
                            const Message_Msg&    message,
                            const Message_Gravity gravity) override;

  const NCollection_DataMap<occ::handle<Standard_Transient>, NCollection_List<Message_Msg>>&
    MapTransient() const;

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

inline const NCollection_DataMap<occ::handle<Standard_Transient>, NCollection_List<Message_Msg>>&
  ShapeExtend_MsgRegistrator::MapTransient() const
{
  return myMapTransient;
}

inline const NCollection_DataMap<TopoDS_Shape,
                                 NCollection_List<Message_Msg>,
                                 TopTools_ShapeMapHasher>&
  ShapeExtend_MsgRegistrator::MapShape() const
{
  return myMapShape;
}
