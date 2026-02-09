

#include <RWGltf_GltfLatePrimitiveArray.hpp>

#include <RWGltf_GltfPrimArrayData.hpp>
#include <RWGltf_MaterialMetallicRoughness.hpp>
#include <RWGltf_MaterialCommon.hpp>
#include <RWGltf_TriangulationReader.hpp>

IMPLEMENT_STANDARD_RTTIEXT(RWGltf_GltfLatePrimitiveArray, RWMesh_TriangulationSource)

RWGltf_GltfLatePrimitiveArray::RWGltf_GltfLatePrimitiveArray(const TCollection_AsciiString& theId,
                                                             const TCollection_AsciiString& theName)
    : myId(theId),
      myName(theName),
      myPrimMode(RWGltf_GltfPrimitiveMode_UNKNOWN)
{
}

RWGltf_GltfLatePrimitiveArray::~RWGltf_GltfLatePrimitiveArray() = default;

Quantity_ColorRGBA RWGltf_GltfLatePrimitiveArray::BaseColor() const
{
  if (!myMaterialPbr.IsNull())
  {
    return myMaterialPbr->BaseColor;
  }
  else if (!myMaterialCommon.IsNull())
  {
    return Quantity_ColorRGBA(myMaterialCommon->DiffuseColor,
                              1.0f - myMaterialCommon->Transparency);
  }
  return Quantity_ColorRGBA();
}

RWGltf_GltfPrimArrayData& RWGltf_GltfLatePrimitiveArray::AddPrimArrayData(
  RWGltf_GltfArrayType theType)
{
  if (theType == RWGltf_GltfArrayType_Position)
  {

    myData.Prepend(RWGltf_GltfPrimArrayData(theType));
    return myData.ChangeFirst();
  }
  else if (theType == RWGltf_GltfArrayType_Indices)
  {

    if (myData.First().Type == RWGltf_GltfArrayType_Position)
    {
      myData.InsertAfter(NCollection_Sequence<RWGltf_GltfPrimArrayData>::Lower(),
                         RWGltf_GltfPrimArrayData(theType));
      return myData.ChangeValue(NCollection_Sequence<RWGltf_GltfPrimArrayData>::Lower() + 1);
    }
    else
    {
      myData.Prepend(RWGltf_GltfPrimArrayData(theType));
      return myData.ChangeFirst();
    }
  }
  else
  {
    myData.Append(RWGltf_GltfPrimArrayData(theType));
    return myData.ChangeLast();
  }
}

occ::handle<Poly_Triangulation> RWGltf_GltfLatePrimitiveArray::LoadStreamData() const
{
  occ::handle<RWGltf_TriangulationReader> aGltfReader =
    occ::down_cast<RWGltf_TriangulationReader>(myReader);
  if (aGltfReader.IsNull())
  {
    return occ::handle<Poly_Triangulation>();
  }

  occ::handle<RWMesh_TriangulationSource> aResult = new RWMesh_TriangulationSource();
  if (!aGltfReader->LoadStreamData(this, aResult))
  {
    return occ::handle<Poly_Triangulation>();
  }
  aResult->SetMeshPurpose(aResult->MeshPurpose() | Poly_MeshPurpose_Loaded);
  return aResult;
}
