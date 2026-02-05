#include <IGESControl_IGESBoundary.hpp>
#include <IGESControl_ToolContainer.hpp>
#include <IGESToBRep_IGESBoundary.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESControl_ToolContainer, IGESToBRep_ToolContainer)

//=================================================================================================

IGESControl_ToolContainer::IGESControl_ToolContainer()

  = default;

//=================================================================================================

occ::handle<IGESToBRep_IGESBoundary> IGESControl_ToolContainer::IGESBoundary() const
{
  return new IGESControl_IGESBoundary;
}
