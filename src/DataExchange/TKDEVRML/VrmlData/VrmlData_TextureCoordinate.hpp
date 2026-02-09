#pragma once

#include <VrmlData_Node.hpp>
class gp_XY;

class VrmlData_TextureCoordinate : public VrmlData_Node
{
public:
  inline VrmlData_TextureCoordinate()
      : myPoints(nullptr),
        myLength(0)
  {
  }

  inline VrmlData_TextureCoordinate(const VrmlData_Scene& theScene,
                                    const char*           theName,
                                    const size_t          nPoints   = 0,
                                    const gp_XY*          arrPoints = nullptr)
      : VrmlData_Node(theScene, theName),
        myPoints(arrPoints),
        myLength(nPoints)
  {
  }

  Standard_EXPORT bool AllocateValues(const size_t theLength);

  inline size_t Length() { return myLength; }

  inline const gp_XY* Points() { return myPoints; }

  inline void SetPoints(const size_t nPoints, const gp_XY* arrPoints)
  {
    myPoints = arrPoints;
    myLength = nPoints;
  }

  Standard_EXPORT occ::handle<VrmlData_Node> Clone(
    const occ::handle<VrmlData_Node>& theOther) const override;

  Standard_EXPORT VrmlData_ErrorStatus Read(VrmlData_InBuffer& theBuffer) override;

private:
  const gp_XY* myPoints;
  size_t       myLength;

public:
  DEFINE_STANDARD_RTTI_INLINE(VrmlData_TextureCoordinate, VrmlData_Node)
};
