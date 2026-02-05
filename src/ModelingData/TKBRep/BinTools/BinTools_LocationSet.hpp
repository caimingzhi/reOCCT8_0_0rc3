#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <TopLoc_Location.hpp>
#include <NCollection_IndexedMap.hpp>
#include <Standard_Integer.hpp>
#include <Standard_OStream.hpp>
#include <Standard_IStream.hpp>
class TopLoc_Location;

//! Operator for writing transformation into the stream
Standard_OStream& operator<<(Standard_OStream& OS, const gp_Trsf& T);

//! The class LocationSet stores a set of location in
//! a relocatable state.
//!
//! It can be created from Locations.
//!
//! It can create Locations.
class BinTools_LocationSet
{
public:
  DEFINE_STANDARD_ALLOC

  //! Returns an empty set of locations.
  Standard_EXPORT BinTools_LocationSet();

  //! Clears the content of the set.
  Standard_EXPORT void Clear();

  //! Incorporate a new Location in the set and returns
  //! its index.
  Standard_EXPORT int Add(const TopLoc_Location& L);

  //! Returns the location of index <I>.
  Standard_EXPORT const TopLoc_Location& Location(const int I) const;

  //! Returns the index of <L>.
  Standard_EXPORT int Index(const TopLoc_Location& L) const;

  //! Returns number of locations.
  Standard_EXPORT int NbLocations() const;

  //! Writes the content of me on the stream <OS> in a
  //! format that can be read back by Read.
  Standard_EXPORT void Write(Standard_OStream& OS) const;

  //! Reads the content of me from the stream <IS>. me
  //! is first cleared.
  Standard_EXPORT void Read(Standard_IStream& IS);

private:
  NCollection_IndexedMap<TopLoc_Location> myMap;
};
