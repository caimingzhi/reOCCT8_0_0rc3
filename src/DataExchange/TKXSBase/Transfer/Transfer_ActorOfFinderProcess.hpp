#pragma once

#include <Standard.hpp>
#include <ShapeProcess.hpp>
#include <Transfer_ActorOfProcessForFinder.hpp>
#include <XSAlgo_ShapeProcessor.hpp>

struct DE_ShapeFixParameters;
class Transfer_Binder;
class Transfer_Finder;
class Transfer_ProcessForFinder;
class Transfer_FinderProcess;
class Standard_Transient;

class Transfer_ActorOfFinderProcess : public Transfer_ActorOfProcessForFinder
{
public:
  Standard_EXPORT Transfer_ActorOfFinderProcess();

  Standard_EXPORT int& ModeTrans();

  Standard_EXPORT occ::handle<Transfer_Binder> Transferring(
    const occ::handle<Transfer_Finder>&           start,
    const occ::handle<Transfer_ProcessForFinder>& TP,
    const Message_ProgressRange&                  theProgress = Message_ProgressRange()) override;

  Standard_EXPORT virtual occ::handle<Transfer_Binder> Transfer(
    const occ::handle<Transfer_Finder>&        start,
    const occ::handle<Transfer_FinderProcess>& TP,
    const Message_ProgressRange&               theProgress = Message_ProgressRange());

  Standard_EXPORT virtual occ::handle<Standard_Transient> TransferTransient(
    const occ::handle<Standard_Transient>&     start,
    const occ::handle<Transfer_FinderProcess>& TP,
    const Message_ProgressRange&               theProgress = Message_ProgressRange());

  Standard_EXPORT void SetShapeFixParameters(
    const XSAlgo_ShapeProcessor::ParameterMap& theParameters);

  Standard_EXPORT void SetShapeFixParameters(XSAlgo_ShapeProcessor::ParameterMap&& theParameters);

  Standard_EXPORT void SetShapeFixParameters(
    const DE_ShapeFixParameters&               theParameters,
    const XSAlgo_ShapeProcessor::ParameterMap& theAdditionalParameters = {});

  inline const XSAlgo_ShapeProcessor::ParameterMap& GetShapeFixParameters() const
  {
    return myShapeProcParams;
  }

  Standard_EXPORT void SetShapeProcessFlags(const ShapeProcess::OperationsFlags& theFlags);

  inline const XSAlgo_ShapeProcessor::ProcessingFlags& GetShapeProcessFlags() const
  {
    return myShapeProcFlags;
  }

  DEFINE_STANDARD_RTTIEXT(Transfer_ActorOfFinderProcess, Transfer_ActorOfProcessForFinder)

protected:
  int themodetrans;

private:
  XSAlgo_ShapeProcessor::ParameterMap    myShapeProcParams;
  XSAlgo_ShapeProcessor::ProcessingFlags myShapeProcFlags;
};
