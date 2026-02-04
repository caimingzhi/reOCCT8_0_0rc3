#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepShape_ManifoldSolidBrep.hpp>

class StepShape_FacetedBrep : public StepShape_ManifoldSolidBrep
{

public:
  //! Returns a FacetedBrep
  Standard_EXPORT StepShape_FacetedBrep();

  DEFINE_STANDARD_RTTIEXT(StepShape_FacetedBrep, StepShape_ManifoldSolidBrep)
};

