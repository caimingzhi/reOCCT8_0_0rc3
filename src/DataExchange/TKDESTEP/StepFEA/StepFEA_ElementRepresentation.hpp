#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepFEA_NodeRepresentation.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepRepr_Representation.hpp>
#include <StepRepr_RepresentationItem.hpp>
class TCollection_HAsciiString;
class StepRepr_RepresentationContext;

//! Representation of STEP entity ElementRepresentation
class StepFEA_ElementRepresentation : public StepRepr_Representation
{

public:
  //! Empty constructor
  Standard_EXPORT StepFEA_ElementRepresentation();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>& aRepresentation_Name,
    const occ::handle<NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>>&
                                                       aRepresentation_Items,
    const occ::handle<StepRepr_RepresentationContext>& aRepresentation_ContextOfItems,
    const occ::handle<NCollection_HArray1<occ::handle<StepFEA_NodeRepresentation>>>& aNodeList);

  //! Returns field NodeList
  Standard_EXPORT occ::handle<NCollection_HArray1<occ::handle<StepFEA_NodeRepresentation>>>
                  NodeList() const;

  //! Set field NodeList
  Standard_EXPORT void SetNodeList(
    const occ::handle<NCollection_HArray1<occ::handle<StepFEA_NodeRepresentation>>>& NodeList);

  DEFINE_STANDARD_RTTIEXT(StepFEA_ElementRepresentation, StepRepr_Representation)

private:
  occ::handle<NCollection_HArray1<occ::handle<StepFEA_NodeRepresentation>>> theNodeList;
};
