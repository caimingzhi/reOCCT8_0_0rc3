#include <XmlObjMgt_SRelocationTable.hpp>

const occ::handle<Storage_HeaderData>& XmlObjMgt_SRelocationTable::GetHeaderData() const
{
  return myHeaderData;
}

void XmlObjMgt_SRelocationTable::SetHeaderData(const occ::handle<Storage_HeaderData>& theHeaderData)
{
  myHeaderData = theHeaderData;
}

void XmlObjMgt_SRelocationTable::Clear(const bool doReleaseMemory)
{
  myHeaderData.Nullify();
  NCollection_IndexedMap<occ::handle<Standard_Transient>>::Clear(doReleaseMemory);
}
