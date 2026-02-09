#pragma once

#include <NCollection_Vec2.hpp>

#include <Standard_TypeDef.hpp>

#include <NCollection_Vec3.hpp>

#include <NCollection_Vec4.hpp>

#include <NCollection_Mat4.hpp>
#include <gp_Pnt.hpp>
#include <TCollection_AsciiString.hpp>
#include <NCollection_IndexedDataMap.hpp>

#include <memory>

class RWPly_PlyWriterContext
{
public:
  Standard_EXPORT RWPly_PlyWriterContext();

  Standard_EXPORT ~RWPly_PlyWriterContext();

public:
  bool IsDoublePrecision() const { return myIsDoublePrec; }

  void SetDoublePrecision(bool theDoublePrec) { myIsDoublePrec = theDoublePrec; }

  bool HasNormals() const { return myHasNormals; }

  void SetNormals(const bool theHasNormals) { myHasNormals = theHasNormals; }

  bool HasTexCoords() const { return myHasTexCoords; }

  void SetTexCoords(const bool theHasTexCoords) { myHasTexCoords = theHasTexCoords; }

  bool HasColors() const { return myHasColors; }

  void SetColors(bool theToWrite) { myHasColors = theToWrite; }

public:
  bool HasSurfaceId() const { return myHasSurfId; }

  void SetSurfaceId(bool theSurfId) { myHasSurfId = theSurfId; }

public:
  bool IsOpened() const { return myStream.get() != nullptr; }

  Standard_EXPORT bool Open(
    const TCollection_AsciiString&       theName,
    const std::shared_ptr<std::ostream>& theStream = std::shared_ptr<std::ostream>());

  Standard_EXPORT bool WriteHeader(
    const int theNbNodes,
    const int theNbElems,
    const NCollection_IndexedDataMap<TCollection_AsciiString, TCollection_AsciiString>&
      theFileInfo);

  Standard_EXPORT bool WriteVertex(const gp_Pnt&                    thePoint,
                                   const NCollection_Vec3<float>&   theNorm,
                                   const NCollection_Vec2<float>&   theUV,
                                   const NCollection_Vec4<uint8_t>& theColor);

  int NbWrittenVertices() const { return myNbVerts; }

  int VertexOffset() const { return myVertOffset; }

  void SetVertexOffset(int theOffset) { myVertOffset = theOffset; }

  int SurfaceId() const { return mySurfId; }

  void SetSurfaceId(int theSurfId) { mySurfId = theSurfId; }

  Standard_EXPORT bool WriteTriangle(const NCollection_Vec3<int>& theTri);

  Standard_EXPORT bool WriteQuad(const NCollection_Vec4<int>& theQuad);

  int NbWrittenElements() const { return myNbElems; }

  Standard_EXPORT bool Close(bool theIsAborted = false);

private:
  std::shared_ptr<std::ostream> myStream;
  TCollection_AsciiString       myName;
  int                           myNbHeaderVerts;
  int                           myNbHeaderElems;
  int                           myNbVerts;
  int                           myNbElems;
  int                           mySurfId;
  int                           myVertOffset;
  bool                          myIsDoublePrec;
  bool                          myHasNormals;
  bool                          myHasColors;
  bool                          myHasTexCoords;
  bool                          myHasSurfId;
};
