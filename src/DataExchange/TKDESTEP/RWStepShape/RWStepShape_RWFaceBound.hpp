#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
class StepData_StepReaderData;
class Interface_Check;
class StepShape_FaceBound;
class StepData_StepWriter;
class Interface_EntityIterator;
class Interface_ShareTool;

//! Read & Write Module for FaceBound
//! Check added by CKY , 7-OCT-1996
class RWStepShape_RWFaceBound
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_HIDDEN RWStepShape_RWFaceBound();

  Standard_HIDDEN void ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                const int                                   num,
                                occ::handle<Interface_Check>&               ach,
                                const occ::handle<StepShape_FaceBound>&     ent) const;

  Standard_HIDDEN void WriteStep(StepData_StepWriter&                    SW,
                                 const occ::handle<StepShape_FaceBound>& ent) const;

  Standard_HIDDEN void Share(const occ::handle<StepShape_FaceBound>& ent,
                             Interface_EntityIterator&               iter) const;

  Standard_HIDDEN void Check(const occ::handle<StepShape_FaceBound>& ent,
                             const Interface_ShareTool&              shares,
                             occ::handle<Interface_Check>&           ach) const;
};
