#pragma once

#include <Graphic3d_BoundBuffer.hpp>

typedef int Graphic3d_ArrayFlags;

enum
{
  Graphic3d_ArrayFlags_None         = 0x00,
  Graphic3d_ArrayFlags_VertexNormal = 0x01,
  Graphic3d_ArrayFlags_VertexColor  = 0x02,
  Graphic3d_ArrayFlags_VertexTexel  = 0x04,
  Graphic3d_ArrayFlags_BoundColor   = 0x10,

  Graphic3d_ArrayFlags_AttribsMutable       = 0x20,
  Graphic3d_ArrayFlags_AttribsDeinterleaved = 0x40,
  Graphic3d_ArrayFlags_IndexesMutable       = 0x80,
};

#include <Graphic3d_Buffer.hpp>
#include <Graphic3d_IndexBuffer.hpp>
#include <Graphic3d_TypeOfPrimitiveArray.hpp>
#include <gp_Dir.hpp>
#include <gp_Pnt.hpp>
#include <Standard_OutOfRange.hpp>
#include <Standard_TypeMismatch.hpp>
#include <Quantity_Color.hpp>

class Graphic3d_ArrayOfPrimitives : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(Graphic3d_ArrayOfPrimitives, Standard_Transient)
public:
  static occ::handle<Graphic3d_ArrayOfPrimitives> CreateArray(
    Graphic3d_TypeOfPrimitiveArray theType,
    int                            theMaxVertexs,
    int                            theMaxEdges,
    Graphic3d_ArrayFlags           theArrayFlags)
  {
    return CreateArray(theType, theMaxVertexs, 0, theMaxEdges, theArrayFlags);
  }

  static Standard_EXPORT occ::handle<Graphic3d_ArrayOfPrimitives> CreateArray(
    Graphic3d_TypeOfPrimitiveArray theType,
    int                            theMaxVertexs,
    int                            theMaxBounds,
    int                            theMaxEdges,
    Graphic3d_ArrayFlags           theArrayFlags);

