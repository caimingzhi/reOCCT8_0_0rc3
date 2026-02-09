#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Interface_GeneralLib.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_DataMap.hpp>
#include <NCollection_IndexedDataMap.hpp>
class Interface_Protocol;
class Interface_SignType;
class Interface_InterfaceModel;
class Interface_GeneralModule;

class Interface_GTool : public Standard_Transient
{

public:
  Standard_EXPORT Interface_GTool();

  Standard_EXPORT Interface_GTool(const occ::handle<Interface_Protocol>& proto,
                                  const int                              nbent = 0);

  Standard_EXPORT void SetSignType(const occ::handle<Interface_SignType>& sign);

  Standard_EXPORT occ::handle<Interface_SignType> SignType() const;

  Standard_EXPORT const char* SignValue(const occ::handle<Standard_Transient>&       ent,
                                        const occ::handle<Interface_InterfaceModel>& model) const;

  Standard_EXPORT const char* SignName() const;

  Standard_EXPORT void SetProtocol(const occ::handle<Interface_Protocol>& proto,
                                   const bool                             enforce = false);

  Standard_EXPORT occ::handle<Interface_Protocol> Protocol() const;

  Standard_EXPORT Interface_GeneralLib& Lib();

  Standard_EXPORT void Reservate(const int nb, const bool enforce = false);

  Standard_EXPORT void ClearEntities();

  Standard_EXPORT bool Select(const occ::handle<Standard_Transient>& ent,
                              occ::handle<Interface_GeneralModule>&  gmod,
                              int&                                   CN,
                              const bool                             enforce = false);

  DEFINE_STANDARD_RTTIEXT(Interface_GTool, Standard_Transient)

private:
  occ::handle<Interface_Protocol>                           theproto;
  occ::handle<Interface_SignType>                           thesign;
  Interface_GeneralLib                                      thelib;
  NCollection_DataMap<occ::handle<Standard_Transient>, int> thentnum;
  NCollection_IndexedDataMap<occ::handle<Standard_Transient>, occ::handle<Standard_Transient>>
    thentmod;
};
