#pragma once

#include <NCollection_BaseAllocator.hpp>
#include <Standard.hpp>

#include <memory>
#include <type_traits>

template <typename ItemType>
class NCollection_OccAllocator
{
public:
  typedef ItemType          value_type;
  typedef value_type*       pointer;
  typedef const value_type* const_pointer;
  typedef value_type&       reference;
  typedef const value_type& const_reference;
  typedef size_t            size_type;
  typedef ptrdiff_t         difference_type;
  typedef std::false_type   propagate_on_container_move_assignment;

  template <typename OtherType>
  struct rebind
  {
    typedef NCollection_OccAllocator<OtherType> other;
  };

  NCollection_OccAllocator() noexcept
      : myAllocator(nullptr)
  {
  }

  NCollection_OccAllocator(const occ::handle<NCollection_BaseAllocator>& theAlloc)
      : myAllocator(theAlloc)
  {
  }

  NCollection_OccAllocator(occ::handle<NCollection_BaseAllocator>&& theAlloc)
      : myAllocator(theAlloc)
  {
  }

  NCollection_OccAllocator(const NCollection_OccAllocator& theOther)

    = default;

  NCollection_OccAllocator(NCollection_OccAllocator&& theOther) noexcept
      : myAllocator(theOther.myAllocator)
  {
  }

  NCollection_OccAllocator& operator=(const NCollection_OccAllocator& theOther) = default;

  NCollection_OccAllocator& operator=(NCollection_OccAllocator&& theOther) noexcept
  {
    myAllocator = theOther.myAllocator;
    return *this;
  }

  template <typename OtherType>
  NCollection_OccAllocator& operator=(const NCollection_OccAllocator<OtherType>& theOther)
  {
    myAllocator = theOther.myAllocator;
    return *this;
  }

  template <typename OtherType>
  NCollection_OccAllocator(const NCollection_OccAllocator<OtherType>& theOther)
      : myAllocator(theOther.Allocator())
  {
  }

  void SetAllocator(const occ::handle<NCollection_BaseAllocator>& theAlloc)
  {
    myAllocator = theAlloc;
  }

  const occ::handle<NCollection_BaseAllocator>& Allocator() const noexcept { return myAllocator; }

  pointer allocate(size_type theSize, const void* = nullptr)
  {
    return static_cast<pointer>(myAllocator.IsNull()
                                  ? Standard::AllocateOptimal(theSize * sizeof(ItemType))
                                  : myAllocator->AllocateOptimal(theSize * sizeof(ItemType)));
  }

  template <typename T>
  void deallocate(T* thePnt, size_type)
  {
    myAllocator.IsNull() ? Standard::Free(thePnt) : myAllocator->Free(thePnt);
  }

  void deallocate(pointer thePnt, size_type)
  {
    myAllocator.IsNull() ? Standard::Free(thePnt) : myAllocator->Free(thePnt);
  }

  template <class _Objty, class... _Types>
  void construct(_Objty* _Ptr, _Types&&... _Args)
  {
    ::new ((void*)_Ptr) _Objty(std::forward<_Types>(_Args)...);
  }

  pointer address(reference theItem) const noexcept { return &theItem; }

  const_pointer address(const_reference theItem) const noexcept { return &theItem; }

  template <class _Uty>
  void destroy(_Uty* _Ptr) noexcept(std::is_nothrow_destructible<_Uty>::value)
  {
    (void)_Ptr;
    _Ptr->~_Uty();
  }

  size_t max_size() const noexcept { return ((size_t)(-1) / sizeof(ItemType)); }

  bool operator==(const NCollection_OccAllocator& theOther) const noexcept
  {
    return theOther.Allocator() == myAllocator;
  }

  template <class U>
  bool operator==(const NCollection_OccAllocator<U>& theOther) const noexcept
  {
    return theOther.Allocator() == myAllocator;
  }

  bool operator!=(const NCollection_OccAllocator& theOther) const noexcept
  {
    return theOther.Allocator() != myAllocator;
  }

  template <class U>
  bool operator!=(const NCollection_OccAllocator<U>& theOther) const noexcept
  {
    return theOther.Allocator() != myAllocator;
  }

private:
  occ::handle<NCollection_BaseAllocator> myAllocator;
};

template <class U, class V>
bool operator==(const NCollection_OccAllocator<U>& theFirst,
                const NCollection_OccAllocator<V>& theSecond) noexcept
{
  return theFirst.Allocator() == theSecond.Allocator();
}