public:
  Standard_EXPORT ~Graphic3d_ArrayOfPrimitives() override;

  const occ::handle<Graphic3d_Buffer>& Attributes() const { return myAttribs; }

  Graphic3d_TypeOfPrimitiveArray Type() const { return myType; }

  Standard_EXPORT const char* StringType() const;

  bool HasVertexNormals() const { return myNormData != nullptr; }

  bool HasVertexColors() const { return myColData != nullptr; }

  bool HasVertexTexels() const { return myTexData != nullptr; }

  int VertexNumber() const { return myAttribs->NbElements; }

  int VertexNumberAllocated() const { return myAttribs->NbMaxElements(); }

  Standard_EXPORT int ItemNumber() const;

  Standard_EXPORT bool IsValid();

  int AddVertex(const gp_Pnt& theVertex)
  {
    return AddVertex(theVertex.X(), theVertex.Y(), theVertex.Z());
  }

  int AddVertex(const NCollection_Vec3<float>& theVertex)
  {
    return AddVertex(theVertex.x(), theVertex.y(), theVertex.z());
  }

  int AddVertex(const double theX, const double theY, const double theZ)
  {
    return AddVertex(RealToShortReal(theX), RealToShortReal(theY), RealToShortReal(theZ));
  }

  int AddVertex(const float theX, const float theY, const float theZ)
  {
    const int anIndex = myAttribs->NbElements + 1;
    SetVertice(anIndex, theX, theY, theZ);
    return anIndex;
  }

  int AddVertex(const gp_Pnt& theVertex, const Quantity_Color& theColor)
  {
    const int anIndex = AddVertex(theVertex);
    SetVertexColor(anIndex, theColor.Red(), theColor.Green(), theColor.Blue());
    return anIndex;
  }

  int AddVertex(const gp_Pnt& theVertex, const int theColor32)
  {
    const int anIndex = AddVertex(theVertex);
    SetVertexColor(anIndex, theColor32);
    return anIndex;
  }

  int AddVertex(const gp_Pnt& theVertex, const NCollection_Vec4<uint8_t>& theColor)
  {
    const int anIndex = AddVertex(theVertex);
    SetVertexColor(anIndex, theColor);
    return anIndex;
  }

  int AddVertex(const gp_Pnt& theVertex, const gp_Dir& theNormal)
  {
    return AddVertex(theVertex.X(),
                     theVertex.Y(),
                     theVertex.Z(),
                     theNormal.X(),
                     theNormal.Y(),
                     theNormal.Z());
  }

  int AddVertex(const double theX,
                const double theY,
                const double theZ,
                const double theNX,
                const double theNY,
                const double theNZ)
  {
    return AddVertex(RealToShortReal(theX),
                     RealToShortReal(theY),
                     RealToShortReal(theZ),
                     float(theNX),
                     float(theNY),
                     float(theNZ));
  }

  int AddVertex(const float theX,
                const float theY,
                const float theZ,
                const float theNX,
                const float theNY,
                const float theNZ)
  {
    const int anIndex = myAttribs->NbElements + 1;
    SetVertice(anIndex, theX, theY, theZ);
    SetVertexNormal(anIndex, theNX, theNY, theNZ);
    return anIndex;
  }

  int AddVertex(const gp_Pnt& theVertex, const gp_Dir& theNormal, const Quantity_Color& theColor)
  {
    const int anIndex = AddVertex(theVertex, theNormal);
    SetVertexColor(anIndex, theColor.Red(), theColor.Green(), theColor.Blue());
    return anIndex;
  }

  int AddVertex(const gp_Pnt& theVertex, const gp_Dir& theNormal, const int theColor32)
  {
    const int anIndex = AddVertex(theVertex, theNormal);
    SetVertexColor(anIndex, theColor32);
    return anIndex;
  }

  int AddVertex(const gp_Pnt& theVertex, const gp_Pnt2d& theTexel)
  {
    return AddVertex(theVertex.X(), theVertex.Y(), theVertex.Z(), theTexel.X(), theTexel.Y());
  }

  int AddVertex(const double theX,
                const double theY,
                const double theZ,
                const double theTX,
                const double theTY)
  {
    return AddVertex(RealToShortReal(theX),
                     RealToShortReal(theY),
                     RealToShortReal(theZ),
                     float(theTX),
                     float(theTY));
  }

  int AddVertex(const float theX,
                const float theY,
                const float theZ,
                const float theTX,
                const float theTY)
  {
    const int anIndex = myAttribs->NbElements + 1;
    SetVertice(anIndex, theX, theY, theZ);
    SetVertexTexel(anIndex, theTX, theTY);
    return anIndex;
  }

  int AddVertex(const gp_Pnt& theVertex, const gp_Dir& theNormal, const gp_Pnt2d& theTexel)
  {
    return AddVertex(theVertex.X(),
                     theVertex.Y(),
                     theVertex.Z(),
                     theNormal.X(),
                     theNormal.Y(),
                     theNormal.Z(),
                     theTexel.X(),
                     theTexel.Y());
  }

  int AddVertex(const double theX,
                const double theY,
                const double theZ,
                const double theNX,
                const double theNY,
                const double theNZ,
                const double theTX,
                const double theTY)
  {
    return AddVertex(RealToShortReal(theX),
                     RealToShortReal(theY),
                     RealToShortReal(theZ),
                     float(theNX),
                     float(theNY),
                     float(theNZ),
                     float(theTX),
                     float(theTY));
  }

  int AddVertex(const float theX,
                const float theY,
                const float theZ,
                const float theNX,
                const float theNY,
                const float theNZ,
                const float theTX,
                const float theTY)
  {
    const int anIndex = myAttribs->NbElements + 1;
    SetVertice(anIndex, theX, theY, theZ);
    SetVertexNormal(anIndex, theNX, theNY, theNZ);
    SetVertexTexel(anIndex, theTX, theTY);
    return anIndex;
  }

  void SetVertice(const int theIndex, const gp_Pnt& theVertex)
  {
    SetVertice(theIndex, float(theVertex.X()), float(theVertex.Y()), float(theVertex.Z()));
  }

  void SetVertice(const int theIndex, const float theX, const float theY, const float theZ)
  {
    Standard_OutOfRange_Raise_if(theIndex < 1 || theIndex > myAttribs->NbMaxElements(),
                                 "BAD VERTEX index");
    NCollection_Vec3<float>& aVec = *reinterpret_cast<NCollection_Vec3<float>*>(
      myAttribs->ChangeData() + myPosStride * ((size_t)theIndex - 1));
    aVec.x() = theX;
    aVec.y() = theY;
    aVec.z() = theZ;
    if (myAttribs->NbElements < theIndex)
    {
      myAttribs->NbElements = theIndex;
    }
  }

  void SetVertexColor(const int theIndex, const Quantity_Color& theColor)
  {
    SetVertexColor(theIndex, theColor.Red(), theColor.Green(), theColor.Blue());
  }

  void SetVertexColor(const int theIndex, const double theR, const double theG, const double theB)
  {
    Standard_OutOfRange_Raise_if(theIndex < 1 || theIndex > myAttribs->NbMaxElements(),
                                 "BAD VERTEX index");
    if (myColData != nullptr)
    {
      NCollection_Vec4<uint8_t>* aColorPtr = reinterpret_cast<NCollection_Vec4<uint8_t>*>(
        myColData + myColStride * ((size_t)theIndex - 1));
      aColorPtr->SetValues(static_cast<uint8_t>(theR * 255.0),
                           static_cast<uint8_t>(theG * 255.0),
                           static_cast<uint8_t>(theB * 255.0),
                           255);
    }
    myAttribs->NbElements = (std::max)(theIndex, myAttribs->NbElements);
  }

  void SetVertexColor(const int theIndex, const NCollection_Vec4<uint8_t>& theColor)
  {
    Standard_OutOfRange_Raise_if(theIndex < 1 || theIndex > myAttribs->NbMaxElements(),
                                 "BAD VERTEX index");
    if (myColData != nullptr)
    {
      NCollection_Vec4<uint8_t>* aColorPtr = reinterpret_cast<NCollection_Vec4<uint8_t>*>(
        myColData + myColStride * ((size_t)theIndex - 1));
      (*aColorPtr) = theColor;
    }
    myAttribs->NbElements = (std::max)(theIndex, myAttribs->NbElements);
  }

  void SetVertexColor(const int theIndex, const int theColor32)
  {
    Standard_OutOfRange_Raise_if(theIndex < 1 || theIndex > myAttribs->NbMaxElements(),
                                 "BAD VERTEX index");
    if (myColData != nullptr)
    {
      *reinterpret_cast<int*>(myColData + myColStride * ((size_t)theIndex - 1)) = theColor32;
    }
  }

  void SetVertexNormal(const int theIndex, const gp_Dir& theNormal)
  {
    SetVertexNormal(theIndex, theNormal.X(), theNormal.Y(), theNormal.Z());
  }

  void SetVertexNormal(const int    theIndex,
                       const double theNX,
                       const double theNY,
                       const double theNZ)
  {
    Standard_OutOfRange_Raise_if(theIndex < 1 || theIndex > myAttribs->NbMaxElements(),
                                 "BAD VERTEX index");
    if (myNormData != nullptr)
    {
      NCollection_Vec3<float>& aVec = *reinterpret_cast<NCollection_Vec3<float>*>(
        myNormData + myNormStride * ((size_t)theIndex - 1));
      aVec.x() = float(theNX);
      aVec.y() = float(theNY);
      aVec.z() = float(theNZ);
    }
    myAttribs->NbElements = (std::max)(theIndex, myAttribs->NbElements);
  }

  void SetVertexTexel(const int theIndex, const gp_Pnt2d& theTexel)
  {
    SetVertexTexel(theIndex, theTexel.X(), theTexel.Y());
  }

  void SetVertexTexel(const int theIndex, const double theTX, const double theTY)
  {
    Standard_OutOfRange_Raise_if(theIndex < 1 || theIndex > myAttribs->NbMaxElements(),
                                 "BAD VERTEX index");
    if (myTexData != nullptr)
    {
      NCollection_Vec2<float>& aVec = *reinterpret_cast<NCollection_Vec2<float>*>(
        myTexData + myTexStride * ((size_t)theIndex - 1));
      aVec.x() = float(theTX);
      aVec.y() = float(theTY);
    }
    myAttribs->NbElements = (std::max)(theIndex, myAttribs->NbElements);
  }

  gp_Pnt Vertice(const int theRank) const
  {
    double anXYZ[3];
    Vertice(theRank, anXYZ[0], anXYZ[1], anXYZ[2]);
    return gp_Pnt(anXYZ[0], anXYZ[1], anXYZ[2]);
  }

  void Vertice(const int theRank, double& theX, double& theY, double& theZ) const
  {
    theX = theY = theZ = 0.0;
    Standard_OutOfRange_Raise_if(theRank < 1 || theRank > myAttribs->NbElements,
                                 "BAD VERTEX index");
    const NCollection_Vec3<float>& aVec = *reinterpret_cast<const NCollection_Vec3<float>*>(
      myAttribs->Data() + myPosStride * ((size_t)theRank - 1));
    theX = double(aVec.x());
    theY = double(aVec.y());
    theZ = double(aVec.z());
  }

  Quantity_Color VertexColor(const int theRank) const
  {
    double anRGB[3];
    VertexColor(theRank, anRGB[0], anRGB[1], anRGB[2]);
    return Quantity_Color(anRGB[0], anRGB[1], anRGB[2], Quantity_TOC_RGB);
  }

  void VertexColor(const int theIndex, NCollection_Vec4<uint8_t>& theColor) const
  {
    Standard_OutOfRange_Raise_if(myColData == nullptr || theIndex < 1
                                   || theIndex > myAttribs->NbElements,
                                 "BAD VERTEX index");
    theColor = *reinterpret_cast<const NCollection_Vec4<uint8_t>*>(
      myColData + myColStride * ((size_t)theIndex - 1));
  }

  void VertexColor(const int theRank, double& theR, double& theG, double& theB) const
  {
    theR = theG = theB = 0.0;
    Standard_OutOfRange_Raise_if(theRank < 1 || theRank > myAttribs->NbElements,
                                 "BAD VERTEX index");
    if (myColData == nullptr)
    {
      return;
    }
    const NCollection_Vec4<uint8_t>& aColor = *reinterpret_cast<const NCollection_Vec4<uint8_t>*>(
      myColData + myColStride * ((size_t)theRank - 1));
    theR = double(aColor.r()) / 255.0;
    theG = double(aColor.g()) / 255.0;
    theB = double(aColor.b()) / 255.0;
  }

  void VertexColor(const int theRank, int& theColor) const
  {
    Standard_OutOfRange_Raise_if(theRank < 1 || theRank > myAttribs->NbElements,
                                 "BAD VERTEX index");
    if (myColData != nullptr)
    {
      theColor = *reinterpret_cast<const int*>(myColData + myColStride * ((size_t)theRank - 1));
    }
  }

  gp_Dir VertexNormal(const int theRank) const
  {
    double anXYZ[3];
    VertexNormal(theRank, anXYZ[0], anXYZ[1], anXYZ[2]);
    return gp_Dir(anXYZ[0], anXYZ[1], anXYZ[2]);
  }

  void VertexNormal(const int theRank, double& theNX, double& theNY, double& theNZ) const
  {
    theNX = theNY = theNZ = 0.0;
    Standard_OutOfRange_Raise_if(theRank < 1 || theRank > myAttribs->NbElements,
                                 "BAD VERTEX index");
    if (myNormData != nullptr)
    {
      const NCollection_Vec3<float>& aVec = *reinterpret_cast<const NCollection_Vec3<float>*>(
        myNormData + myNormStride * ((size_t)theRank - 1));
      theNX = double(aVec.x());
      theNY = double(aVec.y());
      theNZ = double(aVec.z());
    }
  }

  gp_Pnt2d VertexTexel(const int theRank) const
  {
    double anXY[2];
    VertexTexel(theRank, anXY[0], anXY[1]);
    return gp_Pnt2d(anXY[0], anXY[1]);
  }

  void VertexTexel(const int theRank, double& theTX, double& theTY) const
  {
    theTX = theTY = 0.0;
    Standard_OutOfRange_Raise_if(theRank < 1 || theRank > myAttribs->NbElements,
                                 "BAD VERTEX index");
    if (myTexData != nullptr)
    {
      const NCollection_Vec2<float>& aVec = *reinterpret_cast<const NCollection_Vec2<float>*>(
        myTexData + myTexStride * ((size_t)theRank - 1));
      theTX = double(aVec.x());
      theTY = double(aVec.y());
    }
  }

