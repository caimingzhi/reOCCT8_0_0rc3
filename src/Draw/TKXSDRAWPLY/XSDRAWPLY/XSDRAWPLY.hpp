#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Draw_Interpretor.hpp>

class XSDRAWPLY
{
  DEFINE_STANDARD_ALLOC
public:
  //! Loads all Draw commands of XSDRAWPLY. Used for plugin.
  Standard_EXPORT static void Factory(Draw_Interpretor& theDI);
};

