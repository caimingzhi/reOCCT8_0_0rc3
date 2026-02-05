#pragma once

#include <Standard_GUID.hpp>

class XmlMDF_ADriverTable;
class Message_Messenger;
class TDocStd_Application;

//! Class for registering storage/retrieval drivers for TObj XML persistence

class XmlTObjDrivers
{
public:
  //! Returns a driver corresponding to <aGUID>. Used for plugin.
  Standard_EXPORT static const occ::handle<Standard_Transient>& Factory(const Standard_GUID& aGUID);

  //! Defines format "TObjXml" and registers its read and write drivers
  //! in the specified application
  Standard_EXPORT static void DefineFormat(const occ::handle<TDocStd_Application>& theApp);

  Standard_EXPORT static void AddDrivers(const occ::handle<XmlMDF_ADriverTable>& aDriverTable,
                                         const occ::handle<Message_Messenger>&   anMsgDrv);
};

#ifdef _MSC_VER
  #pragma once
#endif
