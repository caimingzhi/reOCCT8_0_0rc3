#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepGeom_GeometricRepresentationItem.hpp>

class StepVisual_TessellatedItem : public StepGeom_GeometricRepresentationItem
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepVisual_TessellatedItem();

  DEFINE_STANDARD_RTTIEXT(StepVisual_TessellatedItem, StepGeom_GeometricRepresentationItem)
};
