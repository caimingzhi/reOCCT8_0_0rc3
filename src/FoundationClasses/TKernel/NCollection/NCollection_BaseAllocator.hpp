#pragma once

#include <Standard_DefineHandle.hpp>
#include <Standard_Transient.hpp>

class NCollection_BaseAllocator : public Standard_Transient
{
public:
  Standard_EXPORT virtual void* Allocate(const size_t theSize);
  Standard_EXPORT virtual void* AllocateOptimal(const size_t theSize);
  Standard_EXPORT virtual void  Free(void* theAddress);

  Standard_EXPORT static const occ::handle<NCollection_BaseAllocator>& CommonBaseAllocator();

protected:
  NCollection_BaseAllocator() noexcept {}

private:
  NCollection_BaseAllocator(const NCollection_BaseAllocator&) = delete;

public:
  DEFINE_STANDARD_RTTIEXT(NCollection_BaseAllocator, Standard_Transient)
};