public:
  const occ::handle<Graphic3d_IndexBuffer>& Indices() const { return myIndices; }

  int EdgeNumber() const { return !myIndices.IsNull() ? myIndices->NbElements : -1; }

  int EdgeNumberAllocated() const { return !myIndices.IsNull() ? myIndices->NbMaxElements() : 0; }

  int Edge(const int theRank) const
  {
    Standard_OutOfRange_Raise_if(myIndices.IsNull() || theRank < 1
                                   || theRank > myIndices->NbElements,
                                 "BAD EDGE index");
    return int(myIndices->Index(theRank - 1) + 1);
  }

  Standard_EXPORT int AddEdge(const int theVertexIndex);

  int AddEdges(int theVertexIndex1, int theVertexIndex2)
  {
    AddEdge(theVertexIndex1);
    return AddEdge(theVertexIndex2);
  }

  int AddSegmentEdges(int theVertexIndex1, int theVertexIndex2)
  {
    Standard_TypeMismatch_Raise_if(myType != Graphic3d_TOPA_SEGMENTS, "Not array of segments");
    return AddEdges(theVertexIndex1, theVertexIndex2);
  }

  int AddEdges(int theVertexIndex1, int theVertexIndex2, int theVertexIndex3)
  {
    AddEdge(theVertexIndex1);
    AddEdge(theVertexIndex2);
    return AddEdge(theVertexIndex3);
  }

  int AddTriangleEdges(int theVertexIndex1, int theVertexIndex2, int theVertexIndex3)
  {
    Standard_TypeMismatch_Raise_if(myType != Graphic3d_TOPA_TRIANGLES, "Not array of triangles");
    return AddEdges(theVertexIndex1, theVertexIndex2, theVertexIndex3);
  }

  int AddTriangleEdges(const NCollection_Vec3<int>& theIndexes)
  {
    Standard_TypeMismatch_Raise_if(myType != Graphic3d_TOPA_TRIANGLES, "Not array of triangles");
    return AddEdges(theIndexes[0], theIndexes[1], theIndexes[2]);
  }

  int AddTriangleEdges(const NCollection_Vec4<int>& theIndexes)
  {
    Standard_TypeMismatch_Raise_if(myType != Graphic3d_TOPA_TRIANGLES, "Not array of triangles");
    return AddEdges(theIndexes[0], theIndexes[1], theIndexes[2]);
  }

  int AddEdges(int theVertexIndex1, int theVertexIndex2, int theVertexIndex3, int theVertexIndex4)
  {
    AddEdge(theVertexIndex1);
    AddEdge(theVertexIndex2);
    AddEdge(theVertexIndex3);
    return AddEdge(theVertexIndex4);
  }

  int AddQuadEdges(int theVertexIndex1,
                   int theVertexIndex2,
                   int theVertexIndex3,
                   int theVertexIndex4)
  {
    Standard_TypeMismatch_Raise_if(myType != Graphic3d_TOPA_QUADRANGLES, "Not array of quads");
    return AddEdges(theVertexIndex1, theVertexIndex2, theVertexIndex3, theVertexIndex4);
  }

  int AddQuadTriangleEdges(int theVertexIndex1,
                           int theVertexIndex2,
                           int theVertexIndex3,
                           int theVertexIndex4)
  {
    AddTriangleEdges(theVertexIndex3, theVertexIndex1, theVertexIndex2);
    return AddTriangleEdges(theVertexIndex1, theVertexIndex3, theVertexIndex4);
  }

  int AddQuadTriangleEdges(const NCollection_Vec4<int>& theIndexes)
  {
    return AddQuadTriangleEdges(theIndexes[0], theIndexes[1], theIndexes[2], theIndexes[3]);
  }

  Standard_EXPORT void AddTriangleStripEdges(int theVertexLower, int theVertexUpper);

  Standard_EXPORT void AddTriangleFanEdges(int theVertexLower, int theVertexUpper, bool theToClose);

  Standard_EXPORT void AddPolylineEdges(int theVertexLower, int theVertexUpper, bool theToClose);

