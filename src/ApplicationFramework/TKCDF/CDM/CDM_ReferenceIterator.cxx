#include <CDM_Document.hpp>
#include <CDM_Reference.hpp>
#include <CDM_ReferenceIterator.hpp>

CDM_ReferenceIterator::CDM_ReferenceIterator(const occ::handle<CDM_Document>& aDocument)
    : myIterator(aDocument->myToReferences)
{
}

bool CDM_ReferenceIterator::More() const
{
  return myIterator.More();
}

void CDM_ReferenceIterator::Next()
{
  myIterator.Next();
}

int CDM_ReferenceIterator::ReferenceIdentifier() const
{
  return myIterator.Value()->ReferenceIdentifier();
}

occ::handle<CDM_Document> CDM_ReferenceIterator::Document() const
{
  return myIterator.Value()->ToDocument();
}

int CDM_ReferenceIterator::DocumentVersion() const
{
  return myIterator.Value()->DocumentVersion();
}
