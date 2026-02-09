#pragma once

#include <NCollection_SparseArrayBase.hpp>

template <class TheItemType>
class NCollection_SparseArray : public NCollection_SparseArrayBase
{
public:
  explicit NCollection_SparseArray(size_t theIncrement) noexcept
      : NCollection_SparseArrayBase(sizeof(TheItemType), theIncrement)
  {
  }

  NCollection_SparseArray& Assign(const NCollection_SparseArray& theOther)
  {
    if (this == &theOther)
      return *this;
    this->assign(theOther);
    return *this;
  }

  void Exchange(NCollection_SparseArray& theOther) noexcept { this->exchange(theOther); }

  ~NCollection_SparseArray() override { Clear(); }

public:
  const TheItemType& Value(const size_t theIndex) const
  {
    return *(const TheItemType*)this->getValue(theIndex);
  }

  const TheItemType& operator()(const size_t theIndex) const { return Value(theIndex); }

  TheItemType& ChangeValue(const size_t theIndex)
  {
    return *(TheItemType*)(this->getValue(theIndex));
  }

  TheItemType& operator()(const size_t theIndex) { return ChangeValue(theIndex); }

  TheItemType& SetValue(const size_t theIndex, const TheItemType& theValue)
  {
    return *(TheItemType*)this->setValue(theIndex, (void*)&theValue);
  }

public:
  size_t Extent() const noexcept { return Size(); }

  bool IsEmpty() const noexcept { return Size() == 0; }

  const TheItemType& Find(const size_t theIndex) const { return Value(theIndex); }

  TheItemType& ChangeFind(const size_t theIndex) { return ChangeValue(theIndex); }

  TheItemType& Bind(const size_t theIndex, const TheItemType& theValue)
  {
    return SetValue(theIndex, theValue);
  }

  bool IsBound(const size_t theIndex) const { return this->HasValue(theIndex); }

  bool UnBind(const size_t theIndex) { return this->UnsetValue(theIndex); }

public:
  class ConstIterator : public NCollection_SparseArrayBase::Iterator
  {
  public:
    ConstIterator() noexcept = default;

    ConstIterator(const NCollection_SparseArray& theVector)
        : NCollection_SparseArrayBase::Iterator(&theVector)
    {
    }

    void Init(const NCollection_SparseArray& theVector) { this->init(&theVector); }

    const TheItemType& Value() const { return *(const TheItemType*)this->value(); }

    const TheItemType& operator()() const { return *(const TheItemType*)this->value(); }

    size_t Key() const noexcept { return Index(); }
  };

  class Iterator : public ConstIterator
  {
  public:
    Iterator() noexcept = default;

    Iterator(NCollection_SparseArray& theVector)
        : ConstIterator(theVector)
    {
    }

    void Init(const NCollection_SparseArray& theVector) { this->init(&theVector); }

    TheItemType& ChangeValue() { return *(TheItemType*)this->value(); }

    TheItemType& operator()() { return *(TheItemType*)this->value(); }

    const TheItemType& operator()() const { return *(const TheItemType*)this->value(); }
  };

private:
  void createItem(void* theAddress, void* theOther) override
  {
    new (theAddress) TheItemType(*(const TheItemType*)theOther);
  }

  void destroyItem(void* theAddress) override
  {
    ((TheItemType*)theAddress)->TheItemType::~TheItemType();
  }

  void copyItem(void* theAddress, void* theOther) override
  {
    (*(TheItemType*)theAddress) = *(const TheItemType*)theOther;
  }
};
