#include <IntPatch_TheSOnBounds.hpp>

#include <StdFail_NotDone.hpp>
#include <Standard_OutOfRange.hpp>
#include <Standard_ConstructionError.hpp>
#include <Adaptor3d_HVertex.hpp>
#include <Adaptor2d_Curve2d.hpp>
#include <IntPatch_HCurve2dTool.hpp>
#include <IntPatch_HInterTool.hpp>
#include <Adaptor3d_TopolTool.hpp>
#include <IntPatch_ArcFunction.hpp>
#include <IntPatch_ThePathPointOfTheSOnBounds.hpp>
#include <NCollection_Sequence.hpp>
#include <IntPatch_TheSegmentOfTheSOnBounds.hpp>

#define TheVertex occ::handle<Adaptor3d_HVertex>
#define TheVertex_hxx <Adaptor3d_HVertex.hpp>
#define TheArc occ::handle<Adaptor2d_Curve2d>
#define TheArc_hxx <Adaptor2d_Curve2d.hpp>
#define TheArcTool IntPatch_HCurve2dTool
#define TheArcTool_hxx <IntPatch_HCurve2dTool.hpp>
#define TheSOBTool IntPatch_HInterTool
#define TheSOBTool_hxx <IntPatch_HInterTool.hpp>
#define Handle_TheTopolTool occ::handle<Adaptor3d_TopolTool>
#define TheTopolTool Adaptor3d_TopolTool
#define TheTopolTool_hxx <Adaptor3d_TopolTool.hpp>
#define TheFunction IntPatch_ArcFunction
#define TheFunction_hxx <IntPatch_ArcFunction.hpp>
#define IntStart_ThePathPoint IntPatch_ThePathPointOfTheSOnBounds
#define IntStart_ThePathPoint_hxx <IntPatch_ThePathPointOfTheSOnBounds.hpp>
#define IntStart_SequenceOfPathPoint NCollection_Sequence<IntPatch_ThePathPointOfTheSOnBounds>
#define IntStart_SequenceOfPathPoint_hxx                                                           \
  <NCollection_Sequence<IntPatch_ThePathPointOfTheSOnBounds>.hxx>
#define IntStart_TheSegment IntPatch_TheSegmentOfTheSOnBounds
#define IntStart_TheSegment_hxx <IntPatch_TheSegmentOfTheSOnBounds.hpp>
#define IntStart_SequenceOfSegment NCollection_Sequence<IntPatch_TheSegmentOfTheSOnBounds>
#define IntStart_SequenceOfSegment_hxx                                                             \
  <NCollection_Sequence<IntPatch_TheSegmentOfTheSOnBounds>.hxx>
#define IntStart_SearchOnBoundaries IntPatch_TheSOnBounds
#define IntStart_SearchOnBoundaries_hxx <IntPatch_TheSOnBounds.hpp>
#include <IntStart_SearchOnBoundaries.hpp>
