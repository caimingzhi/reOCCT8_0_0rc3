#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Transient.hpp>
#include <Standard_OStream.hpp>

//! defines a IndexedLineSet node of VRML specifying geometry shapes.
//! This node represents a 3D shape formed by constructing polylines from vertices
//! located at the current coordinates. IndexedLineSet uses the indices in its coordIndex
//! field to specify the polylines. An index of -1 separates one polyline from the next
//! (thus, a final -1 is optional). the current polyline has ended and the next one begins.
//! Treatment of the current material and normal binding is as follows: The PER_PART binding
//! specifies a material or normal for each segment of the line. The PER_FACE binding
//! specifies a material or normal for each polyline. PER_VERTEX specifies a material or
//! normal for each vertex. The corresponding _INDEXED bindings are the same, but use
//! the materialIndex or normalIndex indices. The DEFAULT material binding is equal
//! to OVERALL. The DEFAULT normal binding is equal to PER_VERTEX_INDEXED;
//! if insufficient normals exist in the state, the lines will be drawn unlit. The same
//! rules for texture coordinate generation as IndexedFaceSet are used.
class Vrml_IndexedLineSet : public Standard_Transient
{

public:
  Standard_EXPORT Vrml_IndexedLineSet(
    const occ::handle<NCollection_HArray1<int>>& aCoordIndex,
    const occ::handle<NCollection_HArray1<int>>& aMaterialIndex,
    const occ::handle<NCollection_HArray1<int>>& aNormalIndex,
    const occ::handle<NCollection_HArray1<int>>& aTextureCoordIndex);

  Standard_EXPORT Vrml_IndexedLineSet();

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

  DEFINE_STANDARD_RTTIEXT(Vrml_IndexedLineSet, Standard_Transient)

private:
  occ::handle<NCollection_HArray1<int>> myCoordIndex;
  occ::handle<NCollection_HArray1<int>> myMaterialIndex;
  occ::handle<NCollection_HArray1<int>> myNormalIndex;
  occ::handle<NCollection_HArray1<int>> myTextureCoordIndex;
};

