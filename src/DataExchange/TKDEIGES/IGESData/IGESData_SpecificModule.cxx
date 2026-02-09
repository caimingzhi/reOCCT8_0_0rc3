

#include <IGESData_IGESDumper.hpp>
#include <IGESData_IGESEntity.hpp>
#include <IGESData_SpecificModule.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESData_SpecificModule, Standard_Transient)

bool IGESData_SpecificModule::OwnCorrect(const int, const occ::handle<IGESData_IGESEntity>&) const
{
  return false;
}
