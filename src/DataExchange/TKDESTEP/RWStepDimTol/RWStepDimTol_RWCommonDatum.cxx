#include <Interface_EntityIterator.hpp>
#include "RWStepDimTol_RWCommonDatum.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepDimTol_CommonDatum.hpp>
#include <StepDimTol_Datum.hpp>
#include <StepRepr_ProductDefinitionShape.hpp>

RWStepDimTol_RWCommonDatum::RWStepDimTol_RWCommonDatum() = default;

void RWStepDimTol_RWCommonDatum::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                          const int                                   num,
                                          occ::handle<Interface_Check>&               ach,
                                          const occ::handle<StepDimTol_CommonDatum>&  ent) const
{

  if (!data->CheckNbParams(num, 9, ach, "common_datum"))
    return;

  occ::handle<TCollection_HAsciiString> aShapeAspect_Name;
  data->ReadString(num, 1, "shape_aspect.name", ach, aShapeAspect_Name);

  occ::handle<TCollection_HAsciiString> aShapeAspect_Description;
  if (data->IsParamDefined(num, 2))
  {
    data->ReadString(num, 2, "shape_aspect.description", ach, aShapeAspect_Description);
  }

  occ::handle<StepRepr_ProductDefinitionShape> aShapeAspect_OfShape;
  data->ReadEntity(num,
                   3,
                   "shape_aspect.of_shape",
                   ach,
                   STANDARD_TYPE(StepRepr_ProductDefinitionShape),
                   aShapeAspect_OfShape);

  StepData_Logical aShapeAspect_ProductDefinitional;
  data->ReadLogical(num,
                    4,
                    "shape_aspect.product_definitional",
                    ach,
                    aShapeAspect_ProductDefinitional);

  occ::handle<TCollection_HAsciiString> aDatum_Name;
  data->ReadString(num, 5, "shape_aspect.name", ach, aDatum_Name);

  occ::handle<TCollection_HAsciiString> aDatum_Description;
  if (data->IsParamDefined(num, 6))
  {
    data->ReadString(num, 6, "shape_aspect.description", ach, aDatum_Description);
  }

  occ::handle<StepRepr_ProductDefinitionShape> aDatum_OfShape;
  data->ReadEntity(num,
                   7,
                   "shape_aspect.of_shape",
                   ach,
                   STANDARD_TYPE(StepRepr_ProductDefinitionShape),
                   aDatum_OfShape);

  StepData_Logical aDatum_ProductDefinitional;
  data->ReadLogical(num, 8, "shape_aspect.product_definitional", ach, aDatum_ProductDefinitional);

  occ::handle<TCollection_HAsciiString> aDatum_Identification;
  data->ReadString(num, 9, "datum.identification", ach, aDatum_Identification);

  ent->Init(aShapeAspect_Name,
            aShapeAspect_Description,
            aShapeAspect_OfShape,
            aShapeAspect_ProductDefinitional,
            aDatum_Name,
            aDatum_Description,
            aDatum_OfShape,
            aDatum_ProductDefinitional,
            aDatum_Identification);
}

void RWStepDimTol_RWCommonDatum::WriteStep(StepData_StepWriter&                       SW,
                                           const occ::handle<StepDimTol_CommonDatum>& ent) const
{

  SW.Send(ent->StepRepr_ShapeAspect::Name());

  SW.Send(ent->StepRepr_ShapeAspect::Description());

  SW.Send(ent->StepRepr_ShapeAspect::OfShape());

  SW.SendLogical(ent->StepRepr_ShapeAspect::ProductDefinitional());

  SW.Send(ent->Datum()->StepRepr_ShapeAspect::Name());

  SW.Send(ent->Datum()->StepRepr_ShapeAspect::Description());

  SW.Send(ent->Datum()->StepRepr_ShapeAspect::OfShape());

  SW.SendLogical(ent->Datum()->StepRepr_ShapeAspect::ProductDefinitional());

  SW.Send(ent->Datum()->Identification());
}

void RWStepDimTol_RWCommonDatum::Share(const occ::handle<StepDimTol_CommonDatum>& ent,
                                       Interface_EntityIterator&                  iter) const
{

  iter.AddItem(ent->StepRepr_ShapeAspect::OfShape());

  iter.AddItem(ent->Datum()->StepRepr_ShapeAspect::OfShape());
}
