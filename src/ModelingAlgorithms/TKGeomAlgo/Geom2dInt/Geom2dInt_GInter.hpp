#pragma once

#include <Geom2dInt_TheCurveLocatorOfTheProjPCurOfGInter.hpp>
#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <IntCurve_IntConicConic.hpp>
#include <Geom2dInt_TheIntConicCurveOfGInter.hpp>
#include <Geom2dInt_TheIntPCurvePCurveOfGInter.hpp>
#include <IntRes2d_Intersection.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
class Standard_ConstructionError;
class Adaptor2d_Curve2d;
class Geom2dInt_Geom2dCurveTool;
class Geom2dInt_TheProjPCurOfGInter;
class Geom2dInt_TheIntConicCurveOfGInter;
class Geom2dInt_TheIntersectorOfTheIntConicCurveOfGInter;
class Geom2dInt_IntConicCurveOfGInter;
class Geom2dInt_TheIntPCurvePCurveOfGInter;
class Geom2dInt_ThePolygon2dOfTheIntPCurvePCurveOfGInter;
class Geom2dInt_TheDistBetweenPCurvesOfTheIntPCurvePCurveOfGInter;
class Geom2dInt_ExactIntersectionPointOfTheIntPCurvePCurveOfGInter;
class IntRes2d_Domain;

class Geom2dInt_GInter : public IntRes2d_Intersection
{
public:
  DEFINE_STANDARD_ALLOC

  Geom2dInt_GInter();

  Geom2dInt_GInter(const Adaptor2d_Curve2d& C, const double TolConf, const double Tol);

  Geom2dInt_GInter(const Adaptor2d_Curve2d& C,
                   const IntRes2d_Domain&   D,
                   const double             TolConf,
                   const double             Tol);

  Geom2dInt_GInter(const Adaptor2d_Curve2d& C1,
                   const Adaptor2d_Curve2d& C2,
                   const double             TolConf,
                   const double             Tol);

  Geom2dInt_GInter(const Adaptor2d_Curve2d& C1,
                   const IntRes2d_Domain&   D1,
                   const Adaptor2d_Curve2d& C2,
                   const double             TolConf,
                   const double             Tol);

  Geom2dInt_GInter(const Adaptor2d_Curve2d& C1,
                   const Adaptor2d_Curve2d& C2,
                   const IntRes2d_Domain&   D2,
                   const double             TolConf,
                   const double             Tol);

  Geom2dInt_GInter(const Adaptor2d_Curve2d& C1,
                   const IntRes2d_Domain&   D1,
                   const Adaptor2d_Curve2d& C2,
                   const IntRes2d_Domain&   D2,
                   const double             TolConf,
                   const double             Tol);

  Standard_EXPORT void Perform(const Adaptor2d_Curve2d& C1,
                               const IntRes2d_Domain&   D1,
                               const Adaptor2d_Curve2d& C2,
                               const IntRes2d_Domain&   D2,
                               const double             TolConf,
                               const double             Tol);

  void Perform(const Adaptor2d_Curve2d& C1,
               const Adaptor2d_Curve2d& C2,
               const double             TolConf,
               const double             Tol);

  Standard_EXPORT void Perform(const Adaptor2d_Curve2d& C1,
                               const IntRes2d_Domain&   D1,
                               const double             TolConf,
                               const double             Tol);

  Standard_EXPORT void Perform(const Adaptor2d_Curve2d& C1, const double TolConf, const double Tol);

  void Perform(const Adaptor2d_Curve2d& C1,
               const IntRes2d_Domain&   D1,
               const Adaptor2d_Curve2d& C2,
               const double             TolConf,
               const double             Tol);

  void Perform(const Adaptor2d_Curve2d& C1,
               const Adaptor2d_Curve2d& C2,
               const IntRes2d_Domain&   D2,
               const double             TolConf,
               const double             Tol);

  Standard_EXPORT IntRes2d_Domain ComputeDomain(const Adaptor2d_Curve2d& C1,
                                                const double             TolDomain) const;

  Standard_EXPORT void SetMinNbSamples(const int theMinNbSamples);
  Standard_EXPORT int  GetMinNbSamples() const;

private:
  Standard_EXPORT void InternalPerform(const Adaptor2d_Curve2d& C1,
                                       const IntRes2d_Domain&   D1,
                                       const Adaptor2d_Curve2d& C2,
                                       const IntRes2d_Domain&   D2,
                                       const double             TolConf,
                                       const double             Tol,
                                       const bool               Composite);

  Standard_EXPORT void InternalCompositePerform_noRecurs(const int                NbInterC1,
                                                         const Adaptor2d_Curve2d& C1,
                                                         const int                NumInterC1,
                                                         const NCollection_Array1<double>& Tab1,
                                                         const IntRes2d_Domain&            D1,
                                                         const int                NbInterC2,
                                                         const Adaptor2d_Curve2d& C2,
                                                         const int                NumInterC2,
                                                         const NCollection_Array1<double>& Tab2,
                                                         const IntRes2d_Domain&            D2,
                                                         const double                      TolConf,
                                                         const double                      Tol);

