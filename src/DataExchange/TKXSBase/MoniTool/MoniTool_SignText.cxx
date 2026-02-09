

#include <MoniTool_SignText.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(MoniTool_SignText, Standard_Transient)

TCollection_AsciiString MoniTool_SignText::TextAlone(
  const occ::handle<Standard_Transient>& ent) const
{
  occ::handle<Standard_Transient> nulctx;
  TCollection_AsciiString         atext = Text(ent, nulctx);
  if (atext.Length() == 0)
  {
    if (ent.IsNull())
      atext.AssignCat("(NULL)");
    else
      atext.AssignCat(ent->DynamicType()->Name());
  }
  return atext;
}
