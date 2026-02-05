#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>

class TDocStd_Context
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TDocStd_Context();

  Standard_EXPORT void SetModifiedReferences(const bool Mod);

  Standard_EXPORT bool ModifiedReferences() const;

private:
  bool modifiedRef;
};
