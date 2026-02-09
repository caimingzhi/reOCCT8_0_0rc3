#include <HLRBRep_TheCSFunctionOfInterCSurf.hpp>

#include <HLRBRep_SurfaceTool.hpp>
#include <gp_Lin.hpp>
#include <HLRBRep_LineTool.hpp>
#include <math_Matrix.hpp>
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
#define IntImp_ZerCSParFunc HLRBRep_TheCSFunctionOfInterCSurf
#define IntImp_ZerCSParFunc_hxx <HLRBRep_TheCSFunctionOfInterCSurf.hpp>
#include <IntImp_ZerCSParFunc.hpp>
