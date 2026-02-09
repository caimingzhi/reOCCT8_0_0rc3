#include <IGESToBRep_IGESBoundary.hpp>
#include <IGESToBRep_ToolContainer.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESToBRep_ToolContainer, Standard_Transient)

IGESToBRep_ToolContainer::IGESToBRep_ToolContainer() = default;

occ::handle<IGESToBRep_IGESBoundary> IGESToBRep_ToolContainer::IGESBoundary() const
{
  return new IGESToBRep_IGESBoundary;
}
