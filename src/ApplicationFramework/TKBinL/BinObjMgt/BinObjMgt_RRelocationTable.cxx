#include <BinObjMgt_RRelocationTable.hpp>

//=======================================================================
// function : GetHeaderData
// purpose  : getter for the file header data
//=======================================================================

const occ::handle<Storage_HeaderData>& BinObjMgt_RRelocationTable::GetHeaderData() const
{
  return myHeaderData;
}

//=======================================================================
// function : SetHeaderData
// purpose  : setter for the file header data
//=======================================================================

void BinObjMgt_RRelocationTable::SetHeaderData(const occ::handle<Storage_HeaderData>& theHeaderData)
{
  myHeaderData = theHeaderData;
}

//=======================================================================
// function : Clear
// purpose  : The relocation table is cleared before/after reading in a document.
//         : In this case the reference to the file header data should also be
//         : cleared, because it is specific to the document.
//=======================================================================
void BinObjMgt_RRelocationTable::Clear(const bool doReleaseMemory)
{
  myHeaderData.Nullify();
  NCollection_DataMap<int, occ::handle<Standard_Transient>>::Clear(doReleaseMemory);
}
