#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopLoc_SListOfItemLocation.hpp>
#include <Standard_Integer.hpp>
#include <Standard_OStream.hpp>

class gp_Trsf;
class TopLoc_Datum3D;

//! A Location is a composite transition. It comprises a
//! series of elementary reference coordinates, i.e.
//! objects of type TopLoc_Datum3D, and the powers to
//! which these objects are raised.
class TopLoc_Location
{
public:
  DEFINE_STANDARD_ALLOC

  //! Constructs an empty local coordinate system object.
  //! Note: A Location constructed from a default datum is said to be "empty".
  Standard_EXPORT TopLoc_Location();

  //! Constructs the local coordinate system object defined
  //! by the transformation T. T invokes in turn, a TopLoc_Datum3D object.
  Standard_EXPORT TopLoc_Location(const gp_Trsf& T);

  //! Constructs the local coordinate system object defined by the 3D datum D.
  //! Exceptions
  //! Standard_ConstructionError if the transformation
  //! T does not represent a 3D coordinate system.
  Standard_EXPORT TopLoc_Location(const occ::handle<TopLoc_Datum3D>& D);

  //! Returns true if this location is equal to the Identity transformation.
  bool IsIdentity() const;

  //! Resets this location to the Identity transformation.
  void Identity();

  //! Returns the first elementary datum of the
  //! Location. Use the NextLocation function recursively to access
  //! the other data comprising this location.
  //! Exceptions
  //! Standard_NoSuchObject if this location is empty.
  const occ::handle<TopLoc_Datum3D>& FirstDatum() const;

  //! Returns the power elevation of the first
  //! elementary datum.
  //! Exceptions
  //! Standard_NoSuchObject if this location is empty.
  int FirstPower() const;

  //! Returns a Location representing <me> without the
  //! first datum. We have the relation:
  //!
  //! <me> = NextLocation() * FirstDatum() ^ FirstPower()
  //! Exceptions
  //! Standard_NoSuchObject if this location is empty.
  const TopLoc_Location& NextLocation() const;

  //! Returns the transformation associated to the
  //! coordinate system.
  Standard_EXPORT const gp_Trsf& Transformation() const;
  Standard_EXPORT                operator gp_Trsf() const;

  //! Returns the inverse of <me>.
  //!
  //! <me> * Inverted() is an Identity.
  [[nodiscard]] Standard_EXPORT TopLoc_Location Inverted() const;

  //! Returns <me> * <Other>, the elementary datums are
  //! concatenated.
  [[nodiscard]] Standard_EXPORT TopLoc_Location Multiplied(const TopLoc_Location& Other) const;

  [[nodiscard]] TopLoc_Location operator*(const TopLoc_Location& Other) const
  {
    return Multiplied(Other);
  }

  //! Returns <me> / <Other>.
  [[nodiscard]] Standard_EXPORT TopLoc_Location Divided(const TopLoc_Location& Other) const;

  [[nodiscard]] TopLoc_Location operator/(const TopLoc_Location& Other) const
  {
    return Divided(Other);
  }

  //! Returns <Other>.Inverted() * <me>.
  [[nodiscard]] Standard_EXPORT TopLoc_Location Predivided(const TopLoc_Location& Other) const;

  //! Returns me at the power <pwr>. If <pwr> is zero
  //! returns Identity. <pwr> can be lower than zero
  //! (usual meaning for powers).
  [[nodiscard]] Standard_EXPORT TopLoc_Location Powered(const int pwr) const;

  //! Returns a hashed value for this local coordinate system. This value is used, with map tables,
  //! to store and retrieve the object easily
  //! @return a computed hash code
  size_t HashCode() const;

  //! Returns true if this location and the location Other
  //! have the same elementary data, i.e. contain the same
  //! series of TopLoc_Datum3D and respective powers.
  //! This method is an alias for operator ==.
  Standard_EXPORT bool IsEqual(const TopLoc_Location& Other) const;

  bool operator==(const TopLoc_Location& Other) const { return IsEqual(Other); }

  //! Returns true if this location and the location Other do
  //! not have the same elementary data, i.e. do not
  //! contain the same series of TopLoc_Datum3D and respective powers.
  //! This method is an alias for operator !=.
  Standard_EXPORT bool IsDifferent(const TopLoc_Location& Other) const;

  bool operator!=(const TopLoc_Location& Other) const { return IsDifferent(Other); }

  //! Dumps the content of me into the stream
  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

  //! Prints the contents of <me> on the stream <s>.
  Standard_EXPORT void ShallowDump(Standard_OStream& S) const;

  //! Clear myItems
  void Clear() { myItems.Clear(); }

  static double ScalePrec() { return 1.e-14; }

private:
  TopLoc_SListOfItemLocation myItems;
};

#include <Standard_HashUtils.hpp>
#include <TopLoc_SListOfItemLocation.hpp>
#include <TopLoc_Datum3D.hpp>
#include <TopLoc_ItemLocation.hpp>

//=================================================================================================

inline bool TopLoc_Location::IsIdentity() const
{
  return myItems.IsEmpty();
}

//=================================================================================================

inline void TopLoc_Location::Identity()
{
  myItems.Clear();
}

//=================================================================================================

inline const occ::handle<TopLoc_Datum3D>& TopLoc_Location::FirstDatum() const
{
  return myItems.Value().myDatum;
}

//=================================================================================================

inline int TopLoc_Location::FirstPower() const
{
  return myItems.Value().myPower;
}

//=================================================================================================

inline const TopLoc_Location& TopLoc_Location::NextLocation() const
{
  return (*(TopLoc_Location*)&(myItems.Tail()));
}

//=================================================================================================

inline size_t TopLoc_Location::HashCode() const
{
  // Hashing base on IsEqual function
  if (myItems.IsEmpty())
  {
    return 0;
  }
  size_t                     aHash = opencascade::MurmurHash::optimalSeed<size_t>();
  TopLoc_SListOfItemLocation items = myItems;
  size_t                     aCombined[3];
  while (items.More())
  {
    aCombined[0] = std::hash<occ::handle<TopLoc_Datum3D>>{}(items.Value().myDatum);
    aCombined[1] = opencascade::hash(items.Value().myPower);
    aCombined[2] = aHash;
    aHash        = opencascade::hashBytes(aCombined, sizeof(aCombined));
    items.Next();
  }
  return aHash;
}

//=================================================================================================

inline void ShallowDump(const TopLoc_Location& me, Standard_OStream& S)
{
  me.ShallowDump(S);
}

namespace std
{
  template <>
  struct hash<TopLoc_Location>
  {
    size_t operator()(const TopLoc_Location& theLocation) const { return theLocation.HashCode(); }
  };
} // namespace std
