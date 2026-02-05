#include <Geom2dInt_IntConicCurveOfGInter.hpp>

#include <Standard_ConstructionError.hpp>
#include <IntCurve_IConicTool.hpp>
#include <Adaptor2d_Curve2d.hpp>
#include <Geom2dInt_Geom2dCurveTool.hpp>
#include <Geom2dInt_TheIntConicCurveOfGInter.hpp>
#include <gp_Lin2d.hpp>
#include <IntRes2d_Domain.hpp>
#include <gp_Circ2d.hpp>
#include <gp_Elips2d.hpp>
#include <gp_Parab2d.hpp>
#include <gp_Hypr2d.hpp>

#define TheImpTool IntCurve_IConicTool
#define TheImpTool_hxx <IntCurve_IConicTool.hpp>
#define ThePCurve Adaptor2d_Curve2d
#define ThePCurve_hxx <Adaptor2d_Curve2d.hpp>
#define ThePCurveTool Geom2dInt_Geom2dCurveTool
#define ThePCurveTool_hxx <Geom2dInt_Geom2dCurveTool.hpp>
#define TheIntConicCurve Geom2dInt_TheIntConicCurveOfGInter
#define TheIntConicCurve_hxx <Geom2dInt_TheIntConicCurveOfGInter.hpp>
#define IntCurve_UserIntConicCurveGen Geom2dInt_IntConicCurveOfGInter
#define IntCurve_UserIntConicCurveGen_hxx <Geom2dInt_IntConicCurveOfGInter.hpp>
#include <IntCurve_UserIntConicCurveGen.hpp>
