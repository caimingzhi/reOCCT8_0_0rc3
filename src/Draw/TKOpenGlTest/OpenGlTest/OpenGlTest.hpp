#pragma once


#include <Draw_Interpretor.hpp>

//! This package defines a set of Draw commands for testing of TKOpenGl library.
class OpenGlTest
{
public:
  DEFINE_STANDARD_ALLOC

  //! Adds Draw commands to the draw interpreter.
  Standard_EXPORT static void Commands(Draw_Interpretor& theDI);

  //! Plugin entry point function.
  Standard_EXPORT static void Factory(Draw_Interpretor& theDI);
};

