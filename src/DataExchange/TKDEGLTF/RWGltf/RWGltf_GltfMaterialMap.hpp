#pragma once

#include <RWMesh_MaterialMap.hpp>
#include <RWGltf_GltfBufferView.hpp>

class RWGltf_GltfOStreamWriter;

class RWGltf_GltfMaterialMap : public RWMesh_MaterialMap
{
  DEFINE_STANDARD_RTTIEXT(RWGltf_GltfMaterialMap, RWMesh_MaterialMap)
public:
  Standard_EXPORT RWGltf_GltfMaterialMap(const TCollection_AsciiString& theFile,
                                         const int                      theDefSamplerId);

  Standard_EXPORT ~RWGltf_GltfMaterialMap() override;

public:
  Standard_EXPORT void AddGlbImages(std::ostream& theBinFile, const XCAFPrs_Style& theStyle);

  Standard_EXPORT void FlushGlbBufferViews(RWGltf_GltfOStreamWriter* theWriter,
                                           const int                 theBinDataBufferId,
                                           int&                      theBuffViewId);

  Standard_EXPORT void FlushGlbImages(RWGltf_GltfOStreamWriter* theWriter);

public:
  Standard_EXPORT void AddImages(RWGltf_GltfOStreamWriter* theWriter,
                                 const XCAFPrs_Style&      theStyle,
                                 bool&                     theIsStarted);

  Standard_EXPORT void AddMaterial(RWGltf_GltfOStreamWriter* theWriter,
                                   const XCAFPrs_Style&      theStyle,
                                   bool&                     theIsStarted);

  Standard_EXPORT void AddTextures(RWGltf_GltfOStreamWriter* theWriter,
                                   const XCAFPrs_Style&      theStyle,
                                   bool&                     theIsStarted);

  int NbImages() const { return myImageMap.Extent(); }

  int NbTextures() const { return myTextureMap.Extent(); }

public:
  Standard_EXPORT static const occ::handle<Image_Texture>& baseColorTexture(
    const occ::handle<XCAFDoc_VisMaterial>& theMat);

protected:
  Standard_EXPORT void addImage(RWGltf_GltfOStreamWriter*         theWriter,
                                const occ::handle<Image_Texture>& theTexture,
                                bool&                             theIsStarted);

  Standard_EXPORT void addGlbImage(std::ostream&                     theBinFile,
                                   const occ::handle<Image_Texture>& theTexture);

  Standard_EXPORT void addTexture(RWGltf_GltfOStreamWriter*         theWriter,
                                  const occ::handle<Image_Texture>& theTexture,
                                  bool&                             theIsStarted);

  Standard_EXPORT TCollection_AsciiString AddMaterial(const XCAFPrs_Style& theStyle) override;

  Standard_EXPORT void DefineMaterial(const XCAFPrs_Style&           theStyle,
                                      const TCollection_AsciiString& theKey,
                                      const TCollection_AsciiString& theName) override;

protected:
  RWGltf_GltfOStreamWriter*                                                     myWriter;
  NCollection_IndexedDataMap<occ::handle<Image_Texture>, RWGltf_GltfBufferView> myImageMap;
  NCollection_Map<occ::handle<Image_Texture>>                                   myTextureMap;

  int myDefSamplerId;
};
