#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_GUID.hpp>
#include <TPrsStd_Driver.hpp>
#include <NCollection_DataMap.hpp>
#include <Standard_Transient.hpp>
class Standard_GUID;
class TPrsStd_Driver;

class TPrsStd_DriverTable : public Standard_Transient
{

public:
  Standard_EXPORT static occ::handle<TPrsStd_DriverTable> Get();

  Standard_EXPORT TPrsStd_DriverTable();

  Standard_EXPORT void InitStandardDrivers();

  Standard_EXPORT bool AddDriver(const Standard_GUID&               guid,
                                 const occ::handle<TPrsStd_Driver>& driver);

  Standard_EXPORT bool FindDriver(const Standard_GUID&         guid,
                                  occ::handle<TPrsStd_Driver>& driver) const;

  Standard_EXPORT bool RemoveDriver(const Standard_GUID& guid);

  Standard_EXPORT void Clear();

  DEFINE_STANDARD_RTTIEXT(TPrsStd_DriverTable, Standard_Transient)

private:
  NCollection_DataMap<Standard_GUID, occ::handle<TPrsStd_Driver>> myDrivers;
};
