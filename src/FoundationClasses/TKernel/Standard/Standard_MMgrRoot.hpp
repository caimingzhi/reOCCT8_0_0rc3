#pragma once

#include <Standard_TypeDef.hpp>

class Standard_MMgrRoot
{
public:
  Standard_EXPORT virtual ~Standard_MMgrRoot();

  Standard_EXPORT virtual void* Allocate(const size_t theSize) = 0;

  Standard_EXPORT virtual void* Reallocate(void* thePtr, const size_t theSize) = 0;

  Standard_EXPORT virtual void Free(void* thePtr) = 0;

  Standard_EXPORT virtual int Purge(bool isDestroyed = false);
};
