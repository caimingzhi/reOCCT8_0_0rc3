#include <HLRBRep_CInter.hpp>

#include <Standard_ConstructionError.hpp>
#include <HLRBRep_CurveTool.hpp>
#include <HLRBRep_TheProjPCurOfCInter.hpp>
#include <HLRBRep_TheCurveLocatorOfTheProjPCurOfCInter.hpp>
#include <HLRBRep_TheLocateExtPCOfTheProjPCurOfCInter.hpp>
#include <HLRBRep_TheIntConicCurveOfCInter.hpp>
#include <HLRBRep_TheIntersectorOfTheIntConicCurveOfCInter.hpp>
#include <HLRBRep_IntConicCurveOfCInter.hpp>
#include <HLRBRep_TheIntPCurvePCurveOfCInter.hpp>
#include <HLRBRep_ThePolygon2dOfTheIntPCurvePCurveOfCInter.hpp>
#include <HLRBRep_TheDistBetweenPCurvesOfTheIntPCurvePCurveOfCInter.hpp>
#include <HLRBRep_ExactIntersectionPointOfTheIntPCurvePCurveOfCInter.hpp>
#include <IntRes2d_Domain.hpp>

#define TheCurve HLRBRep_CurvePtr
#define TheCurve_hxx <HLRBRep_TypeDef.hpp>
#define TheCurveTool HLRBRep_CurveTool
#define TheCurveTool_hxx <HLRBRep_CurveTool.hpp>
#define IntCurve_TheProjPCur HLRBRep_TheProjPCurOfCInter
#define IntCurve_TheProjPCur_hxx <HLRBRep_TheProjPCurOfCInter.hpp>
#define IntCurve_TheCurveLocatorOfTheProjPCur HLRBRep_TheCurveLocatorOfTheProjPCurOfCInter
#define IntCurve_TheCurveLocatorOfTheProjPCur_hxx                                                  \
  <HLRBRep_TheCurveLocatorOfTheProjPCurOfCInter.hpp>
#define IntCurve_TheLocateExtPCOfTheProjPCur HLRBRep_TheLocateExtPCOfTheProjPCurOfCInter
#define IntCurve_TheLocateExtPCOfTheProjPCur_hxx <HLRBRep_TheLocateExtPCOfTheProjPCurOfCInter.hpp>
#define IntCurve_TheCurveLocatorOfTheProjPCur HLRBRep_TheCurveLocatorOfTheProjPCurOfCInter
#define IntCurve_TheCurveLocatorOfTheProjPCur_hxx                                                  \
  <HLRBRep_TheCurveLocatorOfTheProjPCurOfCInter.hpp>
#define IntCurve_TheLocateExtPCOfTheProjPCur HLRBRep_TheLocateExtPCOfTheProjPCurOfCInter
#define IntCurve_TheLocateExtPCOfTheProjPCur_hxx <HLRBRep_TheLocateExtPCOfTheProjPCurOfCInter.hpp>
#define IntCurve_TheIntConicCurve HLRBRep_TheIntConicCurveOfCInter
#define IntCurve_TheIntConicCurve_hxx <HLRBRep_TheIntConicCurveOfCInter.hpp>
#define IntCurve_TheIntersectorOfTheIntConicCurve HLRBRep_TheIntersectorOfTheIntConicCurveOfCInter
#define IntCurve_TheIntersectorOfTheIntConicCurve_hxx                                              \
  <HLRBRep_TheIntersectorOfTheIntConicCurveOfCInter.hpp>
#define IntCurve_TheIntersectorOfTheIntConicCurve HLRBRep_TheIntersectorOfTheIntConicCurveOfCInter
#define IntCurve_TheIntersectorOfTheIntConicCurve_hxx                                              \
  <HLRBRep_TheIntersectorOfTheIntConicCurveOfCInter.hpp>
#define IntCurve_IntConicCurve HLRBRep_IntConicCurveOfCInter
#define IntCurve_IntConicCurve_hxx <HLRBRep_IntConicCurveOfCInter.hpp>
#define IntCurve_TheIntPCurvePCurve HLRBRep_TheIntPCurvePCurveOfCInter
#define IntCurve_TheIntPCurvePCurve_hxx <HLRBRep_TheIntPCurvePCurveOfCInter.hpp>
#define IntCurve_ThePolygon2dOfTheIntPCurvePCurve HLRBRep_ThePolygon2dOfTheIntPCurvePCurveOfCInter
#define IntCurve_ThePolygon2dOfTheIntPCurvePCurve_hxx                                              \
  <HLRBRep_ThePolygon2dOfTheIntPCurvePCurveOfCInter.hpp>
#define IntCurve_TheDistBetweenPCurvesOfTheIntPCurvePCurve                                         \
  HLRBRep_TheDistBetweenPCurvesOfTheIntPCurvePCurveOfCInter
#define IntCurve_TheDistBetweenPCurvesOfTheIntPCurvePCurve_hxx                                     \
  <HLRBRep_TheDistBetweenPCurvesOfTheIntPCurvePCurveOfCInter.hpp>
#define IntCurve_ExactIntersectionPointOfTheIntPCurvePCurve                                        \
  HLRBRep_ExactIntersectionPointOfTheIntPCurvePCurveOfCInter
#define IntCurve_ExactIntersectionPointOfTheIntPCurvePCurve_hxx                                    \
  <HLRBRep_ExactIntersectionPointOfTheIntPCurvePCurveOfCInter.hpp>
#define IntCurve_ThePolygon2dOfTheIntPCurvePCurve HLRBRep_ThePolygon2dOfTheIntPCurvePCurveOfCInter
#define IntCurve_ThePolygon2dOfTheIntPCurvePCurve_hxx                                              \
  <HLRBRep_ThePolygon2dOfTheIntPCurvePCurveOfCInter.hpp>
#define IntCurve_TheDistBetweenPCurvesOfTheIntPCurvePCurve                                         \
  HLRBRep_TheDistBetweenPCurvesOfTheIntPCurvePCurveOfCInter
#define IntCurve_TheDistBetweenPCurvesOfTheIntPCurvePCurve_hxx                                     \
  <HLRBRep_TheDistBetweenPCurvesOfTheIntPCurvePCurveOfCInter.hpp>
#define IntCurve_ExactIntersectionPointOfTheIntPCurvePCurve                                        \
  HLRBRep_ExactIntersectionPointOfTheIntPCurvePCurveOfCInter
#define IntCurve_ExactIntersectionPointOfTheIntPCurvePCurve_hxx                                    \
  <HLRBRep_ExactIntersectionPointOfTheIntPCurvePCurveOfCInter.hpp>
#define IntCurve_IntCurveCurveGen HLRBRep_CInter
#define IntCurve_IntCurveCurveGen_hxx <HLRBRep_CInter.hpp>
#include <IntCurve_IntCurveCurveGen.hpp>
