#pragma once

#include <Standard_Integer.hpp>
#include <NCollection_List.hpp>
#include <NCollection_Vector.hpp>
#include <gp_XYZ.hpp>
#include <NCollection_CellFilter.hpp>

typedef NCollection_Vector<gp_XYZ> VectorOfPoint;

class BRepBuilderAPI_VertexInspector : public NCollection_CellFilter_InspectorXYZ
{
public:
  typedef int Target;

  BRepBuilderAPI_VertexInspector(const double theTol)
      : myTol(theTol * theTol)
  {
  }

  void Add(const gp_XYZ& thePnt) { myPoints.Append(thePnt); }

  void ClearResList() { myResInd.Clear(); }

  void SetCurrent(const gp_XYZ& theCurPnt) { myCurrent = theCurPnt; }

  const NCollection_List<int>& ResInd() { return myResInd; }

  Standard_EXPORT NCollection_CellFilter_Action Inspect(const int theTarget);

private:
  double                myTol;
  NCollection_List<int> myResInd;
  VectorOfPoint         myPoints;
  gp_XYZ                myCurrent;
};
