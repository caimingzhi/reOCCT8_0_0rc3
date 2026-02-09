#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepGeom_RWSurfaceCurve.hpp"
#include "RWStepGeom_RWSurfaceCurveAndBoundedCurve.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepGeom_BoundedCurve.hpp>
#include <StepGeom_Curve.hpp>
#include <StepGeom_SurfaceCurveAndBoundedCurve.hpp>
#include <TCollection_AsciiString.hpp>

#include "RWStepGeom_RWPreferredSurfaceCurveRepresentation.hpp"

RWStepGeom_RWSurfaceCurveAndBoundedCurve::RWStepGeom_RWSurfaceCurveAndBoundedCurve() = default;

void RWStepGeom_RWSurfaceCurveAndBoundedCurve::ReadStep(
  const occ::handle<StepData_StepReaderData>&              data,
  const int                                                num,
  occ::handle<Interface_Check>&                            ach,
  const occ::handle<StepGeom_SurfaceCurveAndBoundedCurve>& ent) const
{

  int num1 = num;

  num1 = data->NextForComplex(num1);

  num1 = data->NextForComplex(num1);

  num1 = data->NextForComplex(num1);
  if (!data->CheckNbParams(num1, 1, ach, "representation_item"))
    return;

  occ::handle<TCollection_HAsciiString> aName;
  data->ReadString(num1, 1, "name", ach, aName);

  num1 = data->NextForComplex(num1);
  if (!data->CheckNbParams(num1, 3, ach, "surface_curve"))
    return;

  occ::handle<StepGeom_Curve> aCurve3d;
  data->ReadEntity(num1, 1, "curve_3d", ach, STANDARD_TYPE(StepGeom_Curve), aCurve3d);

  occ::handle<NCollection_HArray1<StepGeom_PcurveOrSurface>> aAssociatedGeometry;
  StepGeom_PcurveOrSurface                                   aAssociatedGeometryItem;
  int                                                        nsub3;
  if (data->ReadSubList(num1, 2, "associated_geometry", ach, nsub3))
  {
    int nb3             = data->NbParams(nsub3);
    aAssociatedGeometry = new NCollection_HArray1<StepGeom_PcurveOrSurface>(1, nb3);
    for (int i3 = 1; i3 <= nb3; i3++)
    {

      if (data->ReadEntity(nsub3, i3, "associated_geometry", ach, aAssociatedGeometryItem))
        aAssociatedGeometry->SetValue(i3, aAssociatedGeometryItem);
    }
  }

  StepGeom_PreferredSurfaceCurveRepresentation aMasterRepresentation = StepGeom_pscrCurve3d;
  if (data->ParamType(num1, 3) == Interface_ParamEnum)
  {
    const char* text = data->ParamCValue(num1, 3);
    if (!RWStepGeom_RWPreferredSurfaceCurveRepresentation::ConvertToEnum(text,
                                                                         aMasterRepresentation))
    {
      ach->AddFail("Enumeration preferred_surface_curve_representation has not an allowed value");
    }
  }
  else
    ach->AddFail("Parameter #3 (master_representation) is not an enumeration");

  ent->Init(aName, aCurve3d, aAssociatedGeometry, aMasterRepresentation);
  ent->BoundedCurve() = new StepGeom_BoundedCurve;
  ent->BoundedCurve()->Init(aName);
}

void RWStepGeom_RWSurfaceCurveAndBoundedCurve::WriteStep(
  StepData_StepWriter&                                     SW,
  const occ::handle<StepGeom_SurfaceCurveAndBoundedCurve>& ent) const
{

  SW.StartEntity("BOUNDED_CURVE");
  SW.StartEntity("CURVE");
  SW.StartEntity("GEOMETRIC_REPRESENTATION_ITEM");

  SW.StartEntity("REPRESENTATION_ITEM");
  SW.Send(ent->Name());

  SW.StartEntity("SURFACE_CURVE");

  SW.Send(ent->Curve3d());

  SW.OpenSub();
  for (int i3 = 1; i3 <= ent->NbAssociatedGeometry(); i3++)
  {
    if (!ent->AssociatedGeometryValue(i3).Value().IsNull())
    {
      SW.Send(ent->AssociatedGeometryValue(i3).Value());
    }
  }
  SW.CloseSub();

  SW.SendEnum(
    RWStepGeom_RWPreferredSurfaceCurveRepresentation::ConvertToString(ent->MasterRepresentation()));
}

void RWStepGeom_RWSurfaceCurveAndBoundedCurve::Share(
  const occ::handle<StepGeom_SurfaceCurveAndBoundedCurve>& ent,
  Interface_EntityIterator&                                iter) const
{
  RWStepGeom_RWSurfaceCurve tool;
  tool.Share(ent, iter);
}
