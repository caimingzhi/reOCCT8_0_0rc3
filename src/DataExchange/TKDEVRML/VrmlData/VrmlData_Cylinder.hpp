#pragma once

#include <VrmlData_Geometry.hpp>

class VrmlData_Cylinder : public VrmlData_Geometry
{
public:
  inline VrmlData_Cylinder()
      : myRadius(1.),
        myHeight(2.),
        myHasBottom(true),
        myHasSide(true),
        myHasTop(true)
  {
  }

  inline VrmlData_Cylinder(const VrmlData_Scene& theScene,
                           const char*           theName,
                           const double          theRadius = 1.,
                           const double          theHeight = 2.)
      : VrmlData_Geometry(theScene, theName),
        myRadius(theRadius),
        myHeight(theHeight),
        myHasBottom(true),
        myHasSide(true),
        myHasTop(true)
  {
  }

  inline double Radius() const { return myRadius; }

  inline double Height() const { return myHeight; }

  inline bool HasBottom() const { return myHasBottom; }

  inline bool HasSide() const { return myHasSide; }

  inline bool HasTop() const { return myHasTop; }

  inline void SetRadius(const double theRadius)
  {
    myRadius = theRadius;
    SetModified();
  }

  inline void SetHeight(const double theHeight)
  {
    myHeight = theHeight;
    SetModified();
  }

  inline void SetFaces(const bool hasBottom, const bool hasSide, const bool hasTop)
  {
    myHasBottom = hasBottom;
    myHasSide   = hasSide;
    myHasTop    = hasTop;
    SetModified();
  }

  Standard_EXPORT const occ::handle<TopoDS_TShape>& TShape() override;

  Standard_EXPORT occ::handle<VrmlData_Node> Clone(
    const occ::handle<VrmlData_Node>& theOther) const override;

  Standard_EXPORT VrmlData_ErrorStatus Read(VrmlData_InBuffer& theBuffer) override;

  Standard_EXPORT VrmlData_ErrorStatus Write(const char* thePrefix) const override;

private:
  double myRadius;
  double myHeight;
  bool   myHasBottom : 1;
  bool   myHasSide : 1;
  bool   myHasTop : 1;

public:
  DEFINE_STANDARD_RTTI_INLINE(VrmlData_Cylinder, VrmlData_Geometry)
};
