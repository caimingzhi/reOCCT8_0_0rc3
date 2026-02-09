#pragma once

#include <Standard.hpp>
#include <TopoDS_Shape.hpp>
#include <Standard_Transient.hpp>
#include <Message_ProgressRange.hpp>

class BRepMesh_DiscretRoot : public Standard_Transient
{
public:
  Standard_EXPORT ~BRepMesh_DiscretRoot() override;

  void SetShape(const TopoDS_Shape& theShape) { myShape = theShape; }

  const TopoDS_Shape& Shape() const { return myShape; }

  bool IsDone() const { return myIsDone; }

  virtual void Perform(const Message_ProgressRange& theRange = Message_ProgressRange()) = 0;

  DEFINE_STANDARD_RTTIEXT(BRepMesh_DiscretRoot, Standard_Transient)

protected:
  Standard_EXPORT BRepMesh_DiscretRoot();

  void setDone() { myIsDone = true; }

  void setNotDone() { myIsDone = false; }

  Standard_EXPORT virtual void init();

  TopoDS_Shape myShape;
  bool         myIsDone;
};
