#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_GUID.hpp>
#include <NCollection_List.hpp>
#include <Standard_OStream.hpp>
#include <TDataStd_RealEnum.hpp>

class TDataStd
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void IDList(NCollection_List<Standard_GUID>& anIDList);

  Standard_EXPORT static Standard_OStream& Print(const TDataStd_RealEnum DIM, Standard_OStream& S);
};
