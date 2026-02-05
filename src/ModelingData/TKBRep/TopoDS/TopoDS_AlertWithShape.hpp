#pragma once

#include <Message_Alert.hpp>
#include <TopoDS_Shape.hpp>

//! Alert object storing TopoDS shape in its field
class TopoDS_AlertWithShape : public Message_Alert
{
public:
  //! Constructor with shape argument
  Standard_EXPORT TopoDS_AlertWithShape(const TopoDS_Shape& theShape);

  //! Returns contained shape
  const TopoDS_Shape& GetShape() const { return myShape; }

  //! Sets the shape
  void SetShape(const TopoDS_Shape& theShape) { myShape = theShape; }

  //! Returns false.
  Standard_EXPORT bool SupportsMerge() const override;

  //! Returns false.
  Standard_EXPORT bool Merge(const occ::handle<Message_Alert>& theTarget) override;

  // OCCT RTTI
  DEFINE_STANDARD_RTTIEXT(TopoDS_AlertWithShape, Message_Alert)

private:
  TopoDS_Shape myShape;
};

//! Helper macro allowing to define alert with shape argument in one line of code
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
