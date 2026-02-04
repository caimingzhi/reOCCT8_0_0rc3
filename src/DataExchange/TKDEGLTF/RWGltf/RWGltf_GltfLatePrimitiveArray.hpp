#pragma once


#include <RWMesh_TriangulationSource.hpp>

#include <NCollection_Sequence.hpp>
#include <RWGltf_GltfArrayType.hpp>
#include <RWGltf_GltfPrimitiveMode.hpp>
#include <Quantity_ColorRGBA.hpp>

class RWGltf_GltfPrimArrayData;
class RWGltf_MaterialMetallicRoughness;
class RWGltf_MaterialCommon;

//! Mesh data wrapper for delayed primitive array loading from glTF file.
class RWGltf_GltfLatePrimitiveArray : public RWMesh_TriangulationSource
{
  DEFINE_STANDARD_RTTIEXT(RWGltf_GltfLatePrimitiveArray, RWMesh_TriangulationSource)
public:
  //! Constructor.
  Standard_EXPORT RWGltf_GltfLatePrimitiveArray(const TCollection_AsciiString& theId,
                                                const TCollection_AsciiString& theName);

  //! Destructor.
  Standard_EXPORT ~RWGltf_GltfLatePrimitiveArray() override;

  //! Entity id.
  const TCollection_AsciiString& Id() const { return myId; }

  //! Entity name.
  const TCollection_AsciiString& Name() const { return myName; }

  //! Assign entity name.
  void SetName(const TCollection_AsciiString& theName) { myName = theName; }

  //! Return type of primitive array.
  RWGltf_GltfPrimitiveMode PrimitiveMode() const { return myPrimMode; }

  //! Set type of primitive array.
  void SetPrimitiveMode(RWGltf_GltfPrimitiveMode theMode) { myPrimMode = theMode; }

  //! Return true if primitive array has assigned material
  bool HasStyle() const { return !myMaterialPbr.IsNull() || !myMaterialCommon.IsNull(); }

  //! Return base color.
  Standard_EXPORT Quantity_ColorRGBA BaseColor() const;

  //! Return PBR material definition.
  const occ::handle<RWGltf_MaterialMetallicRoughness>& MaterialPbr() const { return myMaterialPbr; }

  //! Set PBR material definition.
  void SetMaterialPbr(const occ::handle<RWGltf_MaterialMetallicRoughness>& theMat)
  {
    myMaterialPbr = theMat;
  }

  //! Return common (obsolete) material definition.
  const occ::handle<RWGltf_MaterialCommon>& MaterialCommon() const { return myMaterialCommon; }

  //! Set common (obsolete) material definition.
  void SetMaterialCommon(const occ::handle<RWGltf_MaterialCommon>& theMat)
  {
    myMaterialCommon = theMat;
  }

  //! Return primitive array data elements.
  const NCollection_Sequence<RWGltf_GltfPrimArrayData>& Data() const { return myData; }

  //! Add primitive array data element.
  Standard_EXPORT RWGltf_GltfPrimArrayData& AddPrimArrayData(RWGltf_GltfArrayType theType);

  //! Return TRUE if there is deferred storage and some triangulation data
  //! that can be loaded using LoadDeferredData().
  bool HasDeferredData() const override
  {
    return !myData.IsEmpty() && (NbDeferredTriangles() > 0 || NbDeferredNodes() > 0);
  }

  //! Load primitive array saved as stream buffer to new triangulation object.
  Standard_EXPORT occ::handle<Poly_Triangulation> LoadStreamData() const;

protected:
  NCollection_Sequence<RWGltf_GltfPrimArrayData> myData;
  occ::handle<RWGltf_MaterialMetallicRoughness>  myMaterialPbr;    //!< PBR material
  occ::handle<RWGltf_MaterialCommon>             myMaterialCommon; //!< common (obsolete) material
  TCollection_AsciiString                        myId;             //!< entity id
  TCollection_AsciiString                        myName;           //!< entity name
  RWGltf_GltfPrimitiveMode                       myPrimMode;       //!< type of primitive array
};

