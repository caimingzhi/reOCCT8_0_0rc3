#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepShape_ConnectedEdgeSet.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepGeom_GeometricRepresentationItem.hpp>
class TCollection_HAsciiString;

//! Representation of STEP entity EdgeBasedWireframeModel
class StepShape_EdgeBasedWireframeModel : public StepGeom_GeometricRepresentationItem
{

public:
  //! Empty constructor
  Standard_EXPORT StepShape_EdgeBasedWireframeModel();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>& aRepresentationItem_Name,
    const occ::handle<NCollection_HArray1<occ::handle<StepShape_ConnectedEdgeSet>>>& aEbwmBoundary);

  //! Returns field EbwmBoundary
  Standard_EXPORT occ::handle<NCollection_HArray1<occ::handle<StepShape_ConnectedEdgeSet>>>
                  EbwmBoundary() const;

  //! Set field EbwmBoundary
  Standard_EXPORT void SetEbwmBoundary(
    const occ::handle<NCollection_HArray1<occ::handle<StepShape_ConnectedEdgeSet>>>& EbwmBoundary);

  DEFINE_STANDARD_RTTIEXT(StepShape_EdgeBasedWireframeModel, StepGeom_GeometricRepresentationItem)

private:
  occ::handle<NCollection_HArray1<occ::handle<StepShape_ConnectedEdgeSet>>> theEbwmBoundary;
};

