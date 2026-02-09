

#include <IGESData_IGESEntity.hpp>
#include <IGESSelect_IGESName.hpp>
#include <Interface_InterfaceModel.hpp>
#include <MoniTool_Macros.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESSelect_IGESName, IFSelect_Signature)

static char falsetype[] = "?";
static char voidlabel[] = "";

IGESSelect_IGESName::IGESSelect_IGESName()
    : IFSelect_Signature("IGES Name (Short Label)")
{
}

const char* IGESSelect_IGESName::Value(const occ::handle<Standard_Transient>& ent,
                                       const occ::handle<Interface_InterfaceModel>&) const
{
  DeclareAndCast(IGESData_IGESEntity, igesent, ent);
  if (igesent.IsNull())
    return &falsetype[0];
  occ::handle<TCollection_HAsciiString> label = igesent->ShortLabel();
  if (label.IsNull())
    return &voidlabel[0];
  return label->ToCString();
}
