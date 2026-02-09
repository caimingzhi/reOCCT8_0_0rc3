#include <Interface_EntityIterator.hpp>
#include "RWStepElement_RWCurveElementEndReleasePacket.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepElement_CurveElementEndReleasePacket.hpp>

RWStepElement_RWCurveElementEndReleasePacket::RWStepElement_RWCurveElementEndReleasePacket() =
  default;

void RWStepElement_RWCurveElementEndReleasePacket::ReadStep(
  const occ::handle<StepData_StepReaderData>&                  data,
  const int                                                    num,
  occ::handle<Interface_Check>&                                ach,
  const occ::handle<StepElement_CurveElementEndReleasePacket>& ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "curve_element_end_release_packet"))
    return;

  StepElement_CurveElementFreedom aReleaseFreedom;
  data->ReadEntity(num, 1, "release_freedom", ach, aReleaseFreedom);

  double aReleaseStiffness;
  data->ReadReal(num, 2, "release_stiffness", ach, aReleaseStiffness);

  ent->Init(aReleaseFreedom, aReleaseStiffness);
}

void RWStepElement_RWCurveElementEndReleasePacket::WriteStep(
  StepData_StepWriter&                                         SW,
  const occ::handle<StepElement_CurveElementEndReleasePacket>& ent) const
{

  SW.Send(ent->ReleaseFreedom().Value());

  SW.Send(ent->ReleaseStiffness());
}

void RWStepElement_RWCurveElementEndReleasePacket::Share(
  const occ::handle<StepElement_CurveElementEndReleasePacket>& ent,
  Interface_EntityIterator&                                    iter) const
{

  iter.AddItem(ent->ReleaseFreedom().Value());
}
