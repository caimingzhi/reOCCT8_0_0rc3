#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class Quantity_Color;

class IGESCAFControl
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static Quantity_Color DecodeColor(const int col);

  Standard_EXPORT static int EncodeColor(const Quantity_Color& col);
};
