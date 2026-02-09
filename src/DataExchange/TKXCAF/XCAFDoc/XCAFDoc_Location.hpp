#pragma once

#include <Standard.hpp>

#include <TopLoc_Location.hpp>
#include <TDF_Attribute.hpp>
class Standard_GUID;
class TDF_Label;
class TDF_RelocationTable;

class XCAFDoc_Location : public TDF_Attribute
{

public:
  Standard_EXPORT XCAFDoc_Location();

  Standard_EXPORT static const Standard_GUID& GetID();

  Standard_EXPORT static occ::handle<XCAFDoc_Location> Set(const TDF_Label&       label,
                                                           const TopLoc_Location& Loc);

  Standard_EXPORT void Set(const TopLoc_Location& Loc);

  Standard_EXPORT const TopLoc_Location& Get() const;

  Standard_EXPORT const Standard_GUID& ID() const override;

  Standard_EXPORT void Restore(const occ::handle<TDF_Attribute>& With) override;

  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;

  Standard_EXPORT void Paste(const occ::handle<TDF_Attribute>&       Into,
                             const occ::handle<TDF_RelocationTable>& RT) const override;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_STANDARD_RTTIEXT(XCAFDoc_Location, TDF_Attribute)

private:
  TopLoc_Location myLocation;
};
