#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepFEA_NodeRepresentation.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepFEA_FeaGroup.hpp>
class TCollection_HAsciiString;
class StepFEA_FeaModel;

class StepFEA_NodeGroup : public StepFEA_FeaGroup
{

public:
  Standard_EXPORT StepFEA_NodeGroup();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>& aGroup_Name,
    const occ::handle<TCollection_HAsciiString>& aGroup_Description,
    const occ::handle<StepFEA_FeaModel>&         aFeaGroup_ModelRef,
    const occ::handle<NCollection_HArray1<occ::handle<StepFEA_NodeRepresentation>>>& aNodes);

  Standard_EXPORT occ::handle<NCollection_HArray1<occ::handle<StepFEA_NodeRepresentation>>> Nodes()
    const;

  Standard_EXPORT void SetNodes(
    const occ::handle<NCollection_HArray1<occ::handle<StepFEA_NodeRepresentation>>>& Nodes);

  DEFINE_STANDARD_RTTIEXT(StepFEA_NodeGroup, StepFEA_FeaGroup)

private:
  occ::handle<NCollection_HArray1<occ::handle<StepFEA_NodeRepresentation>>> theNodes;
};
