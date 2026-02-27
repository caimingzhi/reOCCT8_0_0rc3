#pragma once

#include <Standard_Handle.hpp>

class Standard_Transient;
class Standard_GUID;
class TCollection_AsciiString;
class XmlMDF_ADriverTable;
namespace System { namespace log {
class Message_Messenger;
}} // namespace System::log

class TDocStd_Application;

class XmlLDrivers
{
public:
  Standard_EXPORT static const occ::handle<Standard_Transient>& Factory(
    const Standard_GUID& theGUID);

  Standard_EXPORT static TCollection_AsciiString CreationDate();

  Standard_EXPORT static void DefineFormat(const occ::handle<TDocStd_Application>& theApp);

  Standard_EXPORT static occ::handle<XmlMDF_ADriverTable> AttributeDrivers(
    const occ::handle<System::log::Message_Messenger>& theMsgDriver);
};
