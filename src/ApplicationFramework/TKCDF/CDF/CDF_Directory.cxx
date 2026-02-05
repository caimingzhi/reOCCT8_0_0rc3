#include <CDF_Directory.hpp>
#include <CDF_DirectoryIterator.hpp>
#include <CDM_Document.hpp>
#include <NCollection_List.hpp>
#include <Standard_NoSuchObject.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(CDF_Directory, Standard_Transient)

CDF_Directory::CDF_Directory() = default;

void CDF_Directory::Add(const occ::handle<CDM_Document>& aDocument)
{
  if (!Contains(aDocument))
    myDocuments.Append(aDocument);
}

void CDF_Directory::Remove(const occ::handle<CDM_Document>& aDocument)
{
  for (NCollection_List<occ::handle<CDM_Document>>::Iterator it(myDocuments); it.More(); it.Next())
  {
    if (aDocument == it.Value())
    {
      myDocuments.Remove(it);
      break;
    }
  }
}

bool CDF_Directory::Contains(const occ::handle<CDM_Document>& aDocument) const
{
  for (NCollection_List<occ::handle<CDM_Document>>::Iterator it(myDocuments); it.More(); it.Next())
  {
    if (aDocument == it.Value())
      return true;
  }
  return false;
}

int CDF_Directory::Length() const
{
  return myDocuments.Extent();
}

const NCollection_List<occ::handle<CDM_Document>>& CDF_Directory::List() const
{

  return myDocuments;
}

bool CDF_Directory::IsEmpty() const
{
  return myDocuments.IsEmpty();
}

occ::handle<CDM_Document> CDF_Directory::Last()
{
  Standard_NoSuchObject_Raise_if(
    IsEmpty(),
    "CDF_Directory::Last: the directory does not contain any document");
  return myDocuments.Last();
}
