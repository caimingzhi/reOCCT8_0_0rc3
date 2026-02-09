#pragma once

#include <Standard_Transient.hpp>
#include <Standard_Macro.hpp>
#include <Standard_Handle.hpp>

class StdStorage_HeaderData;
class StdStorage_TypeData;
class StdStorage_RootData;

class StdStorage_Data : public Standard_Transient
{

public:
  Standard_EXPORT StdStorage_Data();

  Standard_EXPORT void Clear();

  occ::handle<StdStorage_HeaderData> HeaderData() { return myHeaderData; }

  occ::handle<StdStorage_TypeData> TypeData() { return myTypeData; }

  occ::handle<StdStorage_RootData> RootData() { return myRootData; }

private:
  occ::handle<StdStorage_HeaderData> myHeaderData;
  occ::handle<StdStorage_TypeData>   myTypeData;
  occ::handle<StdStorage_RootData>   myRootData;
};
