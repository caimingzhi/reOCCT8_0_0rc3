#pragma once


#include <Standard.hpp>

#include <TCollection_AsciiString.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepRepr_Representation.hpp>
#include <StepRepr_RepresentationItem.hpp>
class TCollection_HAsciiString;
class StepRepr_RepresentationContext;

//! Representation of STEP entity FeaModel
class StepFEA_FeaModel : public StepRepr_Representation
{

public:
  //! Empty constructor
  Standard_EXPORT StepFEA_FeaModel();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>& aRepresentation_Name,
    const occ::handle<NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>>&
                                                                     aRepresentation_Items,
    const occ::handle<StepRepr_RepresentationContext>&               aRepresentation_ContextOfItems,
    const occ::handle<TCollection_HAsciiString>&                     aCreatingSoftware,
    const occ::handle<NCollection_HArray1<TCollection_AsciiString>>& aIntendedAnalysisCode,
    const occ::handle<TCollection_HAsciiString>&                     aDescription,
    const occ::handle<TCollection_HAsciiString>&                     aAnalysisType);

  //! Returns field CreatingSoftware
  Standard_EXPORT occ::handle<TCollection_HAsciiString> CreatingSoftware() const;

  //! Set field CreatingSoftware
  Standard_EXPORT void SetCreatingSoftware(
    const occ::handle<TCollection_HAsciiString>& CreatingSoftware);

  //! Returns field IntendedAnalysisCode
  Standard_EXPORT occ::handle<NCollection_HArray1<TCollection_AsciiString>> IntendedAnalysisCode()
    const;

  //! Set field IntendedAnalysisCode
  Standard_EXPORT void SetIntendedAnalysisCode(
    const occ::handle<NCollection_HArray1<TCollection_AsciiString>>& IntendedAnalysisCode);

  //! Returns field Description
  Standard_EXPORT occ::handle<TCollection_HAsciiString> Description() const;

  //! Set field Description
  Standard_EXPORT void SetDescription(const occ::handle<TCollection_HAsciiString>& Description);

  //! Returns field AnalysisType
  Standard_EXPORT occ::handle<TCollection_HAsciiString> AnalysisType() const;

  //! Set field AnalysisType
  Standard_EXPORT void SetAnalysisType(const occ::handle<TCollection_HAsciiString>& AnalysisType);

  DEFINE_STANDARD_RTTIEXT(StepFEA_FeaModel, StepRepr_Representation)

private:
  occ::handle<TCollection_HAsciiString>                     theCreatingSoftware;
  occ::handle<NCollection_HArray1<TCollection_AsciiString>> theIntendedAnalysisCode;
  occ::handle<TCollection_HAsciiString>                     theDescription;
  occ::handle<TCollection_HAsciiString>                     theAnalysisType;
};

