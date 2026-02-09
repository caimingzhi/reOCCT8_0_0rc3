

#include <IFSelect_SignType.hpp>
#include <Interface_InterfaceModel.hpp>
#include <MoniTool_Macros.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IFSelect_SignType, IFSelect_Signature)

static const char* nulsign = "";

IFSelect_SignType::IFSelect_SignType(const bool nopk)
    : IFSelect_Signature((const char*)(nopk ? "Class Type" : "Dynamic Type")),
      thenopk(nopk)
{
}

const char* IFSelect_SignType::Value(const occ::handle<Standard_Transient>& ent,
                                     const occ::handle<Interface_InterfaceModel>&) const
{
  if (ent.IsNull())
    return nulsign;
  DeclareAndCast(Standard_Type, atype, ent);
  if (atype.IsNull())
    atype = ent->DynamicType();
  const char* tn = atype->Name();
  if (!thenopk)
    return tn;
  for (int i = 0; tn[i] != '\0'; i++)
  {
    if (tn[i] == '_')
      return &tn[i + 1];
  }
  return tn;
}
