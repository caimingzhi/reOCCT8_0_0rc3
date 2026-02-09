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

  Standard_EXPORT CDF_DirectoryIterator();

  Standard_EXPORT CDF_DirectoryIterator(const occ::handle<CDF_Directory>& aDirectory);

  Standard_EXPORT bool MoreDocument();

  Standard_EXPORT void NextDocument();

  Standard_EXPORT occ::handle<CDM_Document> Document();

private:
  NCollection_List<occ::handle<CDM_Document>>::Iterator myIterator;
};
