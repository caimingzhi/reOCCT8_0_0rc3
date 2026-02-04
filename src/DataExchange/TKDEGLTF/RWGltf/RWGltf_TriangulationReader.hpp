#pragma once


#include <RWMesh_TriangulationReader.hpp>
#include <RWGltf_GltfAccessor.hpp>
#include <RWGltf_GltfArrayType.hpp>

class RWGltf_GltfLatePrimitiveArray;
class RWGltf_GltfPrimArrayData;

//! RWMesh_TriangulationReader implementation creating Poly_Triangulation.
class RWGltf_TriangulationReader : public RWMesh_TriangulationReader
{
  DEFINE_STANDARD_RTTIEXT(RWGltf_TriangulationReader, RWMesh_TriangulationReader)
public:
  //! Empty constructor.
  Standard_EXPORT RWGltf_TriangulationReader();

  //! Loads only primitive arrays saved as stream buffer
  //! (it is primarily glTF data encoded in base64 saved to temporary buffer during glTF file
  //! reading).
  Standard_EXPORT bool LoadStreamData(const occ::handle<RWMesh_TriangulationSource>& theSourceMesh,
                                      const occ::handle<Poly_Triangulation>& theDestMesh) const;

  //! Fills triangulation, lines and points data.
  //! @param theSourceGltfMesh source glTF triangulation
  //! @param theDestMesh       triangulation to be modified
  //! @param theStream         input stream to read from
  //! @param theAccessor       buffer accessor
  //! @param theType           array type
  //! @return FALSE on error
  Standard_EXPORT bool ReadStream(const occ::handle<RWGltf_GltfLatePrimitiveArray>& theSourceMesh,
                                  const occ::handle<Poly_Triangulation>&            theDestMesh,
                                  std::istream&                                     theStream,
                                  const RWGltf_GltfAccessor&                        theAccessor,
                                  RWGltf_GltfArrayType                              theType) const;

protected:
  //! Reports error.
  Standard_EXPORT virtual void reportError(const TCollection_AsciiString& theText) const;

  //! Loads only primitive arrays from file data.
  //! @param theSourceMesh    source triangulation
  //! @param theDestMesh      triangulation to be modified
  //! @param theFileSystem    shared file system to read from
  //! Note: this method skips "stream data" that should be loaded by LoadStreamData() call.
  Standard_EXPORT bool load(const occ::handle<RWMesh_TriangulationSource>& theSourceMesh,
                            const occ::handle<Poly_Triangulation>&         theDestMesh,
                            const occ::handle<OSD_FileSystem>& theFileSystem) const override;

  //! Performs additional actions to finalize data loading.
  //! @param theSourceMesh source triangulation
  //! @param theDestMesh   triangulation to be modified
  Standard_EXPORT bool finalizeLoading(
    const occ::handle<RWMesh_TriangulationSource>& theSourceMesh,
    const occ::handle<Poly_Triangulation>&         theDestMesh) const override;

  //! Loads only primitive arrays saved as stream buffer
  //! (it is primarily glTF data encoded in base64 saved to temporary buffer during glTF file
  //! reading).
  //! @param theSourceMesh    source triangulation
  //! @param theDestMesh      triangulation to be modified
  //! @param theToResetStream if TRUE reset input stream data buffer after its loading.
  Standard_EXPORT bool loadStreamData(const occ::handle<RWMesh_TriangulationSource>& theSourceMesh,
                                      const occ::handle<Poly_Triangulation>&         theDestMesh,
                                      bool theToResetStream = true) const;

  //! Reads primitive array from stream data.
  //! @param theSourceGltfMesh source glTF triangulation
  //! @param theGltfData       primitive array element (stream data should not be NULL)
  //! @param theDestMesh       triangulation to be modified
  Standard_EXPORT bool readStreamData(
    const occ::handle<RWGltf_GltfLatePrimitiveArray>& theSourceGltfMesh,
    const RWGltf_GltfPrimArrayData&                   theGltfData,
    const occ::handle<Poly_Triangulation>&            theDestMesh) const;

  //! Reads primitive array from file data.
  //! @param theSourceGltfMesh source glTF triangulation
  //! @param theGltfData       primitive array element (Uri of file stream should not be empty)
  //! @param theDestMesh       triangulation to be modified
  //! @param theFileSystem     shared file system to read from
  Standard_EXPORT bool readFileData(
    const occ::handle<RWGltf_GltfLatePrimitiveArray>& theSourceGltfMesh,
    const RWGltf_GltfPrimArrayData&                   theGltfData,
    const occ::handle<Poly_Triangulation>&            theDestMesh,
    const occ::handle<OSD_FileSystem>&                theFileSystem) const;

  //! Fills triangulation data and ignore non-triangulation primitives.
  //! @param theSourceGltfMesh source glTF triangulation
  //! @param theDestMesh       triangulation to be modified
  //! @param theStream         input stream to read from
  //! @param theAccessor       buffer accessor
  //! @param theType           array type
  //! @return FALSE on error
  Standard_EXPORT virtual bool readBuffer(
    const occ::handle<RWGltf_GltfLatePrimitiveArray>& theSourceGltfMesh,
    const occ::handle<Poly_Triangulation>&            theDestMesh,
    std::istream&                                     theStream,
    const RWGltf_GltfAccessor&                        theAccessor,
    RWGltf_GltfArrayType                              theType) const;

  //! Reads primitive array from file data compressed in Draco format.
  //! @param theSourceGltfMesh source glTF triangulation
  //! @param theGltfData       primitive array element (Uri of file stream should not be empty)
  //! @param theDestMesh       triangulation to be modified
  //! @param theFileSystem     shared file system to read from
  Standard_EXPORT virtual bool readDracoBuffer(
    const occ::handle<RWGltf_GltfLatePrimitiveArray>& theSourceGltfMesh,
    const RWGltf_GltfPrimArrayData&                   theGltfData,
    const occ::handle<Poly_Triangulation>&            theDestMesh,
    const occ::handle<OSD_FileSystem>&                theFileSystem) const;

protected:
  occ::handle<RWMesh_TriangulationSource> myTriangulation;
};

