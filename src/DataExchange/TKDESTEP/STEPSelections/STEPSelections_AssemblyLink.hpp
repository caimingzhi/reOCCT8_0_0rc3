#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class StepRepr_NextAssemblyUsageOccurrence;
class STEPSelections_AssemblyComponent;

class STEPSelections_AssemblyLink : public Standard_Transient
{

public:
  Standard_EXPORT STEPSelections_AssemblyLink();

  Standard_EXPORT STEPSelections_AssemblyLink(
    const occ::handle<StepRepr_NextAssemblyUsageOccurrence>& nauo,
    const occ::handle<Standard_Transient>&                   item,
    const occ::handle<STEPSelections_AssemblyComponent>&     part);

  occ::handle<StepRepr_NextAssemblyUsageOccurrence> GetNAUO() const;

  occ::handle<Standard_Transient> GetItem() const;

  occ::handle<STEPSelections_AssemblyComponent> GetComponent() const;

  void SetNAUO(const occ::handle<StepRepr_NextAssemblyUsageOccurrence>& nauo);

  void SetItem(const occ::handle<Standard_Transient>& item);

  void SetComponent(const occ::handle<STEPSelections_AssemblyComponent>& part);

  DEFINE_STANDARD_RTTIEXT(STEPSelections_AssemblyLink, Standard_Transient)

private:
  occ::handle<StepRepr_NextAssemblyUsageOccurrence> myNAUO;
  occ::handle<Standard_Transient>                   myItem;
  occ::handle<STEPSelections_AssemblyComponent>     myComponent;
};

inline occ::handle<StepRepr_NextAssemblyUsageOccurrence> STEPSelections_AssemblyLink::GetNAUO()
  const
{
  return myNAUO;
}

inline occ::handle<Standard_Transient> STEPSelections_AssemblyLink::GetItem() const
{
  return myItem;
}

inline occ::handle<STEPSelections_AssemblyComponent> STEPSelections_AssemblyLink::GetComponent()
  const
{
  return myComponent;
}

inline void STEPSelections_AssemblyLink::SetNAUO(
  const occ::handle<StepRepr_NextAssemblyUsageOccurrence>& nauo)
{
  myNAUO = nauo;
}

inline void STEPSelections_AssemblyLink::SetItem(const occ::handle<Standard_Transient>& item)
{
  myItem = item;
}

inline void STEPSelections_AssemblyLink::SetComponent(
  const occ::handle<STEPSelections_AssemblyComponent>& part)
{
  myComponent = part;
}
