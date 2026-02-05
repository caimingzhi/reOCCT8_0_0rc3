#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepShape_OrientedEdge.hpp>
class StepGeom_Pcurve;
class TCollection_HAsciiString;
class StepShape_Edge;

//! Representation of STEP entity SeamEdge
class StepShape_SeamEdge : public StepShape_OrientedEdge
{

public:
  //! Empty constructor
  Standard_EXPORT StepShape_SeamEdge();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aRepresentationItem_Name,
                            const occ::handle<StepShape_Edge>&           aOrientedEdge_EdgeElement,
                            const bool                                   aOrientedEdge_Orientation,
                            const occ::handle<StepGeom_Pcurve>&          aPcurveReference);

  //! Returns field PcurveReference
  Standard_EXPORT occ::handle<StepGeom_Pcurve> PcurveReference() const;

  //! Set field PcurveReference
  Standard_EXPORT void SetPcurveReference(const occ::handle<StepGeom_Pcurve>& PcurveReference);

  DEFINE_STANDARD_RTTIEXT(StepShape_SeamEdge, StepShape_OrientedEdge)

private:
  occ::handle<StepGeom_Pcurve> thePcurveReference;
};
