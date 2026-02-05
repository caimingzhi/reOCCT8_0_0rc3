#pragma once

#include <VrmlData_Geometry.hpp>

/**
 *  Implementation of the Sphere node.
 */
class VrmlData_Sphere : public VrmlData_Geometry
{
public:
  // ---------- PUBLIC METHODS ----------

  /**
   * Empty constructor
   */
  inline VrmlData_Sphere()
      : myRadius(1.)
  {
  }

  /**
   * Constructor
   */
  inline VrmlData_Sphere(const VrmlData_Scene& theScene,
                         const char*           theName,
                         const double          theRadius = 1.)
      : VrmlData_Geometry(theScene, theName),
        myRadius(theRadius)
  {
  }

  /**
   * Query the sphere radius
   */
  inline double Radius() const { return myRadius; }

  /**
   * Set the sphere radius
   */
  inline void SetRadius(const double theRadius)
  {
    myRadius = theRadius;
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

  double myRadius;

public:
  // Declaration of CASCADE RTTI
  DEFINE_STANDARD_RTTI_INLINE(VrmlData_Sphere, VrmlData_Geometry)
};

// Definition of HANDLE object using Standard_DefineHandle.hpp
