#pragma once

#include <Standard_Macro.hpp>
#include <Storage_Error.hpp>
class StdStorage_Data;
class Storage_BaseDriver;
class TCollection_AsciiString;

//! StdStorage package is used to write and read persistent objects.
//! These objects are read and written by a retrieval or storage
//! algorithm (compatible with legacy Storage_Schema) in a container
//! (disk, memory, network ...). Drivers (FSD_File objects) assign a physical
//! container for data to be stored or retrieved.
//! The standard procedure for an application in reading a container is
//!  to call one of the Read functions providing either a file path or a driver
//! opened for reading. Thes function update the instance of the StdStorage_Data
//! class which contains the data being read.
//! The standard procedure for an application in writing a container is the following:
//! -   open the driver in writing mode,
//! -   create an instance of the StdStorage_Data class, then
//! add the persistent data to write with the function AddRoot,
//! -   call the function Write from the storage, setting the driver and the
//! Storage_Data instance as parameters,
//! -   close the driver.
class StdStorage
{

public:
  //! Returns the version of Storage's read/write routines
  Standard_EXPORT static TCollection_AsciiString Version();

  //! Returns the data read from a file located at theFileName.
  //! The storage format is compartible with legacy persistent one.
  //! These data are aggregated in a StdStorage_Data object which may be
  //! browsed in order to extract the root objects from the container.
  //! Note: - theData object will be created if it is null or cleared otherwise.
  Standard_EXPORT static Storage_Error Read(const TCollection_AsciiString& theFileName,
                                            occ::handle<StdStorage_Data>&  theData);

  //! Returns the data read from the container defined by theDriver.
  //! The storage format is compartible with legacy persistent one.
  //! These data are aggregated in a StdStorage_Data object which may be
  //! browsed in order to extract the root objects from the container.
  //! Note: - theData object will be created if it is null or cleared otherwise.
  Standard_EXPORT static Storage_Error Read(const occ::handle<Storage_BaseDriver>& theDriver,
                                            occ::handle<StdStorage_Data>&          theData);

  //! Writes the data aggregated in theData object into the container defined by
  //! theDriver. The storage format is compartible with legacy persistent one.
  //! Note: - theData may aggregate several root objects to be stored together.
  //!       - creation date specified in the storage header will be overwritten.
  Standard_EXPORT static Storage_Error Write(const occ::handle<Storage_BaseDriver>& theDriver,
                                             const occ::handle<StdStorage_Data>&    theData);
};
