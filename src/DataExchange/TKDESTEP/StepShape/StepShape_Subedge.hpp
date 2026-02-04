#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepShape_Edge.hpp>
class TCollection_HAsciiString;
class StepShape_Vertex;

//! Representation of STEP entity Subedge
class StepShape_Subedge : public StepShape_Edge
{

public:
  //! Empty constructor
  Standard_EXPORT StepShape_Subedge();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aRepresentationItem_Name,
                            const occ::handle<StepShape_Vertex>&         aEdge_EdgeStart,
                            const occ::handle<StepShape_Vertex>&         aEdge_EdgeEnd,
                            const occ::handle<StepShape_Edge>&           aParentEdge);

  //! Returns field ParentEdge
  Standard_EXPORT occ::handle<StepShape_Edge> ParentEdge() const;

  //! Set field ParentEdge
  Standard_EXPORT void SetParentEdge(const occ::handle<StepShape_Edge>& ParentEdge);

  DEFINE_STANDARD_RTTIEXT(StepShape_Subedge, StepShape_Edge)

private:
  occ::handle<StepShape_Edge> theParentEdge;
};

