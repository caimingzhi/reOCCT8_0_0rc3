#include <TDocStd_XLinkIterator.hpp>

#include <Standard_NoMoreObject.hpp>
#include <TDocStd_Document.hpp>
#include <TDocStd_XLink.hpp>
#include <TDocStd_XLinkRoot.hpp>

//=================================================================================================

TDocStd_XLinkIterator::TDocStd_XLinkIterator()
    : myValue(nullptr)
{
}

//=================================================================================================

TDocStd_XLinkIterator::TDocStd_XLinkIterator(const occ::handle<TDocStd_Document>& DOC)
    : myValue(nullptr)
{
  Init(DOC);
}

//=================================================================================================

void TDocStd_XLinkIterator::Initialize(const occ::handle<TDocStd_Document>& DOC)
{
  myValue = nullptr;
  Init(DOC);
}

//=================================================================================================

void TDocStd_XLinkIterator::Next()
{
  if (myValue == nullptr)
    throw Standard_NoMoreObject("TDocStd_XLinkIterator::Next() - no more values available");
  else
    myValue = myValue->Next();
}

//=================================================================================================

void TDocStd_XLinkIterator::Init(const occ::handle<TDocStd_Document>& DOC)
{
  occ::handle<TDocStd_XLinkRoot> xRefRoot;
  if (DOC->GetData()->Root().FindAttribute(TDocStd_XLinkRoot::GetID(), xRefRoot))
    myValue = xRefRoot->First();
}
