#include <Message_Msg.hpp>
#include <ShapeExtend_MsgRegistrator.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>
#include <TopoDS_Shape.hpp>

IMPLEMENT_STANDARD_RTTIEXT(ShapeExtend_MsgRegistrator, ShapeExtend_BasicMsgRegistrator)

ShapeExtend_MsgRegistrator::ShapeExtend_MsgRegistrator()

  = default;

void ShapeExtend_MsgRegistrator::Send(const occ::handle<Standard_Transient>& object,
                                      const Message_Msg&                     message,
                                      const Message_Gravity)
{
  if (object.IsNull())
  {
#ifdef OCCT_DEBUG
    std::cout << "Warning: ShapeExtend_MsgRegistrator::Send: null object" << std::endl;
#endif
    return;
  }
  if (myMapTransient.IsBound(object))
  {
    NCollection_List<Message_Msg>& list = myMapTransient.ChangeFind(object);
    list.Append(message);
  }
  else
  {
    NCollection_List<Message_Msg> list;
    list.Append(message);
    myMapTransient.Bind(object, list);
  }
}

void ShapeExtend_MsgRegistrator::Send(const TopoDS_Shape& shape,
                                      const Message_Msg&  message,
                                      const Message_Gravity)
{
  if (shape.IsNull())
  {
#ifdef OCCT_DEBUG
    std::cout << "Warning: ShapeExtend_MsgRegistrator::Send: null shape" << std::endl;
#endif
    return;
  }
  if (myMapShape.IsBound(shape))
  {
    NCollection_List<Message_Msg>& list = myMapShape.ChangeFind(shape);
    list.Append(message);
  }
  else
  {
    NCollection_List<Message_Msg> list;
    list.Append(message);
    myMapShape.Bind(shape, list);
  }
}
