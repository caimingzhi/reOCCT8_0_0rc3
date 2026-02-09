#pragma once

#include <Standard_Handle.hpp>

class Standard_Transient;
class Standard_GUID;
class TDocStd_Application;

class XmlXCAFDrivers
{
public:
  Standard_EXPORT static const occ::handle<Standard_Transient>& Factory(const Standard_GUID& aGUID);

  Standard_EXPORT static void DefineFormat(const occ::handle<TDocStd_Application>& theApp);
};
