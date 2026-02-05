#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>
class Standard_GUID;
class TCollection_ExtendedString;

//! This package provides data framework for binding
//! features and data structures.
//!
//! The feature structure is a tree used to bind
//! semantic information about each feature together.
//!
//! The only one concrete attribute defined in this
//! package is the TagSource attribute.This attribute
//! is used for random creation of child labels under
//! a given label. Tags are randomly delivered.
class TDF
{
public:
  DEFINE_STANDARD_ALLOC

  //! Returns ID "00000000-0000-0000-0000-000000000000",
  //! sometimes used as null ID.
  Standard_EXPORT static const Standard_GUID& LowestID();

  //! Returns ID "ffffffff-ffff-ffff-ffff-ffffffffffff".
  Standard_EXPORT static const Standard_GUID& UppestID();

  //! Sets link between GUID and ProgID in hidden DataMap
  Standard_EXPORT static void AddLinkGUIDToProgID(const Standard_GUID&              ID,
                                                  const TCollection_ExtendedString& ProgID);

  //! Returns True if there is GUID for given <ProgID> then GUID is returned in <ID>
  Standard_EXPORT static bool GUIDFromProgID(const TCollection_ExtendedString& ProgID,
                                             Standard_GUID&                    ID);

  //! Returns True if there is ProgID for given <ID> then ProgID is returned in <ProgID>
  Standard_EXPORT static bool ProgIDFromGUID(const Standard_GUID&        ID,
                                             TCollection_ExtendedString& ProgID);
};
