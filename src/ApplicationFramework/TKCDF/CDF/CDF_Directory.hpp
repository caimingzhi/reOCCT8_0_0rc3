#pragma once


#include <Standard.hpp>

#include <CDM_Document.hpp>
#include <NCollection_List.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Integer.hpp>
class CDM_Document;

//! A directory is a collection of documents. There is only one instance
//! of a given document in a directory.
//! put.
class CDF_Directory : public Standard_Transient
{

public:
  //! Creates an empty directory.
  Standard_EXPORT CDF_Directory();

  //! adds a document into the directory.
  Standard_EXPORT void Add(const occ::handle<CDM_Document>& aDocument);

  //! removes the document.
  Standard_EXPORT void Remove(const occ::handle<CDM_Document>& aDocument);

  //! Returns true if the document aDocument is in the directory
  Standard_EXPORT bool Contains(const occ::handle<CDM_Document>& aDocument) const;

  //! returns the last document (if any) which has been added
  //! in the directory.
  Standard_EXPORT occ::handle<CDM_Document> Last();

  //! returns the number of documents of the directory.
  Standard_EXPORT int Length() const;

  //! returns true if the directory is empty.
  Standard_EXPORT bool IsEmpty() const;

  friend class CDF_DirectoryIterator;

  DEFINE_STANDARD_RTTIEXT(CDF_Directory, Standard_Transient)

private:
  Standard_EXPORT const NCollection_List<occ::handle<CDM_Document>>& List() const;

  NCollection_List<occ::handle<CDM_Document>> myDocuments;
};

