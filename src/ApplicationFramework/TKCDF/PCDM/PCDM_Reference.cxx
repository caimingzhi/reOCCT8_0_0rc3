#include <PCDM_Reference.hpp>
#include <TCollection_ExtendedString.hpp>

PCDM_Reference::PCDM_Reference()
    : myReferenceIdentifier(0),
      myDocumentVersion(0)
{
}

PCDM_Reference::PCDM_Reference(const int                         aReferenceIdentifier,
                               const TCollection_ExtendedString& aFileName,
                               const int                         aDocumentVersion)
    : myReferenceIdentifier(aReferenceIdentifier),
      myFileName(aFileName),
      myDocumentVersion(aDocumentVersion)
{
}

int PCDM_Reference::ReferenceIdentifier() const
{
  return myReferenceIdentifier;
}

TCollection_ExtendedString PCDM_Reference::FileName() const
{
  return myFileName;
}

int PCDM_Reference::DocumentVersion() const
{
  return myDocumentVersion;
}
