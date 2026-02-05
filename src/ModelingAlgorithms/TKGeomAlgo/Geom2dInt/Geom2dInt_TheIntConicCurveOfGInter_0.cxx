#include <Geom2dInt_TheIntConicCurveOfGInter.hpp>

#include <IntCurve_IConicTool.hpp>
#include <Adaptor2d_Curve2d.hpp>
#include <Geom2dInt_Geom2dCurveTool.hpp>
#include <Geom2dInt_TheProjPCurOfGInter.hpp>
#include <Geom2dInt_TheIntersectorOfTheIntConicCurveOfGInter.hpp>
#include <Geom2dInt_MyImpParToolOfTheIntersectorOfTheIntConicCurveOfGInter.hpp>
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
#define TheProjPCur Geom2dInt_TheProjPCurOfGInter
#define TheProjPCur_hxx <Geom2dInt_TheProjPCurOfGInter.hpp>
#define IntCurve_TheIntersector Geom2dInt_TheIntersectorOfTheIntConicCurveOfGInter
#define IntCurve_TheIntersector_hxx <Geom2dInt_TheIntersectorOfTheIntConicCurveOfGInter.hpp>
#define IntCurve_MyImpParToolOfTheIntersector                                                      \
  Geom2dInt_MyImpParToolOfTheIntersectorOfTheIntConicCurveOfGInter
#define IntCurve_MyImpParToolOfTheIntersector_hxx                                                  \
  <Geom2dInt_MyImpParToolOfTheIntersectorOfTheIntConicCurveOfGInter.hpp>
#define IntCurve_MyImpParToolOfTheIntersector                                                      \
  Geom2dInt_MyImpParToolOfTheIntersectorOfTheIntConicCurveOfGInter
#define IntCurve_MyImpParToolOfTheIntersector_hxx                                                  \
  <Geom2dInt_MyImpParToolOfTheIntersectorOfTheIntConicCurveOfGInter.hpp>
#define IntCurve_IntConicCurveGen Geom2dInt_TheIntConicCurveOfGInter
#define IntCurve_IntConicCurveGen_hxx <Geom2dInt_TheIntConicCurveOfGInter.hpp>
#include <IntCurve_IntConicCurveGen.hpp>
