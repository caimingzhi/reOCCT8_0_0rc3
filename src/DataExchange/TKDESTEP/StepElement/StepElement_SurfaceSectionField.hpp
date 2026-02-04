#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>

//! Representation of STEP entity SurfaceSectionField
class StepElement_SurfaceSectionField : public Standard_Transient
{

public:
  //! Empty constructor
  Standard_EXPORT StepElement_SurfaceSectionField();

  DEFINE_STANDARD_RTTIEXT(StepElement_SurfaceSectionField, Standard_Transient)
};

