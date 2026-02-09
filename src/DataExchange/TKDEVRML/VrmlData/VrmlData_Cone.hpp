#pragma once

#include <VrmlData_Geometry.hpp>

class VrmlData_Cone : public VrmlData_Geometry
{
public:
  inline VrmlData_Cone()
      : myBottomRadius(1.),
        myHeight(2.),
        myHasSide(true),
        myHasBottom(true)
  {
  }

  inline VrmlData_Cone(const VrmlData_Scene& theScene,
                       const char*           theName,
                       const double          theBottomRadius = 1.,
                       const double          theHeight       = 2.)
      : VrmlData_Geometry(theScene, theName),
        myBottomRadius(theBottomRadius),
        myHeight(theHeight),
        myHasSide(true),
        myHasBottom(true)
  {
  }

  inline double BottomRadius() const { return myBottomRadius; }

  inline double Height() const { return myHeight; }

  inline bool HasBottom() const { return myHasBottom; }

  inline bool HasSide() const { return myHasSide; }

  inline void SetBottomRadius(const double theRadius)
  {
    myBottomRadius = theRadius;
    SetModified();
  }

  inline void SetHeight(const double theHeight)
  {
    myHeight = theHeight;
    SetModified();
  }

  inline void SetFaces(const bool hasBottom, const bool hasSide)
  {
    myHasBottom = hasBottom;
    myHasSide   = hasSide;
    SetModified();
  }

  Standard_EXPORT const occ::handle<TopoDS_TShape>& TShape() override;

  Standard_EXPORT occ::handle<VrmlData_Node> Clone(
    const occ::handle<VrmlData_Node>& theOther) const override;

  Standard_EXPORT VrmlData_ErrorStatus Read(VrmlData_InBuffer& theBuffer) override;

  Standard_EXPORT VrmlData_ErrorStatus Write(const char* thePrefix) const override;

private:
  double myBottomRadius;
  double myHeight;
  bool   myHasSide : 1;
  bool   myHasBottom : 1;

public:
  DEFINE_STANDARD_RTTI_INLINE(VrmlData_Cone, VrmlData_Geometry)
};
