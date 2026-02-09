

#include <Interface_InterfaceModel.hpp>
#include <Interface_SignLabel.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Interface_SignLabel, MoniTool_SignText)

Interface_SignLabel::Interface_SignLabel() = default;

const char* Interface_SignLabel::Name() const
{
  return "Entity Label";
}

TCollection_AsciiString Interface_SignLabel::Text(
  const occ::handle<Standard_Transient>& ent,
  const occ::handle<Standard_Transient>& context) const
{
  TCollection_AsciiString               atext;
  occ::handle<Interface_InterfaceModel> model = occ::down_cast<Interface_InterfaceModel>(context);
  if (ent.IsNull() || model.IsNull())
    return atext;
  occ::handle<TCollection_HAsciiString> lab = model->StringLabel(ent);
  if (!lab.IsNull())
    atext = lab->String();
  return atext;
}
