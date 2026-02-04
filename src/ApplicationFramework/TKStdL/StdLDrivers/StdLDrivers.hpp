#pragma once


#include <Standard_Handle.hpp>

class Standard_Transient;
class Standard_GUID;
class StdObjMgt_MapOfInstantiators;
class TDocStd_Application;

class StdLDrivers
{
public:
  //! Depending from the ID, returns a list of storage
  //! or retrieval attribute drivers. Used for plugin
  Standard_EXPORT static occ::handle<Standard_Transient> Factory(const Standard_GUID& aGUID);

  //! Defines format "OCC-StdLite" and registers its retrieval driver
  //! in the specified application
  Standard_EXPORT static void DefineFormat(const occ::handle<TDocStd_Application>& theApp);

  //! Register types.
  Standard_EXPORT static void BindTypes(StdObjMgt_MapOfInstantiators& theMap);
};

