#pragma once

#include <Standard_Integer.hpp>
#include <NCollection_List.hpp>
#include <NCollection_Vector.hpp>
#include <gp_XYZ.hpp>
#include <NCollection_CellFilter.hpp>

typedef NCollection_Vector<gp_XYZ> VectorOfPoint;

//=======================================================================
//! Class BRepBuilderAPI_VertexInspector
//!   derived from NCollection_CellFilter_InspectorXYZ
//!   This class define the Inspector interface for CellFilter algorithm,
//!   working with gp_XYZ points in 3d space.
//!   Used in search of coincidence points with a certain tolerance.
//=======================================================================

class BRepBuilderAPI_VertexInspector : public NCollection_CellFilter_InspectorXYZ
{
public:
  typedef int Target;

  //! Constructor; remembers the tolerance
  BRepBuilderAPI_VertexInspector(const double theTol)
      : myTol(theTol * theTol)
  {
  }

  //! Keep the points used for comparison
  void Add(const gp_XYZ& thePnt) { myPoints.Append(thePnt); }

  //! Clear the list of adjacent points
  void ClearResList() { myResInd.Clear(); }

  //! Set current point to search for coincidence
  void SetCurrent(const gp_XYZ& theCurPnt) { myCurrent = theCurPnt; }

  //! Get list of indexes of points adjacent with the current
  const NCollection_List<int>& ResInd() { return myResInd; }

  //! Implementation of inspection method
  Standard_EXPORT NCollection_CellFilter_Action Inspect(const int theTarget);

private:
  double                myTol;
  NCollection_List<int> myResInd;
  VectorOfPoint         myPoints;
  gp_XYZ                myCurrent;
};
