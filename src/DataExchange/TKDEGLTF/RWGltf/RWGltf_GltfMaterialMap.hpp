#pragma once


#include <RWMesh_MaterialMap.hpp>
#include <RWGltf_GltfBufferView.hpp>

class RWGltf_GltfOStreamWriter;

//! Material manager for exporting into glTF format.
class RWGltf_GltfMaterialMap : public RWMesh_MaterialMap
{
  DEFINE_STANDARD_RTTIEXT(RWGltf_GltfMaterialMap, RWMesh_MaterialMap)
public:
  //! Main constructor.
  Standard_EXPORT RWGltf_GltfMaterialMap(const TCollection_AsciiString& theFile,
                                         const int                      theDefSamplerId);

  //! Destructor.
  Standard_EXPORT ~RWGltf_GltfMaterialMap() override;

public:
  //! Add material images into GLB stream.
  //! @param[in][out] theBinFile   output file stream
  //! @param[in] theStyle    material images to add
  Standard_EXPORT void AddGlbImages(std::ostream& theBinFile, const XCAFPrs_Style& theStyle);

  //! Add bufferView's into RWGltf_GltfRootElement_BufferViews section with images collected by
  //! AddImagesToGlb().
  Standard_EXPORT void FlushGlbBufferViews(RWGltf_GltfOStreamWriter* theWriter,
                                           const int                 theBinDataBufferId,
                                           int&                      theBuffViewId);

  //! Write RWGltf_GltfRootElement_Images section with images collected by AddImagesToGlb().
  Standard_EXPORT void FlushGlbImages(RWGltf_GltfOStreamWriter* theWriter);

public:
  //! Add material images in case of non-GLB file
  //! (an alternative to AddImagesToGlb() + FlushBufferViews() + FlushImagesGlb()).
  Standard_EXPORT void AddImages(RWGltf_GltfOStreamWriter* theWriter,
                                 const XCAFPrs_Style&      theStyle,
                                 bool&                     theIsStarted);

  //! Add material.
  Standard_EXPORT void AddMaterial(RWGltf_GltfOStreamWriter* theWriter,
                                   const XCAFPrs_Style&      theStyle,
                                   bool&                     theIsStarted);
  //! Add material textures.
  Standard_EXPORT void AddTextures(RWGltf_GltfOStreamWriter* theWriter,
                                   const XCAFPrs_Style&      theStyle,
                                   bool&                     theIsStarted);

  //! Return extent of images map.
  int NbImages() const { return myImageMap.Extent(); }

  //! Return extent of textures map.
  int NbTextures() const { return myTextureMap.Extent(); }

public:
  //! Return base color texture.
  Standard_EXPORT static const occ::handle<Image_Texture>& baseColorTexture(
    const occ::handle<XCAFDoc_VisMaterial>& theMat);

protected:
  //! Add texture image.
  Standard_EXPORT void addImage(RWGltf_GltfOStreamWriter*         theWriter,
                                const occ::handle<Image_Texture>& theTexture,
                                bool&                             theIsStarted);

  //! Add texture image into GLB stream.
  //! @param[in][out] theBinFile   output file stream
  //! @param[in] theTexture  texture image to add
  Standard_EXPORT void addGlbImage(std::ostream&                     theBinFile,
                                   const occ::handle<Image_Texture>& theTexture);

  //! Add texture.
  Standard_EXPORT void addTexture(RWGltf_GltfOStreamWriter*         theWriter,
                                  const occ::handle<Image_Texture>& theTexture,
                                  bool&                             theIsStarted);

  //! Add material
  Standard_EXPORT TCollection_AsciiString AddMaterial(const XCAFPrs_Style& theStyle) override;

  //! Virtual method actually defining the material (e.g. export to the file).
  Standard_EXPORT void DefineMaterial(const XCAFPrs_Style&           theStyle,
                                      const TCollection_AsciiString& theKey,
                                      const TCollection_AsciiString& theName) override;

protected:
  RWGltf_GltfOStreamWriter*                                                     myWriter;
  NCollection_IndexedDataMap<occ::handle<Image_Texture>, RWGltf_GltfBufferView> myImageMap;
  NCollection_Map<occ::handle<Image_Texture>>                                   myTextureMap;

  int myDefSamplerId;
};

