

#include <Interface_EntityIterator.hpp>
#include "RWStepGeom_RWSurfacePatch.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepGeom_BoundedSurface.hpp>
#include <StepGeom_SurfacePatch.hpp>
#include <StepGeom_TransitionCode.hpp>
#include <TCollection_AsciiString.hpp>

#include "RWStepGeom_RWTransitionCode.hpp"

RWStepGeom_RWSurfacePatch::RWStepGeom_RWSurfacePatch() = default;

void RWStepGeom_RWSurfacePatch::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                         const int                                   num,
                                         occ::handle<Interface_Check>&               ach,
                                         const occ::handle<StepGeom_SurfacePatch>&   ent) const
{

  if (!data->CheckNbParams(num, 5, ach, "surface_patch"))
    return;

  occ::handle<StepGeom_BoundedSurface> aParentSurface;

  data->ReadEntity(num,
                   1,
                   "parent_surface",
                   ach,
                   STANDARD_TYPE(StepGeom_BoundedSurface),
                   aParentSurface);

  StepGeom_TransitionCode aUTransition = StepGeom_tcDiscontinuous;
  if (data->ParamType(num, 2) == Interface_ParamEnum)
  {
    const char* text = data->ParamCValue(num, 2);
    if (!RWStepGeom_RWTransitionCode::ConvertToEnum(text, aUTransition))
    {
      ach->AddFail("Enumeration transition_code has not an allowed value");
    }
  }
  else
    ach->AddFail("Parameter #2 (u_transition) is not an enumeration");

  StepGeom_TransitionCode aVTransition = StepGeom_tcDiscontinuous;
  if (data->ParamType(num, 3) == Interface_ParamEnum)
  {
    const char* text = data->ParamCValue(num, 3);
    if (!RWStepGeom_RWTransitionCode::ConvertToEnum(text, aVTransition))
    {
      ach->AddFail("Enumeration transition_code has not an allowed value");
    }
  }
  else
    ach->AddFail("Parameter #3 (v_transition) is not an enumeration");

  bool aUSense;

  data->ReadBoolean(num, 4, "u_sense", ach, aUSense);

  bool aVSense;

  data->ReadBoolean(num, 5, "v_sense", ach, aVSense);

  ent->Init(aParentSurface, aUTransition, aVTransition, aUSense, aVSense);
}

void RWStepGeom_RWSurfacePatch::WriteStep(StepData_StepWriter&                      SW,
                                          const occ::handle<StepGeom_SurfacePatch>& ent) const
{

  SW.Send(ent->ParentSurface());

  SW.SendEnum(RWStepGeom_RWTransitionCode::ConvertToString(ent->UTransition()));

  SW.SendEnum(RWStepGeom_RWTransitionCode::ConvertToString(ent->VTransition()));

  SW.SendBoolean(ent->USense());

  SW.SendBoolean(ent->VSense());
}

void RWStepGeom_RWSurfacePatch::Share(const occ::handle<StepGeom_SurfacePatch>& ent,
                                      Interface_EntityIterator&                 iter) const
{

  iter.GetOneItem(ent->ParentSurface());
}
