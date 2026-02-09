#pragma once

#include <TopoDS_Edge.hpp>
#include <TopoDS_Wire.hpp>
#include <Geom2d_Curve.hpp>
#include <Geom_Plane.hpp>
#include <NCollection_List.hpp>
#include <NCollection_Sequence.hpp>
#include <Standard_Integer.hpp>

class FilletPoint;

class ChFi2d_FilletAlgo
{
public:
  Standard_EXPORT ChFi2d_FilletAlgo();

  Standard_EXPORT ChFi2d_FilletAlgo(const TopoDS_Wire& theWire, const gp_Pln& thePlane);

  Standard_EXPORT ChFi2d_FilletAlgo(const TopoDS_Edge& theEdge1,
                                    const TopoDS_Edge& theEdge2,
                                    const gp_Pln&      thePlane);

  Standard_EXPORT void Init(const TopoDS_Wire& theWire, const gp_Pln& thePlane);

  Standard_EXPORT void Init(const TopoDS_Edge& theEdge1,
                            const TopoDS_Edge& theEdge2,
                            const gp_Pln&      thePlane);

  Standard_EXPORT bool Perform(const double theRadius);

  Standard_EXPORT int NbResults(const gp_Pnt& thePoint);

  Standard_EXPORT TopoDS_Edge Result(const gp_Pnt& thePoint,
                                     TopoDS_Edge&  theEdge1,
                                     TopoDS_Edge&  theEdge2,
                                     const int     iSolution = -1);

private:
  void FillPoint(FilletPoint*, const double theLimit);

  void FillDiff(FilletPoint*, double theDiffStep, bool theFront);

  void PerformNewton(FilletPoint*, FilletPoint*);

  bool ProcessPoint(FilletPoint*, FilletPoint*, double);

  TopoDS_Edge myEdge1, myEdge2;

  occ::handle<Geom_Plane> myPlane;

  occ::handle<Geom2d_Curve> myCurve1, myCurve2;

  double myStart1, myEnd1, myStart2, myEnd2, myRadius;

  NCollection_List<double> myResultParams;

  NCollection_Sequence<int> myResultOrientation;

  bool myStartSide;

  bool myEdgesExchnged;

  int myDegreeOfRecursion;
};

class FilletPoint
{
public:
  FilletPoint(const double theParam);

  void setParam(double theParam) { myParam = theParam; }

  double getParam() const { return myParam; }

  int getNBValues() { return myV.Length(); }

  double getValue(int theIndex) { return myV.Value(theIndex); }

  double getDiff(int theIndex) { return myD.Value(theIndex); }

  bool isValid(int theIndex) { return myValid.Value(theIndex); }

  int getNear(int theIndex) { return myNear.Value(theIndex); }

  void setParam2(const double theParam2) { myParam2 = theParam2; }

  double getParam2() { return myParam2; }

  void setCenter(const gp_Pnt2d thePoint) { myCenter = thePoint; }

  const gp_Pnt2d getCenter() { return myCenter; }

  void appendValue(double theValue, bool theValid);

  bool calculateDiff(FilletPoint*);

  void FilterPoints(FilletPoint*);

  FilletPoint* Copy();

  int hasSolution(double theRadius);

  double LowerValue()
  {
    int    a, aResultIndex = 0;
    double aValue;
    for (a = myV.Length(); a > 0; a--)
    {
      if (aResultIndex == 0 || std::abs(aValue) > std::abs(myV.Value(a)))
      {
        aResultIndex = a;
        aValue       = myV.Value(a);
      }
    }
    return aValue;
  }

  void remove(int theIndex);

private:
  double myParam;

  double myParam2;

  NCollection_Sequence<double> myV, myD;

  gp_Pnt2d myCenter;

  NCollection_Sequence<bool> myValid;
  NCollection_Sequence<int>  myNear;
};
