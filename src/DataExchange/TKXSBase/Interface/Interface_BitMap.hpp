#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <TCollection_AsciiString.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>

class Interface_BitMap
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Interface_BitMap();

  Standard_EXPORT Interface_BitMap(const int nbitems, const int resflags = 0);

  Standard_EXPORT void Initialize(const int nbitems, const int resflags = 0);

  Standard_EXPORT Interface_BitMap(const Interface_BitMap& other, const bool copied = false);

  Standard_EXPORT void Initialize(const Interface_BitMap& other, const bool copied = false);

  Standard_EXPORT void Reservate(const int moreflags);

  Standard_EXPORT void SetLength(const int nbitems);

  Standard_EXPORT int AddFlag(const char* name = "");

  Standard_EXPORT int AddSomeFlags(const int more);

  Standard_EXPORT bool RemoveFlag(const int num);

  Standard_EXPORT bool SetFlagName(const int num, const char* name);

  Standard_EXPORT int NbFlags() const;

  Standard_EXPORT int Length() const;

  Standard_EXPORT const char* FlagName(const int num) const;

  Standard_EXPORT int FlagNumber(const char* name) const;

  Standard_EXPORT bool Value(const int item, const int flag = 0) const;

  Standard_EXPORT void SetValue(const int item, const bool val, const int flag = 0) const;

  Standard_EXPORT void SetTrue(const int item, const int flag = 0) const;

  Standard_EXPORT void SetFalse(const int item, const int flag = 0) const;

  Standard_EXPORT bool CTrue(const int item, const int flag = 0) const;

  Standard_EXPORT bool CFalse(const int item, const int flag = 0) const;

  Standard_EXPORT void Init(const bool val, const int flag = 0) const;

  Standard_EXPORT void Clear();

private:
  int                                                         thenbitems;
  int                                                         thenbwords;
  int                                                         thenbflags;
  occ::handle<NCollection_HArray1<int>>                       theflags;
  occ::handle<NCollection_HSequence<TCollection_AsciiString>> thenames;
};
