#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <gp_Pnt.hpp>
#include <gp_Pnt2d.hpp>
#include <NCollection_Array1.hpp>
#include <Precision.hpp>
#include <ShapeExtend_Status.hpp>
#include <Standard_Transient.hpp>

#include <utility>

class Geom2d_Curve;
class Geom_Curve;
class Geom_Surface;
class ShapeAnalysis_Surface;

#ifdef Status
  #undef Status
#endif

class ShapeConstruct_ProjectCurveOnSurface : public Standard_Transient
{
public:
  using ArrayOfPnt   = NCollection_Array1<gp_Pnt>;
  using ArrayOfPnt2d = NCollection_Array1<gp_Pnt2d>;
  using ArrayOfReal  = NCollection_Array1<double>;

  using CachePoint = std::pair<gp_Pnt, gp_Pnt2d>;
  using CacheArray = NCollection_Array1<CachePoint>;

public:
  Standard_EXPORT ShapeConstruct_ProjectCurveOnSurface();

  Standard_EXPORT virtual void Init(const occ::handle<Geom_Surface>& theSurf,
                                    const double                     thePreci);

  Standard_EXPORT virtual void Init(const occ::handle<ShapeAnalysis_Surface>& theSurf,
                                    const double                              thePreci);

  Standard_EXPORT void SetSurface(const occ::handle<Geom_Surface>& theSurf);

  Standard_EXPORT void SetSurface(const occ::handle<ShapeAnalysis_Surface>& theSurf);

  Standard_EXPORT void SetPrecision(const double thePreci);

  Standard_EXPORT int& AdjustOverDegenMode();

  Standard_EXPORT bool Status(const ShapeExtend_Status theStatus) const;

  Standard_EXPORT virtual bool Perform(const occ::handle<Geom_Curve>& theC3D,
                                       const double                   theFirst,
                                       const double                   theLast,
                                       occ::handle<Geom2d_Curve>&     theC2D,
                                       const double theTolFirst = Precision::Confusion(),
                                       const double theTolLast  = Precision::Confusion());

  DEFINE_STANDARD_RTTIEXT(ShapeConstruct_ProjectCurveOnSurface, Standard_Transient)

protected:
  Standard_EXPORT occ::handle<Geom2d_Curve> getLine(const ArrayOfPnt&  thePoints,
                                                    const ArrayOfReal& theParams,
                                                    ArrayOfPnt2d&      thePoints2d,
                                                    const double       theTol,
                                                    bool&              theIsRecompute,
                                                    bool&              theIsFromCache) const;

  Standard_EXPORT bool PerformByProjLib(const occ::handle<Geom_Curve>& theC3D,
                                        const double                   theFirst,
                                        const double                   theLast,
                                        occ::handle<Geom2d_Curve>&     theC2D);

  Standard_EXPORT occ::handle<Geom2d_Curve> projectAnalytic(
    const occ::handle<Geom_Curve>& theC3D) const;

  Standard_EXPORT bool approxPCurve(const int                      theNbPnt,
                                    const occ::handle<Geom_Curve>& theC3D,
                                    const double                   theTolFirst,
                                    const double                   theTolLast,
                                    ArrayOfPnt&                    thePoints,
                                    ArrayOfReal&                   theParams,
                                    ArrayOfPnt2d&                  thePoints2d,
                                    occ::handle<Geom2d_Curve>&     theC2D);

  Standard_EXPORT void correctExtremity(const occ::handle<Geom_Curve>& theC3D,
                                        const ArrayOfReal&             theParams,
                                        ArrayOfPnt2d&                  thePoints2d,
                                        const bool                     theIsFirstPoint,
                                        const gp_Pnt2d&                thePointOnIsoLine,
                                        const bool                     theIsUIso);

  Standard_EXPORT void insertAdditionalPointOrAdjust(bool&                          theToAdjust,
                                                     const int                      theIndCoord,
                                                     const double                   thePeriod,
                                                     const double                   theTolOnPeriod,
                                                     double&                        theCurCoord,
                                                     const double                   thePrevCoord,
                                                     const occ::handle<Geom_Curve>& theC3D,
                                                     int&                           theIndex,
                                                     ArrayOfPnt&                    thePoints,
                                                     ArrayOfReal&                   theParams,
                                                     ArrayOfPnt2d&                  thePoints2d);

  Standard_EXPORT occ::handle<Geom2d_Curve> interpolatePCurve(const int           theNbPnt,
                                                              const ArrayOfPnt2d& thePoints2d,
                                                              const ArrayOfReal&  theParams) const;

  Standard_EXPORT occ::handle<Geom2d_Curve> approximatePCurve(const ArrayOfPnt2d& thePoints2d,
                                                              const ArrayOfReal&  theParams) const;

  Standard_EXPORT void checkPoints(ArrayOfPnt&  thePoints,
                                   ArrayOfReal& theParams,
                                   double&      thePreci) const;

  Standard_EXPORT void checkPoints2d(ArrayOfPnt2d& thePoints2d,
                                     ArrayOfReal&  theParams,
                                     double&       thePreci) const;

  Standard_EXPORT bool isAnIsoparametric(const int                theNbPnt,
                                         const ArrayOfPnt&        thePoints,
                                         const ArrayOfReal&       theParams,
                                         bool&                    theIsTypeU,
                                         bool&                    theP1OnIso,
                                         gp_Pnt2d&                theValueP1,
                                         bool&                    theP2OnIso,
                                         gp_Pnt2d&                theValueP2,
                                         bool&                    theIsoPar2d3d,
                                         occ::handle<Geom_Curve>& theCIso,
                                         double&                  theT1,
                                         double&                  theT2,
                                         ArrayOfReal&             theParamsOut) const;

private:
  occ::handle<ShapeAnalysis_Surface> mySurf;
  double                             myPreci;
  int                                myStatus;
  int                                myAdjustOverDegen;
  CacheArray                         myCache;
};
