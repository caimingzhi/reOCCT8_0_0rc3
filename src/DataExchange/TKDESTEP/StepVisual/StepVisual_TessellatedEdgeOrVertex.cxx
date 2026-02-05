// Created on : Thu Mar 24 18:30:12 2022

#include <StepVisual_TessellatedEdgeOrVertex.hpp>
#include <StepVisual_TessellatedEdge.hpp>
#include <StepVisual_TessellatedVertex.hpp>

//=================================================================================================

StepVisual_TessellatedEdgeOrVertex::StepVisual_TessellatedEdgeOrVertex() = default;

//=================================================================================================

int StepVisual_TessellatedEdgeOrVertex::CaseNum(const occ::handle<Standard_Transient>& ent) const
{
  if (ent.IsNull())
    return 0;
  if (ent->IsKind(STANDARD_TYPE(StepVisual_TessellatedEdge)))
    return 1;
  if (ent->IsKind(STANDARD_TYPE(StepVisual_TessellatedVertex)))
    return 2;
  return 0;
}

//=================================================================================================

occ::handle<StepVisual_TessellatedEdge> StepVisual_TessellatedEdgeOrVertex::TessellatedEdge() const
{
  return occ::down_cast<StepVisual_TessellatedEdge>(Value());
}

//=================================================================================================

occ::handle<StepVisual_TessellatedVertex> StepVisual_TessellatedEdgeOrVertex::TessellatedVertex()
  const
{
  return occ::down_cast<StepVisual_TessellatedVertex>(Value());
}
