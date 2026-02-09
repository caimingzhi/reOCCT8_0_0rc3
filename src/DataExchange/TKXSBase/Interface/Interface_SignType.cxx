

#include <Interface_InterfaceModel.hpp>
#include <Interface_SignType.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Interface_SignType, MoniTool_SignText)

TCollection_AsciiString Interface_SignType::Text(
  const occ::handle<Standard_Transient>& ent,
  const occ::handle<Standard_Transient>& context) const
{
  TCollection_AsciiString               atext;
  occ::handle<Interface_InterfaceModel> model = occ::down_cast<Interface_InterfaceModel>(context);
  if (ent.IsNull() || model.IsNull())
    return atext;
  atext.AssignCat(Value(ent, model));
  return atext;
}

const char* Interface_SignType::ClassName(const char* typnam)
{
  char* tn = (char*)typnam;
  for (int i = 0; tn[i] != '\0'; i++)
  {
    if (tn[i] == '_')
      return &tn[i + 1];
  }
  return tn;
}
