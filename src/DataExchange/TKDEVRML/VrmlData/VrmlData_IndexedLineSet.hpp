#pragma once

#include <VrmlData_Geometry.hpp>
#include <VrmlData_Coordinate.hpp>
#include <VrmlData_Color.hpp>

class VrmlData_IndexedLineSet : public VrmlData_Geometry
{
public:
  inline VrmlData_IndexedLineSet()
      : myArrPolygons(nullptr),
        myArrColorInd(nullptr),
        myNbPolygons(0),
        myNbColors(0),
        myColorPerVertex(true)
  {
  }

  inline VrmlData_IndexedLineSet(const VrmlData_Scene& theScene,
                                 const char*           theName,
                                 const bool            isColorPerVertex = true)
      : VrmlData_Geometry(theScene, theName),
        myArrPolygons(nullptr),
        myArrColorInd(nullptr),
        myNbPolygons(0),
        myNbColors(0),
        myColorPerVertex(isColorPerVertex)
  {
  }

  inline const occ::handle<VrmlData_Coordinate>& Coordinates() const { return myCoords; }

  inline void SetCoordinates(const occ::handle<VrmlData_Coordinate>& theCoord)
  {
    myCoords = theCoord;
  }

  inline const occ::handle<VrmlData_Color>& Colors() const { return myColors; }

  inline void SetColors(const occ::handle<VrmlData_Color>& theColors) { myColors = theColors; }

  inline size_t Polygons(const int**& arrPolygons) const
  {
    arrPolygons = myArrPolygons;
    return myNbPolygons;
  }

  inline int Polygon(const int iPolygon, const int*& outIndice)
  {
    return *(outIndice = myArrPolygons[iPolygon])++;
  }

  inline void SetPolygons(const size_t nPolygons, const int** thePolygons)
  {
    myNbPolygons  = nPolygons;
    myArrPolygons = thePolygons;
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

  inline void SetColorPerVertex(const bool isColorPerVertex)
  {
    myColorPerVertex = isColorPerVertex;
  }

  Standard_EXPORT const occ::handle<TopoDS_TShape>& TShape() override;

  Standard_EXPORT occ::handle<VrmlData_Node> Clone(
    const occ::handle<VrmlData_Node>& theOther) const override;

  Standard_EXPORT VrmlData_ErrorStatus Read(VrmlData_InBuffer& theBuffer) override;

  Standard_EXPORT VrmlData_ErrorStatus Write(const char* thePrefix) const override;

  Standard_EXPORT bool IsDefault() const override;

private:
  occ::handle<VrmlData_Coordinate> myCoords;
  occ::handle<VrmlData_Color>      myColors;
  const int**                      myArrPolygons;
  const int**                      myArrColorInd;
  size_t                           myNbPolygons;
  size_t                           myNbColors;
  bool                             myColorPerVertex;

public:
  DEFINE_STANDARD_RTTIEXT(VrmlData_IndexedLineSet, VrmlData_Geometry)
};
