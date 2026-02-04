#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class BinMDF_ADriverTable;
class Message_Messenger;

//! This package provides classes and methods to
//! translate a transient DF into a persistent one and
//! vice versa.
//!
//! Driver
//!
//! A driver is a tool used to translate a transient
//! attribute into a persistent one and vice versa.
//!
//! Driver Table
//!
//! A driver table is an object building links between
//! object types and object drivers. In the
//! translation process, a driver table is asked to
//! give a translation driver for each current object
//! to be translated.
class BinMDF
{
public:
  DEFINE_STANDARD_ALLOC

  //! Adds the attribute storage drivers to <aDriverTable>.
  Standard_EXPORT static void AddDrivers(const occ::handle<BinMDF_ADriverTable>& aDriverTable,
                                         const occ::handle<Message_Messenger>&   aMsgDrv);
};

