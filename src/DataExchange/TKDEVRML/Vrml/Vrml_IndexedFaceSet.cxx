

#include <Standard_Type.hpp>
#include <Vrml_IndexedFaceSet.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Vrml_IndexedFaceSet, Standard_Transient)

Vrml_IndexedFaceSet::Vrml_IndexedFaceSet(
  const occ::handle<NCollection_HArray1<int>>& aCoordIndex,
  const occ::handle<NCollection_HArray1<int>>& aMaterialIndex,
  const occ::handle<NCollection_HArray1<int>>& aNormalIndex,
  const occ::handle<NCollection_HArray1<int>>& aTextureCoordIndex)
{
  myCoordIndex        = aCoordIndex;
  myMaterialIndex     = aMaterialIndex;
  myNormalIndex       = aNormalIndex;
  myTextureCoordIndex = aTextureCoordIndex;
}

Vrml_IndexedFaceSet::Vrml_IndexedFaceSet()
{
  myCoordIndex        = new NCollection_HArray1<int>(1, 1, 0);
  myMaterialIndex     = new NCollection_HArray1<int>(1, 1, -1);
  myNormalIndex       = new NCollection_HArray1<int>(1, 1, -1);
  myTextureCoordIndex = new NCollection_HArray1<int>(1, 1, -1);
}

void Vrml_IndexedFaceSet::SetCoordIndex(const occ::handle<NCollection_HArray1<int>>& aCoordIndex)
{
  myCoordIndex = aCoordIndex;
}

occ::handle<NCollection_HArray1<int>> Vrml_IndexedFaceSet::CoordIndex() const
{
  return myCoordIndex;
}

void Vrml_IndexedFaceSet::SetMaterialIndex(
  const occ::handle<NCollection_HArray1<int>>& aMaterialIndex)
{
  myMaterialIndex = aMaterialIndex;
}

occ::handle<NCollection_HArray1<int>> Vrml_IndexedFaceSet::MaterialIndex() const
{
  return myMaterialIndex;
}

void Vrml_IndexedFaceSet::SetNormalIndex(const occ::handle<NCollection_HArray1<int>>& aNormalIndex)
{
  myNormalIndex = aNormalIndex;
}

occ::handle<NCollection_HArray1<int>> Vrml_IndexedFaceSet::NormalIndex() const

{
  return myNormalIndex;
}

void Vrml_IndexedFaceSet::SetTextureCoordIndex(
  const occ::handle<NCollection_HArray1<int>>& aTextureCoordIndex)
{
  myTextureCoordIndex = aTextureCoordIndex;
}

occ::handle<NCollection_HArray1<int>> Vrml_IndexedFaceSet::TextureCoordIndex() const
{
  return myTextureCoordIndex;
}

Standard_OStream& Vrml_IndexedFaceSet::Print(Standard_OStream& anOStream) const
{
  int i;
  anOStream << "IndexedFaceSet {\n";

  if (myCoordIndex->Length() != 1 || myCoordIndex->Value(myCoordIndex->Lower()) != 0)
  {
    anOStream << "    coordIndex [\n\t";
    for (i = myCoordIndex->Lower(); i <= myCoordIndex->Upper(); i++)
    {
      anOStream << myCoordIndex->Value(i);

      if (i < myCoordIndex->Length())
        anOStream << ",";

      if (myCoordIndex->Value(i) == -1)
        anOStream << "\n\t";
    }
    anOStream << "]\n";
  }

  if (myMaterialIndex->Length() != 1 || myMaterialIndex->Value(myMaterialIndex->Lower()) != -1)
  {
    anOStream << "    materialIndex [\n\t";
    for (i = myMaterialIndex->Lower(); i <= myMaterialIndex->Upper(); i++)
    {
      anOStream << myMaterialIndex->Value(i);
      if (i < myMaterialIndex->Length())
        anOStream << ",";

      if (myMaterialIndex->Value(i) == -1)
        anOStream << "\n\t";
    }
    anOStream << "]\n";
  }

  if (myNormalIndex->Length() != 1 || myNormalIndex->Value(myNormalIndex->Lower()) != -1)
  {
    anOStream << "    normalIndex [\n\t";
    for (i = myNormalIndex->Lower(); i <= myNormalIndex->Upper(); i++)
    {
      anOStream << myNormalIndex->Value(i);
      if (i < myNormalIndex->Length())
        anOStream << ",";

      if (myNormalIndex->Value(i) == -1)
        anOStream << "\n\t";
    }
    anOStream << "]\n";
  }
  if (myTextureCoordIndex->Length() != 1
      || myTextureCoordIndex->Value(myTextureCoordIndex->Lower()) != -1)
  {
    anOStream << "    textureCoordIndex [\n\t";
    for (i = myTextureCoordIndex->Lower(); i <= myTextureCoordIndex->Upper(); i++)
    {
      anOStream << myTextureCoordIndex->Value(i);
      if (i < myTextureCoordIndex->Length())
        anOStream << ",";

      if (myTextureCoordIndex->Value(i) == -1)
        anOStream << "\n\t";
    }
    anOStream << "]\n";
  }
  anOStream << "}\n";
  return anOStream;
}
