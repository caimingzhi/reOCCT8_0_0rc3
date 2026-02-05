#include <HLRBRep_TheIntConicCurveOfCInter.hpp>

#include <IntCurve_IConicTool.hpp>
#include <HLRBRep_CurveTool.hpp>
#include <HLRBRep_TheProjPCurOfCInter.hpp>
#include <HLRBRep_TheIntersectorOfTheIntConicCurveOfCInter.hpp>
#include <HLRBRep_MyImpParToolOfTheIntersectorOfTheIntConicCurveOfCInter.hpp>
#include <gp_Lin2d.hpp>
#include <IntRes2d_Domain.hpp>
#include <gp_Circ2d.hpp>
#include <gp_Elips2d.hpp>
#include <gp_Parab2d.hpp>
#include <gp_Hypr2d.hpp>

#define TheImpTool IntCurve_IConicTool
#define TheImpTool_hxx <IntCurve_IConicTool.hpp>
#define ThePCurve HLRBRep_CurvePtr
#define ThePCurve_hxx <HLRBRep_TypeDef.hpp>
#define ThePCurveTool HLRBRep_CurveTool
#define ThePCurveTool_hxx <HLRBRep_CurveTool.hpp>
#define TheProjPCur HLRBRep_TheProjPCurOfCInter
#define TheProjPCur_hxx <HLRBRep_TheProjPCurOfCInter.hpp>
#define IntCurve_TheIntersector HLRBRep_TheIntersectorOfTheIntConicCurveOfCInter
#define IntCurve_TheIntersector_hxx <HLRBRep_TheIntersectorOfTheIntConicCurveOfCInter.hpp>
#define IntCurve_MyImpParToolOfTheIntersector                                                      \
  HLRBRep_MyImpParToolOfTheIntersectorOfTheIntConicCurveOfCInter
#define IntCurve_MyImpParToolOfTheIntersector_hxx                                                  \
  <HLRBRep_MyImpParToolOfTheIntersectorOfTheIntConicCurveOfCInter.hpp>
#define IntCurve_MyImpParToolOfTheIntersector                                                      \
  HLRBRep_MyImpParToolOfTheIntersectorOfTheIntConicCurveOfCInter
#define IntCurve_MyImpParToolOfTheIntersector_hxx                                                  \
  <HLRBRep_MyImpParToolOfTheIntersectorOfTheIntConicCurveOfCInter.hpp>
#define IntCurve_IntConicCurveGen HLRBRep_TheIntConicCurveOfCInter
#define IntCurve_IntConicCurveGen_hxx <HLRBRep_TheIntConicCurveOfCInter.hpp>
#include <IntCurve_IntConicCurveGen.hpp>
