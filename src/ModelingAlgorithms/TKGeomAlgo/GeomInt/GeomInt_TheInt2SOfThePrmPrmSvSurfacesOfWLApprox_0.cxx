#include <GeomInt_TheInt2SOfThePrmPrmSvSurfacesOfWLApprox.hpp>

#include <StdFail_NotDone.hpp>
#include <Standard_DomainError.hpp>
#include <Standard_ConstructionError.hpp>
#include <StdFail_UndefinedDerivative.hpp>
#include <Adaptor3d_Surface.hpp>
#include <Adaptor3d_HSurfaceTool.hpp>
#include <GeomInt_TheFunctionOfTheInt2SOfThePrmPrmSvSurfacesOfWLApprox.hpp>
#include <math_FunctionSetRoot.hpp>
#include <IntSurf_PntOn2S.hpp>
#include <gp_Dir.hpp>
#include <gp_Dir2d.hpp>

#define ThePSurface occ::handle<Adaptor3d_Surface>
#define ThePSurface_hxx <Adaptor3d_Surface.hpp>
#define ThePSurfaceTool Adaptor3d_HSurfaceTool
#define ThePSurfaceTool_hxx <Adaptor3d_HSurfaceTool.hpp>
#define IntImp_TheFunction GeomInt_TheFunctionOfTheInt2SOfThePrmPrmSvSurfacesOfWLApprox
#define IntImp_TheFunction_hxx <GeomInt_TheFunctionOfTheInt2SOfThePrmPrmSvSurfacesOfWLApprox.hpp>
#define IntImp_Int2S GeomInt_TheInt2SOfThePrmPrmSvSurfacesOfWLApprox
#define IntImp_Int2S_hxx <GeomInt_TheInt2SOfThePrmPrmSvSurfacesOfWLApprox.hpp>
#include <IntImp_Int2S.hpp>
