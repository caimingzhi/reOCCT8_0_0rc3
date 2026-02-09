#pragma once

#include <Standard_Handle.hpp>
#include <Standard_Transient.hpp>
#include <NCollection_IndexedMap.hpp>
#include <Storage_HeaderData.hpp>

class XmlObjMgt_SRelocationTable : public NCollection_IndexedMap<occ::handle<Standard_Transient>>
{
public:
  Standard_EXPORT const occ::handle<Storage_HeaderData>& GetHeaderData() const;

  Standard_EXPORT void SetHeaderData(const occ::handle<Storage_HeaderData>& theHeaderData);

  Standard_EXPORT void Clear(const bool doReleaseMemory = true);

private:
  occ::handle<Storage_HeaderData> myHeaderData;
};
