// Created on: 1999-06-11
// Created by: Vladislav ROMASHKO
// Copyright (c) 1999 Matra Datavision
// Copyright (c) 1999-2014 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.

#ifndef _TFunction_DriverTable_HeaderFile
#define _TFunction_DriverTable_HeaderFile

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

//! A container for instances of drivers.
//! You create a new instance of TFunction_Driver
//! and use the method AddDriver to load it into the driver table.
class TFunction_DriverTable : public Standard_Transient
{

public:
  //! Returns the driver table. If a driver does not exist, creates it.
  Standard_EXPORT static occ::handle<TFunction_DriverTable> Get();

  //! Default constructor
  Standard_EXPORT TFunction_DriverTable();

  //! Returns true if the driver has been added successfully to the driver table.
  Standard_EXPORT bool AddDriver(const Standard_GUID&                 guid,
                                 const occ::handle<TFunction_Driver>& driver,
                                 const int                            thread = 0);

  //! Returns true if the driver exists in the driver table.
  Standard_EXPORT bool HasDriver(const Standard_GUID& guid, const int thread = 0) const;

  //! Returns true if the driver was found.
  Standard_EXPORT bool FindDriver(const Standard_GUID&           guid,
                                  occ::handle<TFunction_Driver>& driver,
                                  const int                      thread = 0) const;

  Standard_EXPORT Standard_OStream& Dump(Standard_OStream& anOS) const;

  Standard_OStream& operator<<(Standard_OStream& anOS) const { return Dump(anOS); }

  //! Removes a driver with the given GUID.
  //! Returns true if the driver has been removed successfully.
  Standard_EXPORT bool RemoveDriver(const Standard_GUID& guid, const int thread = 0);

  //! Removes all drivers. Returns true if the driver has been removed successfully.
  Standard_EXPORT void Clear();

  DEFINE_STANDARD_RTTIEXT(TFunction_DriverTable, Standard_Transient)

private:
  NCollection_DataMap<Standard_GUID, occ::handle<TFunction_Driver>> myDrivers;
  occ::handle<
    NCollection_HArray1<NCollection_DataMap<Standard_GUID, occ::handle<TFunction_Driver>>>>
    myThreadDrivers;
};

#endif // _TFunction_DriverTable_HeaderFile
