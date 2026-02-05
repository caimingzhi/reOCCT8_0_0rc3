#include <HLRBRep_TheIntersectorOfTheIntConicCurveOfCInter.hpp>

#include <Standard_ConstructionError.hpp>
#include <IntCurve_IConicTool.hpp>
#include <HLRBRep_CurveTool.hpp>
#include <HLRBRep_TheProjPCurOfCInter.hpp>
#include <HLRBRep_MyImpParToolOfTheIntersectorOfTheIntConicCurveOfCInter.hpp>
#include <IntRes2d_Domain.hpp>
#include <gp_Pnt2d.hpp>

#define ImpTool IntCurve_IConicTool
#define ImpTool_hxx <IntCurve_IConicTool.hpp>
#define ParCurve HLRBRep_CurvePtr
#define ParCurve_hxx <HLRBRep_TypeDef.hpp>
#define ParTool HLRBRep_CurveTool
#define ParTool_hxx <HLRBRep_CurveTool.hpp>
#define ProjectOnPCurveTool HLRBRep_TheProjPCurOfCInter
#define ProjectOnPCurveTool_hxx <HLRBRep_TheProjPCurOfCInter.hpp>
#define IntImpParGen_MyImpParTool HLRBRep_MyImpParToolOfTheIntersectorOfTheIntConicCurveOfCInter
#define IntImpParGen_MyImpParTool_hxx                                                              \
  <HLRBRep_MyImpParToolOfTheIntersectorOfTheIntConicCurveOfCInter.hpp>
#define IntImpParGen_Intersector HLRBRep_TheIntersectorOfTheIntConicCurveOfCInter
#define IntImpParGen_Intersector_hxx <HLRBRep_TheIntersectorOfTheIntConicCurveOfCInter.hpp>
#include <IntImpParGen_Intersector.hpp>
