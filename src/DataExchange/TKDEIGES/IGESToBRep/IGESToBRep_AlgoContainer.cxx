#include <IGESToBRep_AlgoContainer.hpp>
#include <IGESToBRep_ToolContainer.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESToBRep_AlgoContainer, Standard_Transient)

//=================================================================================================

IGESToBRep_AlgoContainer::IGESToBRep_AlgoContainer()
{
  myTC = new IGESToBRep_ToolContainer;
}
