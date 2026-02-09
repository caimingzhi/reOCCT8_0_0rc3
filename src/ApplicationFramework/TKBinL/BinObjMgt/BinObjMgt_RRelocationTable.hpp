#pragma once

#include <Standard_Integer.hpp>
#include <Standard_Transient.hpp>
#include <NCollection_DataMap.hpp>
#include <Storage_HeaderData.hpp>

class BinObjMgt_RRelocationTable : public NCollection_DataMap<int, occ::handle<Standard_Transient>>
{
public:
  Standard_EXPORT const occ::handle<Storage_HeaderData>& GetHeaderData() const;

  Standard_EXPORT void SetHeaderData(const occ::handle<Storage_HeaderData>& theHeaderData);

  Standard_EXPORT void Clear(const bool doReleaseMemory = true);

private:
  occ::handle<Storage_HeaderData> myHeaderData;
};
