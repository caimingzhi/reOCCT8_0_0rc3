#pragma once

#include <NCollection_Vec2.hpp>

#include <Standard_TypeDef.hpp>

#include <NCollection_Vec3.hpp>

#include <NCollection_Vec4.hpp>

#include <NCollection_Mat4.hpp>
#include <TCollection_AsciiString.hpp>
#include <NCollection_IndexedDataMap.hpp>

class RWObj_ObjWriterContext
{
public:
  Standard_EXPORT RWObj_ObjWriterContext(const TCollection_AsciiString& theName);

  Standard_EXPORT ~RWObj_ObjWriterContext();

  bool IsOpened() const { return myFile != nullptr; }

  Standard_EXPORT bool Close();

  bool HasNormals() const { return myHasNormals; }

  void SetNormals(const bool theHasNormals) { myHasNormals = theHasNormals; }

  bool HasTexCoords() const { return myHasTexCoords; }

  void SetTexCoords(const bool theHasTexCoords) { myHasTexCoords = theHasTexCoords; }

  Standard_EXPORT bool WriteHeader(
    const int                      theNbNodes,
    const int                      theNbElems,
    const TCollection_AsciiString& theMatLib,
    const NCollection_IndexedDataMap<TCollection_AsciiString, TCollection_AsciiString>&
      theFileInfo);

  const TCollection_AsciiString& ActiveMaterial() const { return myActiveMaterial; }

  Standard_EXPORT bool WriteActiveMaterial(const TCollection_AsciiString& theMaterial);

  Standard_EXPORT bool WriteTriangle(const NCollection_Vec3<int>& theTri);

  Standard_EXPORT bool WriteQuad(const NCollection_Vec4<int>& theQuad);

  Standard_EXPORT bool WriteVertex(const NCollection_Vec3<float>& theValue);

  Standard_EXPORT bool WriteNormal(const NCollection_Vec3<float>& theValue);

  Standard_EXPORT bool WriteTexCoord(const NCollection_Vec2<float>& theValue);

  Standard_EXPORT bool WriteGroup(const TCollection_AsciiString& theValue);

  Standard_EXPORT void FlushFace(int theNbNodes);

public:
  int NbFaces;

private:
  FILE*                   myFile;
  TCollection_AsciiString myName;
  TCollection_AsciiString myActiveMaterial;
  NCollection_Vec4<int>   myElemPosFirst;
  NCollection_Vec4<int>   myElemNormFirst;
  NCollection_Vec4<int>   myElemUVFirst;
  bool                    myHasNormals;
  bool                    myHasTexCoords;
};
