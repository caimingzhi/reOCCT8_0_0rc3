

#include <IGESData_IGESEntity.hpp>
#include <IGESSelect_SelectVisibleStatus.hpp>
#include <Interface_InterfaceModel.hpp>
#include <MoniTool_Macros.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESSelect_SelectVisibleStatus, IFSelect_SelectExtract)

IGESSelect_SelectVisibleStatus::IGESSelect_SelectVisibleStatus() = default;

bool IGESSelect_SelectVisibleStatus::Sort(const int,
                                          const occ::handle<Standard_Transient>& ent,
                                          const occ::handle<Interface_InterfaceModel>&) const
{
  DeclareAndCast(IGESData_IGESEntity, igesent, ent);
  if (igesent.IsNull())
    return false;
  return (igesent->BlankStatus() == 0);
}

TCollection_AsciiString IGESSelect_SelectVisibleStatus::ExtractLabel() const
{
  return TCollection_AsciiString("IGES Entity, Status Visible");
}
