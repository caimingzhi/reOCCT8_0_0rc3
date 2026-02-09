#pragma once

#include <VrmlData_Texture.hpp>

class VrmlData_ImageTexture : public VrmlData_Texture
{
public:
  inline VrmlData_ImageTexture() = default;

  Standard_EXPORT VrmlData_ImageTexture(const VrmlData_Scene& theScene,
                                        const char*           theName,
                                        const char*           theURL  = nullptr,
                                        const bool            theRepS = false,
                                        const bool            theRepT = false);

  inline const NCollection_List<TCollection_AsciiString>& URL() const { return myURL; }

  Standard_EXPORT occ::handle<VrmlData_Node> Clone(
    const occ::handle<VrmlData_Node>& theOther) const override;

  Standard_EXPORT VrmlData_ErrorStatus Read(VrmlData_InBuffer& theBuffer) override;

  Standard_EXPORT VrmlData_ErrorStatus Write(const char* thePrefix) const override;

private:
  NCollection_List<TCollection_AsciiString> myURL;

public:
  DEFINE_STANDARD_RTTI_INLINE(VrmlData_ImageTexture, VrmlData_Texture)
};
