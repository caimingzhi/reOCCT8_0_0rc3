#include <Contap_TheSearch.hpp>

#include <StdFail_NotDone.hpp>
#include <Standard_OutOfRange.hpp>
#include <Standard_ConstructionError.hpp>
#include <Adaptor3d_HVertex.hpp>
#include <Adaptor2d_Curve2d.hpp>
#include <Contap_HCurve2dTool.hpp>
#include <Contap_HContTool.hpp>
#include <Adaptor3d_TopolTool.hpp>
#include <Contap_ArcFunction.hpp>
#include <Contap_ThePathPointOfTheSearch.hpp>
#include <NCollection_Sequence.hpp>
#include <Contap_TheSegmentOfTheSearch.hpp>

#define TheVertex occ::handle<Adaptor3d_HVertex>
#define TheVertex_hxx <Adaptor3d_HVertex.hpp>
#define TheArc occ::handle<Adaptor2d_Curve2d>
#define TheArc_hxx <Adaptor2d_Curve2d.hpp>
#define TheArcTool Contap_HCurve2dTool
#define TheArcTool_hxx <Contap_HCurve2dTool.hpp>
#define TheSOBTool Contap_HContTool
#define TheSOBTool_hxx <Contap_HContTool.hpp>
#define Handle_TheTopolTool occ::handle<Adaptor3d_TopolTool>
#define TheTopolTool Adaptor3d_TopolTool
#define TheTopolTool_hxx <Adaptor3d_TopolTool.hpp>
#define TheFunction Contap_ArcFunction
#define TheFunction_hxx <Contap_ArcFunction.hpp>
#define IntStart_ThePathPoint Contap_ThePathPointOfTheSearch
#define IntStart_ThePathPoint_hxx <Contap_ThePathPointOfTheSearch.hpp>
#define IntStart_SequenceOfPathPoint NCollection_Sequence<Contap_ThePathPointOfTheSearch>
#define IntStart_SequenceOfPathPoint_hxx <NCollection_Sequence<Contap_ThePathPointOfTheSearch>.hxx>
#define IntStart_TheSegment Contap_TheSegmentOfTheSearch
#define IntStart_TheSegment_hxx <Contap_TheSegmentOfTheSearch.hpp>
#define IntStart_SequenceOfSegment NCollection_Sequence<Contap_TheSegmentOfTheSearch>
#define IntStart_SequenceOfSegment_hxx <NCollection_Sequence<Contap_TheSegmentOfTheSearch>.hxx>
#define IntStart_SearchOnBoundaries Contap_TheSearch
#define IntStart_SearchOnBoundaries_hxx <Contap_TheSearch.hpp>
#include <IntStart_SearchOnBoundaries.hpp>
