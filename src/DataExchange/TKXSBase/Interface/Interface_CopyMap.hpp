#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
#include <NCollection_Array1.hpp>
#include <Interface_CopyControl.hpp>
class Interface_InterfaceModel;
class Standard_Transient;

class Interface_CopyMap : public Interface_CopyControl
{

public:
  Standard_EXPORT Interface_CopyMap(const occ::handle<Interface_InterfaceModel>& amodel);

  Standard_EXPORT void Clear() override;

  Standard_EXPORT occ::handle<Interface_InterfaceModel> Model() const;

  Standard_EXPORT void Bind(const occ::handle<Standard_Transient>& ent,
                            const occ::handle<Standard_Transient>& res) override;

  Standard_EXPORT bool Search(const occ::handle<Standard_Transient>& ent,
                              occ::handle<Standard_Transient>&       res) const override;

  DEFINE_STANDARD_RTTIEXT(Interface_CopyMap, Interface_CopyControl)

private:
  occ::handle<Interface_InterfaceModel>               themod;
  NCollection_Array1<occ::handle<Standard_Transient>> theres;
};
