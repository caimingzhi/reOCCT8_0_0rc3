

#include <IFSelect_SelectUnknownEntities.hpp>
#include <Interface_InterfaceModel.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IFSelect_SelectUnknownEntities, IFSelect_SelectExtract)

IFSelect_SelectUnknownEntities::IFSelect_SelectUnknownEntities() = default;

bool IFSelect_SelectUnknownEntities::Sort(const int,
                                          const occ::handle<Standard_Transient>&       ent,
                                          const occ::handle<Interface_InterfaceModel>& model) const
{
  return model->IsUnknownEntity(model->Number(ent));
}

TCollection_AsciiString IFSelect_SelectUnknownEntities::ExtractLabel() const
{
  return TCollection_AsciiString("Unrecognized type Entities");
}
