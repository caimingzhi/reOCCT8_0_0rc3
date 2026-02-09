#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepGeom_RWCurveBoundedSurface.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepGeom_CurveBoundedSurface.hpp>
#include <StepGeom_SurfaceBoundary.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepGeom_Surface.hpp>

RWStepGeom_RWCurveBoundedSurface::RWStepGeom_RWCurveBoundedSurface() = default;

void RWStepGeom_RWCurveBoundedSurface::ReadStep(
  const occ::handle<StepData_StepReaderData>&      data,
  const int                                        num,
  occ::handle<Interface_Check>&                    ach,
  const occ::handle<StepGeom_CurveBoundedSurface>& ent) const
{

  if (!data->CheckNbParams(num, 4, ach, "curve_bounded_surface"))
    return;

  occ::handle<TCollection_HAsciiString> aRepresentationItem_Name;
  data->ReadString(num, 1, "representation_item.name", ach, aRepresentationItem_Name);

  occ::handle<StepGeom_Surface> aBasisSurface;
  data->ReadEntity(num, 2, "basis_surface", ach, STANDARD_TYPE(StepGeom_Surface), aBasisSurface);

  occ::handle<NCollection_HArray1<StepGeom_SurfaceBoundary>> aBoundaries;
  int                                                        sub3 = 0;
  if (data->ReadSubList(num, 3, "boundaries", ach, sub3))
  {
    int num2    = sub3;
    int nb0     = data->NbParams(num2);
    aBoundaries = new NCollection_HArray1<StepGeom_SurfaceBoundary>(1, nb0);
    for (int i0 = 1; i0 <= nb0; i0++)
    {
      StepGeom_SurfaceBoundary anIt0;
      data->ReadEntity(num2, i0, "boundaries", ach, anIt0);
      aBoundaries->SetValue(i0, anIt0);
    }
  }

  bool aImplicitOuter;
  data->ReadBoolean(num, 4, "implicit_outer", ach, aImplicitOuter);

  ent->Init(aRepresentationItem_Name, aBasisSurface, aBoundaries, aImplicitOuter);
}

void RWStepGeom_RWCurveBoundedSurface::WriteStep(
  StepData_StepWriter&                             SW,
  const occ::handle<StepGeom_CurveBoundedSurface>& ent) const
{

  SW.Send(ent->StepRepr_RepresentationItem::Name());

  SW.Send(ent->BasisSurface());

  SW.OpenSub();
  for (int i2 = 1; i2 <= ent->Boundaries()->Length(); i2++)
  {
    StepGeom_SurfaceBoundary Var0 = ent->Boundaries()->Value(i2);
    SW.Send(Var0.Value());
  }
  SW.CloseSub();

  SW.SendBoolean(ent->ImplicitOuter());
}

void RWStepGeom_RWCurveBoundedSurface::Share(const occ::handle<StepGeom_CurveBoundedSurface>& ent,
                                             Interface_EntityIterator& iter) const
{

  iter.AddItem(ent->BasisSurface());

  for (int i2 = 1; i2 <= ent->Boundaries()->Length(); i2++)
  {
    StepGeom_SurfaceBoundary Var0 = ent->Boundaries()->Value(i2);
    iter.AddItem(Var0.Value());
  }
}
