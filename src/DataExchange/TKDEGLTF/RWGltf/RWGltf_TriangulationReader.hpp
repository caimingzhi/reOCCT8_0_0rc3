#pragma once

#include <RWMesh_TriangulationReader.hpp>
#include <RWGltf_GltfAccessor.hpp>
#include <RWGltf_GltfArrayType.hpp>

class RWGltf_GltfLatePrimitiveArray;
class RWGltf_GltfPrimArrayData;

class RWGltf_TriangulationReader : public RWMesh_TriangulationReader
{
  DEFINE_STANDARD_RTTIEXT(RWGltf_TriangulationReader, RWMesh_TriangulationReader)
public:
  Standard_EXPORT RWGltf_TriangulationReader();

  Standard_EXPORT bool LoadStreamData(const occ::handle<RWMesh_TriangulationSource>& theSourceMesh,
                                      const occ::handle<Poly_Triangulation>& theDestMesh) const;

  Standard_EXPORT bool ReadStream(const occ::handle<RWGltf_GltfLatePrimitiveArray>& theSourceMesh,
                                  const occ::handle<Poly_Triangulation>&            theDestMesh,
                                  std::istream&                                     theStream,
                                  const RWGltf_GltfAccessor&                        theAccessor,
                                  RWGltf_GltfArrayType                              theType) const;

protected:
  Standard_EXPORT virtual void reportError(const TCollection_AsciiString& theText) const;

  Standard_EXPORT bool load(const occ::handle<RWMesh_TriangulationSource>& theSourceMesh,
                            const occ::handle<Poly_Triangulation>&         theDestMesh,
                            const occ::handle<OSD_FileSystem>& theFileSystem) const override;

  Standard_EXPORT bool finalizeLoading(
    const occ::handle<RWMesh_TriangulationSource>& theSourceMesh,
    const occ::handle<Poly_Triangulation>&         theDestMesh) const override;

  Standard_EXPORT bool loadStreamData(const occ::handle<RWMesh_TriangulationSource>& theSourceMesh,
                                      const occ::handle<Poly_Triangulation>&         theDestMesh,
                                      bool theToResetStream = true) const;

  Standard_EXPORT bool readStreamData(
    const occ::handle<RWGltf_GltfLatePrimitiveArray>& theSourceGltfMesh,
    const RWGltf_GltfPrimArrayData&                   theGltfData,
    const occ::handle<Poly_Triangulation>&            theDestMesh) const;

  Standard_EXPORT bool readFileData(
    const occ::handle<RWGltf_GltfLatePrimitiveArray>& theSourceGltfMesh,
    const RWGltf_GltfPrimArrayData&                   theGltfData,
    const occ::handle<Poly_Triangulation>&            theDestMesh,
    const occ::handle<OSD_FileSystem>&                theFileSystem) const;

  Standard_EXPORT virtual bool readBuffer(
    const occ::handle<RWGltf_GltfLatePrimitiveArray>& theSourceGltfMesh,
    const occ::handle<Poly_Triangulation>&            theDestMesh,
    std::istream&                                     theStream,
    const RWGltf_GltfAccessor&                        theAccessor,
    RWGltf_GltfArrayType                              theType) const;

  Standard_EXPORT virtual bool readDracoBuffer(
    const occ::handle<RWGltf_GltfLatePrimitiveArray>& theSourceGltfMesh,
    const RWGltf_GltfPrimArrayData&                   theGltfData,
    const occ::handle<Poly_Triangulation>&            theDestMesh,
    const occ::handle<OSD_FileSystem>&                theFileSystem) const;

protected:
  occ::handle<RWMesh_TriangulationSource> myTriangulation;
};
