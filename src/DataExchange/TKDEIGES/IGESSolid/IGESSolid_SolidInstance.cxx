#include <IGESSolid_SolidInstance.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESSolid_SolidInstance, IGESData_IGESEntity)

IGESSolid_SolidInstance::IGESSolid_SolidInstance() = default;

void IGESSolid_SolidInstance::Init(const occ::handle<IGESData_IGESEntity>& anEntity)
{
  theEntity = anEntity;
  InitTypeAndForm(430, 0);
}

bool IGESSolid_SolidInstance::IsBrep() const
{
  return (FormNumber() == 1);
}

void IGESSolid_SolidInstance::SetBrep(const bool brep)
{
  InitTypeAndForm(430, (brep ? 1 : 0));
}

occ::handle<IGESData_IGESEntity> IGESSolid_SolidInstance::Entity() const
{
  return theEntity;
}
