#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepFEA_NodeRepresentation.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepFEA_FeaGroup.hpp>
class TCollection_HAsciiString;
class StepFEA_FeaModel;

//! Representation of STEP entity NodeGroup
class StepFEA_NodeGroup : public StepFEA_FeaGroup
{

public:
  //! Empty constructor
  Standard_EXPORT StepFEA_NodeGroup();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>& aGroup_Name,
    const occ::handle<TCollection_HAsciiString>& aGroup_Description,
    const occ::handle<StepFEA_FeaModel>&         aFeaGroup_ModelRef,
    const occ::handle<NCollection_HArray1<occ::handle<StepFEA_NodeRepresentation>>>& aNodes);

  //! Returns field Nodes
  Standard_EXPORT occ::handle<NCollection_HArray1<occ::handle<StepFEA_NodeRepresentation>>> Nodes()
    const;

  //! Set field Nodes
  Standard_EXPORT void SetNodes(
    const occ::handle<NCollection_HArray1<occ::handle<StepFEA_NodeRepresentation>>>& Nodes);

  DEFINE_STANDARD_RTTIEXT(StepFEA_NodeGroup, StepFEA_FeaGroup)

private:
  occ::handle<NCollection_HArray1<occ::handle<StepFEA_NodeRepresentation>>> theNodes;
};

