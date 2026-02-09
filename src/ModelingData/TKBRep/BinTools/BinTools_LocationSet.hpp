#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <TopLoc_Location.hpp>
#include <NCollection_IndexedMap.hpp>
#include <Standard_Integer.hpp>
#include <Standard_OStream.hpp>
#include <Standard_IStream.hpp>
class TopLoc_Location;

Standard_OStream& operator<<(Standard_OStream& OS, const gp_Trsf& T);

class BinTools_LocationSet
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BinTools_LocationSet();

  Standard_EXPORT void Clear();

  Standard_EXPORT int Add(const TopLoc_Location& L);

  Standard_EXPORT const TopLoc_Location& Location(const int I) const;

  Standard_EXPORT int Index(const TopLoc_Location& L) const;

  Standard_EXPORT int NbLocations() const;

  Standard_EXPORT void Write(Standard_OStream& OS) const;

  Standard_EXPORT void Read(Standard_IStream& IS);

private:
  NCollection_IndexedMap<TopLoc_Location> myMap;
};
