#pragma once

#include <VrmlData_Appearance.hpp>
#include <VrmlData_Geometry.hpp>

class VrmlData_ShapeNode : public VrmlData_Node
{
public:
  inline VrmlData_ShapeNode() = default;

  inline VrmlData_ShapeNode(const VrmlData_Scene& theScene, const char* theName)
      : VrmlData_Node(theScene, theName)
  {
  }

  inline const occ::handle<VrmlData_Appearance>& Appearance() const { return myAppearance; }

  inline const occ::handle<VrmlData_Geometry>& Geometry() const { return myGeometry; }

  inline void SetAppearance(const occ::handle<VrmlData_Appearance>& theAppear)
  {
    myAppearance = theAppear;
  }

  inline void SetGeometry(const occ::handle<VrmlData_Geometry>& theGeometry)
  {
    myGeometry = theGeometry;
  }

  Standard_EXPORT occ::handle<VrmlData_Node> Clone(
    const occ::handle<VrmlData_Node>& theOther) const override;

  Standard_EXPORT VrmlData_ErrorStatus Read(VrmlData_InBuffer& theBuffer) override;

  Standard_EXPORT VrmlData_ErrorStatus Write(const char* thePrefix) const override;

  Standard_EXPORT bool IsDefault() const override;

private:
  occ::handle<VrmlData_Appearance> myAppearance;
  occ::handle<VrmlData_Geometry>   myGeometry;

public:
  DEFINE_STANDARD_RTTI_INLINE(VrmlData_ShapeNode, VrmlData_Node)
};
