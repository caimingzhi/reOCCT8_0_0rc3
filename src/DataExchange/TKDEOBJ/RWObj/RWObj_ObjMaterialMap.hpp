#pragma once


#include <NCollection_DataMap.hpp>
#include <RWMesh_MaterialMap.hpp>

//! Material MTL file writer for OBJ export.
class RWObj_ObjMaterialMap : public RWMesh_MaterialMap
{
  DEFINE_STANDARD_RTTIEXT(RWObj_ObjMaterialMap, RWMesh_MaterialMap)
public:
  //! Main constructor.
  Standard_EXPORT RWObj_ObjMaterialMap(const TCollection_AsciiString& theFile);

  //! Destructor, will emit error message if file was not closed.
  Standard_EXPORT ~RWObj_ObjMaterialMap() override;

  //! Add material
  Standard_EXPORT TCollection_AsciiString AddMaterial(const XCAFPrs_Style& theStyle) override;

  //! Virtual method actually defining the material (e.g. export to the file).
  Standard_EXPORT void DefineMaterial(const XCAFPrs_Style&           theStyle,
                                      const TCollection_AsciiString& theKey,
                                      const TCollection_AsciiString& theName) override;

private:
  FILE*                                                                    myFile;
  NCollection_DataMap<occ::handle<Image_Texture>, TCollection_AsciiString> myImageMap;
};

