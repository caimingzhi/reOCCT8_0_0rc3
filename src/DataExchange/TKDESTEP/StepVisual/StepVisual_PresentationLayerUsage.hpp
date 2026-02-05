#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class StepVisual_PresentationLayerAssignment;
class StepVisual_PresentationRepresentation;

//! Added from StepVisual Rev2 to Rev4
class StepVisual_PresentationLayerUsage : public Standard_Transient
{

public:
  Standard_EXPORT StepVisual_PresentationLayerUsage();

  Standard_EXPORT void Init(
    const occ::handle<StepVisual_PresentationLayerAssignment>& aAssignment,
    const occ::handle<StepVisual_PresentationRepresentation>&  aPresentation);

  Standard_EXPORT void SetAssignment(
    const occ::handle<StepVisual_PresentationLayerAssignment>& aAssignment);

  Standard_EXPORT occ::handle<StepVisual_PresentationLayerAssignment> Assignment() const;

  Standard_EXPORT void SetPresentation(
    const occ::handle<StepVisual_PresentationRepresentation>& aPresentation);

  Standard_EXPORT occ::handle<StepVisual_PresentationRepresentation> Presentation() const;

  DEFINE_STANDARD_RTTIEXT(StepVisual_PresentationLayerUsage, Standard_Transient)

private:
  occ::handle<StepVisual_PresentationLayerAssignment> theAssignment;
  occ::handle<StepVisual_PresentationRepresentation>  thePresentation;
};
