#pragma once

#include <VrmlData_Node.hpp>
#include <TopoDS_TShape.hpp>

/**
 *  Implementation of the Geometry node.
 *  Contains the topological representation (TopoDS_Shell) of the VRML geometry
 */

class VrmlData_Geometry : public VrmlData_Node
{
public:
  // ---------- PUBLIC METHODS ----------

  /**
   * Empty constructor
   */
  inline VrmlData_Geometry()
      : myIsModified(true)
  {
  }

  /**
   * Constructor
   */
  inline VrmlData_Geometry(const VrmlData_Scene& theScene, const char* theName)
      : VrmlData_Node(theScene, theName),
        myIsModified(true)
  {
  }

  /**
   * Query the shape. This method checks the flag myIsModified; if True it
   * should rebuild the shape presentation.
   */
  Standard_EXPORT virtual const occ::handle<TopoDS_TShape>& TShape() = 0;

protected:
  // ---------- PROTECTED METHODS ----------

  /**
   * Set the TShape.
   */
  inline void SetTShape(const occ::handle<TopoDS_TShape>& theTShape) { myTShape = theTShape; }

  /**
   * Mark modification
   */
  inline void SetModified() { myIsModified = true; }

protected:
  // ---------- PROTECTED FIELDS ----------

  occ::handle<TopoDS_TShape> myTShape;
  bool                       myIsModified;

public:
  // Declaration of CASCADE RTTI
  DEFINE_STANDARD_RTTIEXT(VrmlData_Geometry, VrmlData_Node)
};

// Definition of HANDLE object using Standard_DefineHandle.hpp
