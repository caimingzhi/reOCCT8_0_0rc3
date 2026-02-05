#pragma once

#include <NCollection_Sequence.hpp>
#include <Standard_Type.hpp>
#include <Standard_Transient.hpp>

//! Template class for Handle-managed sequences.
//! Inherits from both NCollection_Sequence<TheItemType> and Standard_Transient,
//! providing reference-counted sequence functionality.
template <typename TheItemType>
class NCollection_HSequence : public NCollection_Sequence<TheItemType>, public Standard_Transient
{
public:
  DEFINE_STANDARD_ALLOC
  DEFINE_NCOLLECTION_ALLOC

  typedef NCollection_Sequence<TheItemType> SequenceType;
  typedef TheItemType                       value_type;

public:
  //! Default constructor.
  NCollection_HSequence() = default;

  //! Copy constructor from sequence.
  //! @param theOther the sequence to copy from
  NCollection_HSequence(const SequenceType& theOther)
      : SequenceType(theOther)
  {
  }

  //! Returns const reference to the underlying sequence.
  const SequenceType& Sequence() const noexcept { return *this; }

  //! Returns mutable reference to the underlying sequence.
  SequenceType& ChangeSequence() noexcept { return *this; }

  //! Append single item.
  //! @param theItem the item to append
  void Append(const TheItemType& theItem) { SequenceType::Append(theItem); }

  //! Append another sequence.
  //! @param theSequence the sequence to append
  void Append(SequenceType& theSequence) { SequenceType::Append(theSequence); }

  //! Append items from another HSequence.
  //! @param theOther handle to another HSequence
  template <class T>
  void Append(
    const opencascade::handle<T>& theOther,
    typename std::enable_if<std::is_base_of<NCollection_HSequence, T>::value>::type* = nullptr)
  {
    SequenceType::Append(theOther->ChangeSequence());
  }

  DEFINE_STANDARD_RTTI_INLINE(NCollection_HSequence, Standard_Transient)
};
