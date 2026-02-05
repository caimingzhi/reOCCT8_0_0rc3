#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
class StepData_StepReaderData;
class Interface_Check;
class StepVisual_PointStyle;
class StepData_StepWriter;
class Interface_EntityIterator;

//! Read & Write Module for PointStyle
class RWStepVisual_RWPointStyle
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_HIDDEN RWStepVisual_RWPointStyle();

  Standard_HIDDEN void ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                const int                                   num,
                                occ::handle<Interface_Check>&               ach,
                                const occ::handle<StepVisual_PointStyle>&   ent) const;

  Standard_HIDDEN void WriteStep(StepData_StepWriter&                      SW,
                                 const occ::handle<StepVisual_PointStyle>& ent) const;

  Standard_HIDDEN void Share(const occ::handle<StepVisual_PointStyle>& ent,
                             Interface_EntityIterator&                 iter) const;
};
