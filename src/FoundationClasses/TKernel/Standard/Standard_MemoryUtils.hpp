#pragma once


#include <NCollection_Allocator.hpp>
#include <NCollection_OccAllocator.hpp>

#include <memory>

namespace opencascade
{
template <class T, class... Args>
std::shared_ptr<T> make_shared(Args&&... theArgs)
{
  return std::allocate_shared<T, NCollection_Allocator<T>, Args...>(NCollection_Allocator<T>(),
                                                                    std::forward<Args>(theArgs)...);
}

template <class T, class... Args>
std::shared_ptr<T> make_oshared(const occ::handle<NCollection_BaseAllocator>& theAlloc,
                                Args&&... theArgs)
{
  return std::allocate_shared<T, NCollection_OccAllocator<T>, Args...>(
    NCollection_OccAllocator<T>(theAlloc),
    std::forward<Args>(theArgs)...);
}

template <class T, class... Args>
std::shared_ptr<T> make_oshared(const NCollection_OccAllocator<T>& theAlloc, Args&&... theArgs)
{
  return std::allocate_shared<T, NCollection_OccAllocator<T>, Args...>(
    theAlloc,
    std::forward<Args>(theArgs)...);
}

template <class T, class... Args>
std::shared_ptr<T> make_oshared(NCollection_OccAllocator<T>&& theAlloc, Args&&... theArgs)
{
  return std::allocate_shared<T, NCollection_OccAllocator<T>, Args...>(
    std::forward<NCollection_OccAllocator<T>>(theAlloc),
    std::forward<Args>(theArgs)...);
}

template <typename T, class... Args>
std::unique_ptr<T> make_unique(Args&&... theArgs)
{
  return std::unique_ptr<T>(new T(std::forward<Args>(theArgs)...));
}
} // namespace opencascade

