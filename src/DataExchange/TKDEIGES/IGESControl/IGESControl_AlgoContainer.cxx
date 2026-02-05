#include <IGESControl_AlgoContainer.hpp>
#include <IGESControl_ToolContainer.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESControl_AlgoContainer, IGESToBRep_AlgoContainer)

//=================================================================================================

IGESControl_AlgoContainer::IGESControl_AlgoContainer()

{
  SetToolContainer(new IGESControl_ToolContainer);
}
