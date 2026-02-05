#pragma once

#include <Standard_Handle.hpp>

class Standard_Transient;
class Standard_GUID;
class TDocStd_Application;

class XmlXCAFDrivers
{
public:
  //! Depending from the ID, returns a list of storage
  //! or retrieval attribute drivers. Used for plugin.
  //!
  //! Standard data model drivers
  //! ===========================
  //! 47b0b826-d931-11d1-b5da-00a0c9064368 Transient-Persistent
  //! 47b0b827-d931-11d1-b5da-00a0c9064368 Persistent-Transient
  //!
  //! XCAF data model drivers
  //! =================================
  //! ed8793f8-3142-11d4-b9b5-0060b0ee281b Transient-Persistent
  //! ed8793f9-3142-11d4-b9b5-0060b0ee281b Persistent-Transient
  //! ed8793fa-3142-11d4-b9b5-0060b0ee281b XCAFSchema
  Standard_EXPORT static const occ::handle<Standard_Transient>& Factory(const Standard_GUID& aGUID);

  //! Defines format "XmlXCAF" and registers its read and write drivers
  //! in the specified application
  Standard_EXPORT static void DefineFormat(const occ::handle<TDocStd_Application>& theApp);
};
