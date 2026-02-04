#pragma once


#include <VrmlData_Geometry.hpp>
#include <gp_XYZ.hpp>

/**
 *  Implementation of the Box node.
 *  This node is defined by Size vector, assuming that the box center is located
 *  in (0., 0., 0.) and that each corner is 0.5*|Size| distance from the center.
 */
class VrmlData_Box : public VrmlData_Geometry
{
public:
  // ---------- PUBLIC METHODS ----------

  /**
   * Empty constructor
   */
  inline VrmlData_Box()
      : mySize(2., 2., 2.)
  {
  }

  /**
   * Constructor
   */
  inline VrmlData_Box(const VrmlData_Scene& theScene,
                      const char*           theName,
                      const double          sizeX = 2.,
                      const double          sizeY = 2.,
                      const double          sizeZ = 2.)
      : VrmlData_Geometry(theScene, theName),
        mySize(sizeX, sizeY, sizeZ)
  {
  }

  /**
   * Query the Box size
   */
  inline const gp_XYZ& Size() const { return mySize; }

  /**
   * Set the Box Size
   */
  inline void SetSize(const gp_XYZ& theSize)
  {
    mySize = theSize;
    SetModified();
  }

  /**
   * Query the primitive topology. This method returns a Null shape if there
   * is an internal error during the primitive creation (zero radius, etc.)
   */
  Standard_EXPORT const occ::handle<TopoDS_TShape>& TShape() override;

  /**
   * Create a copy of this node.
   * If the parameter is null, a new copied node is created. Otherwise new node
   * is not created, but rather the given one is modified.
   */
  Standard_EXPORT occ::handle<VrmlData_Node> Clone(
    const occ::handle<VrmlData_Node>& theOther) const override;

  /**
   * Fill the Node internal data from the given input stream.
   */
  Standard_EXPORT VrmlData_ErrorStatus Read(VrmlData_InBuffer& theBuffer) override;

  /**
   * Write the Node to output stream.
   */
  Standard_EXPORT VrmlData_ErrorStatus Write(const char* thePrefix) const override;

private:
  // ---------- PRIVATE FIELDS ----------

  gp_XYZ mySize;

public:
  // Declaration of CASCADE RTTI
  DEFINE_STANDARD_RTTI_INLINE(VrmlData_Box, VrmlData_Geometry)
};

// Definition of HANDLE object using Standard_DefineHandle.hpp
