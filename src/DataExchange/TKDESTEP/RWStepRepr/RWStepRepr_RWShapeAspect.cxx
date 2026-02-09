

#include <Interface_EntityIterator.hpp>
#include "RWStepRepr_RWShapeAspect.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepRepr_ProductDefinitionShape.hpp>
#include <StepRepr_ShapeAspect.hpp>

RWStepRepr_RWShapeAspect::RWStepRepr_RWShapeAspect() = default;

void RWStepRepr_RWShapeAspect::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                        const int                                   num,
                                        occ::handle<Interface_Check>&               ach,
                                        const occ::handle<StepRepr_ShapeAspect>&    ent) const
{

  if (!data->CheckNbParams(num, 4, ach, "shape_aspect"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<TCollection_HAsciiString> aDescription;
  if (data->IsParamDefined(num, 2))
  {

    data->ReadString(num, 2, "description", ach, aDescription);
  }

  occ::handle<StepRepr_ProductDefinitionShape> aOfShape;

  data
    ->ReadEntity(num, 3, "of_shape", ach, STANDARD_TYPE(StepRepr_ProductDefinitionShape), aOfShape);

  StepData_Logical aProductDefinitional;

  data->ReadLogical(num, 4, "product_definitional", ach, aProductDefinitional);

  ent->Init(aName, aDescription, aOfShape, aProductDefinitional);
}

void RWStepRepr_RWShapeAspect::WriteStep(StepData_StepWriter&                     SW,
                                         const occ::handle<StepRepr_ShapeAspect>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->Description());

  SW.Send(ent->OfShape());

  SW.SendLogical(ent->ProductDefinitional());
}

void RWStepRepr_RWShapeAspect::Share(const occ::handle<StepRepr_ShapeAspect>& ent,
                                     Interface_EntityIterator&                iter) const
{

  iter.GetOneItem(ent->OfShape());
}
