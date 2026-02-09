#pragma once

#include <Standard_Handle.hpp>

class Standard_Transient;
class Standard_GUID;
class StdObjMgt_MapOfInstantiators;
class TDocStd_Application;

class StdDrivers
{
public:
  Standard_EXPORT static occ::handle<Standard_Transient> Factory(const Standard_GUID& aGUID);

  Standard_EXPORT static void DefineFormat(const occ::handle<TDocStd_Application>& theApp);

  Standard_EXPORT static void BindTypes(StdObjMgt_MapOfInstantiators& theMap);
};
