

#include "RWStepVisual_RWSurfaceStyleRenderingWithProperties.hpp"
#include <Interface_EntityIterator.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepVisual_SurfaceStyleRenderingWithProperties.hpp>
#include <StepVisual_ShadingSurfaceMethod.hpp>
#include <StepVisual_Colour.hpp>
#include <StepVisual_RenderingPropertiesSelect.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

RWStepVisual_RWSurfaceStyleRenderingWithProperties::
  RWStepVisual_RWSurfaceStyleRenderingWithProperties() = default;

void RWStepVisual_RWSurfaceStyleRenderingWithProperties::ReadStep(
  const occ::handle<StepData_StepReaderData>&                        data,
  const int                                                          num,
  occ::handle<Interface_Check>&                                      ach,
  const occ::handle<StepVisual_SurfaceStyleRenderingWithProperties>& ent) const
{

  if (!data->CheckNbParams(num, 3, ach, "surface_style_rendering_with_properties"))
    return;

  StepVisual_ShadingSurfaceMethod aSurfaceStyleRendering_RenderingMethod =
    StepVisual_ssmNormalShading;
  if (data->ParamType(num, 1) == Interface_ParamEnum)
  {
    const char* text = data->ParamCValue(num, 1);
    if (strcmp(text, ".CONSTANT_SHADING."))
      aSurfaceStyleRendering_RenderingMethod = StepVisual_ssmConstantShading;
    else if (strcmp(text, ".COLOUR_SHADING."))
      aSurfaceStyleRendering_RenderingMethod = StepVisual_ssmColourShading;
    else if (strcmp(text, ".DOT_SHADING."))
      aSurfaceStyleRendering_RenderingMethod = StepVisual_ssmDotShading;
    else if (strcmp(text, ".NORMAL_SHADING."))
      aSurfaceStyleRendering_RenderingMethod = StepVisual_ssmNormalShading;
    else
      ach->AddFail("Parameter #1 (surface_style_rendering.rendering_method) has not allowed value");
  }
  else
    ach->AddFail("Parameter #1 (surface_style_rendering.rendering_method) is not enumeration");

  occ::handle<StepVisual_Colour> aSurfaceStyleRendering_SurfaceColour;
  data->ReadEntity(num,
                   2,
                   "surface_style_rendering.surface_colour",
                   ach,
                   STANDARD_TYPE(StepVisual_Colour),
                   aSurfaceStyleRendering_SurfaceColour);

  occ::handle<NCollection_HArray1<StepVisual_RenderingPropertiesSelect>> aProperties;
  int                                                                    sub3 = 0;
  if (data->ReadSubList(num, 3, "properties", ach, sub3))
  {
    int nb0     = data->NbParams(sub3);
    aProperties = new NCollection_HArray1<StepVisual_RenderingPropertiesSelect>(1, nb0);
    int num2    = sub3;
    for (int i0 = 1; i0 <= nb0; i0++)
    {
      StepVisual_RenderingPropertiesSelect anIt0;
      data->ReadEntity(num2, i0, "rendering_properties_select", ach, anIt0);
      aProperties->SetValue(i0, anIt0);
    }
  }

  ent->Init(aSurfaceStyleRendering_RenderingMethod,
            aSurfaceStyleRendering_SurfaceColour,
            aProperties);
}

void RWStepVisual_RWSurfaceStyleRenderingWithProperties::WriteStep(
  StepData_StepWriter&                                               SW,
  const occ::handle<StepVisual_SurfaceStyleRenderingWithProperties>& ent) const
{

  switch (ent->RenderingMethod())
  {
    case StepVisual_ssmConstantShading:
      SW.SendEnum(".CONSTANT_SHADING.");
      break;
    case StepVisual_ssmColourShading:
      SW.SendEnum(".COLOUR_SHADING.");
      break;
    case StepVisual_ssmDotShading:
      SW.SendEnum(".DOT_SHADING.");
      break;
    case StepVisual_ssmNormalShading:
      SW.SendEnum(".NORMAL_SHADING.");
      break;
  }

  SW.Send(ent->SurfaceColour());

  SW.OpenSub();
  for (int i2 = 1; i2 <= ent->Properties()->Length(); i2++)
  {
    StepVisual_RenderingPropertiesSelect Var0 = ent->Properties()->Value(i2);
    SW.Send(Var0.Value());
  }
  SW.CloseSub();
}

void RWStepVisual_RWSurfaceStyleRenderingWithProperties::Share(
  const occ::handle<StepVisual_SurfaceStyleRenderingWithProperties>& ent,
  Interface_EntityIterator&                                          iter) const
{

  iter.AddItem(ent->StepVisual_SurfaceStyleRendering::SurfaceColour());

  for (int i2 = 1; i2 <= ent->Properties()->Length(); i2++)
  {
    StepVisual_RenderingPropertiesSelect Var0 = ent->Properties()->Value(i2);
    iter.AddItem(Var0.Value());
  }
}
