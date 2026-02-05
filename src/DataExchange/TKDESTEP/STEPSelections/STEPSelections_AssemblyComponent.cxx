#include <STEPSelections_AssemblyComponent.hpp>
#include <StepShape_ShapeDefinitionRepresentation.hpp>

IMPLEMENT_STANDARD_RTTIEXT(STEPSelections_AssemblyComponent, Standard_Transient)

STEPSelections_AssemblyComponent::STEPSelections_AssemblyComponent() = default;

STEPSelections_AssemblyComponent::STEPSelections_AssemblyComponent(
  const occ::handle<StepShape_ShapeDefinitionRepresentation>&                         sdr,
  const occ::handle<NCollection_HSequence<occ::handle<STEPSelections_AssemblyLink>>>& list)
{
  mySDR  = sdr;
  myList = list;
}
