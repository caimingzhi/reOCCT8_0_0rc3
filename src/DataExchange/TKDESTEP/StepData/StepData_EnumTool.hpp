#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TCollection_AsciiString.hpp>
#include <NCollection_Sequence.hpp>
#include <Standard_CString.hpp>
class TCollection_AsciiString;

class StepData_EnumTool
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepData_EnumTool(const char* e0  = "",
                                    const char* e1  = "",
                                    const char* e2  = "",
                                    const char* e3  = "",
                                    const char* e4  = "",
                                    const char* e5  = "",
                                    const char* e6  = "",
                                    const char* e7  = "",
                                    const char* e8  = "",
                                    const char* e9  = "",
                                    const char* e10 = "",
                                    const char* e11 = "",
                                    const char* e12 = "",
                                    const char* e13 = "",
                                    const char* e14 = "",
                                    const char* e15 = "",
                                    const char* e16 = "",
                                    const char* e17 = "",
                                    const char* e18 = "",
                                    const char* e19 = "",
                                    const char* e20 = "",
                                    const char* e21 = "",
                                    const char* e22 = "",
                                    const char* e23 = "",
                                    const char* e24 = "",
                                    const char* e25 = "",
                                    const char* e26 = "",
                                    const char* e27 = "",
                                    const char* e28 = "",
                                    const char* e29 = "",
                                    const char* e30 = "",
                                    const char* e31 = "",
                                    const char* e32 = "",
                                    const char* e33 = "",
                                    const char* e34 = "",
                                    const char* e35 = "",
                                    const char* e36 = "",
                                    const char* e37 = "",
                                    const char* e38 = "",
                                    const char* e39 = "");

  Standard_EXPORT void AddDefinition(const char* term);

  Standard_EXPORT bool IsSet() const;

  Standard_EXPORT int MaxValue() const;

  Standard_EXPORT void Optional(const bool mode);

  Standard_EXPORT int NullValue() const;

  Standard_EXPORT const TCollection_AsciiString& Text(const int num) const;

  Standard_EXPORT int Value(const char* txt) const;

  Standard_EXPORT int Value(const TCollection_AsciiString& txt) const;

private:
  NCollection_Sequence<TCollection_AsciiString> thetexts;
  int                                           theinit;
  bool                                          theopt;
};
