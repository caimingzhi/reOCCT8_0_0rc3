#include <XmlObjMgt_SRelocationTable.hpp>

//=======================================================================
// function : GetHeaderData
// purpose  : getter for the file header data
//=======================================================================

const occ::handle<Storage_HeaderData>& XmlObjMgt_SRelocationTable::GetHeaderData() const
{
  return myHeaderData;
}

//=======================================================================
// function : SetHeaderData
// purpose  : setter for the file header data
//=======================================================================

void XmlObjMgt_SRelocationTable::SetHeaderData(const occ::handle<Storage_HeaderData>& theHeaderData)
{
  myHeaderData = theHeaderData;
}

//=======================================================================
// function : Clear
// purpose  : The relocation table is cleared before/after reading in a document.
//         : In this case the reference to the file header data should also be
//         : cleared, because it is specific to the document.
//=======================================================================
void XmlObjMgt_SRelocationTable::Clear(const bool doReleaseMemory)
{
  myHeaderData.Nullify();
  NCollection_IndexedMap<occ::handle<Standard_Transient>>::Clear(doReleaseMemory);
}
