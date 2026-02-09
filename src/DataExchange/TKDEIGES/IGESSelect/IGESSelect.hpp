#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
class IGESData_IGESEntity;
class Interface_Graph;

class IGESSelect
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void Run();

  Standard_EXPORT static int WhatIges(const occ::handle<IGESData_IGESEntity>& ent,
                                      const Interface_Graph&                  G,
                                      occ::handle<IGESData_IGESEntity>&       sup,
                                      int&                                    index);
};
