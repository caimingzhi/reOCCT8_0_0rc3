#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <NCollection_List.hpp>
#include <Standard_Boolean.hpp>

class Aspect_GenId
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Aspect_GenId();

  Standard_EXPORT Aspect_GenId(const int theLow, const int theUpper);

  Standard_EXPORT void Free();

  Standard_EXPORT void Free(const int theId);

  bool HasFree() const { return myFreeCount > 0 || myFreeIds.Extent() > 0; }

  int Available() const { return myFreeCount + myFreeIds.Extent(); }

  int Lower() const { return myLowerBound; }

  Standard_EXPORT int Next();

  Standard_EXPORT bool Next(int& theId);

  int Upper() const { return myUpperBound; }

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

private:
  int                   myFreeCount;
  int                   myLength;
  int                   myLowerBound;
  int                   myUpperBound;
  NCollection_List<int> myFreeIds;
};
