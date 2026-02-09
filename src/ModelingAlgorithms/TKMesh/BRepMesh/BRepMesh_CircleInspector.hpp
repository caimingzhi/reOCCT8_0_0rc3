#pragma once

#include <IMeshData_Types.hpp>
#include <BRepMesh_Circle.hpp>
#include <gp_XY.hpp>
#include <NCollection_CellFilter.hpp>

class BRepMesh_CircleInspector : public NCollection_CellFilter_InspectorXY
{
public:
  typedef int Target;

  BRepMesh_CircleInspector(const double                                 theTolerance,
                           const int                                    theReservedSize,
                           const occ::handle<NCollection_IncAllocator>& theAllocator)
      : mySqTolerance(theTolerance * theTolerance),
        myResIndices(theAllocator),
        myCircles(theReservedSize, theAllocator)
  {
  }

  void Bind(const int theIndex, const BRepMesh_Circle& theCircle)
  {
    myCircles.SetValue(theIndex, theCircle);
  }

  const IMeshData::VectorOfCircle& Circles() const { return myCircles; }

  BRepMesh_Circle& Circle(const int theIndex) { return myCircles(theIndex); }

  void SetPoint(const gp_XY& thePoint)
  {
    myResIndices.Clear();
    myPoint = thePoint;
  }

  IMeshData::ListOfInteger& GetShotCircles() { return myResIndices; }

  NCollection_CellFilter_Action Inspect(const int theTargetIndex)
  {
    BRepMesh_Circle& aCircle = myCircles(theTargetIndex);
    const double&    aRadius = aCircle.Radius();
    if (aRadius < 0.)
      return CellFilter_Purge;

    gp_XY& aLoc = const_cast<gp_XY&>(aCircle.Location());

    const double aDX = myPoint.ChangeCoord(1) - aLoc.ChangeCoord(1);
    const double aDY = myPoint.ChangeCoord(2) - aLoc.ChangeCoord(2);

    if ((aDX * aDX + aDY * aDY) - (aRadius * aRadius) <= mySqTolerance)
      myResIndices.Append(theTargetIndex);

    return CellFilter_Keep;
  }

  static bool IsEqual(const int theIndex, const int theTargetIndex)
  {
    return (theIndex == theTargetIndex);
  }

private:
  double                    mySqTolerance;
  IMeshData::ListOfInteger  myResIndices;
  IMeshData::VectorOfCircle myCircles;
  gp_XY                     myPoint;
};
