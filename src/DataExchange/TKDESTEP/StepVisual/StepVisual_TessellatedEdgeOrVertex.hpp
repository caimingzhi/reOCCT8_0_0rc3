#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>
#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>

class Standard_Transient;
class StepVisual_TessellatedEdge;
class StepVisual_TessellatedVertex;

//! Representation of STEP SELECT type TessellatedEdgeOrVertex
class StepVisual_TessellatedEdgeOrVertex : public StepData_SelectType
{

public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  Standard_EXPORT StepVisual_TessellatedEdgeOrVertex();

  //! Recognizes a kind of TessellatedEdgeOrVertex select type
  //! -- 1 -> TessellatedEdge
  //! -- 2 -> TessellatedVertex
  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  //! Returns Value as TessellatedEdge (or Null if another type)
  Standard_EXPORT occ::handle<StepVisual_TessellatedEdge> TessellatedEdge() const;

  //! Returns Value as TessellatedVertex (or Null if another type)
  Standard_EXPORT occ::handle<StepVisual_TessellatedVertex> TessellatedVertex() const;
};
