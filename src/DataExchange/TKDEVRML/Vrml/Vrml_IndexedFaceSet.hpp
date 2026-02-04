#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Transient.hpp>
#include <Standard_OStream.hpp>

//! defines a IndexedFaceSet node of VRML specifying geometry shapes.
//! This node represents a 3D shape formed by constructing faces (polygons) from
//! vertices located at the current coordinates. IndexedFaceSet uses the indices
//! in its coordIndex to define polygonal faces. An index of -1 separates faces
//! (so a -1 at the end of the list is optional).
class Vrml_IndexedFaceSet : public Standard_Transient
{

public:
  Standard_EXPORT Vrml_IndexedFaceSet(
    const occ::handle<NCollection_HArray1<int>>& aCoordIndex,
    const occ::handle<NCollection_HArray1<int>>& aMaterialIndex,
    const occ::handle<NCollection_HArray1<int>>& aNormalIndex,
    const occ::handle<NCollection_HArray1<int>>& aTextureCoordIndex);

  Standard_EXPORT Vrml_IndexedFaceSet();

  Standard_EXPORT void SetCoordIndex(const occ::handle<NCollection_HArray1<int>>& aCoordIndex);

  Standard_EXPORT occ::handle<NCollection_HArray1<int>> CoordIndex() const;

  Standard_EXPORT void SetMaterialIndex(
    const occ::handle<NCollection_HArray1<int>>& aMaterialIndex);

  Standard_EXPORT occ::handle<NCollection_HArray1<int>> MaterialIndex() const;

  Standard_EXPORT void SetNormalIndex(const occ::handle<NCollection_HArray1<int>>& aNormalIndex);

  Standard_EXPORT occ::handle<NCollection_HArray1<int>> NormalIndex() const;

  Standard_EXPORT void SetTextureCoordIndex(
    const occ::handle<NCollection_HArray1<int>>& aTextureCoordIndex);

  Standard_EXPORT occ::handle<NCollection_HArray1<int>> TextureCoordIndex() const;

  Standard_EXPORT Standard_OStream& Print(Standard_OStream& anOStream) const;

  DEFINE_STANDARD_RTTIEXT(Vrml_IndexedFaceSet, Standard_Transient)

private:
  occ::handle<NCollection_HArray1<int>> myCoordIndex;
  occ::handle<NCollection_HArray1<int>> myMaterialIndex;
  occ::handle<NCollection_HArray1<int>> myNormalIndex;
  occ::handle<NCollection_HArray1<int>> myTextureCoordIndex;
};

