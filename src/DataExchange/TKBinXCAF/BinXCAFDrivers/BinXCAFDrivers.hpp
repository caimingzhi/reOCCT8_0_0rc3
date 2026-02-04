#pragma once


#include <Standard_Handle.hpp>

class Standard_Transient;
class Standard_GUID;
class BinMDF_ADriverTable;
class Message_Messenger;
class TDocStd_Application;

class BinXCAFDrivers
{
public:
  Standard_EXPORT static const occ::handle<Standard_Transient>& Factory(
    const Standard_GUID& theGUID);

  //! Defines format "BinXCAF" and registers its read and write drivers
  //! in the specified application
  Standard_EXPORT static void DefineFormat(const occ::handle<TDocStd_Application>& theApp);

  //! Creates the table of drivers of types supported
  Standard_EXPORT static occ::handle<BinMDF_ADriverTable> AttributeDrivers(
    const occ::handle<Message_Messenger>& MsgDrv);
};

