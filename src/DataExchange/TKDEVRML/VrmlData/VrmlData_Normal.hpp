#pragma once

#include <VrmlData_ArrayVec3d.hpp>

/**
 *  Implementation of the node Normal
 */
class VrmlData_Normal : public VrmlData_ArrayVec3d
{
public:
  // ---------- PUBLIC METHODS ----------

  /**
   * Empty constructor
   */
  inline VrmlData_Normal() = default;

  /**
   * Constructor
   */
  inline VrmlData_Normal(const VrmlData_Scene& theScene,
                         const char*           theName,
                         const size_t          nVec   = 0,
                         const gp_XYZ*         arrVec = nullptr)
      : VrmlData_ArrayVec3d(theScene, theName, nVec, arrVec)
  {
  }

  /**
   * Query one normal
   * @param i
   *   index in the array of normals [0 .. N-1]
   * @return
   *   the normal value for the index. If index irrelevant, returns (0., 0., 0.)
   */
  inline const gp_XYZ& Normal(const int i) const { return Value(i); }

  /**
   * Create a copy of this node.
   * If the parameter is null, a new copied node is created. Otherwise new node
   * is not created, but rather the given one is modified.
   */
  Standard_EXPORT occ::handle<VrmlData_Node> Clone(
    const occ::handle<VrmlData_Node>& theOther) const override;

  /**
   * Read the Node from input stream.
   */
  Standard_EXPORT VrmlData_ErrorStatus Read(VrmlData_InBuffer& theBuffer) override;

  /**
   * Write the Node to the Scene output.
   */
  Standard_EXPORT VrmlData_ErrorStatus Write(const char* thePrefix) const override;

public:
  // Declaration of CASCADE RTTI
  DEFINE_STANDARD_RTTI_INLINE(VrmlData_Normal, VrmlData_ArrayVec3d)
};

// Definition of HANDLE object using Standard_DefineHandle.hpp
