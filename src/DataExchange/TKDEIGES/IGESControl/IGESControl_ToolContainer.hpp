#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IGESToBRep_ToolContainer.hpp>
class IGESToBRep_IGESBoundary;

class IGESControl_ToolContainer : public IGESToBRep_ToolContainer
{

public:
  //! Empty constructor
  Standard_EXPORT IGESControl_ToolContainer();

  //! Returns IGESControl_IGESBoundary
  Standard_EXPORT occ::handle<IGESToBRep_IGESBoundary> IGESBoundary() const override;

  DEFINE_STANDARD_RTTIEXT(IGESControl_ToolContainer, IGESToBRep_ToolContainer)
};

