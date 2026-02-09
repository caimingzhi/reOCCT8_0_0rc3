#include <Interface_EntityIterator.hpp>
#include "RWStepRepr_RWDerivedShapeAspect.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepRepr_DerivedShapeAspect.hpp>
#include <StepRepr_ProductDefinitionShape.hpp>

RWStepRepr_RWDerivedShapeAspect::RWStepRepr_RWDerivedShapeAspect() = default;

void RWStepRepr_RWDerivedShapeAspect::ReadStep(
  const occ::handle<StepData_StepReaderData>&     data,
  const int                                       num,
  occ::handle<Interface_Check>&                   ach,
  const occ::handle<StepRepr_DerivedShapeAspect>& ent) const
{

  if (!data->CheckNbParams(num, 4, ach, "derived_shape_aspect"))
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

  ent->Init(aShapeAspect_Name,
            aShapeAspect_Description,
            aShapeAspect_OfShape,
            aShapeAspect_ProductDefinitional);
}

void RWStepRepr_RWDerivedShapeAspect::WriteStep(
  StepData_StepWriter&                            SW,
  const occ::handle<StepRepr_DerivedShapeAspect>& ent) const
{

  SW.Send(ent->StepRepr_ShapeAspect::Name());

  SW.Send(ent->StepRepr_ShapeAspect::Description());

  SW.Send(ent->StepRepr_ShapeAspect::OfShape());

  SW.SendLogical(ent->StepRepr_ShapeAspect::ProductDefinitional());
}

void RWStepRepr_RWDerivedShapeAspect::Share(const occ::handle<StepRepr_DerivedShapeAspect>& ent,
                                            Interface_EntityIterator& iter) const
{

  iter.AddItem(ent->StepRepr_ShapeAspect::OfShape());
}
