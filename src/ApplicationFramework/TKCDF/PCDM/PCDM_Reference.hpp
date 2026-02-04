#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TCollection_ExtendedString.hpp>

class PCDM_Reference
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT PCDM_Reference();

  Standard_EXPORT PCDM_Reference(const int                         aReferenceIdentifier,
                                 const TCollection_ExtendedString& aFileName,
                                 const int                         aDocumentVersion);

  Standard_EXPORT int ReferenceIdentifier() const;

  Standard_EXPORT TCollection_ExtendedString FileName() const;

  Standard_EXPORT int DocumentVersion() const;

private:
  int                        myReferenceIdentifier;
  TCollection_ExtendedString myFileName;
  int                        myDocumentVersion;
};

