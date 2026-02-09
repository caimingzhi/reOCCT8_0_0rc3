#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepFEA_RWCurve3dElementProperty.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepFEA_Curve3dElementProperty.hpp>
#include <StepFEA_CurveElementEndOffset.hpp>
#include <StepFEA_CurveElementEndRelease.hpp>
#include <StepFEA_CurveElementInterval.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

RWStepFEA_RWCurve3dElementProperty::RWStepFEA_RWCurve3dElementProperty() = default;

void RWStepFEA_RWCurve3dElementProperty::ReadStep(
  const occ::handle<StepData_StepReaderData>&        data,
  const int                                          num,
  occ::handle<Interface_Check>&                      ach,
  const occ::handle<StepFEA_Curve3dElementProperty>& ent) const
{

  if (!data->CheckNbParams(num, 5, ach, "curve3d_element_property"))
    return;

  occ::handle<TCollection_HAsciiString> aPropertyId;
  data->ReadString(num, 1, "property_id", ach, aPropertyId);

  occ::handle<TCollection_HAsciiString> aDescription;
  data->ReadString(num, 2, "description", ach, aDescription);

  occ::handle<NCollection_HArray1<occ::handle<StepFEA_CurveElementInterval>>> aIntervalDefinitions;
  int                                                                         sub3 = 0;
  if (data->ReadSubList(num, 3, "interval_definitions", ach, sub3))
  {
    int nb0 = data->NbParams(sub3);
    aIntervalDefinitions =
      new NCollection_HArray1<occ::handle<StepFEA_CurveElementInterval>>(1, nb0);
    int num2 = sub3;
    for (int i0 = 1; i0 <= nb0; i0++)
    {
      occ::handle<StepFEA_CurveElementInterval> anIt0;
      data->ReadEntity(num2,
                       i0,
                       "curve_element_interval",
                       ach,
                       STANDARD_TYPE(StepFEA_CurveElementInterval),
                       anIt0);
      aIntervalDefinitions->SetValue(i0, anIt0);
    }
  }

  occ::handle<NCollection_HArray1<occ::handle<StepFEA_CurveElementEndOffset>>> aEndOffsets;
  int                                                                          sub4 = 0;
  if (data->ReadSubList(num, 4, "end_offsets", ach, sub4))
  {
    int nb0     = data->NbParams(sub4);
    aEndOffsets = new NCollection_HArray1<occ::handle<StepFEA_CurveElementEndOffset>>(1, nb0);
    int num2    = sub4;
    for (int i0 = 1; i0 <= nb0; i0++)
    {
      occ::handle<StepFEA_CurveElementEndOffset> anIt0;
      data->ReadEntity(num2,
                       i0,
                       "curve_element_end_offset",
                       ach,
                       STANDARD_TYPE(StepFEA_CurveElementEndOffset),
                       anIt0);
      aEndOffsets->SetValue(i0, anIt0);
    }
  }

  occ::handle<NCollection_HArray1<occ::handle<StepFEA_CurveElementEndRelease>>> aEndReleases;
  int                                                                           sub5 = 0;
  if (data->ReadSubList(num, 5, "end_releases", ach, sub5))
  {
    int nb0      = data->NbParams(sub5);
    aEndReleases = new NCollection_HArray1<occ::handle<StepFEA_CurveElementEndRelease>>(1, nb0);
    int num2     = sub5;
    for (int i0 = 1; i0 <= nb0; i0++)
    {
      occ::handle<StepFEA_CurveElementEndRelease> anIt0;
      data->ReadEntity(num2,
                       i0,
                       "curve_element_end_release",
                       ach,
                       STANDARD_TYPE(StepFEA_CurveElementEndRelease),
                       anIt0);
      aEndReleases->SetValue(i0, anIt0);
    }
  }

  ent->Init(aPropertyId, aDescription, aIntervalDefinitions, aEndOffsets, aEndReleases);
}

void RWStepFEA_RWCurve3dElementProperty::WriteStep(
  StepData_StepWriter&                               SW,
  const occ::handle<StepFEA_Curve3dElementProperty>& ent) const
{

  SW.Send(ent->PropertyId());

  SW.Send(ent->Description());

  SW.OpenSub();
  for (int i2 = 1; i2 <= ent->IntervalDefinitions()->Length(); i2++)
  {
    occ::handle<StepFEA_CurveElementInterval> Var0 = ent->IntervalDefinitions()->Value(i2);
    SW.Send(Var0);
  }
  SW.CloseSub();

  SW.OpenSub();
  for (int i3 = 1; i3 <= ent->EndOffsets()->Length(); i3++)
  {
    occ::handle<StepFEA_CurveElementEndOffset> Var0 = ent->EndOffsets()->Value(i3);
    SW.Send(Var0);
  }
  SW.CloseSub();

  SW.OpenSub();
  for (int i4 = 1; i4 <= ent->EndReleases()->Length(); i4++)
  {
    occ::handle<StepFEA_CurveElementEndRelease> Var0 = ent->EndReleases()->Value(i4);
    SW.Send(Var0);
  }
  SW.CloseSub();
}

void RWStepFEA_RWCurve3dElementProperty::Share(
  const occ::handle<StepFEA_Curve3dElementProperty>& ent,
  Interface_EntityIterator&                          iter) const
{

  for (int i1 = 1; i1 <= ent->IntervalDefinitions()->Length(); i1++)
  {
    occ::handle<StepFEA_CurveElementInterval> Var0 = ent->IntervalDefinitions()->Value(i1);
    iter.AddItem(Var0);
  }

  for (int i2 = 1; i2 <= ent->EndOffsets()->Length(); i2++)
  {
    occ::handle<StepFEA_CurveElementEndOffset> Var0 = ent->EndOffsets()->Value(i2);
    iter.AddItem(Var0);
  }

  for (int i3 = 1; i3 <= ent->EndReleases()->Length(); i3++)
  {
    occ::handle<StepFEA_CurveElementEndRelease> Var0 = ent->EndReleases()->Value(i3);
    iter.AddItem(Var0);
  }
}
