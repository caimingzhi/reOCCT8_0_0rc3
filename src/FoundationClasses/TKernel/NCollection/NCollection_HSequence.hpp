#pragma once

#include <NCollection_Sequence.hpp>
#include <Standard_Type.hpp>
#include <Standard_Transient.hpp>

template <typename TheItemType>
class NCollection_HSequence : public NCollection_Sequence<TheItemType>, public Standard_Transient
{
public:
  DEFINE_STANDARD_ALLOC
  DEFINE_NCOLLECTION_ALLOC

  typedef NCollection_Sequence<TheItemType> SequenceType;
  typedef TheItemType                       value_type;

public:
  NCollection_HSequence() = default;

  NCollection_HSequence(const SequenceType& theOther)
      : SequenceType(theOther)
  {
  }

  const SequenceType& Sequence() const noexcept { return *this; }

  SequenceType& ChangeSequence() noexcept { return *this; }

  void Append(const TheItemType& theItem) { SequenceType::Append(theItem); }

  void Append(SequenceType& theSequence) { SequenceType::Append(theSequence); }

  template <class T>
  void Append(
    const opencascade::handle<T>& theOther,
    typename std::enable_if<std::is_base_of<NCollection_HSequence, T>::value>::type* = nullptr)
  {
    SequenceType::Append(theOther->ChangeSequence());
  }

  DEFINE_STANDARD_RTTI_INLINE(NCollection_HSequence, Standard_Transient)
};
