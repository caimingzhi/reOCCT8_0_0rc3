

#include <Transfer_ActorOfTransientProcess.hpp>
#include <Transfer_Binder.hpp>
#include <Transfer_ProcessForTransient.hpp>
#include <Transfer_SimpleBinderOfTransient.hpp>
#include <Transfer_TransientProcess.hpp>
#include <XSAlgo_ShapeProcessor.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Transfer_ActorOfTransientProcess, Transfer_ActorOfProcessForTransient)

Transfer_ActorOfTransientProcess::Transfer_ActorOfTransientProcess() = default;

occ::handle<Transfer_Binder> Transfer_ActorOfTransientProcess::Transfer(
  const occ::handle<Standard_Transient>&        start,
  const occ::handle<Transfer_TransientProcess>& TP,
  const Message_ProgressRange&                  theProgress)
{
  occ::handle<Standard_Transient> res = TransferTransient(start, TP, theProgress);
  if (res.IsNull())
    return NullResult();
  return TransientResult(res);
}

occ::handle<Transfer_Binder> Transfer_ActorOfTransientProcess::Transferring(
  const occ::handle<Standard_Transient>&           ent,
  const occ::handle<Transfer_ProcessForTransient>& TP,
  const Message_ProgressRange&                     theProgress)
{
  return Transfer(ent, occ::down_cast<Transfer_TransientProcess>(TP), theProgress);
}

occ::handle<Standard_Transient> Transfer_ActorOfTransientProcess::TransferTransient(
  const occ::handle<Standard_Transient>&,
  const occ::handle<Transfer_TransientProcess>&,
  const Message_ProgressRange&)
{
  occ::handle<Standard_Transient> nulres;
  return nulres;
}

void Transfer_ActorOfTransientProcess::SetShapeFixParameters(
  const XSAlgo_ShapeProcessor::ParameterMap& theParameters)
{
  myShapeProcParams = theParameters;
}

void Transfer_ActorOfTransientProcess::SetShapeFixParameters(
  XSAlgo_ShapeProcessor::ParameterMap&& theParameters)
{
  myShapeProcParams = std::move(theParameters);
}

void Transfer_ActorOfTransientProcess::SetShapeFixParameters(
  const DE_ShapeFixParameters&               theParameters,
  const XSAlgo_ShapeProcessor::ParameterMap& theAdditionalParameters)
{
  XSAlgo_ShapeProcessor::SetShapeFixParameters(theParameters,
                                               theAdditionalParameters,
                                               myShapeProcParams);
}

void Transfer_ActorOfTransientProcess::SetProcessingFlags(
  const ShapeProcess::OperationsFlags& theFlags)
{
  myShapeProcFlags.first  = theFlags;
  myShapeProcFlags.second = true;
}
