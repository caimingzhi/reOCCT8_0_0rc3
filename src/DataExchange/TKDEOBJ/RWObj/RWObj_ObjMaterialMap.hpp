#pragma once

#include <NCollection_DataMap.hpp>
#include <RWMesh_MaterialMap.hpp>

class RWObj_ObjMaterialMap : public RWMesh_MaterialMap
{
  DEFINE_STANDARD_RTTIEXT(RWObj_ObjMaterialMap, RWMesh_MaterialMap)
public:
  Standard_EXPORT RWObj_ObjMaterialMap(const TCollection_AsciiString& theFile);

  Standard_EXPORT ~RWObj_ObjMaterialMap() override;

  Standard_EXPORT TCollection_AsciiString AddMaterial(const XCAFPrs_Style& theStyle) override;

  Standard_EXPORT void DefineMaterial(const XCAFPrs_Style&           theStyle,
                                      const TCollection_AsciiString& theKey,
                                      const TCollection_AsciiString& theName) override;

private:
  FILE*                                                                    myFile;
  NCollection_DataMap<occ::handle<Image_Texture>, TCollection_AsciiString> myImageMap;
};
