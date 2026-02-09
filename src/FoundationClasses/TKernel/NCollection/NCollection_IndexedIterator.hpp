#pragma once

#include <Standard_Assert.hpp>
#include <iterator>

template <class Category, class BaseIndexedMap, class ItemType, bool IsConstant>
class NCollection_IndexedIterator
{
public:
  using iterator_category = Category;
  using value_type        = ItemType;
  using difference_type   = ptrdiff_t;
  using pointer           = typename std::conditional<IsConstant, const ItemType*, ItemType*>::type;
  using reference         = typename std::conditional<IsConstant, const ItemType&, ItemType&>::type;

  NCollection_IndexedIterator() noexcept
      : myIndex(0),
        myIndexedMap(nullptr)
  {
  }

  NCollection_IndexedIterator(const BaseIndexedMap& theMap) noexcept
      : myIndex(0),
        myIndexedMap((&const_cast<BaseIndexedMap&>(theMap)))
  {
  }

  NCollection_IndexedIterator(const size_t theIndex, const BaseIndexedMap& theMap) noexcept
      : myIndex(theIndex),
        myIndexedMap(&const_cast<BaseIndexedMap&>(theMap))
  {
  }

  NCollection_IndexedIterator(
    const NCollection_IndexedIterator<Category, BaseIndexedMap, ItemType, false>& theOther) noexcept
      : myIndex(theOther.myIndex),
        myIndexedMap(theOther.myIndexedMap)
  {
  }

  NCollection_IndexedIterator& operator=(
    const NCollection_IndexedIterator<Category, BaseIndexedMap, ItemType, false>& theOther) noexcept
  {
    myIndex      = theOther.myIndex;
    myIndexedMap = theOther.myIndexedMap;
    return *this;
  }

protected:
  template <bool Condition>
  typename std::enable_if<!Condition, ItemType&>::type Reference() const
  {
    return myIndexedMap->at(myIndex);
  }

  template <bool Condition>
  typename std::enable_if<Condition, const ItemType&>::type Reference() const
  {
    return myIndexedMap->at(myIndex);
  }

public:
  bool operator==(const NCollection_IndexedIterator& theOther) const noexcept
  {
    return myIndexedMap == theOther.myIndexedMap && myIndex == theOther.myIndex;
  }

  template <bool theOtherIsConstant>
  bool operator==(
    const NCollection_IndexedIterator<Category, BaseIndexedMap, ItemType, theOtherIsConstant>&
      theOther) const noexcept
  {
    return myIndexedMap == theOther.myIndexedMap && myIndex == theOther.myIndex;
  }

  template <bool theOtherIsConstant>
  bool operator!=(
    const NCollection_IndexedIterator<Category, BaseIndexedMap, ItemType, theOtherIsConstant>&
      theOther) const noexcept
  {
    return myIndexedMap != theOther.myIndexedMap || myIndex != theOther.myIndex;
  }

  bool operator!=(const NCollection_IndexedIterator& theOther) const noexcept
  {
    return !(*this == theOther);
  }

  typename NCollection_IndexedIterator::reference operator*() const
  {
    return Reference<IsConstant>();
  }

  typename NCollection_IndexedIterator::pointer operator->() const
  {
    return &Reference<IsConstant>();
  }

  NCollection_IndexedIterator& operator++() noexcept
  {
    myIndex++;
    return *this;
  }

  NCollection_IndexedIterator operator++(int) noexcept
  {
    const NCollection_IndexedIterator theOld(*this);
    ++(*this);
    return theOld;
  }

public:
  NCollection_IndexedIterator& operator--() noexcept
  {
    Standard_STATIC_ASSERT(
      (opencascade::std::is_same<std::bidirectional_iterator_tag, Category>::value
       || opencascade::std::is_same<std::random_access_iterator_tag, Category>::value));
    myIndex--;
    return *this;
  }

  NCollection_IndexedIterator operator--(int) noexcept
  {
    NCollection_IndexedIterator theOld(*this);
    --(*this);
    return theOld;
  }

public:
  NCollection_IndexedIterator& operator+=(
    typename NCollection_IndexedIterator::difference_type theOffset) noexcept
  {
    Standard_STATIC_ASSERT(
      (opencascade::std::is_same<std::random_access_iterator_tag, Category>::value));
    myIndex += theOffset;
    return *this;
  }

  NCollection_IndexedIterator operator+(
    typename NCollection_IndexedIterator::difference_type theOffset) const noexcept
  {
    NCollection_IndexedIterator aTemp(*this);
    return aTemp += theOffset;
  }

  NCollection_IndexedIterator& operator-=(
    typename NCollection_IndexedIterator::difference_type theOffset) noexcept
  {
    return *this += -theOffset;
  }

  NCollection_IndexedIterator operator-(
    typename NCollection_IndexedIterator::difference_type theOffset) const noexcept
  {
    NCollection_IndexedIterator aTemp(*this);
    return aTemp += -theOffset;
  }

  typename NCollection_IndexedIterator::difference_type operator-(
    const NCollection_IndexedIterator& theOther) const noexcept
  {
    Standard_STATIC_ASSERT(
      (opencascade::std::is_same<std::random_access_iterator_tag, Category>::value));
    return myIndex - theOther.myIndex;
  }

  typename NCollection_IndexedIterator::reference operator[](
    typename NCollection_IndexedIterator::difference_type theOffset) const
  {
    return *(*this + theOffset);
  }

  bool operator<(const NCollection_IndexedIterator& theOther) const noexcept
  {
    return (*this - theOther) < 0;
  }

  bool operator>(const NCollection_IndexedIterator& theOther) const noexcept
  {
    return theOther < *this;
  }

  bool operator<=(const NCollection_IndexedIterator& theOther) const noexcept
  {
    return !(theOther < *this);
  }

  bool operator>=(const NCollection_IndexedIterator& theOther) const noexcept
  {
    return !(*this < theOther);
  }

  friend class NCollection_IndexedIterator<Category, BaseIndexedMap, ItemType, !IsConstant>;

private:
  size_t          myIndex;
  BaseIndexedMap* myIndexedMap;
};
