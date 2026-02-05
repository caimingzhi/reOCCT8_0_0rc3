#include <Standard_Type.hpp>
#include <StepBasic_ActionMethod.hpp>
#include <StepBasic_ActionRequestSolution.hpp>
#include <StepBasic_VersionedActionRequest.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_ActionRequestSolution, Standard_Transient)

//=================================================================================================

StepBasic_ActionRequestSolution::StepBasic_ActionRequestSolution() = default;

//=================================================================================================

void StepBasic_ActionRequestSolution::Init(
  const occ::handle<StepBasic_ActionMethod>&           aMethod,
  const occ::handle<StepBasic_VersionedActionRequest>& aRequest)
{

  theMethod = aMethod;

  theRequest = aRequest;
}

//=================================================================================================

occ::handle<StepBasic_ActionMethod> StepBasic_ActionRequestSolution::Method() const
{
  return theMethod;
}

//=================================================================================================

void StepBasic_ActionRequestSolution::SetMethod(const occ::handle<StepBasic_ActionMethod>& aMethod)
{
  theMethod = aMethod;
}

//=================================================================================================

occ::handle<StepBasic_VersionedActionRequest> StepBasic_ActionRequestSolution::Request() const
{
  return theRequest;
}

//=================================================================================================

void StepBasic_ActionRequestSolution::SetRequest(
  const occ::handle<StepBasic_VersionedActionRequest>& aRequest)
{
  theRequest = aRequest;
}
