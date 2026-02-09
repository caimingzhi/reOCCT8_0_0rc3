#include <BinObjMgt_RRelocationTable.hpp>

const occ::handle<Storage_HeaderData>& BinObjMgt_RRelocationTable::GetHeaderData() const
{
  return myHeaderData;
}

void BinObjMgt_RRelocationTable::SetHeaderData(const occ::handle<Storage_HeaderData>& theHeaderData)
{
  myHeaderData = theHeaderData;
}

void BinObjMgt_RRelocationTable::Clear(const bool doReleaseMemory)
{
  myHeaderData.Nullify();
  NCollection_DataMap<int, occ::handle<Standard_Transient>>::Clear(doReleaseMemory);
}
