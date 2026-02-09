#pragma once

#include <Standard.hpp>

#include <CDM_Document.hpp>
#include <NCollection_List.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Integer.hpp>
class CDM_Document;

class CDF_Directory : public Standard_Transient
{

public:
  Standard_EXPORT CDF_Directory();

  Standard_EXPORT void Add(const occ::handle<CDM_Document>& aDocument);

  Standard_EXPORT void Remove(const occ::handle<CDM_Document>& aDocument);

  Standard_EXPORT bool Contains(const occ::handle<CDM_Document>& aDocument) const;

  Standard_EXPORT occ::handle<CDM_Document> Last();

  Standard_EXPORT int Length() const;

  Standard_EXPORT bool IsEmpty() const;

  friend class CDF_DirectoryIterator;

  DEFINE_STANDARD_RTTIEXT(CDF_Directory, Standard_Transient)

private:
  Standard_EXPORT const NCollection_List<occ::handle<CDM_Document>>& List() const;

  NCollection_List<occ::handle<CDM_Document>> myDocuments;
};
