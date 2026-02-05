#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class Quantity_Color;

//! Provides high-level API to translate IGES file
//! to and from DECAF document
class IGESCAFControl
{
public:
  DEFINE_STANDARD_ALLOC

  //! Provides a tool for writing IGES file
  //! Converts IGES color index to CASCADE color
  Standard_EXPORT static Quantity_Color DecodeColor(const int col);

  //! Tries to Convert CASCADE color to IGES color index
  //! If no corresponding color defined in IGES, returns 0
  Standard_EXPORT static int EncodeColor(const Quantity_Color& col);
};
