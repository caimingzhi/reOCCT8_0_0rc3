#pragma once

#include <Approx_ParametrizationType.hpp>
#include <NCollection_List.hpp>
#include <NCollection_LocalArray.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_Vector.hpp>
#include <Standard_Boolean.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Integer.hpp>
#include <Standard_Macro.hpp>
#include <Standard_Real.hpp>
#include <NCollection_Array1.hpp>
#include <gp_Pnt.hpp>
#include <gp_Pnt2d.hpp>
#include <math_Vector.hpp>

class IntPatch_WLine;

class ApproxInt_KnotTools
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void BuildKnots(const NCollection_Array1<gp_Pnt>&   thePntsXYZ,
                                         const NCollection_Array1<gp_Pnt2d>& thePntsU1V1,
                                         const NCollection_Array1<gp_Pnt2d>& thePntsU2V2,
                                         const math_Vector&                  thePars,
                                         const bool                          theApproxXYZ,
                                         const bool                          theApproxU1V1,
                                         const bool                          theApproxU2V2,
                                         const int                           theMinNbPnts,
                                         NCollection_Vector<int>&            theKnots);

  Standard_EXPORT static void BuildCurvature(const NCollection_LocalArray<double>& theCoords,
                                             const int                             theDim,
                                             const math_Vector&                    thePars,
                                             NCollection_Array1<double>&           theCurv,
                                             double&                               theMaxCurv);

  Standard_EXPORT static Approx_ParametrizationType DefineParType(
    const occ::handle<IntPatch_WLine>& theWL,
    const int                          theFpar,
    const int                          theLpar,
    const bool                         theApproxXYZ,
    const bool                         theApproxU1V1,
    const bool                         theApproxU2V2);

private:
  static void ComputeKnotInds(const NCollection_LocalArray<double>& theCoords,
                              const int                             theDim,
                              const math_Vector&                    thePars,
                              NCollection_Sequence<int>&            theInds);

  static bool InsKnotBefI(const int                             theI,
                          const NCollection_Array1<double>&     theCurv,
                          const NCollection_LocalArray<double>& theCoords,
                          const int                             theDim,
                          NCollection_Sequence<int>&            theInds,
                          const bool                            ChkCurv);

  static void FilterKnots(NCollection_Sequence<int>& theInds,
                          const int                  theMinNbPnts,
                          NCollection_Vector<int>&   theLKnots);
};
