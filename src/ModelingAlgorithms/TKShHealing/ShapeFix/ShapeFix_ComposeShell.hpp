#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TopLoc_Location.hpp>
#include <TopoDS_Face.hpp>
#include <TopAbs_Orientation.hpp>
#include <TopoDS_Shape.hpp>
#include <Standard_Integer.hpp>
#include <ShapeFix_Root.hpp>
#include <ShapeExtend_Status.hpp>
#include <ShapeFix_WireSegment.hpp>
#include <NCollection_Sequence.hpp>
class ShapeExtend_CompositeSurface;
class ShapeAnalysis_TransferParameters;
class ShapeExtend_WireData;
class gp_Lin2d;
class ShapeFix_WireSegment;
class Geom_Surface;

#ifdef Status
  #undef Status
#endif

class ShapeFix_ComposeShell : public ShapeFix_Root
{

public:
  Standard_EXPORT ShapeFix_ComposeShell();

  Standard_EXPORT void Init(const occ::handle<ShapeExtend_CompositeSurface>& Grid,
                            const TopLoc_Location&                           L,
                            const TopoDS_Face&                               Face,
                            const double                                     Prec);

  Standard_EXPORT bool& ClosedMode();

  Standard_EXPORT virtual bool Perform();

  Standard_EXPORT void SplitEdges();

  Standard_EXPORT const TopoDS_Shape& Result() const;

  Standard_EXPORT bool Status(const ShapeExtend_Status status) const;

  Standard_EXPORT void DispatchWires(NCollection_Sequence<TopoDS_Shape>&         faces,
                                     NCollection_Sequence<ShapeFix_WireSegment>& wires) const;

  Standard_EXPORT void SetTransferParamTool(
    const occ::handle<ShapeAnalysis_TransferParameters>& TransferParam);

  Standard_EXPORT occ::handle<ShapeAnalysis_TransferParameters> GetTransferParamTool() const;

  DEFINE_STANDARD_RTTIEXT(ShapeFix_ComposeShell, ShapeFix_Root)

protected:
  Standard_EXPORT void LoadWires(NCollection_Sequence<ShapeFix_WireSegment>& seqw) const;

  Standard_EXPORT int ComputeCode(const occ::handle<ShapeExtend_WireData>& wire,
                                  const gp_Lin2d&                          line,
                                  const int                                begInd,
                                  const int                                endInd,
                                  const double                             begPar,
                                  const double                             endPar,
                                  const bool                               IsInternal = false);

  Standard_EXPORT ShapeFix_WireSegment SplitWire(ShapeFix_WireSegment&               wire,
                                                 NCollection_Sequence<int>&          indexes,
                                                 const NCollection_Sequence<double>& values,
                                                 NCollection_Sequence<TopoDS_Shape>& vertices,
                                                 const NCollection_Sequence<int>&    segcodes,
                                                 const bool                          cutbyu,
                                                 const int                           cutindex);

  Standard_EXPORT bool SplitByLine(ShapeFix_WireSegment&               wire,
                                   const gp_Lin2d&                     line,
                                   const bool                          cutbyu,
                                   const int                           cutindex,
                                   NCollection_Sequence<double>&       SplitLinePar,
                                   NCollection_Sequence<int>&          SplitLineCode,
                                   NCollection_Sequence<TopoDS_Shape>& SplitLineVertex);

  Standard_EXPORT void SplitByLine(NCollection_Sequence<ShapeFix_WireSegment>& seqw,
                                   const gp_Lin2d&                             line,
                                   const bool                                  cutbyu,
                                   const int                                   cutindex);

  Standard_EXPORT void SplitByGrid(NCollection_Sequence<ShapeFix_WireSegment>& seqw);

  Standard_EXPORT void BreakWires(NCollection_Sequence<ShapeFix_WireSegment>& seqw);

  Standard_EXPORT void CollectWires(NCollection_Sequence<ShapeFix_WireSegment>& wires,
                                    NCollection_Sequence<ShapeFix_WireSegment>& seqw);

  Standard_EXPORT void MakeFacesOnPatch(NCollection_Sequence<TopoDS_Shape>& faces,
                                        const occ::handle<Geom_Surface>&    surf,
                                        NCollection_Sequence<TopoDS_Shape>& loops) const;

  TopAbs_Orientation myOrient;
  TopoDS_Shape       myResult;
  int                myStatus;

private:
  occ::handle<ShapeExtend_CompositeSurface>     myGrid;
  TopLoc_Location                               myLoc;
  TopoDS_Face                                   myFace;
  double                                        myUResolution;
  double                                        myVResolution;
  occ::handle<ShapeAnalysis_TransferParameters> myTransferParamTool;
  bool                                          myInvertEdgeStatus;
  bool                                          myClosedMode;
  bool                                          myUClosed;
  bool                                          myVClosed;
  double                                        myUPeriod;
  double                                        myVPeriod;
};
