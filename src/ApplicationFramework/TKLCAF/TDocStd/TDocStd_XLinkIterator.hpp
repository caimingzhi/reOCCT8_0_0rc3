#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TDocStd_XLinkPtr.hpp>
#include <Standard_Boolean.hpp>
class TDocStd_Document;

//! Iterates on Reference attributes.
//! This is an iterator giving all the external references
//! of a Document.
class TDocStd_XLinkIterator
{
public:
  DEFINE_STANDARD_ALLOC

  //! Returns an empty iterator;
  Standard_EXPORT TDocStd_XLinkIterator();

  //! Creates an iterator on Reference of <D>.
  Standard_EXPORT TDocStd_XLinkIterator(const occ::handle<TDocStd_Document>& D);

  //! Restarts an iteration with <D>.
  Standard_EXPORT void Initialize(const occ::handle<TDocStd_Document>& D);

  //! Returns True if there is a current Item in the
  //! iteration.
  bool More() const;

  //! Move to the next item; raises if there is no more item.
  Standard_EXPORT void Next();

  //! Returns the current item; a null handle if there is none.
  TDocStd_XLinkPtr Value() const;

private:
  Standard_EXPORT void Init(const occ::handle<TDocStd_Document>& D);

  TDocStd_XLinkPtr myValue;
};

inline bool TDocStd_XLinkIterator::More() const
{
  return (myValue != nullptr);
}

inline TDocStd_XLink* TDocStd_XLinkIterator::Value() const
{
  return myValue;
}