  Standard_EXPORT void InternalCompositePerform(const Adaptor2d_Curve2d&          C1,
                                                const IntRes2d_Domain&            D1,
                                                const int                         N1,
                                                const int                         NB1,
                                                const NCollection_Array1<double>& Tab1,
                                                const Adaptor2d_Curve2d&          C2,
                                                const IntRes2d_Domain&            D2,
                                                const int                         N2,
                                                const int                         NB2,
                                                const NCollection_Array1<double>& Tab2,
                                                const double                      TolConf,
                                                const double                      Tol,
                                                const bool                        Composite);

  double                               param1inf;
  double                               param1sup;
  double                               param2inf;
  double                               param2sup;
  IntCurve_IntConicConic               intconiconi;
  Geom2dInt_TheIntConicCurveOfGInter   intconicurv;
  Geom2dInt_TheIntPCurvePCurveOfGInter intcurvcurv;
};

#define TheCurve Adaptor2d_Curve2d
#define TheCurve_hxx <Adaptor2d_Curve2d.hpp>
#define TheCurveTool Geom2dInt_Geom2dCurveTool
#define TheCurveTool_hxx <Geom2dInt_Geom2dCurveTool.hpp>
#define IntCurve_TheProjPCur Geom2dInt_TheProjPCurOfGInter
#define IntCurve_TheProjPCur_hxx <Geom2dInt_TheProjPCurOfGInter.hpp>
#define IntCurve_TheCurveLocatorOfTheProjPCur Geom2dInt_TheCurveLocatorOfTheProjPCurOfGInter
#define IntCurve_TheCurveLocatorOfTheProjPCur_hxx                                                  \
  <Geom2dInt_TheCurveLocatorOfTheProjPCurOfGInter.hpp>
#define IntCurve_TheLocateExtPCOfTheProjPCur Geom2dInt_TheLocateExtPCOfTheProjPCurOfGInter
#define IntCurve_TheLocateExtPCOfTheProjPCur_hxx                                                   \
  <Geom2dInt_TheLocateExtPCOfTheProjPCurOfGInter.hpp>
#define IntCurve_TheCurveLocatorOfTheProjPCur Geom2dInt_TheCurveLocatorOfTheProjPCurOfGInter
#define IntCurve_TheCurveLocatorOfTheProjPCur_hxx                                                  \
  <Geom2dInt_TheCurveLocatorOfTheProjPCurOfGInter.hpp>
#define IntCurve_TheLocateExtPCOfTheProjPCur Geom2dInt_TheLocateExtPCOfTheProjPCurOfGInter
#define IntCurve_TheLocateExtPCOfTheProjPCur_hxx                                                   \
  <Geom2dInt_TheLocateExtPCOfTheProjPCurOfGInter.hpp>
#define IntCurve_TheIntConicCurve Geom2dInt_TheIntConicCurveOfGInter
#define IntCurve_TheIntConicCurve_hxx <Geom2dInt_TheIntConicCurveOfGInter.hpp>
#define IntCurve_TheIntersectorOfTheIntConicCurve Geom2dInt_TheIntersectorOfTheIntConicCurveOfGInter
#define IntCurve_TheIntersectorOfTheIntConicCurve_hxx                                              \
  <Geom2dInt_TheIntersectorOfTheIntConicCurveOfGInter.hpp>
#define IntCurve_TheIntersectorOfTheIntConicCurve Geom2dInt_TheIntersectorOfTheIntConicCurveOfGInter
#define IntCurve_TheIntersectorOfTheIntConicCurve_hxx                                              \
  <Geom2dInt_TheIntersectorOfTheIntConicCurveOfGInter.hpp>
#define IntCurve_IntConicCurve Geom2dInt_IntConicCurveOfGInter
#define IntCurve_IntConicCurve_hxx <Geom2dInt_IntConicCurveOfGInter.hpp>
#define IntCurve_TheIntPCurvePCurve Geom2dInt_TheIntPCurvePCurveOfGInter
#define IntCurve_TheIntPCurvePCurve_hxx <Geom2dInt_TheIntPCurvePCurveOfGInter.hpp>
#define IntCurve_ThePolygon2dOfTheIntPCurvePCurve Geom2dInt_ThePolygon2dOfTheIntPCurvePCurveOfGInter
#define IntCurve_ThePolygon2dOfTheIntPCurvePCurve_hxx                                              \
  <Geom2dInt_ThePolygon2dOfTheIntPCurvePCurveOfGInter.hpp>
#define IntCurve_TheDistBetweenPCurvesOfTheIntPCurvePCurve                                         \
  Geom2dInt_TheDistBetweenPCurvesOfTheIntPCurvePCurveOfGInter
