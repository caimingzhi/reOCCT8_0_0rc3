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
  //! Empty constructor
  XSAlgo_AlgoContainer() = default;

  //! Performs actions necessary for preparing environment
  //! for transfer. Empty in Open version.
  Standard_EXPORT virtual void PrepareForTransfer() const;

  //! Does shape processing with specified tolerances
  //! @param[in] theShape shape to process
  //! @param[in] thePrec basic precision and tolerance
  //! @param[in] theMaxTol maximum allowed tolerance
  //! @param[in] thePrscfile name of the resource file
  //! @param[in] thePseq name of the sequence of operators defined in the resource file for Shape
  //! Processing
  //! @param[out] theInfo information to be recorded in the translation map
  //! @param[in] theProgress progress indicator
  //! @param[in] theNonManifold flag to proceed with non-manifold topology
  //! @param[in] theDetailingLevel the lowest shape type to be processed, lower shapes are ignored
  //! @return the processed shape
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

  //! Checks quality of pcurve of the edge on the given face,
  //! and corrects it if necessary.
  Standard_EXPORT virtual bool CheckPCurve(const TopoDS_Edge& theEdge,
                                           const TopoDS_Face& theFace,
                                           const double       thePrecision,
                                           const bool         theIsSeam) const;

  Standard_EXPORT virtual void MergeTransferInfo(const occ::handle<Transfer_TransientProcess>& TP,
                                                 const occ::handle<Standard_Transient>&        info,
                                                 const int startTPitem = 1) const;

  //! Updates translation map (TP or FP) with information
  //! resulting from ShapeProcessing
  //! Parameter startTPitem can be used for optimisation, to
  //! restrict modifications to entities stored in TP starting
  //! from item startTPitem
  Standard_EXPORT virtual void MergeTransferInfo(const occ::handle<Transfer_FinderProcess>& FP,
                                                 const occ::handle<Standard_Transient>& info) const;

  DEFINE_STANDARD_RTTIEXT(XSAlgo_AlgoContainer, Standard_Transient)
};
