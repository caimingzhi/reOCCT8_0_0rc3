#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepFEA_NodeRepresentation.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepGeom_GeometricRepresentationItem.hpp>
class TCollection_HAsciiString;

//! Representation of STEP entity NodeSet
class StepFEA_NodeSet : public StepGeom_GeometricRepresentationItem
{

public:
  //! Empty constructor
  Standard_EXPORT StepFEA_NodeSet();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>& aRepresentationItem_Name,
    const occ::handle<NCollection_HArray1<occ::handle<StepFEA_NodeRepresentation>>>& aNodes);

  //! Returns field Nodes
  Standard_EXPORT occ::handle<NCollection_HArray1<occ::handle<StepFEA_NodeRepresentation>>> Nodes()
    const;

  //! Set field Nodes
  Standard_EXPORT void SetNodes(
    const occ::handle<NCollection_HArray1<occ::handle<StepFEA_NodeRepresentation>>>& Nodes);

  DEFINE_STANDARD_RTTIEXT(StepFEA_NodeSet, StepGeom_GeometricRepresentationItem)

private:
  occ::handle<NCollection_HArray1<occ::handle<StepFEA_NodeRepresentation>>> theNodes;
};

