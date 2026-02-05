#include <CDF_Directory.hpp>
#include <CDF_DirectoryIterator.hpp>
#include <CDM_Document.hpp>

CDF_DirectoryIterator::CDF_DirectoryIterator(const occ::handle<CDF_Directory>& aDirectory)
    : myIterator(aDirectory->List())
{
}

bool CDF_DirectoryIterator::MoreDocument()
{
  return myIterator.More();
}

void CDF_DirectoryIterator::NextDocument()
{
  myIterator.Next();
}

occ::handle<CDM_Document> CDF_DirectoryIterator::Document()
{

  return myIterator.Value();
}
