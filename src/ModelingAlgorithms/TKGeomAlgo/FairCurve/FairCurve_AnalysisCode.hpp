#pragma once

//! To deal with different results in the computation of curvatures.
//! -   FairCurve_OK describes the case where computation is successfully
//! completed
//! -   FairCurve_NotConverged describes
//! the case where the algorithm does not
//! converge. In this case, you can not be
//! certain of the result quality and should
//! resume computation if you want to make use of the curve.
//! -   FairCurve_InfiniteSliding describes the case where sliding is infinite, and,
//! consequently, computation stops. The solution is to use an imposed sliding value.
//! -   FairCurve_NullHeight describes the case where no matter is left at one of the
//! ends of the curve, and as a result, computation stops. The solution is to
//! change (increase or reduce) the slope value by increasing or decreasing it.
enum FairCurve_AnalysisCode
{
  FairCurve_OK,
  FairCurve_NotConverged,
  FairCurve_InfiniteSliding,
  FairCurve_NullHeight
};
