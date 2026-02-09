#include <XmlObjMgt_RRelocationTable.hpp>

const occ::handle<Storage_HeaderData>& XmlObjMgt_RRelocationTable::GetHeaderData() const
{
  return myHeaderData;
}

void XmlObjMgt_RRelocationTable::SetHeaderData(const occ::handle<Storage_HeaderData>& theHeaderData)
{
  myHeaderData = theHeaderData;
}

void XmlObjMgt_RRelocationTable::Clear(const bool doReleaseMemory)
{
  myHeaderData.Nullify();
  NCollection_DataMap<int, occ::handle<Standard_Transient>>::Clear(doReleaseMemory);
}
