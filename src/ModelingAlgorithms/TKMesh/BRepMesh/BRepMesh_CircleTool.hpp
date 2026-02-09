#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Macro.hpp>

#include <Standard_Real.hpp>
#include <BRepMesh_CircleInspector.hpp>
#include <gp_XY.hpp>
#include <Standard_Integer.hpp>
#include <Standard_Boolean.hpp>
#include <IMeshData_Types.hpp>
#include <NCollection_Array1.hpp>

class gp_Circ2d;

class BRepMesh_CircleTool
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepMesh_CircleTool(const occ::handle<NCollection_IncAllocator>& theAllocator);

  Standard_EXPORT BRepMesh_CircleTool(const int                                    theReservedSize,
                                      const occ::handle<NCollection_IncAllocator>& theAllocator);

  void Init(const int) { myTolerance = Precision::PConfusion(); }

  void SetCellSize(const double theSize) { myCellFilter.Reset(theSize, myAllocator); }

  void SetCellSize(const double theSizeX, const double theSizeY)
  {
    double                     aCellSizeC[2] = {theSizeX, theSizeY};
    NCollection_Array1<double> aCellSize(aCellSizeC[0], 1, 2);
    myCellFilter.Reset(aCellSize, myAllocator);
  }

  void SetMinMaxSize(const gp_XY& theMin, const gp_XY& theMax)
  {
    myFaceMin = theMin;
    myFaceMax = theMax;
  }

  bool IsEmpty() const { return mySelector.Circles().IsEmpty(); }

  Standard_EXPORT void Bind(const int theIndex, const gp_Circ2d& theCircle);

  Standard_EXPORT static bool MakeCircle(const gp_XY& thePoint1,
                                         const gp_XY& thePoint2,
                                         const gp_XY& thePoint3,
                                         gp_XY&       theLocation,
                                         double&      theRadius);

  Standard_EXPORT bool Bind(const int    theIndex,
                            const gp_XY& thePoint1,
                            const gp_XY& thePoint2,
                            const gp_XY& thePoint3);

  Standard_EXPORT void MocBind(const int theIndex);

  Standard_EXPORT void Delete(const int theIndex);

  Standard_EXPORT IMeshData::ListOfInteger& Select(const gp_XY& thePoint);

private:
  void bind(const int theIndex, const gp_XY& theLocation, const double theRadius);

private:
  double                                myTolerance;
  occ::handle<NCollection_IncAllocator> myAllocator;
  IMeshData::CircleCellFilter           myCellFilter;
  BRepMesh_CircleInspector              mySelector;
  gp_XY                                 myFaceMax;
  gp_XY                                 myFaceMin;
};
