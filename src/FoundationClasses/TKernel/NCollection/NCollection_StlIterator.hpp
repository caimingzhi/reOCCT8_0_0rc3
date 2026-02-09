#pragma once

#include <Standard_Assert.hpp>
#include <iterator>

template <class Category, class BaseIterator, class ItemType, bool IsConstant>
class NCollection_StlIterator
{
public:
  using iterator_category = Category;
  using value_type        = ItemType;
  using difference_type   = ptrdiff_t;
  using pointer           = typename std::conditional<IsConstant, const ItemType*, ItemType*>::type;
  using reference         = typename std::conditional<IsConstant, const ItemType&, ItemType&>::type;

  NCollection_StlIterator() = default;

  NCollection_StlIterator(const BaseIterator& theIterator)
      : myIterator(theIterator)
  {
  }

  NCollection_StlIterator(
    const NCollection_StlIterator<Category, BaseIterator, ItemType, false>& theIterator)
      : myIterator(theIterator.Iterator())
  {
  }

  NCollection_StlIterator& operator=(
    const NCollection_StlIterator<Category, BaseIterator, ItemType, false>& theIterator)
  {
    myIterator = theIterator.myIterator;
    return *this;
  }

  const BaseIterator& Iterator() const noexcept { return myIterator; }

  BaseIterator& ChangeIterator() noexcept { return myIterator; }

protected:
  template <bool Condition>
  typename std::enable_if<!Condition, ItemType&>::type Reference() const
  {
    return myIterator.ChangeValue();
  }

  template <bool Condition>
  typename std::enable_if<Condition, const ItemType&>::type Reference() const
  {
    return myIterator.Value();
  }

public:
  bool operator==(const NCollection_StlIterator& theOther) const
  {
    return myIterator.More() == theOther.myIterator.More()
           && (!myIterator.More() || myIterator.IsEqual(theOther.myIterator));
  }

  bool operator!=(const NCollection_StlIterator& theOther) const { return !(*this == theOther); }

  typename NCollection_StlIterator::reference operator*() const { return Reference<IsConstant>(); }

  typename NCollection_StlIterator::pointer operator->() const { return &Reference<IsConstant>(); }

  NCollection_StlIterator& operator++()
  {
    myIterator.Next();
    return *this;
  }

  NCollection_StlIterator operator++(int)
  {
    const NCollection_StlIterator theOld(*this);
    ++(*this);
    return theOld;
  }

public:
  NCollection_StlIterator& operator--()
  {
    Standard_STATIC_ASSERT(
      (opencascade::std::is_same<std::bidirectional_iterator_tag, Category>::value
       || opencascade::std::is_same<std::random_access_iterator_tag, Category>::value));
    myIterator.Previous();
    return *this;
  }

  NCollection_StlIterator operator--(int)
  {
    NCollection_StlIterator theOld(*this);
    --(*this);
    return theOld;
  }

public:
  NCollection_StlIterator& operator+=(typename NCollection_StlIterator::difference_type theOffset)
  {
    Standard_STATIC_ASSERT(
      (opencascade::std::is_same<std::random_access_iterator_tag, Category>::value));
    myIterator.Offset(theOffset);
    return *this;
  }

  NCollection_StlIterator operator+(
    typename NCollection_StlIterator::difference_type theOffset) const
  {
    NCollection_StlIterator aTemp(*this);
    return aTemp += theOffset;
  }

  NCollection_StlIterator& operator-=(typename NCollection_StlIterator::difference_type theOffset)
  {
    return *this += -theOffset;
  }

  NCollection_StlIterator operator-(
    typename NCollection_StlIterator::difference_type theOffset) const
  {
    NCollection_StlIterator aTemp(*this);
    return aTemp += -theOffset;
  }

  typename NCollection_StlIterator::difference_type operator-(
    const NCollection_StlIterator& theOther) const
  {
    Standard_STATIC_ASSERT(
      (opencascade::std::is_same<std::random_access_iterator_tag, Category>::value));
    return myIterator.Differ(theOther.myIterator);
  }

  typename NCollection_StlIterator::reference operator[](
    typename NCollection_StlIterator::difference_type theOffset) const
  {
    return *(*this + theOffset);
  }

  bool operator<(const NCollection_StlIterator& theOther) const { return (*this - theOther) < 0; }

  bool operator>(const NCollection_StlIterator& theOther) const { return theOther < *this; }

  bool operator<=(const NCollection_StlIterator& theOther) const { return !(theOther < *this); }

  bool operator>=(const NCollection_StlIterator& theOther) const { return !(*this < theOther); }

private:
  BaseIterator myIterator;
};
