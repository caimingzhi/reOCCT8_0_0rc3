

#include <Interface_EntityIterator.hpp>
#include "RWStepGeom_RWHyperbola.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepGeom_Hyperbola.hpp>

RWStepGeom_RWHyperbola::RWStepGeom_RWHyperbola() = default;

void RWStepGeom_RWHyperbola::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                      const int                                   num,
                                      occ::handle<Interface_Check>&               ach,
                                      const occ::handle<StepGeom_Hyperbola>&      ent) const
{

  if (!data->CheckNbParams(num, 4, ach, "hyperbola"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  StepGeom_Axis2Placement aPosition;

  data->ReadEntity(num, 2, "position", ach, aPosition);

  double aSemiAxis;

  data->ReadReal(num, 3, "semi_axis", ach, aSemiAxis);

  double aSemiImagAxis;

  data->ReadReal(num, 4, "semi_imag_axis", ach, aSemiImagAxis);

  ent->Init(aName, aPosition, aSemiAxis, aSemiImagAxis);
}

void RWStepGeom_RWHyperbola::WriteStep(StepData_StepWriter&                   SW,
                                       const occ::handle<StepGeom_Hyperbola>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->Position().Value());

  SW.Send(ent->SemiAxis());

  SW.Send(ent->SemiImagAxis());
}

void RWStepGeom_RWHyperbola::Share(const occ::handle<StepGeom_Hyperbola>& ent,
                                   Interface_EntityIterator&              iter) const
{

  iter.GetOneItem(ent->Position().Value());
}
