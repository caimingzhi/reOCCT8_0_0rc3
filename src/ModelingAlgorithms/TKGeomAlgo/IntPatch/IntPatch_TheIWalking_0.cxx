#include <IntPatch_TheIWalking.hpp>

#include <StdFail_NotDone.hpp>
#include <Standard_OutOfRange.hpp>
#include <IntSurf_PathPoint.hpp>
#include <IntSurf_PathPointTool.hpp>
#include <IntSurf_InteriorPoint.hpp>
#include <IntSurf_InteriorPointTool.hpp>
#include <Adaptor3d_Surface.hpp>
#include <Adaptor3d_HSurfaceTool.hpp>
#include <IntPatch_TheSurfFunction.hpp>
#include <IntPatch_TheIWLineOfTheIWalking.hpp>
#include <NCollection_Sequence.hpp>
#include <IntSurf_PntOn2S.hpp>

#define ThePointOfPath IntSurf_PathPoint
#define ThePointOfPath_hxx <IntSurf_PathPoint.hpp>
#define ThePointOfPathTool IntSurf_PathPointTool
#define ThePointOfPathTool_hxx <IntSurf_PathPointTool.hpp>
#define ThePOPIterator NCollection_Sequence<IntSurf_PathPoint>
#define ThePOPIterator_hxx <NCollection_Sequence<IntSurf_PathPoint>.hxx>
#define ThePointOfLoop IntSurf_InteriorPoint
#define ThePointOfLoop_hxx <IntSurf_InteriorPoint.hpp>
#define ThePointOfLoopTool IntSurf_InteriorPointTool
#define ThePointOfLoopTool_hxx <IntSurf_InteriorPointTool.hpp>
#define ThePOLIterator NCollection_Sequence<IntSurf_InteriorPoint>
#define ThePOLIterator_hxx <NCollection_Sequence<IntSurf_InteriorPoint>.hxx>
#define ThePSurface occ::handle<Adaptor3d_Surface>
#define ThePSurface_hxx <Adaptor3d_Surface.hpp>
#define ThePSurfaceTool Adaptor3d_HSurfaceTool
#define ThePSurfaceTool_hxx <Adaptor3d_HSurfaceTool.hpp>
#define TheIWFunction IntPatch_TheSurfFunction
#define TheIWFunction_hxx <IntPatch_TheSurfFunction.hpp>
#define IntWalk_TheIWLine IntPatch_TheIWLineOfTheIWalking
#define IntWalk_TheIWLine_hxx <IntPatch_TheIWLineOfTheIWalking.hpp>
#define IntWalk_SequenceOfIWLine NCollection_Sequence<occ::handle<IntPatch_TheIWLineOfTheIWalking>>
#define IntWalk_SequenceOfIWLine_hxx                                                               \
  <NCollection_Sequence<occ::handle<IntPatch_TheIWLineOfTheIWalking>>.hxx>
#define Handle_IntWalk_TheIWLine occ::handle<IntPatch_TheIWLineOfTheIWalking>
#define IntWalk_IWalking IntPatch_TheIWalking
#define IntWalk_IWalking_hxx <IntPatch_TheIWalking.hpp>
#include <IntWalk_IWalking.hpp>
