#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_GUID.hpp>
#include <TPrsStd_Driver.hpp>
#include <NCollection_DataMap.hpp>
#include <Standard_Transient.hpp>
class Standard_GUID;
class TPrsStd_Driver;

//! This class is a container to record (AddDriver)
//! binding between GUID and TPrsStd_Driver.
//! You create a new instance of TPrsStd_Driver
//! and use the method AddDriver to load it into the driver table.
class TPrsStd_DriverTable : public Standard_Transient
{

public:
  //! Returns the static table.
  //! If it does not exist, creates it and fills it with standard drivers.
  Standard_EXPORT static occ::handle<TPrsStd_DriverTable> Get();

  //! Default constructor
  Standard_EXPORT TPrsStd_DriverTable();

  //! Fills the table with standard drivers
  Standard_EXPORT void InitStandardDrivers();

  //! Returns true if the driver has been added successfully to the driver table.
  Standard_EXPORT bool AddDriver(const Standard_GUID&               guid,
                                 const occ::handle<TPrsStd_Driver>& driver);

  //! Returns true if the driver was found.
  Standard_EXPORT bool FindDriver(const Standard_GUID&         guid,
                                  occ::handle<TPrsStd_Driver>& driver) const;

  //! Removes a driver with the given GUID.
  //! Returns true if the driver has been removed successfully.
  Standard_EXPORT bool RemoveDriver(const Standard_GUID& guid);

  //! Removes all drivers.
  //! Returns true if the driver has been removed successfully.
  //! If this method is used, the InitStandardDrivers method should be
  //! called to fill the table with standard drivers.
  Standard_EXPORT void Clear();

  DEFINE_STANDARD_RTTIEXT(TPrsStd_DriverTable, Standard_Transient)

private:
  NCollection_DataMap<Standard_GUID, occ::handle<TPrsStd_Driver>> myDrivers;
};

