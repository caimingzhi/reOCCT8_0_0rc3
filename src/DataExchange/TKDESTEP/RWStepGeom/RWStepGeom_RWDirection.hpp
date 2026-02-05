#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
class StepData_StepReaderData;
class Interface_Check;
class StepGeom_Direction;
class StepData_StepWriter;
class Interface_ShareTool;

//! Read & Write Module for Direction
//! Check added by CKY , 7-OCT-1996
class RWStepGeom_RWDirection
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_HIDDEN RWStepGeom_RWDirection();

  Standard_HIDDEN void ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                const int                                   num,
                                occ::handle<Interface_Check>&               ach,
                                const occ::handle<StepGeom_Direction>&      ent) const;

  Standard_HIDDEN void WriteStep(StepData_StepWriter&                   SW,
                                 const occ::handle<StepGeom_Direction>& ent) const;

  Standard_HIDDEN void Check(const occ::handle<StepGeom_Direction>& ent,
                             const Interface_ShareTool&             shares,
                             occ::handle<Interface_Check>&          ach) const;
};
