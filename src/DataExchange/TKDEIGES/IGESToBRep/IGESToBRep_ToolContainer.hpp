#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class IGESToBRep_IGESBoundary;

class IGESToBRep_ToolContainer : public Standard_Transient
{

public:
  //! Empty constructor
  Standard_EXPORT IGESToBRep_ToolContainer();

  //! Returns IGESToBRep_IGESBoundary
  Standard_EXPORT virtual occ::handle<IGESToBRep_IGESBoundary> IGESBoundary() const;

  DEFINE_STANDARD_RTTIEXT(IGESToBRep_ToolContainer, Standard_Transient)
};
