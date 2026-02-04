#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class StepData_StepReaderData;
class Interface_Check;
class StepData_StepWriter;
class Interface_EntityIterator;
class StepVisual_SurfaceStyleReflectanceAmbientDiffuseSpecular;

//! Read & Write tool for SurfaceStyleReflectanceAmbientDiffuseSpecular
class RWStepVisual_RWSurfaceStyleReflectanceAmbientDiffuseSpecular
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_HIDDEN RWStepVisual_RWSurfaceStyleReflectanceAmbientDiffuseSpecular();

  Standard_HIDDEN void ReadStep(
    const occ::handle<StepData_StepReaderData>&                                  theData,
    const int                                                                    theNum,
    occ::handle<Interface_Check>&                                                theAch,
    const occ::handle<StepVisual_SurfaceStyleReflectanceAmbientDiffuseSpecular>& theEnt) const;

  Standard_HIDDEN void WriteStep(
    StepData_StepWriter&                                                         theSW,
    const occ::handle<StepVisual_SurfaceStyleReflectanceAmbientDiffuseSpecular>& theEnt) const;

  Standard_HIDDEN void Share(
    const occ::handle<StepVisual_SurfaceStyleReflectanceAmbientDiffuseSpecular>& theEnt,
    Interface_EntityIterator&                                                    theIter) const;
};
