#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <CDM_Reference.hpp>

#include <NCollection_List.hpp>
#include <Standard_Integer.hpp>
class CDM_Document;

class CDM_ReferenceIterator
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT CDM_ReferenceIterator(const occ::handle<CDM_Document>& aDocument);

  Standard_EXPORT bool More() const;

  Standard_EXPORT void Next();

  Standard_EXPORT occ::handle<CDM_Document> Document() const;

  Standard_EXPORT int ReferenceIdentifier() const;

  Standard_EXPORT int DocumentVersion() const;

private:
  NCollection_List<occ::handle<CDM_Reference>>::Iterator myIterator;
};
