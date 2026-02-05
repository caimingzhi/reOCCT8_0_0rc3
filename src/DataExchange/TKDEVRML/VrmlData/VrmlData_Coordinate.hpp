#pragma once

#include <VrmlData_ArrayVec3d.hpp>

/**
 *  Implementation of the node Coordinate
 */
class VrmlData_Coordinate : public VrmlData_ArrayVec3d
{
public:
  // ---------- PUBLIC METHODS ----------

  /**
   * Empty Constructor
   */
  inline VrmlData_Coordinate() = default;

  /**
   * Constructor
   */
  inline VrmlData_Coordinate(const VrmlData_Scene& theScene,
                             const char*           theName,
                             const size_t          nPoints   = 0,
                             const gp_XYZ*         arrPoints = nullptr)
      : VrmlData_ArrayVec3d(theScene, theName, nPoints, arrPoints)
  {
  }

  /**
   * Query one point
   * @param i
   *   index in the array of points [0 .. N-1]
   * @return
   *   the coordinate for the index. If index irrelevant, returns (0., 0., 0.)
   */
  inline const gp_XYZ& Coordinate(const int i) const { return Value(i); }

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
  DEFINE_STANDARD_RTTI_INLINE(VrmlData_Coordinate, VrmlData_ArrayVec3d)
};

// Definition of HANDLE object using Standard_DefineHandle.hpp
