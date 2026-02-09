#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <BRepAdaptor_Curve.hpp>
#include <Standard_Integer.hpp>
#include <IntTools_CommonPrt.hpp>
#include <NCollection_Sequence.hpp>
#include <IntTools_Range.hpp>
#include <TopAbs_ShapeEnum.hpp>
class Geom_Curve;
class Bnd_Box;

class IntTools_EdgeEdge
{
public:
  DEFINE_STANDARD_ALLOC

  IntTools_EdgeEdge();

  ~IntTools_EdgeEdge();

  IntTools_EdgeEdge(const TopoDS_Edge& theEdge1, const TopoDS_Edge& theEdge2);

  IntTools_EdgeEdge(const TopoDS_Edge& theEdge1,
                    const double       aT11,
                    const double       aT12,
                    const TopoDS_Edge& theEdge2,
                    const double       aT21,
                    const double       aT22);

  void SetEdge1(const TopoDS_Edge& theEdge);

  void SetEdge1(const TopoDS_Edge& theEdge, const double aT1, const double aT2);

  void SetRange1(const IntTools_Range& theRange1);

  void SetRange1(const double aT1, const double aT2);

  void SetEdge2(const TopoDS_Edge& theEdge);

  void SetEdge2(const TopoDS_Edge& theEdge, const double aT1, const double aT2);

  void SetRange2(const IntTools_Range& theRange);

  void SetRange2(const double aT1, const double aT2);

  void SetFuzzyValue(const double theFuzz);

  Standard_EXPORT void Perform();

  bool IsDone() const;

  double FuzzyValue() const;

  const NCollection_Sequence<IntTools_CommonPrt>& CommonParts() const;

  void UseQuickCoincidenceCheck(const bool bFlag) { myQuickCoincidenceCheck = bFlag; }

  bool IsCoincidenceCheckedQuickly() { return myQuickCoincidenceCheck; }

protected:
  void CheckData();

  Standard_EXPORT void Prepare();

  Standard_EXPORT void ComputeLineLine();

  Standard_EXPORT void FindSolutions(NCollection_Sequence<IntTools_Range>& theRanges1,
                                     NCollection_Sequence<IntTools_Range>& theRanges2,
                                     bool&                                 bSplit2);

  Standard_EXPORT void FindSolutions(const IntTools_Range&                 theR1,
                                     const Bnd_Box&                        theBox1,
                                     const IntTools_Range&                 theR2,
                                     const Bnd_Box&                        theBox2,
                                     NCollection_Sequence<IntTools_Range>& theRanges1,
                                     NCollection_Sequence<IntTools_Range>& theRanges2);

  Standard_EXPORT void MergeSolutions(const NCollection_Sequence<IntTools_Range>& theRanges1,
                                      const NCollection_Sequence<IntTools_Range>& theRanges2,
                                      const bool                                  bSplit2);

  Standard_EXPORT static bool FindParameters(const BRepAdaptor_Curve& theBAC,
                                             const double             aT1,
                                             const double             aT2,
                                             const double             theTol,
                                             const double             theRes,
                                             const double             thePTol,
                                             const double             theResCoeff,
                                             const Bnd_Box&           theCBox,
                                             double&                  aTB1,
                                             double&                  aTB2);

  Standard_EXPORT int CheckCoincidence(const double aT11,
                                       const double aT12,
                                       const double aT21,
                                       const double aT22,
                                       const double theCriteria,
                                       const double theCurveRes1);

  Standard_EXPORT void AddSolution(const double           aT11,
                                   const double           aT12,
                                   const double           aT21,
                                   const double           aT22,
                                   const TopAbs_ShapeEnum theType);

  Standard_EXPORT void FindBestSolution(const double aT11,
                                        const double aT12,
                                        const double aT21,
                                        const double aT22,
                                        double&      aT1,
                                        double&      aT2);

  Standard_EXPORT bool IsIntersection(const double aT11,
                                      const double aT12,
                                      const double aT21,
                                      const double aT22);

  Standard_EXPORT bool IsCoincident();

  TopoDS_Edge                              myEdge1;
  TopoDS_Edge                              myEdge2;
  occ::handle<Geom_Curve>                  myGeom1;
  occ::handle<Geom_Curve>                  myGeom2;
  BRepAdaptor_Curve                        myCurve1;
  BRepAdaptor_Curve                        myCurve2;
  double                                   myTol1;
  double                                   myTol2;
  double                                   myTol;
  double                                   myFuzzyValue;
  double                                   myRes1;
  double                                   myRes2;
  double                                   myResCoeff1;
  double                                   myResCoeff2;
  double                                   myPTol1;
  double                                   myPTol2;
  IntTools_Range                           myRange1;
  IntTools_Range                           myRange2;
  bool                                     mySwap;
  int                                      myErrorStatus;
  NCollection_Sequence<IntTools_CommonPrt> myCommonParts;

