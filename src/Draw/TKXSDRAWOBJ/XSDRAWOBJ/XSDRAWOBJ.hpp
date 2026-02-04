#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Draw_Interpretor.hpp>

class XSDRAWOBJ
{
  DEFINE_STANDARD_ALLOC
public:
  //! Loads all Draw commands of XSDRAWOBJ. Used for plugin.
  Standard_EXPORT static void Factory(Draw_Interpretor& theDI);
};

