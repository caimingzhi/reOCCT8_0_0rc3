#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class TCollection_AsciiString;

class Storage
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static TCollection_AsciiString Version();
};
