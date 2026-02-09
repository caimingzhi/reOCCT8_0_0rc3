#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDS_Edge.hpp>
#include <Standard_Real.hpp>
#include <Standard_Integer.hpp>
#include <BRepAdaptor_Curve.hpp>
#include <BRepAdaptor_Surface.hpp>
#include <Standard_Boolean.hpp>
#include <IntTools_CommonPrt.hpp>
#include <NCollection_Sequence.hpp>
#include <IntTools_Range.hpp>
class IntTools_Context;
class gp_Pnt;
class IntTools_CommonPrt;

class IntTools_EdgeFace
{
public:
  DEFINE_STANDARD_ALLOC

public:
  Standard_EXPORT IntTools_EdgeFace();

public:
  void SetEdge(const TopoDS_Edge& theEdge) { myEdge = theEdge; }

  const TopoDS_Edge& Edge() const { return myEdge; }

  void SetFace(const TopoDS_Face& theFace) { myFace = theFace; }

  const TopoDS_Face& Face() const { return myFace; }

  void SetRange(const IntTools_Range& theRange) { myRange = theRange; }

  void SetRange(const double theFirst, const double theLast)
  {
    myRange.SetFirst(theFirst);
    myRange.SetLast(theLast);
  }

  const IntTools_Range& Range() const { return myRange; }

  void SetContext(const occ::handle<IntTools_Context>& theContext) { myContext = theContext; }

  const occ::handle<IntTools_Context>& Context() const { return myContext; }

  void SetFuzzyValue(const double theFuzz)
  {
    myFuzzyValue = (std::max)(theFuzz, Precision::Confusion());
  }

  double FuzzyValue() const { return myFuzzyValue; }

  void UseQuickCoincidenceCheck(const bool theFlag) { myQuickCoincidenceCheck = theFlag; }

  bool IsCoincidenceCheckedQuickly() { return myQuickCoincidenceCheck; }

public:
  Standard_EXPORT void Perform();

public:
  bool IsDone() const { return myIsDone; }

  int ErrorStatus() const { return myErrorStatus; }

public:
  const NCollection_Sequence<IntTools_CommonPrt>& CommonParts() const { return mySeqOfCommonPrts; }

  double MinimalDistance() const { return myMinDistance; }

protected:
  Standard_EXPORT static bool IsEqDistance(const gp_Pnt&              aP,
                                           const BRepAdaptor_Surface& aS,
                                           const double               aT,
                                           double&                    aD);
  Standard_EXPORT void        CheckData();

  Standard_EXPORT bool IsProjectable(const double t) const;

  Standard_EXPORT double DistanceFunction(const double t);

  Standard_EXPORT int MakeType(IntTools_CommonPrt& aCP);

  Standard_EXPORT bool CheckTouch(const IntTools_CommonPrt& aCP, double& aTX);

  Standard_EXPORT bool CheckTouchVertex(const IntTools_CommonPrt& aCP, double& aTX);

  Standard_EXPORT bool IsCoincident();

protected:
  TopoDS_Edge                              myEdge;
  TopoDS_Face                              myFace;
  double                                   myFuzzyValue;
  BRepAdaptor_Curve                        myC;
  BRepAdaptor_Surface                      myS;
  double                                   myCriteria;
  bool                                     myIsDone;
  int                                      myErrorStatus;
  occ::handle<IntTools_Context>            myContext;
  NCollection_Sequence<IntTools_CommonPrt> mySeqOfCommonPrts;
  IntTools_Range                           myRange;
  bool                                     myQuickCoincidenceCheck;
  double                                   myMinDistance;
};
