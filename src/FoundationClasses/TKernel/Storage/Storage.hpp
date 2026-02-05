#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class TCollection_AsciiString;

//! Storage package is used to write and read persistent objects.
//! These objects are read and written by a retrieval or storage
//! algorithm (Storage_Schema object) in a container (disk, memory,
//! network ...). Drivers (FSD_File objects) assign a physical
//! container for data to be stored or retrieved.
//! The standard procedure for an application in
//! reading a container is the following:
//! -   open the driver in reading mode,
//! -   call the Read function from the schema,
//! setting the driver as a parameter. This function returns
//! an instance of the Storage_Data class which contains the data being read,
//! -   close the driver.
//! The standard procedure for an application in writing a container is the following:
//! -   open the driver in writing mode,
//! -   create an instance of the Storage_Data class, then
//! add the persistent data to write with the function AddRoot,
//! -   call the function Write from the schema,
//! setting the driver and the Storage_Data instance as parameters,
//! -   close the driver.
class Storage
{
public:
  DEFINE_STANDARD_ALLOC

  //! returns the version of Storage's read/write routines
  Standard_EXPORT static TCollection_AsciiString Version();
};
