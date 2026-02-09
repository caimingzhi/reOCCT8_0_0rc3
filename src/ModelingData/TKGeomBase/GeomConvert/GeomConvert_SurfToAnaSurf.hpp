#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Real.hpp>
#include <Standard_Boolean.hpp>
#include <GeomConvert_ConvType.hpp>
#include <GeomAbs_SurfaceType.hpp>
#include <gp_XYZ.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
class Geom_Surface;
class Geom_SurfaceOfRevolution;
class Geom_Circle;

class GeomConvert_SurfToAnaSurf
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomConvert_SurfToAnaSurf();

  Standard_EXPORT GeomConvert_SurfToAnaSurf(const occ::handle<Geom_Surface>& S);

  Standard_EXPORT void Init(const occ::handle<Geom_Surface>& S);

  void SetConvType(const GeomConvert_ConvType theConvType = GeomConvert_Simplest)
  {
    myConvType = theConvType;
  }

  void SetTarget(const GeomAbs_SurfaceType theSurfType = GeomAbs_Plane) { myTarget = theSurfType; }

  double Gap() const { return myGap; }

  Standard_EXPORT occ::handle<Geom_Surface> ConvertToAnalytical(const double InitialToler);
  Standard_EXPORT occ::handle<Geom_Surface> ConvertToAnalytical(const double InitialToler,
                                                                const double Umin,
                                                                const double Umax,
                                                                const double Vmin,
                                                                const double Vmax);

  Standard_EXPORT static bool IsSame(const occ::handle<Geom_Surface>& S1,
                                     const occ::handle<Geom_Surface>& S2,
                                     const double                     tol);

  Standard_EXPORT static bool IsCanonical(const occ::handle<Geom_Surface>& S);

private:
  static void CheckVTrimForRevSurf(const occ::handle<Geom_SurfaceOfRevolution>& aRevSurf,
                                   double&                                      V1,
                                   double&                                      V2);

  static occ::handle<Geom_Surface> TryCylinerCone(const occ::handle<Geom_Surface>& theSurf,
                                                  const bool                       theVCase,
                                                  const occ::handle<Geom_Curve>&   theUmidiso,
                                                  const occ::handle<Geom_Curve>&   theVmidiso,
                                                  const double                     theU1,
                                                  const double                     theU2,
                                                  const double                     theV1,
                                                  const double                     theV2,
                                                  const double                     theToler);

  static bool GetCylByLS(const occ::handle<NCollection_HArray1<gp_XYZ>>& thePoints,
                         const double                                    theTol,
                         gp_Ax3&                                         thePos,
                         double&                                         theR,
                         double&                                         theGap);

  static occ::handle<Geom_Surface> TryCylinderByGaussField(const occ::handle<Geom_Surface>& theSurf,
                                                           const double                     theU1,
                                                           const double                     theU2,
                                                           const double                     theV1,
                                                           const double                     theV2,
                                                           const double theToler,
                                                           const int    theNbU         = 20,
                                                           const int    theNbV         = 20,
                                                           const bool   theLeastSquare = false);

  static occ::handle<Geom_Surface> TryTorusSphere(const occ::handle<Geom_Surface>& theSurf,
                                                  const occ::handle<Geom_Circle>&  circle,
                                                  const occ::handle<Geom_Circle>&  otherCircle,
                                                  const double                     Param1,
                                                  const double                     Param2,
                                                  const double                     aParam1ToCrv,
                                                  const double                     aParam2ToCrv,
                                                  const double                     toler,
                                                  const bool                       isTryUMajor);

  static double ComputeGap(const occ::handle<Geom_Surface>& theSurf,
                           const double                     theU1,
                           const double                     theU2,
                           const double                     theV1,
                           const double                     theV2,
                           const occ::handle<Geom_Surface>& theNewSurf,
                           const double                     theTol = RealLast());

private:
  occ::handle<Geom_Surface> mySurf;
  double                    myGap;
  GeomConvert_ConvType      myConvType;
  GeomAbs_SurfaceType       myTarget;
};
