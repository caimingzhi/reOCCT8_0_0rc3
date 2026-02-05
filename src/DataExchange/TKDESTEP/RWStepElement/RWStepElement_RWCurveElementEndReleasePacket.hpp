#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
class StepData_StepReaderData;
class Interface_Check;
class StepElement_CurveElementEndReleasePacket;
class StepData_StepWriter;
class Interface_EntityIterator;

//! Read & Write tool for CurveElementEndReleasePacket
class RWStepElement_RWCurveElementEndReleasePacket
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  Standard_HIDDEN RWStepElement_RWCurveElementEndReleasePacket();

  //! Reads CurveElementEndReleasePacket
  Standard_HIDDEN void ReadStep(
    const occ::handle<StepData_StepReaderData>&                  data,
    const int                                                    num,
    occ::handle<Interface_Check>&                                ach,
    const occ::handle<StepElement_CurveElementEndReleasePacket>& ent) const;

  //! Writes CurveElementEndReleasePacket
  Standard_HIDDEN void WriteStep(
    StepData_StepWriter&                                         SW,
    const occ::handle<StepElement_CurveElementEndReleasePacket>& ent) const;

  //! Fills data for graph (shared items)
  Standard_HIDDEN void Share(const occ::handle<StepElement_CurveElementEndReleasePacket>& ent,
                             Interface_EntityIterator& iter) const;
};
