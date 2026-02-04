#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>
class IFSelect_WorkSession;

//! Gives tools to manage Selecting a group of Entities
//! processed by an Interface, for instance to divide up an
//! original Model (from a File) to several smaller ones
//! They use description of an Interface Model as a graph
//!
//! Remark that this corresponds to the description of a
//! "scenario" of sharing out a File. Parts of this Scenario
//! are intended to be permanently stored. IFSelect provides
//! the Transient, active counterparts (to run the Scenario).
//! But a permanent one (either as Persistent Objects or as
//! interpretable Text) must be provided elsewhere.
class IFSelect
{
public:
  DEFINE_STANDARD_ALLOC

  //! Saves the state of a WorkSession from IFSelect, by using a
  //! SessionFile from IFSelect. Returns True if Done, False in
  //! case of Error on Writing. <file> gives the name of the File
  //! to be produced (this avoids to export the class SessionFile).
  Standard_EXPORT static bool SaveSession(const occ::handle<IFSelect_WorkSession>& WS,
                                          const char*                              file);

  //! Restore the state of a WorkSession from IFSelect, by using a
  //! SessionFile from IFSelect. Returns True if Done, False in
  //! case of Error on Writing. <file> gives the name of the File
  //! to be used (this avoids to export the class SessionFile).
  Standard_EXPORT static bool RestoreSession(const occ::handle<IFSelect_WorkSession>& WS,
                                             const char*                              file);
};

