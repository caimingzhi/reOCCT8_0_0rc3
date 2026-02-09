#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepShape_Edge.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepShape_TopologicalRepresentationItem.hpp>
class TCollection_HAsciiString;

class StepShape_ConnectedEdgeSet : public StepShape_TopologicalRepresentationItem
{

public:
  Standard_EXPORT StepShape_ConnectedEdgeSet();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&                         aRepresentationItem_Name,
    const occ::handle<NCollection_HArray1<occ::handle<StepShape_Edge>>>& aCesEdges);

  Standard_EXPORT occ::handle<NCollection_HArray1<occ::handle<StepShape_Edge>>> CesEdges() const;

  Standard_EXPORT void SetCesEdges(
    const occ::handle<NCollection_HArray1<occ::handle<StepShape_Edge>>>& CesEdges);

  DEFINE_STANDARD_RTTIEXT(StepShape_ConnectedEdgeSet, StepShape_TopologicalRepresentationItem)

private:
  occ::handle<NCollection_HArray1<occ::handle<StepShape_Edge>>> theCesEdges;
};
