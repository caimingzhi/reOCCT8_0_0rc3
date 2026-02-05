#include <IFSelect_SignAncestor.hpp>
#include <Interface_InterfaceModel.hpp>
#include <MoniTool_Macros.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IFSelect_SignAncestor, IFSelect_SignType)

IFSelect_SignAncestor::IFSelect_SignAncestor(const bool nopk)
    : IFSelect_SignType(nopk)
{
}

bool IFSelect_SignAncestor::Matches(const occ::handle<Standard_Transient>& ent,
                                    const occ::handle<Interface_InterfaceModel>& /*model*/,
                                    const TCollection_AsciiString& text,
                                    const bool /*exact*/) const
{
  if (ent.IsNull())
    return false;
  DeclareAndCast(Standard_Type, atype, ent);
  if (atype.IsNull())
    atype = ent->DynamicType();
  return atype->SubType(text.ToCString());
}
