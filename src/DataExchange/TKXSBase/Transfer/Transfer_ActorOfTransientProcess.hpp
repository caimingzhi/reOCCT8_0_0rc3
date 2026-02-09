#pragma once

#include <ShapeProcess.hpp>
#include <Standard.hpp>
#include <Transfer_ActorOfProcessForTransient.hpp>
#include <XSAlgo_ShapeProcessor.hpp>

struct DE_ShapeFixParameters;
class Transfer_Binder;
class Standard_Transient;
class Transfer_ProcessForTransient;
class Transfer_TransientProcess;

class Transfer_ActorOfTransientProcess : public Transfer_ActorOfProcessForTransient
{
public:
  Standard_EXPORT Transfer_ActorOfTransientProcess();

  Standard_EXPORT occ::handle<Transfer_Binder> Transferring(
    const occ::handle<Standard_Transient>&           start,
    const occ::handle<Transfer_ProcessForTransient>& TP,
    const Message_ProgressRange& theProgress = Message_ProgressRange()) override;

  Standard_EXPORT virtual occ::handle<Transfer_Binder> Transfer(
    const occ::handle<Standard_Transient>&        start,
    const occ::handle<Transfer_TransientProcess>& TP,
    const Message_ProgressRange&                  theProgress = Message_ProgressRange());

  Standard_EXPORT virtual occ::handle<Standard_Transient> TransferTransient(
    const occ::handle<Standard_Transient>&        start,
    const occ::handle<Transfer_TransientProcess>& TP,
    const Message_ProgressRange&                  theProgress = Message_ProgressRange());

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

  Standard_EXPORT void SetProcessingFlags(const ShapeProcess::OperationsFlags& theFlags);

  inline const XSAlgo_ShapeProcessor::ProcessingFlags& GetProcessingFlags() const
  {
    return myShapeProcFlags;
  }

  DEFINE_STANDARD_RTTIEXT(Transfer_ActorOfTransientProcess, Transfer_ActorOfProcessForTransient)

private:
  XSAlgo_ShapeProcessor::ParameterMap    myShapeProcParams;
  XSAlgo_ShapeProcessor::ProcessingFlags myShapeProcFlags;
};
