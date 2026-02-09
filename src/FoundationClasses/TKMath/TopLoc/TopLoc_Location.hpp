#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopLoc_SListOfItemLocation.hpp>
#include <Standard_Integer.hpp>
#include <Standard_OStream.hpp>

class gp_Trsf;
class TopLoc_Datum3D;

class TopLoc_Location
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopLoc_Location();

  Standard_EXPORT TopLoc_Location(const gp_Trsf& T);

  Standard_EXPORT TopLoc_Location(const occ::handle<TopLoc_Datum3D>& D);

  bool IsIdentity() const;

  void Identity();

  const occ::handle<TopLoc_Datum3D>& FirstDatum() const;

  int FirstPower() const;

  const TopLoc_Location& NextLocation() const;

  Standard_EXPORT const gp_Trsf& Transformation() const;
  Standard_EXPORT                operator gp_Trsf() const;

  [[nodiscard]] Standard_EXPORT TopLoc_Location Inverted() const;

  [[nodiscard]] Standard_EXPORT TopLoc_Location Multiplied(const TopLoc_Location& Other) const;

  [[nodiscard]] TopLoc_Location operator*(const TopLoc_Location& Other) const
  {
    return Multiplied(Other);
  }

  [[nodiscard]] Standard_EXPORT TopLoc_Location Divided(const TopLoc_Location& Other) const;

  [[nodiscard]] TopLoc_Location operator/(const TopLoc_Location& Other) const
  {
    return Divided(Other);
  }

  [[nodiscard]] Standard_EXPORT TopLoc_Location Predivided(const TopLoc_Location& Other) const;

  [[nodiscard]] Standard_EXPORT TopLoc_Location Powered(const int pwr) const;

  size_t HashCode() const;

  Standard_EXPORT bool IsEqual(const TopLoc_Location& Other) const;

  bool operator==(const TopLoc_Location& Other) const { return IsEqual(Other); }

  Standard_EXPORT bool IsDifferent(const TopLoc_Location& Other) const;

  bool operator!=(const TopLoc_Location& Other) const { return IsDifferent(Other); }

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

  Standard_EXPORT void ShallowDump(Standard_OStream& S) const;

  void Clear() { myItems.Clear(); }

  static double ScalePrec() { return 1.e-14; }

private:
  TopLoc_SListOfItemLocation myItems;
};

#include <Standard_HashUtils.hpp>
#include <TopLoc_SListOfItemLocation.hpp>
#include <TopLoc_Datum3D.hpp>
#include <TopLoc_ItemLocation.hpp>

inline bool TopLoc_Location::IsIdentity() const
{
  return myItems.IsEmpty();
}

inline void TopLoc_Location::Identity()
{
  myItems.Clear();
}

inline const occ::handle<TopLoc_Datum3D>& TopLoc_Location::FirstDatum() const
{
  return myItems.Value().myDatum;
}

inline int TopLoc_Location::FirstPower() const
{
  return myItems.Value().myPower;
}

inline const TopLoc_Location& TopLoc_Location::NextLocation() const
{
  return (*(TopLoc_Location*)&(myItems.Tail()));
}

inline size_t TopLoc_Location::HashCode() const
{

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
