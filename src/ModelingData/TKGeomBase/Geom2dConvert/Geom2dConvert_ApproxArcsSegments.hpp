#pragma once

#include <Geom2d_Curve.hpp>
#include <NCollection_Sequence.hpp>
#include <Geom2dConvert_PPoint.hpp>
#include <Geom2d_TrimmedCurve.hpp>
class Geom2dConvert_PPoint;

class Geom2dConvert_ApproxArcsSegments
{
public:
  enum Status
  {
    StatusOK = 0,
    StatusNotDone,
    StatusError
  };

  Standard_EXPORT Geom2dConvert_ApproxArcsSegments(const Adaptor2d_Curve2d& theCurve,
                                                   const double             theTolerance,
                                                   const double             theAngleTol);

  const NCollection_Sequence<occ::handle<Geom2d_Curve>>& GetResult() const { return mySeqCurves; }

private:
  occ::handle<Geom2d_Curve> makeCircle(const Geom2dConvert_PPoint& theFirst,
                                       const Geom2dConvert_PPoint& theLast) const;

  bool makeArc(const Geom2dConvert_PPoint&       theParam1,
               Geom2dConvert_PPoint&             theParam2,
               const bool                        isFirst,
               occ::handle<Geom2d_TrimmedCurve>& theCurve) const;

  occ::handle<Geom2d_TrimmedCurve> makeLine(Geom2dConvert_PPoint& theFirst,
                                            Geom2dConvert_PPoint& theLast,
                                            const bool            isCheck) const;

  bool makeFreeform();

  void getLinearParts(NCollection_Sequence<Geom2dConvert_PPoint>& theSeqParam);

  Geom2dConvert_PPoint findInflection(const Geom2dConvert_PPoint& theParamIsIn,
                                      const Geom2dConvert_PPoint& theParamNoIn) const;

  bool makeApproximation(Geom2dConvert_PPoint& theFirstParam, Geom2dConvert_PPoint& theLastParam);

  bool calculateBiArcs(Geom2dConvert_PPoint& theFirstParam, Geom2dConvert_PPoint& theLastParam);

  bool calculateLines(Geom2dConvert_PPoint& theFirstParam, Geom2dConvert_PPoint& theLastParam);

  bool checkCurve(const occ::handle<Geom2d_Curve>& aCurve,
                  const double                     theFirstParam,
                  const double                     theLastParam) const;

private:
  const Adaptor2d_Curve2d& myCurve;
  Geom2dConvert_PPoint     myExt[2];

  occ::handle<NCollection_BaseAllocator> myAlloc;
  double                                 myTolerance;
  double                                 myAngleTolerance;

  NCollection_Sequence<Geom2dConvert_PPoint>      mySeqParams;
  NCollection_Sequence<occ::handle<Geom2d_Curve>> mySeqCurves;
  Status                                          myStatus;

  void operator=(const Geom2dConvert_ApproxArcsSegments&) = delete;
};
