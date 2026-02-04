#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <CDM_Document.hpp>

#include <NCollection_List.hpp>
class CDF_Directory;
class CDM_Document;

class CDF_DirectoryIterator
{
public:
  DEFINE_STANDARD_ALLOC

  //! creates an Iterator with the directory
  //! of the current CDF.
  Standard_EXPORT CDF_DirectoryIterator();

  Standard_EXPORT CDF_DirectoryIterator(const occ::handle<CDF_Directory>& aDirectory);

  //! Returns True if there are more entries to return
  Standard_EXPORT bool MoreDocument();

  //! Go to the next entry
  //! (if there is not, Value will raise an exception)
  Standard_EXPORT void NextDocument();

  //! Returns item value of current entry
  Standard_EXPORT occ::handle<CDM_Document> Document();

private:
  NCollection_List<occ::handle<CDM_Document>>::Iterator myIterator;
};

