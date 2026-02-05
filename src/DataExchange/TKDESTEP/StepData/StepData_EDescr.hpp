#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class StepData_Described;

//! This class is intended to describe the authorized form for an
//! entity, either Simple or Plex
class StepData_EDescr : public Standard_Transient
{

public:
  //! Tells if a ESDescr matches a step type : exact or super type
  Standard_EXPORT virtual bool Matches(const char* steptype) const = 0;

  //! Tells if a EDescr is complex (ECDescr) or simple (ESDescr)
  Standard_EXPORT virtual bool IsComplex() const = 0;

  //! Creates a described entity (i.e. a simple one)
  Standard_EXPORT virtual occ::handle<StepData_Described> NewEntity() const = 0;

  DEFINE_STANDARD_RTTIEXT(StepData_EDescr, Standard_Transient)
};
