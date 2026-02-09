

#include <IFSelect_SelectAnyType.hpp>
#include <Interface_InterfaceModel.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IFSelect_SelectAnyType, IFSelect_SelectExtract)

bool IFSelect_SelectAnyType::Sort(const int,
                                  const occ::handle<Standard_Transient>& ent,
                                  const occ::handle<Interface_InterfaceModel>&) const
{
  return ent->IsKind(TypeForMatch());
}