#define IntCurve_TheDistBetweenPCurvesOfTheIntPCurvePCurve_hxx                                     \
  <Geom2dInt_TheDistBetweenPCurvesOfTheIntPCurvePCurveOfGInter.hpp>
#define IntCurve_ExactIntersectionPointOfTheIntPCurvePCurve                                        \
  Geom2dInt_ExactIntersectionPointOfTheIntPCurvePCurveOfGInter
#define IntCurve_ExactIntersectionPointOfTheIntPCurvePCurve_hxx                                    \
  <Geom2dInt_ExactIntersectionPointOfTheIntPCurvePCurveOfGInter.hpp>
#define IntCurve_ThePolygon2dOfTheIntPCurvePCurve Geom2dInt_ThePolygon2dOfTheIntPCurvePCurveOfGInter
#define IntCurve_ThePolygon2dOfTheIntPCurvePCurve_hxx                                              \
  <Geom2dInt_ThePolygon2dOfTheIntPCurvePCurveOfGInter.hpp>
#define IntCurve_TheDistBetweenPCurvesOfTheIntPCurvePCurve                                         \
  Geom2dInt_TheDistBetweenPCurvesOfTheIntPCurvePCurveOfGInter
#define IntCurve_TheDistBetweenPCurvesOfTheIntPCurvePCurve_hxx                                     \
  <Geom2dInt_TheDistBetweenPCurvesOfTheIntPCurvePCurveOfGInter.hpp>
#define IntCurve_ExactIntersectionPointOfTheIntPCurvePCurve                                        \
  Geom2dInt_ExactIntersectionPointOfTheIntPCurvePCurveOfGInter
#define IntCurve_ExactIntersectionPointOfTheIntPCurvePCurve_hxx                                    \
  <Geom2dInt_ExactIntersectionPointOfTheIntPCurvePCurveOfGInter.hpp>
#define IntCurve_IntCurveCurveGen Geom2dInt_GInter
#define IntCurve_IntCurveCurveGen_hxx <Geom2dInt_GInter.hpp>

#include <IntCurve_IntCurveCurveGen_1.hpp>

#undef TheCurve
#undef TheCurve_hxx
#undef TheCurveTool
#undef TheCurveTool_hxx
#undef IntCurve_TheProjPCur
#undef IntCurve_TheProjPCur_hxx
#undef IntCurve_TheCurveLocatorOfTheProjPCur
#undef IntCurve_TheCurveLocatorOfTheProjPCur_hxx
#undef IntCurve_TheLocateExtPCOfTheProjPCur
#undef IntCurve_TheLocateExtPCOfTheProjPCur_hxx
#undef IntCurve_TheCurveLocatorOfTheProjPCur
#undef IntCurve_TheCurveLocatorOfTheProjPCur_hxx
#undef IntCurve_TheLocateExtPCOfTheProjPCur
#undef IntCurve_TheLocateExtPCOfTheProjPCur_hxx
#undef IntCurve_TheIntConicCurve
#undef IntCurve_TheIntConicCurve_hxx
#undef IntCurve_TheIntersectorOfTheIntConicCurve
#undef IntCurve_TheIntersectorOfTheIntConicCurve_hxx
#undef IntCurve_TheIntersectorOfTheIntConicCurve
#undef IntCurve_TheIntersectorOfTheIntConicCurve_hxx
#undef IntCurve_IntConicCurve
#undef IntCurve_IntConicCurve_hxx
#undef IntCurve_TheIntPCurvePCurve
#undef IntCurve_TheIntPCurvePCurve_hxx
#undef IntCurve_ThePolygon2dOfTheIntPCurvePCurve
#undef IntCurve_ThePolygon2dOfTheIntPCurvePCurve_hxx
#undef IntCurve_TheDistBetweenPCurvesOfTheIntPCurvePCurve
#undef IntCurve_TheDistBetweenPCurvesOfTheIntPCurvePCurve_hxx
#undef IntCurve_ExactIntersectionPointOfTheIntPCurvePCurve
#undef IntCurve_ExactIntersectionPointOfTheIntPCurvePCurve_hxx
#undef IntCurve_ThePolygon2dOfTheIntPCurvePCurve
#undef IntCurve_ThePolygon2dOfTheIntPCurvePCurve_hxx
#undef IntCurve_TheDistBetweenPCurvesOfTheIntPCurvePCurve
#undef IntCurve_TheDistBetweenPCurvesOfTheIntPCurvePCurve_hxx
#undef IntCurve_ExactIntersectionPointOfTheIntPCurvePCurve
#undef IntCurve_ExactIntersectionPointOfTheIntPCurvePCurve_hxx
#undef IntCurve_IntCurveCurveGen
#undef IntCurve_IntCurveCurveGen_hxx
