#pragma once

#include <RWMesh_TriangulationSource.hpp>

#include <NCollection_Sequence.hpp>
#include <RWGltf_GltfArrayType.hpp>
#include <RWGltf_GltfPrimitiveMode.hpp>
#include <Quantity_ColorRGBA.hpp>

class RWGltf_GltfPrimArrayData;
class RWGltf_MaterialMetallicRoughness;
class RWGltf_MaterialCommon;

class RWGltf_GltfLatePrimitiveArray : public RWMesh_TriangulationSource
{
  DEFINE_STANDARD_RTTIEXT(RWGltf_GltfLatePrimitiveArray, RWMesh_TriangulationSource)
public:
  Standard_EXPORT RWGltf_GltfLatePrimitiveArray(const TCollection_AsciiString& theId,
                                                const TCollection_AsciiString& theName);

  Standard_EXPORT ~RWGltf_GltfLatePrimitiveArray() override;

  const TCollection_AsciiString& Id() const { return myId; }

  const TCollection_AsciiString& Name() const { return myName; }

  void SetName(const TCollection_AsciiString& theName) { myName = theName; }

  RWGltf_GltfPrimitiveMode PrimitiveMode() const { return myPrimMode; }

  void SetPrimitiveMode(RWGltf_GltfPrimitiveMode theMode) { myPrimMode = theMode; }

  bool HasStyle() const { return !myMaterialPbr.IsNull() || !myMaterialCommon.IsNull(); }

  Standard_EXPORT Quantity_ColorRGBA BaseColor() const;

  const occ::handle<RWGltf_MaterialMetallicRoughness>& MaterialPbr() const { return myMaterialPbr; }

  void SetMaterialPbr(const occ::handle<RWGltf_MaterialMetallicRoughness>& theMat)
  {
    myMaterialPbr = theMat;
  }

  const occ::handle<RWGltf_MaterialCommon>& MaterialCommon() const { return myMaterialCommon; }

  void SetMaterialCommon(const occ::handle<RWGltf_MaterialCommon>& theMat)
  {
    myMaterialCommon = theMat;
  }

  const NCollection_Sequence<RWGltf_GltfPrimArrayData>& Data() const { return myData; }

  Standard_EXPORT RWGltf_GltfPrimArrayData& AddPrimArrayData(RWGltf_GltfArrayType theType);

  bool HasDeferredData() const override
  {
    return !myData.IsEmpty() && (NbDeferredTriangles() > 0 || NbDeferredNodes() > 0);
  }

  Standard_EXPORT occ::handle<Poly_Triangulation> LoadStreamData() const;

protected:
  NCollection_Sequence<RWGltf_GltfPrimArrayData> myData;
  occ::handle<RWGltf_MaterialMetallicRoughness>  myMaterialPbr;
  occ::handle<RWGltf_MaterialCommon>             myMaterialCommon;
  TCollection_AsciiString                        myId;
  TCollection_AsciiString                        myName;
  RWGltf_GltfPrimitiveMode                       myPrimMode;
};
