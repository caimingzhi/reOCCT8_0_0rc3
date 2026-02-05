#include <IntCurve_IntImpConicParConic.hpp>

#include <Standard_ConstructionError.hpp>
#include <IntCurve_IConicTool.hpp>
#include <IntCurve_PConic.hpp>
#include <IntCurve_PConicTool.hpp>
#include <IntCurve_ProjectOnPConicTool.hpp>
#include <IntCurve_MyImpParToolOfIntImpConicParConic.hpp>
#include <IntRes2d_Domain.hpp>
#include <gp_Pnt2d.hpp>

#define ImpTool IntCurve_IConicTool
#define ImpTool_hxx <IntCurve_IConicTool.hpp>
#define ParCurve IntCurve_PConic
#define ParCurve_hxx <IntCurve_PConic.hpp>
#define ParTool IntCurve_PConicTool
#define ParTool_hxx <IntCurve_PConicTool.hpp>
#define ProjectOnPCurveTool IntCurve_ProjectOnPConicTool
#define ProjectOnPCurveTool_hxx <IntCurve_ProjectOnPConicTool.hpp>
#define IntImpParGen_MyImpParTool IntCurve_MyImpParToolOfIntImpConicParConic
#define IntImpParGen_MyImpParTool_hxx <IntCurve_MyImpParToolOfIntImpConicParConic.hpp>
#define IntImpParGen_Intersector IntCurve_IntImpConicParConic
#define IntImpParGen_Intersector_hxx <IntCurve_IntImpConicParConic.hpp>
#include <IntImpParGen_Intersector.hpp>
