#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Draw_Interpretor.hpp>

class XSDRAWDE
{
  DEFINE_STANDARD_ALLOC
public:
  //! Loads all Draw commands of XSDRAWDE. Used for plugin.
  Standard_EXPORT static void Factory(Draw_Interpretor& theDI);
};
