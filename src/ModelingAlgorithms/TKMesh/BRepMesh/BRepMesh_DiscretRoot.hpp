#pragma once


#include <Standard.hpp>
#include <TopoDS_Shape.hpp>
#include <Standard_Transient.hpp>
#include <Message_ProgressRange.hpp>

//! This is a common interface for meshing algorithms
//! instantiated by Mesh Factory and implemented by plugins.
class BRepMesh_DiscretRoot : public Standard_Transient
{
public:
  //! Destructor
  Standard_EXPORT ~BRepMesh_DiscretRoot() override;

  //! Set the shape to triangulate.
  void SetShape(const TopoDS_Shape& theShape) { myShape = theShape; }

  const TopoDS_Shape& Shape() const { return myShape; }

  //! Returns true if triangualtion was performed and has success.
  bool IsDone() const { return myIsDone; }

  //! Compute triangulation for set shape.
  virtual void Perform(const Message_ProgressRange& theRange = Message_ProgressRange()) = 0;

  DEFINE_STANDARD_RTTIEXT(BRepMesh_DiscretRoot, Standard_Transient)

protected:
  //! Constructor
  Standard_EXPORT BRepMesh_DiscretRoot();

  //! Sets IsDone flag.
  void setDone() { myIsDone = true; }

  //! Clears IsDone flag.
  void setNotDone() { myIsDone = false; }

  Standard_EXPORT virtual void init();

  TopoDS_Shape myShape;
  bool         myIsDone;
};

