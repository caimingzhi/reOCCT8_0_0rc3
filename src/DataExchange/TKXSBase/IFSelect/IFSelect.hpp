#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>
class IFSelect_WorkSession;

class IFSelect
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static bool SaveSession(const occ::handle<IFSelect_WorkSession>& WS,
                                          const char*                              file);

  Standard_EXPORT static bool RestoreSession(const occ::handle<IFSelect_WorkSession>& WS,
                                             const char*                              file);
};
