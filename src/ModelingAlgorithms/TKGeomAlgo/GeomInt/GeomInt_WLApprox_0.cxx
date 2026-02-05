#include <GeomInt_WLApprox.hpp>

#include <Standard_OutOfRange.hpp>
#include <StdFail_NotDone.hpp>
#include <Adaptor3d_Surface.hpp>
#include <Adaptor3d_HSurfaceTool.hpp>
#include <IntSurf_Quadric.hpp>
#include <IntSurf_QuadricTool.hpp>
#include <IntPatch_WLine.hpp>
#include <GeomInt_ThePrmPrmSvSurfacesOfWLApprox.hpp>
#include <GeomInt_TheInt2SOfThePrmPrmSvSurfacesOfWLApprox.hpp>
#include <GeomInt_TheImpPrmSvSurfacesOfWLApprox.hpp>
#include <GeomInt_TheZerImpFuncOfTheImpPrmSvSurfacesOfWLApprox.hpp>
#include <GeomInt_TheMultiLineOfWLApprox.hpp>
#include <GeomInt_TheMultiLineToolOfWLApprox.hpp>
#include <GeomInt_TheComputeLineOfWLApprox.hpp>
#include <GeomInt_MyBSplGradientOfTheComputeLineOfWLApprox.hpp>
#include <GeomInt_MyGradientbisOfTheComputeLineOfWLApprox.hpp>
#include <GeomInt_TheComputeLineBezierOfWLApprox.hpp>
#include <GeomInt_MyGradientOfTheComputeLineBezierOfWLApprox.hpp>
#include <AppParCurves_MultiBSpCurve.hpp>

#define ThePSurface occ::handle<Adaptor3d_Surface>
#define ThePSurface_hxx <Adaptor3d_Surface.hpp>
#define ThePSurfaceTool Adaptor3d_HSurfaceTool
#define ThePSurfaceTool_hxx <Adaptor3d_HSurfaceTool.hpp>
#define TheISurface IntSurf_Quadric
#define TheISurface_hxx <IntSurf_Quadric.hpp>
#define TheISurfaceTool IntSurf_QuadricTool
#define TheISurfaceTool_hxx <IntSurf_QuadricTool.hpp>
#define Handle_TheWLine occ::handle<IntPatch_WLine>
#define TheWLine IntPatch_WLine
#define TheWLine_hxx <IntPatch_WLine.hpp>
#define ApproxInt_ThePrmPrmSvSurfaces GeomInt_ThePrmPrmSvSurfacesOfWLApprox
#define ApproxInt_ThePrmPrmSvSurfaces_hxx <GeomInt_ThePrmPrmSvSurfacesOfWLApprox.hpp>
#define ApproxInt_TheInt2SOfThePrmPrmSvSurfaces GeomInt_TheInt2SOfThePrmPrmSvSurfacesOfWLApprox
#define ApproxInt_TheInt2SOfThePrmPrmSvSurfaces_hxx                                                \
  <GeomInt_TheInt2SOfThePrmPrmSvSurfacesOfWLApprox.hpp>
#define ApproxInt_TheInt2SOfThePrmPrmSvSurfaces GeomInt_TheInt2SOfThePrmPrmSvSurfacesOfWLApprox
#define ApproxInt_TheInt2SOfThePrmPrmSvSurfaces_hxx                                                \
  <GeomInt_TheInt2SOfThePrmPrmSvSurfacesOfWLApprox.hpp>
#define ApproxInt_TheImpPrmSvSurfaces GeomInt_TheImpPrmSvSurfacesOfWLApprox
#define ApproxInt_TheImpPrmSvSurfaces_hxx <GeomInt_TheImpPrmSvSurfacesOfWLApprox.hpp>
#define ApproxInt_TheZerImpFuncOfTheImpPrmSvSurfaces                                               \
  GeomInt_TheZerImpFuncOfTheImpPrmSvSurfacesOfWLApprox
#define ApproxInt_TheZerImpFuncOfTheImpPrmSvSurfaces_hxx                                           \
  <GeomInt_TheZerImpFuncOfTheImpPrmSvSurfacesOfWLApprox.hpp>
#define ApproxInt_TheZerImpFuncOfTheImpPrmSvSurfaces                                               \
  GeomInt_TheZerImpFuncOfTheImpPrmSvSurfacesOfWLApprox
#define ApproxInt_TheZerImpFuncOfTheImpPrmSvSurfaces_hxx                                           \
  <GeomInt_TheZerImpFuncOfTheImpPrmSvSurfacesOfWLApprox.hpp>
#define ApproxInt_TheMultiLine GeomInt_TheMultiLineOfWLApprox
#define ApproxInt_TheMultiLine_hxx <GeomInt_TheMultiLineOfWLApprox.hpp>
#define ApproxInt_TheMultiLineTool GeomInt_TheMultiLineToolOfWLApprox
#define ApproxInt_TheMultiLineTool_hxx <GeomInt_TheMultiLineToolOfWLApprox.hpp>
#define ApproxInt_TheComputeLine GeomInt_TheComputeLineOfWLApprox
#define ApproxInt_TheComputeLine_hxx <GeomInt_TheComputeLineOfWLApprox.hpp>
#define ApproxInt_MyBSplGradientOfTheComputeLine GeomInt_MyBSplGradientOfTheComputeLineOfWLApprox
#define ApproxInt_MyBSplGradientOfTheComputeLine_hxx                                               \
  <GeomInt_MyBSplGradientOfTheComputeLineOfWLApprox.hpp>
#define ApproxInt_MyGradientbisOfTheComputeLine GeomInt_MyGradientbisOfTheComputeLineOfWLApprox
#define ApproxInt_MyGradientbisOfTheComputeLine_hxx                                                \
  <GeomInt_MyGradientbisOfTheComputeLineOfWLApprox.hpp>
#define ApproxInt_MyBSplGradientOfTheComputeLine GeomInt_MyBSplGradientOfTheComputeLineOfWLApprox
#define ApproxInt_MyBSplGradientOfTheComputeLine_hxx                                               \
  <GeomInt_MyBSplGradientOfTheComputeLineOfWLApprox.hpp>
#define ApproxInt_MyGradientbisOfTheComputeLine GeomInt_MyGradientbisOfTheComputeLineOfWLApprox
#define ApproxInt_MyGradientbisOfTheComputeLine_hxx                                                \
  <GeomInt_MyGradientbisOfTheComputeLineOfWLApprox.hpp>
#define ApproxInt_TheComputeLineBezier GeomInt_TheComputeLineBezierOfWLApprox
#define ApproxInt_TheComputeLineBezier_hxx <GeomInt_TheComputeLineBezierOfWLApprox.hpp>
#define ApproxInt_MyGradientOfTheComputeLineBezier                                                 \
  GeomInt_MyGradientOfTheComputeLineBezierOfWLApprox
#define ApproxInt_MyGradientOfTheComputeLineBezier_hxx                                             \
  <GeomInt_MyGradientOfTheComputeLineBezierOfWLApprox.hpp>
#define ApproxInt_MyGradientOfTheComputeLineBezier                                                 \
  GeomInt_MyGradientOfTheComputeLineBezierOfWLApprox
#define ApproxInt_MyGradientOfTheComputeLineBezier_hxx                                             \
  <GeomInt_MyGradientOfTheComputeLineBezierOfWLApprox.hpp>
#define ApproxInt_Approx GeomInt_WLApprox
#define ApproxInt_Approx_hxx <GeomInt_WLApprox.hpp>
#include <ApproxInt_Approx.hpp>
