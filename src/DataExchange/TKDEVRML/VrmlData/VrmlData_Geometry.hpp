#pragma once

#include <VrmlData_Node.hpp>
#include <TopoDS_TShape.hpp>

class VrmlData_Geometry : public VrmlData_Node
{
public:
  inline VrmlData_Geometry()
      : myIsModified(true)
  {
  }

  inline VrmlData_Geometry(const VrmlData_Scene& theScene, const char* theName)
      : VrmlData_Node(theScene, theName),
        myIsModified(true)
  {
  }

  Standard_EXPORT virtual const occ::handle<TopoDS_TShape>& TShape() = 0;

protected:
  inline void SetTShape(const occ::handle<TopoDS_TShape>& theTShape) { myTShape = theTShape; }

  inline void SetModified() { myIsModified = true; }

protected:
  occ::handle<TopoDS_TShape> myTShape;
  bool                       myIsModified;

public:
  DEFINE_STANDARD_RTTIEXT(VrmlData_Geometry, VrmlData_Node)
};
