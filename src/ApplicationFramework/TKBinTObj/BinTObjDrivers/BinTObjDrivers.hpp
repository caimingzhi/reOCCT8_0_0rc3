#pragma once


#include <Standard_GUID.hpp>

class BinMDF_ADriverTable;
class Message_Messenger;
class TDocStd_Application;

//! Class for registering storage/retrieval drivers for TObj Bin persistence

class BinTObjDrivers
{
public:
  // ---------- PUBLIC METHODS ----------

  Standard_EXPORT static const occ::handle<Standard_Transient>& Factory(const Standard_GUID& aGUID);
  // Returns a driver corresponding to <aGUID>. Used for plugin.

  //! Defines format "TObjBin" and registers its read and write drivers
  //! in the specified application
  Standard_EXPORT static void DefineFormat(const occ::handle<TDocStd_Application>& theApp);

  Standard_EXPORT static void AddDrivers(const occ::handle<BinMDF_ADriverTable>& aDriverTable,
                                         const occ::handle<Message_Messenger>&   aMsgDrv);
};


#ifdef _MSC_VER
#pragma once
#endif
