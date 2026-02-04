#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class StepData_StepReaderData;
class Interface_Check;
class StepData_StepWriter;
class Interface_EntityIterator;
class StepVisual_SurfaceStyleReflectanceAmbient;

//! Read & Write tool for SurfaceStyleReflectanceAmbient
class RWStepVisual_RWSurfaceStyleReflectanceAmbient
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_HIDDEN RWStepVisual_RWSurfaceStyleReflectanceAmbient();

  Standard_HIDDEN void ReadStep(
    const occ::handle<StepData_StepReaderData>&                   data,
    const int                                                     num,
    occ::handle<Interface_Check>&                                 ach,
    const occ::handle<StepVisual_SurfaceStyleReflectanceAmbient>& ent) const;

  Standard_HIDDEN void WriteStep(
    StepData_StepWriter&                                          SW,
    const occ::handle<StepVisual_SurfaceStyleReflectanceAmbient>& ent) const;

  Standard_HIDDEN void Share(const occ::handle<StepVisual_SurfaceStyleReflectanceAmbient>& ent,
                             Interface_EntityIterator& iter) const;
};
