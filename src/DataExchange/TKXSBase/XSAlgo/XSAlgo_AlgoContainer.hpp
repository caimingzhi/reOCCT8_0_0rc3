#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Message_ProgressRange.hpp>
#include <Standard_Integer.hpp>
#include <Standard_Transient.hpp>
#include <TopAbs_ShapeEnum.hpp>

class XSAlgo_ToolContainer;
class TopoDS_Shape;
class TopoDS_Edge;
class TopoDS_Face;
class Transfer_TransientProcess;
class Transfer_FinderProcess;

class XSAlgo_AlgoContainer : public Standard_Transient
{
public:
  XSAlgo_AlgoContainer() = default;

  Standard_EXPORT virtual void PrepareForTransfer() const;

  Standard_EXPORT virtual TopoDS_Shape ProcessShape(
    const TopoDS_Shape&              theShape,
    const double                     thePrec,
    const double                     theMaxTol,
    const char*                      thePrscfile,
    const char*                      thePseq,
    occ::handle<Standard_Transient>& theInfo,
    const Message_ProgressRange&     theProgress       = Message_ProgressRange(),
    const bool                       theNonManifold    = false,
    const TopAbs_ShapeEnum           theDetailingLevel = TopAbs_VERTEX) const;

  Standard_EXPORT virtual bool CheckPCurve(const TopoDS_Edge& theEdge,
                                           const TopoDS_Face& theFace,
                                           const double       thePrecision,
                                           const bool         theIsSeam) const;

  Standard_EXPORT virtual void MergeTransferInfo(const occ::handle<Transfer_TransientProcess>& TP,
                                                 const occ::handle<Standard_Transient>&        info,
                                                 const int startTPitem = 1) const;

  Standard_EXPORT virtual void MergeTransferInfo(const occ::handle<Transfer_FinderProcess>& FP,
                                                 const occ::handle<Standard_Transient>& info) const;

  DEFINE_STANDARD_RTTIEXT(XSAlgo_AlgoContainer, Standard_Transient)
};
