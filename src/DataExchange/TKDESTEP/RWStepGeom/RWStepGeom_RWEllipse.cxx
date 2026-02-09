

#include <Interface_EntityIterator.hpp>
#include <Interface_ShareTool.hpp>
#include "RWStepGeom_RWEllipse.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepGeom_Ellipse.hpp>

RWStepGeom_RWEllipse::RWStepGeom_RWEllipse() = default;

void RWStepGeom_RWEllipse::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                    const int                                   num,
                                    occ::handle<Interface_Check>&               ach,
                                    const occ::handle<StepGeom_Ellipse>&        ent) const
{

  if (!data->CheckNbParams(num, 4, ach, "ellipse"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  StepGeom_Axis2Placement aPosition;

  data->ReadEntity(num, 2, "position", ach, aPosition);

  double aSemiAxis1;

  data->ReadReal(num, 3, "semi_axis_1", ach, aSemiAxis1);

  double aSemiAxis2;

  data->ReadReal(num, 4, "semi_axis_2", ach, aSemiAxis2);

  ent->Init(aName, aPosition, aSemiAxis1, aSemiAxis2);
}

void RWStepGeom_RWEllipse::WriteStep(StepData_StepWriter&                 SW,
                                     const occ::handle<StepGeom_Ellipse>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->Position().Value());

  SW.Send(ent->SemiAxis1());

  SW.Send(ent->SemiAxis2());
}

void RWStepGeom_RWEllipse::Share(const occ::handle<StepGeom_Ellipse>& ent,
                                 Interface_EntityIterator&            iter) const
{

  iter.GetOneItem(ent->Position().Value());
}

void RWStepGeom_RWEllipse::Check(const occ::handle<StepGeom_Ellipse>& ent,
                                 const Interface_ShareTool&,
                                 occ::handle<Interface_Check>& ach) const
{
  if (ent->SemiAxis1() < ent->SemiAxis2())
    ach->AddWarning("ERROR: Ellipse: SemiMajor smaller than SemiMinor");
}
