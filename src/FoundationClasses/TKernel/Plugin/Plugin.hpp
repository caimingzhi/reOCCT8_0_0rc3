#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class Standard_Transient;
class Standard_GUID;

class Plugin
{
public:
  Standard_EXPORT static occ::handle<Standard_Transient> Load(const Standard_GUID& aGUID,
                                                              const bool theVerbose = true);
};

