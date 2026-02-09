#pragma once

#include <VrmlData_Material.hpp>
#include <VrmlData_Texture.hpp>
#include <VrmlData_TextureTransform.hpp>

class VrmlData_Appearance : public VrmlData_Node
{
public:
  inline VrmlData_Appearance() = default;

  inline VrmlData_Appearance(const VrmlData_Scene& theScene, const char* theName)
      : VrmlData_Node(theScene, theName)
  {
  }

  inline const occ::handle<VrmlData_Material>& Material() const { return myMaterial; }

  inline const occ::handle<VrmlData_Texture>& Texture() const { return myTexture; }

  inline const occ::handle<VrmlData_TextureTransform>& TextureTransform() const
  {
    return myTTransform;
  }

  inline void SetMaterial(const occ::handle<VrmlData_Material>& theMat) { myMaterial = theMat; }

  inline void SetTexture(const occ::handle<VrmlData_Texture>& theTexture)
  {
    myTexture = theTexture;
  }

  inline void SetTextureTransform(const occ::handle<VrmlData_TextureTransform>& theTT)
  {
    myTTransform = theTT;
  }

  Standard_EXPORT occ::handle<VrmlData_Node> Clone(
    const occ::handle<VrmlData_Node>&) const override;

  Standard_EXPORT VrmlData_ErrorStatus Read(VrmlData_InBuffer& theBuffer) override;

  Standard_EXPORT VrmlData_ErrorStatus Write(const char* thePrefix) const override;

  Standard_EXPORT bool IsDefault() const override;

private:
  occ::handle<VrmlData_Material>         myMaterial;
  occ::handle<VrmlData_Texture>          myTexture;
  occ::handle<VrmlData_TextureTransform> myTTransform;

public:
  DEFINE_STANDARD_RTTI_INLINE(VrmlData_Appearance, VrmlData_Node)
};
