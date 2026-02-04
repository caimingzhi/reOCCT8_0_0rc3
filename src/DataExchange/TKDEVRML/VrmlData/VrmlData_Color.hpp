#pragma once


#include <VrmlData_ArrayVec3d.hpp>
#include <Quantity_Color.hpp>
#include <gp_XYZ.hpp>

/**
 *  Implementation of the node Color
 */
class VrmlData_Color : public VrmlData_ArrayVec3d
{
public:
  // ---------- PUBLIC METHODS ----------

  /**
   * Empty constructor.
   */
  inline VrmlData_Color() = default;

  /**
   * Constructor.
   */
  inline VrmlData_Color(const VrmlData_Scene& theScene,
                        const char*           theName,
                        const size_t          nColors   = 0,
                        const gp_XYZ*         arrColors = nullptr)
      : VrmlData_ArrayVec3d(theScene, theName, nColors, arrColors)
  {
  }

  /**
   * Query one color
   * @param i
   *   index in the array of colors [0 .. N-1]
   * @return
   *   the color value for the index. If index irrelevant, returns (0., 0., 0.)
   */
  inline const Quantity_Color Color(const int i) const
  {
    return Quantity_Color(Value(i).X(), Value(i).Y(), Value(i).Z(), Quantity_TOC_sRGB);
  }

  /**
   * Set the array data
   */
  inline void SetColors(const size_t nColors, const gp_XYZ* arrColors)
  {
    myLength = nColors;
    myArray  = arrColors;
  }

  /**
   * Create a copy of this node.
   * If the parameter is null, a new copied node is created. Otherwise new node
   * is not created, but rather the given one is modified.<p>
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
  DEFINE_STANDARD_RTTI_INLINE(VrmlData_Color, VrmlData_ArrayVec3d)
};

// Definition of HANDLE object using Standard_DefineHandle.hpp