  bool myQuickCoincidenceCheck;
};

#include <Precision.hpp>
#include <BRep_Tool.hpp>

inline IntTools_EdgeEdge::IntTools_EdgeEdge()
    : myTol1(0.),
      myTol2(0.),
      myTol(0.),
      myFuzzyValue(Precision::Confusion()),
      myRes1(0.),
      myRes2(0.),
      myResCoeff1(0.),
      myResCoeff2(0.),
      myPTol1(0.),
      myPTol2(0.),
      myRange1(0., 0.),
      myRange2(0., 0.),
      mySwap(false),
      myErrorStatus(0),
      myQuickCoincidenceCheck(false)
{
}

inline IntTools_EdgeEdge::IntTools_EdgeEdge(const TopoDS_Edge& theEdge1,
                                            const TopoDS_Edge& theEdge2)
    : myEdge1(theEdge1),
      myEdge2(theEdge2),
      myTol1(0.),
      myTol2(0.),
      myTol(0.),
      myFuzzyValue(Precision::Confusion()),
      myRes1(0.),
      myRes2(0.),
      myResCoeff1(0.),
      myResCoeff2(0.),
      myPTol1(0.),
      myPTol2(0.),
      myRange1(0., 0.),
      myRange2(0., 0.),
      mySwap(false),
      myErrorStatus(0),
      myQuickCoincidenceCheck(false)
{
}

inline IntTools_EdgeEdge::IntTools_EdgeEdge(const TopoDS_Edge& theEdge1,
                                            const double       aT11,
                                            const double       aT12,
                                            const TopoDS_Edge& theEdge2,
                                            const double       aT21,
                                            const double       aT22)
    : myEdge1(theEdge1),
      myEdge2(theEdge2),
      myTol1(0.),
      myTol2(0.),
      myTol(0.),
      myFuzzyValue(Precision::Confusion()),
      myRes1(0.),
      myRes2(0.),
      myResCoeff1(0.),
      myResCoeff2(0.),
      myPTol1(0.),
      myPTol2(0.),
      myRange1(aT11, aT12),
      myRange2(aT21, aT22),
      mySwap(false),
      myErrorStatus(0),
      myQuickCoincidenceCheck(false)
{
}

inline IntTools_EdgeEdge::~IntTools_EdgeEdge() = default;

inline void IntTools_EdgeEdge::SetEdge1(const TopoDS_Edge& theEdge)
{
  myEdge1 = theEdge;
}

inline void IntTools_EdgeEdge::SetRange1(const IntTools_Range& theRange)
{
  myRange1 = theRange;
}

inline void IntTools_EdgeEdge::SetRange1(const double aT1, const double aT2)
{
  myRange1.SetFirst(aT1);
  myRange1.SetLast(aT2);
}

inline void IntTools_EdgeEdge::SetEdge1(const TopoDS_Edge& theEdge,
                                        const double       aT1,
                                        const double       aT2)
{
  SetEdge1(theEdge);
  SetRange1(aT1, aT2);
}

inline void IntTools_EdgeEdge::SetEdge2(const TopoDS_Edge& theEdge)
{
  myEdge2 = theEdge;
}

inline void IntTools_EdgeEdge::SetRange2(const IntTools_Range& theRange)
{
  myRange2 = theRange;
}

inline void IntTools_EdgeEdge::SetRange2(const double aT1, const double aT2)
{
  myRange2.SetFirst(aT1);
  myRange2.SetLast(aT2);
}

inline void IntTools_EdgeEdge::SetEdge2(const TopoDS_Edge& theEdge,
                                        const double       aT1,
                                        const double       aT2)
{
  SetEdge2(theEdge);
  SetRange2(aT1, aT2);
}

inline void IntTools_EdgeEdge::SetFuzzyValue(const double theFuzz)
{
  myFuzzyValue = std::max(theFuzz, Precision::Confusion());
}

inline double IntTools_EdgeEdge::FuzzyValue() const
{
  return myFuzzyValue;
}

inline const NCollection_Sequence<IntTools_CommonPrt>& IntTools_EdgeEdge::CommonParts() const
{
  return myCommonParts;
}

inline bool IntTools_EdgeEdge::IsDone() const
{
  return (myErrorStatus == 0);
}

inline void IntTools_EdgeEdge::CheckData()
{
  if (myEdge1.IsNull() || myEdge2.IsNull())
  {
    myErrorStatus = 1;
    return;
  }

  if (BRep_Tool::Degenerated(myEdge1) || BRep_Tool::Degenerated(myEdge2))
  {
    myErrorStatus = 2;
    return;
  }

  if (!BRep_Tool::IsGeometric(myEdge1) || !BRep_Tool::IsGeometric(myEdge2))
  {
    myErrorStatus = 3;
    return;
  }
}