public:
  const occ::handle<Graphic3d_BoundBuffer>& Bounds() const { return myBounds; }

  bool HasBoundColors() const { return !myBounds.IsNull() && myBounds->Colors != nullptr; }

  int BoundNumber() const { return !myBounds.IsNull() ? myBounds->NbBounds : -1; }

  int BoundNumberAllocated() const { return !myBounds.IsNull() ? myBounds->NbMaxBounds : 0; }

  int Bound(const int theRank) const
  {
    Standard_OutOfRange_Raise_if(myBounds.IsNull() || theRank < 1 || theRank > myBounds->NbBounds,
                                 "BAD BOUND index");
    return myBounds->Bounds[theRank - 1];
  }

  Quantity_Color BoundColor(const int theRank) const
  {
    double anRGB[3] = {0.0, 0.0, 0.0};
    BoundColor(theRank, anRGB[0], anRGB[1], anRGB[2]);
    return Quantity_Color(anRGB[0], anRGB[1], anRGB[2], Quantity_TOC_RGB);
  }

  void BoundColor(const int theRank, double& theR, double& theG, double& theB) const
  {
    Standard_OutOfRange_Raise_if(myBounds.IsNull() || myBounds->Colors == nullptr || theRank < 1
                                   || theRank > myBounds->NbBounds,
                                 "BAD BOUND index");
    const NCollection_Vec4<float>& aVec = myBounds->Colors[theRank - 1];
    theR                                = double(aVec.r());
    theG                                = double(aVec.g());
    theB                                = double(aVec.b());
  }

  Standard_EXPORT int AddBound(const int theEdgeNumber);

  int AddBound(const int theEdgeNumber, const Quantity_Color& theBColor)
  {
    return AddBound(theEdgeNumber, theBColor.Red(), theBColor.Green(), theBColor.Blue());
  }

  Standard_EXPORT int AddBound(const int    theEdgeNumber,
                               const double theR,
                               const double theG,
                               const double theB);

  void SetBoundColor(const int theIndex, const Quantity_Color& theColor)
  {
    SetBoundColor(theIndex, theColor.Red(), theColor.Green(), theColor.Blue());
  }

  void SetBoundColor(const int theIndex, const double theR, const double theG, const double theB)
  {
    if (myBounds.IsNull())
    {
      return;
    }
    Standard_OutOfRange_Raise_if(myBounds.IsNull() || myBounds->Colors == nullptr || theIndex < 1
                                   || theIndex > myBounds->NbMaxBounds,
                                 "BAD BOUND index");
    NCollection_Vec4<float>& aVec = myBounds->Colors[theIndex - 1];
    aVec.r()                      = float(theR);
    aVec.g()                      = float(theG);
    aVec.b()                      = float(theB);
    aVec.a()                      = 1.0f;
    myBounds->NbBounds            = (std::max)(theIndex, myBounds->NbBounds);
  }

