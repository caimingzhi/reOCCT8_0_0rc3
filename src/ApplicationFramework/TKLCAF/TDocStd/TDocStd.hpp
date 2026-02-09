#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_GUID.hpp>
#include <NCollection_List.hpp>

class TDocStd
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void IDList(NCollection_List<Standard_GUID>& anIDList);
};
