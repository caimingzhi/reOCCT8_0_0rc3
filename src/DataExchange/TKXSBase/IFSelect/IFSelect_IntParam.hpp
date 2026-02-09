#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <TCollection_AsciiString.hpp>
#include <NCollection_DefineAlloc.hpp>
#include <Standard_Transient.hpp>

class IFSelect_IntParam : public Standard_Transient
{

public:
  Standard_EXPORT IFSelect_IntParam();

  Standard_EXPORT void SetStaticName(const char* statname);

  Standard_EXPORT const char* StaticName() const;

  Standard_EXPORT int Value() const;

  Standard_EXPORT void SetValue(const int val);

  DEFINE_STANDARD_RTTIEXT(IFSelect_IntParam, Standard_Transient)

private:
  int                     theval;
  TCollection_AsciiString thestn;
};