protected:
  Graphic3d_ArrayOfPrimitives(Graphic3d_TypeOfPrimitiveArray theType,
                              int                            theMaxVertexs,
                              int                            theMaxBounds,
                              int                            theMaxEdges,
                              Graphic3d_ArrayFlags           theArrayFlags)
      : myNormData(nullptr),
        myTexData(nullptr),
        myColData(nullptr),
        myPosStride(0),
        myNormStride(0),
        myTexStride(0),
        myColStride(0),
        myType(Graphic3d_TOPA_UNDEFINED)
  {
    init(theType, theMaxVertexs, theMaxBounds, theMaxEdges, theArrayFlags);
  }

  Standard_EXPORT void init(Graphic3d_TypeOfPrimitiveArray theType,
                            int                            theMaxVertexs,
                            int                            theMaxBounds,
                            int                            theMaxEdges,
                            Graphic3d_ArrayFlags           theArrayFlags);

private:
  occ::handle<Graphic3d_IndexBuffer> myIndices;
  occ::handle<Graphic3d_Buffer>      myAttribs;
  occ::handle<Graphic3d_BoundBuffer> myBounds;
  uint8_t*                           myNormData;
  uint8_t*                           myTexData;
  uint8_t*                           myColData;
  size_t                             myPosStride;
  size_t                             myNormStride;
  size_t                             myTexStride;
  size_t                             myColStride;
  Graphic3d_TypeOfPrimitiveArray     myType;
};
