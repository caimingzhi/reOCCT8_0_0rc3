#pragma once


#include <Standard_Integer.hpp>
#include <Standard_Transient.hpp>
#include <NCollection_DataMap.hpp>
#include <Storage_HeaderData.hpp>

//! Retrieval relocation table is modeled as a child class of
//! NCollection_DataMap<int, occ::handle<Standard_Transient>> that stores a handle to the file
//! header section. With that attribute drivers have access to the file header
//! section.
class BinObjMgt_RRelocationTable : public NCollection_DataMap<int, occ::handle<Standard_Transient>>
{
public:
  //! Returns a handle to the header data of the file that is begin read
  Standard_EXPORT const occ::handle<Storage_HeaderData>& GetHeaderData() const;

  //! Sets the storage header data.
  //!
  //! @param theHeaderData header data of the file that is begin read
  Standard_EXPORT void SetHeaderData(const occ::handle<Storage_HeaderData>& theHeaderData);

  Standard_EXPORT void Clear(const bool doReleaseMemory = true);

private:
  occ::handle<Storage_HeaderData> myHeaderData;
};

