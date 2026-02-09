#pragma once

#include <VrmlData_Geometry.hpp>

class VrmlData_Faceted : public VrmlData_Geometry
{
public:
  inline VrmlData_Faceted()
      : myCreaseAngle(0.),
        myIsCCW(true),
        myIsSolid(true),
        myIsConvex(true)
  {
  }

  inline VrmlData_Faceted(const VrmlData_Scene& theScene,
                          const char*           theName,
                          const bool            isCCW,
                          const bool            isSolid,
                          const bool            isConvex,
                          const double          theCreaseAngle)
      : VrmlData_Geometry(theScene, theName),
        myCreaseAngle(theCreaseAngle),
        myIsCCW(isCCW),
        myIsSolid(isSolid),
        myIsConvex(isConvex)
  {
  }

  inline bool IsCCW() const { return myIsCCW; }

  inline bool IsSolid() const { return myIsSolid; }

  inline bool IsConvex() const { return myIsConvex; }

  inline double CreaseAngle() const { return myCreaseAngle; }

  inline void SetCCW(const bool theValue) { myIsCCW = theValue; }

  inline void SetSolid(const bool theValue) { myIsSolid = theValue; }

  inline void SetConvex(const bool theValue) { myIsConvex = theValue; }

  inline void SetCreaseAngle(const double theValue) { myCreaseAngle = theValue; }

protected:
  Standard_EXPORT VrmlData_ErrorStatus readData(VrmlData_InBuffer& theBuffer);

private:
  double myCreaseAngle;
  bool   myIsCCW : 1;
  bool   myIsSolid : 1;
  bool   myIsConvex : 1;

public:
  DEFINE_STANDARD_RTTI_INLINE(VrmlData_Faceted, VrmlData_Geometry)
};

#include <VrmlData_Coordinate.hpp>
#include <VrmlData_Normal.hpp>
#include <VrmlData_Color.hpp>
#include <VrmlData_TextureCoordinate.hpp>
#include <gp_XYZ.hpp>
#include <Quantity_Color.hpp>

class VrmlData_IndexedFaceSet : public VrmlData_Faceted
{
public:
  inline VrmlData_IndexedFaceSet()
      : myArrPolygons(nullptr),
        myArrNormalInd(nullptr),
        myArrColorInd(nullptr),
        myArrTextureInd(nullptr),
        myNbPolygons(0),
        myNbNormals(0),
        myNbColors(0),
        myNbTextures(0),
        myNormalPerVertex(true),
        myColorPerVertex(true)
  {
  }

  inline VrmlData_IndexedFaceSet(const VrmlData_Scene& theScene,
                                 const char*           theName,
                                 const bool            isCCW          = true,
                                 const bool            isSolid        = true,
                                 const bool            isConvex       = true,
                                 const double          theCreaseAngle = 0.)
      : VrmlData_Faceted(theScene, theName, isCCW, isSolid, isConvex, theCreaseAngle),
        myArrPolygons(nullptr),
        myArrNormalInd(nullptr),
        myArrColorInd(nullptr),
        myArrTextureInd(nullptr),
        myNbPolygons(0),
        myNbNormals(0),
        myNbColors(0),
        myNbTextures(0),
        myNormalPerVertex(true),
        myColorPerVertex(true)
  {
  }

  inline const occ::handle<VrmlData_Normal>& Normals() const { return myNormals; }

  inline const occ::handle<VrmlData_Color>& Colors() const { return myColors; }

  inline const occ::handle<VrmlData_TextureCoordinate>& TextureCoords() const { return myTxCoords; }

  inline const occ::handle<VrmlData_Coordinate>& Coordinates() const { return myCoords; }

  inline size_t Polygons(const int**& arrPolygons) const
  {
    arrPolygons = myArrPolygons;
    return myNbPolygons;
  }

  inline int Polygon(const int iFace, const int*& outIndice)
  {
    return *(outIndice = myArrPolygons[iFace])++;
  }

  inline void SetCoordinates(const occ::handle<VrmlData_Coordinate>& theCoord)
  {
    myCoords = theCoord;
  }

  inline void SetPolygons(const size_t nPolygons, const int** thePolygons)
  {
    myNbPolygons  = nPolygons;
    myArrPolygons = thePolygons;
  }

  inline size_t ArrayNormalInd(const int**& arrNormalInd) const
  {
    arrNormalInd = myArrNormalInd;
    return myNbNormals;
  }

  inline int IndiceNormals(const int iFace, const int*& outIndice)
  {
    return *(outIndice = myArrNormalInd[iFace])++;
  }

  Standard_EXPORT gp_XYZ GetNormal(const int iFace, const int iVertex);

  inline void SetNormalInd(const size_t nIndice, const int** theIndice)
  {
    myNbNormals    = nIndice;
    myArrNormalInd = theIndice;
  }

  inline void SetNormals(const occ::handle<VrmlData_Normal>& theNormals) { myNormals = theNormals; }

  inline void SetNormalPerVertex(const bool isNormalPerVertex)
  {
    myNormalPerVertex = isNormalPerVertex;
  }

  inline size_t ArrayColorInd(const int**& arrColorInd) const
  {
    arrColorInd = myArrColorInd;
    return myNbColors;
  }

  Standard_EXPORT Quantity_Color GetColor(const int iFace, const int iVertex);

  inline void SetColorInd(const size_t nIndice, const int** theIndice)
  {
    myNbColors    = nIndice;
    myArrColorInd = theIndice;
  }

  inline void SetColors(const occ::handle<VrmlData_Color>& theColors) { myColors = theColors; }

  inline void SetColorPerVertex(const bool isColorPerVertex)
  {
    myColorPerVertex = isColorPerVertex;
  }

  inline size_t ArrayTextureCoordInd(const int**& arrTextureCoordInd) const
  {
    arrTextureCoordInd = myArrTextureInd;
    return myNbTextures;
  }

  inline void SetTextureCoordInd(const size_t nIndice, const int** theIndice)
  {
    myNbTextures    = nIndice;
    myArrTextureInd = theIndice;
  }

  inline void SetTextureCoords(const occ::handle<VrmlData_TextureCoordinate>& tc)
  {
    myTxCoords = tc;
  }

  Standard_EXPORT const occ::handle<TopoDS_TShape>& TShape() override;

  Standard_EXPORT occ::handle<VrmlData_Node> Clone(
    const occ::handle<VrmlData_Node>& theOther) const override;

  Standard_EXPORT VrmlData_ErrorStatus Read(VrmlData_InBuffer& theBuffer) override;

  Standard_EXPORT VrmlData_ErrorStatus Write(const char* thePrefix) const override;

  Standard_EXPORT bool IsDefault() const override;

private:
  occ::handle<VrmlData_Coordinate>        myCoords;
  occ::handle<VrmlData_Normal>            myNormals;
  occ::handle<VrmlData_Color>             myColors;
  occ::handle<VrmlData_TextureCoordinate> myTxCoords;
  const int**                             myArrPolygons;
  const int**                             myArrNormalInd;
  const int**                             myArrColorInd;
  const int**                             myArrTextureInd;
  size_t                                  myNbPolygons;
  size_t                                  myNbNormals;
  size_t                                  myNbColors;
  size_t                                  myNbTextures;
  bool                                    myNormalPerVertex;
  bool                                    myColorPerVertex;

public:
  DEFINE_STANDARD_RTTIEXT(VrmlData_IndexedFaceSet, VrmlData_Faceted)
};
