#include <HLRBRep_TheExactInterCSurf.hpp>

#include <StdFail_NotDone.hpp>
#include <Standard_DomainError.hpp>
#include <HLRBRep_SurfaceTool.hpp>
#include <gp_Lin.hpp>
#include <HLRBRep_LineTool.hpp>
#include <HLRBRep_TheCSFunctionOfInterCSurf.hpp>
#include <math_FunctionSetRoot.hpp>
#include <gp_Pnt.hpp>
#include <HLRBRep_Surface.hpp>

typedef HLRBRep_Surface* ThePSurface;
#define ThePSurface_hxx <HLRBRep_Surface.hpp>
#define ThePSurfaceTool HLRBRep_SurfaceTool
#define ThePSurfaceTool_hxx <HLRBRep_SurfaceTool.hpp>
#define TheCurve gp_Lin
#define TheCurve_hxx <gp_Lin.hpp>
#define TheCurveTool HLRBRep_LineTool
#define TheCurveTool_hxx <HLRBRep_LineTool.hpp>
#define TheFunction HLRBRep_TheCSFunctionOfInterCSurf
#define TheFunction_hxx <HLRBRep_TheCSFunctionOfInterCSurf.hpp>
#define IntImp_IntCS HLRBRep_TheExactInterCSurf
#define IntImp_IntCS_hxx <HLRBRep_TheExactInterCSurf.hpp>
#include <IntImp_IntCS.hpp>
