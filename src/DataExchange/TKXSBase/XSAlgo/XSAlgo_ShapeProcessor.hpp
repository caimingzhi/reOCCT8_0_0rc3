#pragma once

#include <DE_ShapeFixParameters.hpp>
#include <ShapeProcess.hpp>
#include <TopAbs_ShapeEnum.hpp>
#include <TopoDS_Shape.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>

class ShapeProcess_ShapeContext;
class ShapeExtend_MsgRegistrator;
class Transfer_TransientProcess;
class Transfer_FinderProcess;
class Transfer_Binder;

class XSAlgo_ShapeProcessor
{
public:
  using ParameterMap   = NCollection_DataMap<TCollection_AsciiString, TCollection_AsciiString>;
  using ProcessingData = std::pair<ParameterMap, ShapeProcess::OperationsFlags>;

  using ProcessingFlags = std::pair<ShapeProcess::OperationsFlags, bool>;

public:
  Standard_EXPORT XSAlgo_ShapeProcessor(const ParameterMap&          theParameters,
                                        const DE_ShapeFixParameters& theShapeFixParameters = {});

  Standard_EXPORT XSAlgo_ShapeProcessor(const DE_ShapeFixParameters& theParameters);

  Standard_EXPORT TopoDS_Shape ProcessShape(const TopoDS_Shape&                  theShape,
                                            const ShapeProcess::OperationsFlags& theOperations,
                                            const Message_ProgressRange&         theProgress);

  occ::handle<ShapeProcess_ShapeContext> GetContext() { return myContext; }

  Standard_EXPORT void MergeTransferInfo(
    const occ::handle<Transfer_TransientProcess>& theTransientProcess,
    const int                                     theFirstTPItemIndex) const;

  Standard_EXPORT void MergeTransferInfo(
    const occ::handle<Transfer_FinderProcess>& theFinderProcess) const;

  Standard_EXPORT static bool CheckPCurve(const TopoDS_Edge& theEdge,
                                          const TopoDS_Face& theFace,
                                          const double       thePrecision,
                                          const bool         theIsSeam);

  Standard_EXPORT static ProcessingData ReadProcessingData(
    const TCollection_AsciiString& theFileResourceName,
    const TCollection_AsciiString& theScopeResourceName);

  Standard_EXPORT static void FillParameterMap(const DE_ShapeFixParameters& theParameters,
                                               const bool                   theIsReplace,
                                               ParameterMap&                theMap);

  Standard_EXPORT static void SetShapeFixParameters(const DE_ShapeFixParameters& theParameters,
                                                    const ParameterMap& theAdditionalParameters,
                                                    ParameterMap&       theTargetParameterMap);

  Standard_EXPORT static void SetParameter(const char*                          theKey,
                                           const DE_ShapeFixParameters::FixMode theValue,
                                           const bool                           theIsReplace,
                                           XSAlgo_ShapeProcessor::ParameterMap& theMap);

  Standard_EXPORT static void SetParameter(const char*   theKey,
                                           const double  theValue,
                                           const bool    theIsReplace,
                                           ParameterMap& theMap);

  Standard_EXPORT static void SetParameter(const char*                    theKey,
                                           const TCollection_AsciiString& theValue,
                                           const bool                     theIsReplace,
                                           ParameterMap&                  theMap);

  Standard_EXPORT static void PrepareForTransfer();

  Standard_EXPORT static void MergeShapeTransferInfo(
    const occ::handle<Transfer_TransientProcess>& theFinderProcess,
    const NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>&
                                                   theModifiedShapesMap,
    const int                                      theFirstTPItemIndex,
    const occ::handle<ShapeExtend_MsgRegistrator>& theMessages);

  Standard_EXPORT static void MergeShapeTransferInfo(
    const occ::handle<Transfer_FinderProcess>& theTransientProcess,
    const NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>&
                                                   theModifiedShapesMap,
    const occ::handle<ShapeExtend_MsgRegistrator>& theMessages);

private:
  void initializeContext(const TopoDS_Shape& theShape);

  static void addMessages(const occ::handle<ShapeExtend_MsgRegistrator>& theMessages,
                          const TopoDS_Shape&                            theShape,
                          occ::handle<Transfer_Binder>&                  theBinder);

  static TopoDS_Edge MakeEdgeOnCurve(const TopoDS_Edge& aSourceEdge);

private:
  ParameterMap                           myParameters;
  occ::handle<ShapeProcess_ShapeContext> myContext;
};
