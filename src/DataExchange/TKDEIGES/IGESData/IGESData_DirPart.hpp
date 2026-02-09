#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class IGESData_IGESType;

class IGESData_DirPart
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IGESData_DirPart();

  Standard_EXPORT void Init(const int   i1,
                            const int   i2,
                            const int   i3,
                            const int   i4,
                            const int   i5,
                            const int   i6,
                            const int   i7,
                            const int   i8,
                            const int   i9,
                            const int   i19,
                            const int   i11,
                            const int   i12,
                            const int   i13,
                            const int   i14,
                            const int   i15,
                            const int   i16,
                            const int   i17,
                            const char* res1,
                            const char* res2,
                            const char* label,
                            const char* subscript);

  Standard_EXPORT void Values(int&        i1,
                              int&        i2,
                              int&        i3,
                              int&        i4,
                              int&        i5,
                              int&        i6,
                              int&        i7,
                              int&        i8,
                              int&        i9,
                              int&        i19,
                              int&        i11,
                              int&        i12,
                              int&        i13,
                              int&        i14,
                              int&        i15,
                              int&        i16,
                              int&        i17,
                              const char* res1,
                              const char* res2,
                              const char* label,
                              const char* subscript) const;

  Standard_EXPORT IGESData_IGESType Type() const;

private:
  int  thevals[17];
  char theres1[10];
  char theres2[10];
  char thelabl[10];
  char thesubs[10];
};
