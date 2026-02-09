#pragma once

#include <Standard.hpp>

#include <TCollection_AsciiString.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepRepr_Representation.hpp>
#include <StepRepr_RepresentationItem.hpp>
class TCollection_HAsciiString;
class StepRepr_RepresentationContext;

class StepFEA_FeaModel : public StepRepr_Representation
{

public:
  Standard_EXPORT StepFEA_FeaModel();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>& aRepresentation_Name,
    const occ::handle<NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>>&
                                                                     aRepresentation_Items,
    const occ::handle<StepRepr_RepresentationContext>&               aRepresentation_ContextOfItems,
    const occ::handle<TCollection_HAsciiString>&                     aCreatingSoftware,
    const occ::handle<NCollection_HArray1<TCollection_AsciiString>>& aIntendedAnalysisCode,
    const occ::handle<TCollection_HAsciiString>&                     aDescription,
    const occ::handle<TCollection_HAsciiString>&                     aAnalysisType);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> CreatingSoftware() const;

  Standard_EXPORT void SetCreatingSoftware(
    const occ::handle<TCollection_HAsciiString>& CreatingSoftware);

  Standard_EXPORT occ::handle<NCollection_HArray1<TCollection_AsciiString>> IntendedAnalysisCode()
    const;

  Standard_EXPORT void SetIntendedAnalysisCode(
    const occ::handle<NCollection_HArray1<TCollection_AsciiString>>& IntendedAnalysisCode);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Description() const;

  Standard_EXPORT void SetDescription(const occ::handle<TCollection_HAsciiString>& Description);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> AnalysisType() const;

  Standard_EXPORT void SetAnalysisType(const occ::handle<TCollection_HAsciiString>& AnalysisType);

  DEFINE_STANDARD_RTTIEXT(StepFEA_FeaModel, StepRepr_Representation)

private:
  occ::handle<TCollection_HAsciiString>                     theCreatingSoftware;
  occ::handle<NCollection_HArray1<TCollection_AsciiString>> theIntendedAnalysisCode;
  occ::handle<TCollection_HAsciiString>                     theDescription;
  occ::handle<TCollection_HAsciiString>                     theAnalysisType;
};
