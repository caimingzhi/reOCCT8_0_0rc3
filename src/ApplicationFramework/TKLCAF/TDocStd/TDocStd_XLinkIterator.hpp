#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TDocStd_XLinkPtr.hpp>
#include <Standard_Boolean.hpp>
class TDocStd_Document;

class TDocStd_XLinkIterator
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TDocStd_XLinkIterator();

  Standard_EXPORT TDocStd_XLinkIterator(const occ::handle<TDocStd_Document>& D);

  Standard_EXPORT void Initialize(const occ::handle<TDocStd_Document>& D);

  bool More() const;

  Standard_EXPORT void Next();

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
