#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>
class TCollection_AsciiString;

class Resource_LexicalCompare
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Resource_LexicalCompare();

  Standard_EXPORT bool IsLower(const TCollection_AsciiString& Left,
                               const TCollection_AsciiString& Right) const;
};
