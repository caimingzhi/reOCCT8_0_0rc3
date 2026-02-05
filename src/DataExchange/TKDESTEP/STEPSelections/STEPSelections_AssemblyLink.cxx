#include <Standard_Transient.hpp>
#include <StepRepr_NextAssemblyUsageOccurrence.hpp>
#include <STEPSelections_AssemblyComponent.hpp>
#include <STEPSelections_AssemblyLink.hpp>

IMPLEMENT_STANDARD_RTTIEXT(STEPSelections_AssemblyLink, Standard_Transient)

STEPSelections_AssemblyLink::STEPSelections_AssemblyLink() = default;

STEPSelections_AssemblyLink::STEPSelections_AssemblyLink(
  const occ::handle<StepRepr_NextAssemblyUsageOccurrence>& nauo,
  const occ::handle<Standard_Transient>&                   item,
  const occ::handle<STEPSelections_AssemblyComponent>&     part)
{
  myNAUO      = nauo;
  myItem      = item;
  myComponent = part;
}
