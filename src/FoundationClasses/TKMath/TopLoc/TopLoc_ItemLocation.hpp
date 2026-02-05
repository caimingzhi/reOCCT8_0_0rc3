#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <Standard_OStream.hpp>
#include <gp_Trsf.hpp>
class TopLoc_Datum3D;

//! An ItemLocation is an elementary coordinate system
//! in a Location.
//!
//! The ItemLocation contains:
//! * The elementary Datum.
//! * The exponent of the elementary Datum.
//! * The transformation associated to the composition.
class TopLoc_ItemLocation
{
public:
  DEFINE_STANDARD_ALLOC

  //! Sets the elementary Datum to <D>
  //! Sets the exponent to <P>
  Standard_EXPORT TopLoc_ItemLocation(const occ::handle<TopLoc_Datum3D>& D, const int P);

  //! Dumps the content of me into the stream
  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

  friend class TopLoc_Location;
  friend class TopLoc_SListOfItemLocation;

private:
  occ::handle<TopLoc_Datum3D> myDatum;
  int                         myPower;
  gp_Trsf                     myTrsf;
};
