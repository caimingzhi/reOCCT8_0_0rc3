#pragma once


#include <VrmlData_Node.hpp>
class gp_XY;

/**
 *  Implementation of the node TextureCoordinate
 */
class VrmlData_TextureCoordinate : public VrmlData_Node
{
public:
  // ---------- PUBLIC METHODS ----------

  /**
   * Empty constructor
   */
  inline VrmlData_TextureCoordinate()
      : myPoints(nullptr),
        myLength(0)
  {
  }

  /**
   * Constructor
   */
  inline VrmlData_TextureCoordinate(const VrmlData_Scene& theScene,
                                    const char*           theName,
                                    const size_t          nPoints   = 0,
                                    const gp_XY*          arrPoints = nullptr)
      : VrmlData_Node(theScene, theName),
        myPoints(arrPoints),
        myLength(nPoints)
  {
  }

  /**
   * Create a data array and assign the field myArray.
   * @return
   *   True if allocation was successful.
   */
  Standard_EXPORT bool AllocateValues(const size_t theLength);

  /**
   * Query the number of points
   */
  inline size_t Length() { return myLength; }

  /**
   * Query the points
   */
  inline const gp_XY* Points() { return myPoints; }

  /**
   * Set the points array
   */
  inline void SetPoints(const size_t nPoints, const gp_XY* arrPoints)
  {
    myPoints = arrPoints;
    myLength = nPoints;
  }

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

private:
  // ---------- PRIVATE FIELDS ----------

  const gp_XY* myPoints;
  size_t       myLength;

public:
  // Declaration of CASCADE RTTI
  DEFINE_STANDARD_RTTI_INLINE(VrmlData_TextureCoordinate, VrmlData_Node)
};

// Definition of HANDLE object using Standard_DefineHandle.hpp
