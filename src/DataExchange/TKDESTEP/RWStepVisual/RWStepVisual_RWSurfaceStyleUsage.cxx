

#include <Interface_EntityIterator.hpp>
#include "RWStepVisual_RWSurfaceStyleUsage.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepVisual_SurfaceSideStyle.hpp>
#include <StepVisual_SurfaceStyleUsage.hpp>
#include <TCollection_AsciiString.hpp>

#include "RWStepVisual_RWSurfaceSide.hpp"

RWStepVisual_RWSurfaceStyleUsage::RWStepVisual_RWSurfaceStyleUsage() = default;

void RWStepVisual_RWSurfaceStyleUsage::ReadStep(
  const occ::handle<StepData_StepReaderData>&      data,
  const int                                        num,
  occ::handle<Interface_Check>&                    ach,
  const occ::handle<StepVisual_SurfaceStyleUsage>& ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "surface_style_usage"))
    return;

  StepVisual_SurfaceSide aSide = StepVisual_ssNegative;
  if (data->ParamType(num, 1) == Interface_ParamEnum)
  {
    const char* text = data->ParamCValue(num, 1);
    if (!RWStepVisual_RWSurfaceSide::ConvertToEnum(text, aSide))
    {
      ach->AddFail("Enumeration surface_side has not an allowed value");
    }
  }
  else
    ach->AddFail("Parameter #1 (side) is not an enumeration");

  occ::handle<StepVisual_SurfaceSideStyle> aStyle;

  data->ReadEntity(num, 2, "style", ach, STANDARD_TYPE(StepVisual_SurfaceSideStyle), aStyle);

  ent->Init(aSide, aStyle);
}

void RWStepVisual_RWSurfaceStyleUsage::WriteStep(
  StepData_StepWriter&                             SW,
  const occ::handle<StepVisual_SurfaceStyleUsage>& ent) const
{

  SW.SendEnum(RWStepVisual_RWSurfaceSide::ConvertToString(ent->Side()));

  SW.Send(ent->Style());
}

void RWStepVisual_RWSurfaceStyleUsage::Share(const occ::handle<StepVisual_SurfaceStyleUsage>& ent,
                                             Interface_EntityIterator& iter) const
{

  iter.GetOneItem(ent->Style());
}
