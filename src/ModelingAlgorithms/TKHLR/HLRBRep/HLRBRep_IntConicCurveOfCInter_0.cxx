#include <HLRBRep_IntConicCurveOfCInter.hpp>

#include <Standard_ConstructionError.hpp>
#include <IntCurve_IConicTool.hpp>
#include <HLRBRep_CurveTool.hpp>
#include <HLRBRep_TheIntConicCurveOfCInter.hpp>
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
#define TheIntConicCurve HLRBRep_TheIntConicCurveOfCInter
#define TheIntConicCurve_hxx <HLRBRep_TheIntConicCurveOfCInter.hpp>
#define IntCurve_UserIntConicCurveGen HLRBRep_IntConicCurveOfCInter
#define IntCurve_UserIntConicCurveGen_hxx <HLRBRep_IntConicCurveOfCInter.hpp>
#include <IntCurve_UserIntConicCurveGen.hpp>
