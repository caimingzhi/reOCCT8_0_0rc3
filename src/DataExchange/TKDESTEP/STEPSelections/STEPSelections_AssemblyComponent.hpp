#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <STEPSelections_AssemblyLink.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <Standard_Transient.hpp>
class StepShape_ShapeDefinitionRepresentation;

class STEPSelections_AssemblyComponent : public Standard_Transient
{

public:
  Standard_EXPORT STEPSelections_AssemblyComponent();

  Standard_EXPORT STEPSelections_AssemblyComponent(
    const occ::handle<StepShape_ShapeDefinitionRepresentation>&                         sdr,
    const occ::handle<NCollection_HSequence<occ::handle<STEPSelections_AssemblyLink>>>& list);

  occ::handle<StepShape_ShapeDefinitionRepresentation> GetSDR() const;

  occ::handle<NCollection_HSequence<occ::handle<STEPSelections_AssemblyLink>>> GetList() const;

  void SetSDR(const occ::handle<StepShape_ShapeDefinitionRepresentation>& sdr);

  void SetList(
    const occ::handle<NCollection_HSequence<occ::handle<STEPSelections_AssemblyLink>>>& list);

  DEFINE_STANDARD_RTTIEXT(STEPSelections_AssemblyComponent, Standard_Transient)

private:
  occ::handle<StepShape_ShapeDefinitionRepresentation>                         mySDR;
  occ::handle<NCollection_HSequence<occ::handle<STEPSelections_AssemblyLink>>> myList;
};

inline occ::handle<StepShape_ShapeDefinitionRepresentation> STEPSelections_AssemblyComponent::
  GetSDR() const
{
  return mySDR;
}

//=================================================================================================

inline occ::handle<NCollection_HSequence<occ::handle<STEPSelections_AssemblyLink>>>
  STEPSelections_AssemblyComponent::GetList() const
{
  return myList;
}

//=================================================================================================

inline void STEPSelections_AssemblyComponent::SetSDR(
  const occ::handle<StepShape_ShapeDefinitionRepresentation>& sdr)
{
  mySDR = sdr;
}

inline void STEPSelections_AssemblyComponent::SetList(
  const occ::handle<NCollection_HSequence<occ::handle<STEPSelections_AssemblyLink>>>& list)
{
  myList = list;
}
