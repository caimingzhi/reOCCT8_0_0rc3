#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_CString.hpp>
#include <Standard_Integer.hpp>
#include <Standard_Transient.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
class Standard_Transient;
class IFSelect_WorkSession;
class IFSelect_Dispatch;

class IFSelect_Functions
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static occ::handle<Standard_Transient> GiveEntity(
    const occ::handle<IFSelect_WorkSession>& WS,
    const char*                              name = "");

  Standard_EXPORT static int GiveEntityNumber(const occ::handle<IFSelect_WorkSession>& WS,
                                              const char*                              name = "");

  Standard_EXPORT static occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>>
    GiveList(const occ::handle<IFSelect_WorkSession>& WS,
             const char*                              first  = "",
             const char*                              second = "");

  Standard_EXPORT static occ::handle<IFSelect_Dispatch> GiveDispatch(
    const occ::handle<IFSelect_WorkSession>& WS,
    const char*                              name,
    const bool                               mode = true);

  Standard_EXPORT static void Init();
};
