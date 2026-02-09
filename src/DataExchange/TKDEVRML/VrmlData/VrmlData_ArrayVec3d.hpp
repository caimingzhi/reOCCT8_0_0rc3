#pragma once

#include <VrmlData_Node.hpp>
class gp_XYZ;

class VrmlData_ArrayVec3d : public VrmlData_Node
{
public:
  inline VrmlData_ArrayVec3d()
      : myArray(nullptr),
        myLength(0)
  {
  }

  inline VrmlData_ArrayVec3d(const VrmlData_Scene& theScene,
                             const char*           theName,
                             const size_t          nVec,
                             const gp_XYZ*         arrVec)
      : VrmlData_Node(theScene, theName),
        myArray(arrVec),
        myLength(nVec)
  {
  }

  inline size_t Length() const { return myLength; }

  inline const gp_XYZ* Values() const { return myArray; }

  Standard_EXPORT bool AllocateValues(const size_t theLength);

  inline void SetValues(const size_t nValues, const gp_XYZ* arrValues)
  {
    myLength = nValues;
    myArray  = arrValues;
  }

  Standard_EXPORT VrmlData_ErrorStatus ReadArray(VrmlData_InBuffer& theBuffer,
                                                 const char*        theName,
                                                 const bool         isScale);

  Standard_EXPORT VrmlData_ErrorStatus WriteArray(const char* theName, const bool isScale) const;

  Standard_EXPORT bool IsDefault() const override;

protected:
  Standard_EXPORT const gp_XYZ& Value(const size_t i) const;

protected:
  const gp_XYZ* myArray;
  size_t        myLength;

public:
  DEFINE_STANDARD_RTTI_INLINE(VrmlData_ArrayVec3d, VrmlData_Node)
};
