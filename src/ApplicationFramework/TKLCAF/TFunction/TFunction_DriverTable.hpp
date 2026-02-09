#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TFunction_Driver.hpp>
#include <Standard_GUID.hpp>
#include <NCollection_DataMap.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Integer.hpp>
#include <Standard_OStream.hpp>
class Standard_GUID;
class TFunction_Driver;

class TFunction_DriverTable : public Standard_Transient
{

public:
  Standard_EXPORT static occ::handle<TFunction_DriverTable> Get();

  Standard_EXPORT TFunction_DriverTable();

  Standard_EXPORT bool AddDriver(const Standard_GUID&                 guid,
                                 const occ::handle<TFunction_Driver>& driver,
                                 const int                            thread = 0);

  Standard_EXPORT bool HasDriver(const Standard_GUID& guid, const int thread = 0) const;

  Standard_EXPORT bool FindDriver(const Standard_GUID&           guid,
                                  occ::handle<TFunction_Driver>& driver,
                                  const int                      thread = 0) const;

  Standard_EXPORT Standard_OStream& Dump(Standard_OStream& anOS) const;

  Standard_OStream& operator<<(Standard_OStream& anOS) const { return Dump(anOS); }

  Standard_EXPORT bool RemoveDriver(const Standard_GUID& guid, const int thread = 0);

  Standard_EXPORT void Clear();

  DEFINE_STANDARD_RTTIEXT(TFunction_DriverTable, Standard_Transient)

private:
  NCollection_DataMap<Standard_GUID, occ::handle<TFunction_Driver>> myDrivers;
  occ::handle<
    NCollection_HArray1<NCollection_DataMap<Standard_GUID, occ::handle<TFunction_Driver>>>>
    myThreadDrivers;
};
