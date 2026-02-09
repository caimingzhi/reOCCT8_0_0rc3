#pragma once

#include <Message_Alert.hpp>
#include <TopoDS_Shape.hpp>

class TopoDS_AlertWithShape : public Message_Alert
{
public:
  Standard_EXPORT TopoDS_AlertWithShape(const TopoDS_Shape& theShape);

  const TopoDS_Shape& GetShape() const { return myShape; }

  void SetShape(const TopoDS_Shape& theShape) { myShape = theShape; }

  Standard_EXPORT bool SupportsMerge() const override;

  Standard_EXPORT bool Merge(const occ::handle<Message_Alert>& theTarget) override;

  DEFINE_STANDARD_RTTIEXT(TopoDS_AlertWithShape, Message_Alert)

private:
  TopoDS_Shape myShape;
};

#define DEFINE_ALERT_WITH_SHAPE(Alert)                                                             \
  class Alert : public TopoDS_AlertWithShape                                                       \
  {                                                                                                \
  public:                                                                                          \
    Alert(const TopoDS_Shape& theShape)                                                            \
        : TopoDS_AlertWithShape(theShape)                                                          \
    {                                                                                              \
    }                                                                                              \
    DEFINE_STANDARD_RTTI_INLINE(Alert, TopoDS_AlertWithShape)                                      \
  };
