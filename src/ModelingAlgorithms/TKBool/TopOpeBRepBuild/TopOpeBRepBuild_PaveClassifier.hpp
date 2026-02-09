#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDS_Edge.hpp>
#include <TopAbs_Orientation.hpp>
#include <Standard_Integer.hpp>
#include <TopOpeBRepBuild_LoopClassifier.hpp>
#include <TopAbs_State.hpp>
class TopoDS_Shape;
class TopOpeBRepBuild_Loop;

class TopOpeBRepBuild_PaveClassifier : public TopOpeBRepBuild_LoopClassifier
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopOpeBRepBuild_PaveClassifier(const TopoDS_Shape& E);

  Standard_EXPORT TopAbs_State Compare(const occ::handle<TopOpeBRepBuild_Loop>& L1,
                                       const occ::handle<TopOpeBRepBuild_Loop>& L2) override;

  Standard_EXPORT void SetFirstParameter(const double P);

  Standard_EXPORT void ClosedVertices(const bool B);

  Standard_EXPORT static double AdjustCase(const double             p1,
                                           const TopAbs_Orientation o,
                                           const double             first,
                                           const double             period,
                                           const double             tol,
                                           int&                     cas);

private:
  Standard_EXPORT TopAbs_State CompareOnNonPeriodic();

  Standard_EXPORT TopAbs_State CompareOnPeriodic();

  Standard_EXPORT void AdjustOnPeriodic();

  Standard_EXPORT bool ToAdjustOnPeriodic() const;

  TopoDS_Edge        myEdge;
  bool               myEdgePeriodic;
  double             myFirst;
  double             myPeriod;
  bool               mySameParameters;
  bool               myClosedVertices;
  double             myP1;
  double             myP2;
  TopAbs_Orientation myO1;
  TopAbs_Orientation myO2;
  int                myCas1;
  int                myCas2;
};
