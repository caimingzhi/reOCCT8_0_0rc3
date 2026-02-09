

#include <IFSelect_SelectErrorEntities.hpp>
#include <Interface_InterfaceModel.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IFSelect_SelectErrorEntities, IFSelect_SelectExtract)

IFSelect_SelectErrorEntities::IFSelect_SelectErrorEntities() = default;

bool IFSelect_SelectErrorEntities::Sort(const int,
                                        const occ::handle<Standard_Transient>&       ent,
                                        const occ::handle<Interface_InterfaceModel>& model) const

{
  return model->IsErrorEntity(model->Number(ent));
}

TCollection_AsciiString IFSelect_SelectErrorEntities::ExtractLabel() const
{
  return TCollection_AsciiString("Error Entities");
}
