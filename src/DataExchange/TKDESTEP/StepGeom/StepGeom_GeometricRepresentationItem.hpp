#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepRepr_RepresentationItem.hpp>

class StepGeom_GeometricRepresentationItem : public StepRepr_RepresentationItem
{

public:
  //! Returns a GeometricRepresentationItem
  Standard_EXPORT StepGeom_GeometricRepresentationItem();

  DEFINE_STANDARD_RTTIEXT(StepGeom_GeometricRepresentationItem, StepRepr_RepresentationItem)
};

