#pragma once

#include <Standard.hpp>
#include <NCollection_BaseAllocator.hpp>

#include <type_traits>
#include <utility>

template <typename ItemType>
class NCollection_Allocator
{
public:
  typedef ItemType          value_type;
  typedef value_type*       pointer;
  typedef const value_type* const_pointer;
  typedef value_type&       reference;
  typedef const value_type& const_reference;
  typedef size_t            size_type;
  typedef ptrdiff_t         difference_type;

  template <typename OtherType>
  struct rebind
  {
    typedef NCollection_Allocator<OtherType> other;
  };

  NCollection_Allocator() noexcept = default;

  NCollection_Allocator(const occ::handle<NCollection_BaseAllocator>&) noexcept {}

  template <typename OtherType>
  NCollection_Allocator& operator=(const NCollection_Allocator<OtherType>&) noexcept
  {
    return *this;
  }

  template <typename OtherType>
  NCollection_Allocator(const NCollection_Allocator<OtherType>&) noexcept
  {
  }

  pointer address(reference theItem) const noexcept { return &theItem; }

  const_pointer address(const_reference theItem) const noexcept { return &theItem; }

  pointer allocate(const size_type theSize, const void* = nullptr) const
  {
    return static_cast<pointer>(Standard::AllocateOptimal(theSize * sizeof(ItemType)));
  }

  void deallocate(pointer thePnt, const size_type) const
  {
    Standard::Free(static_cast<void*>(thePnt));
  }

  pointer reallocate(pointer thePnt, const size_type theSize) const
  {
    return static_cast<pointer>(Standard::Reallocate(thePnt, theSize * sizeof(ItemType)));
  }

  template <class _Objty, class... _Types>
  void construct(_Objty* _Ptr, _Types&&... _Args)
  {
    ::new ((void*)_Ptr) _Objty(std::forward<_Types>(_Args)...);
  }

  void destroy(pointer thePnt) noexcept(std::is_nothrow_destructible<value_type>::value)
  {
    (void)thePnt;
    thePnt->~value_type();
  }

  constexpr bool operator==(const NCollection_Allocator&) const noexcept { return true; }

  template <class U>
  constexpr bool operator==(const NCollection_Allocator<U>&) const noexcept
  {
    return true;
  }

  constexpr bool operator!=(const NCollection_Allocator&) const noexcept { return false; }

  template <class U>
  constexpr bool operator!=(const NCollection_Allocator<U>&) const noexcept
  {
    return false;
  }
};

template <class U, class V>
constexpr bool operator==(const NCollection_Allocator<U>&, const NCollection_Allocator<V>&) noexcept
{
  return true;
}
