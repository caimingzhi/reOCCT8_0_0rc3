#pragma once

#include <Standard_GUID.hpp>

class BinMDF_ADriverTable;
class Message_Messenger;
class TDocStd_Application;

class BinTObjDrivers
{
public:
  Standard_EXPORT static const occ::handle<Standard_Transient>& Factory(const Standard_GUID& aGUID);

  Standard_EXPORT static void DefineFormat(const occ::handle<TDocStd_Application>& theApp);

  Standard_EXPORT static void AddDrivers(const occ::handle<BinMDF_ADriverTable>& aDriverTable,
                                         const occ::handle<Message_Messenger>&   aMsgDrv);
};

#ifdef _MSC_VER
  #pragma once
#endif
