#pragma once

#include <NCollection_DoubleMap.hpp>
#include <NCollection_Map.hpp>
#include <XCAFPrs_Style.hpp>

class RWMesh_MaterialMap : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(RWMesh_MaterialMap, Standard_Transient)
public:
  Standard_EXPORT RWMesh_MaterialMap(const TCollection_AsciiString& theFile);

  Standard_EXPORT ~RWMesh_MaterialMap() override;

  const XCAFPrs_Style& DefaultStyle() const { return myDefaultStyle; }

  void SetDefaultStyle(const XCAFPrs_Style& theStyle) { myDefaultStyle = theStyle; }

  TCollection_AsciiString FindMaterial(const XCAFPrs_Style& theStyle) const
  {
    if (myStyles.IsBound1(theStyle))
    {
      return myStyles.Find1(theStyle);
    }
    return TCollection_AsciiString();
  }

  Standard_EXPORT virtual TCollection_AsciiString AddMaterial(const XCAFPrs_Style& theStyle);

  Standard_EXPORT virtual bool CreateTextureFolder();

  Standard_EXPORT virtual bool CopyTexture(TCollection_AsciiString&          theResTexture,
                                           const occ::handle<Image_Texture>& theTexture,
                                           const TCollection_AsciiString&    theKey);

  virtual void DefineMaterial(const XCAFPrs_Style&           theStyle,
                              const TCollection_AsciiString& theKey,
                              const TCollection_AsciiString& theName) = 0;

  bool IsFailed() const { return myIsFailed; }

protected:
  Standard_EXPORT static bool copyFileTo(const TCollection_AsciiString& theFileSrc,
                                         const TCollection_AsciiString& theFileDst);

protected:
  TCollection_AsciiString                                       myFolder;
  TCollection_AsciiString                                       myTexFolder;
  TCollection_AsciiString                                       myTexFolderShort;
  TCollection_AsciiString                                       myFileName;
  TCollection_AsciiString                                       myShortFileNameBase;
  TCollection_AsciiString                                       myKeyPrefix;
  NCollection_DoubleMap<XCAFPrs_Style, TCollection_AsciiString> myStyles;
  NCollection_Map<occ::handle<Image_Texture>>                   myImageFailMap;

  XCAFPrs_Style myDefaultStyle;

  int  myNbMaterials;
  bool myIsFailed;
  bool myMatNameAsKey;
};
