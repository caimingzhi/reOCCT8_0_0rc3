#pragma once


#include <Standard.hpp>

#include <TopLoc_Location.hpp>
#include <TDF_Attribute.hpp>
class Standard_GUID;
class TDF_Label;
class TDF_RelocationTable;

//! attribute to store TopLoc_Location
class XCAFDoc_Location : public TDF_Attribute
{

public:
  //! class methods
  //! =============
  Standard_EXPORT XCAFDoc_Location();

  Standard_EXPORT static const Standard_GUID& GetID();

  //! Find, or create, a Location attribute and set it's value
  //! the Location attribute is returned.
  //! Location methods
  //! ===============
  Standard_EXPORT static occ::handle<XCAFDoc_Location> Set(const TDF_Label&       label,
                                                           const TopLoc_Location& Loc);

  Standard_EXPORT void Set(const TopLoc_Location& Loc);

  //! Returns True if there is a reference on the same label
  Standard_EXPORT const TopLoc_Location& Get() const;

  Standard_EXPORT const Standard_GUID& ID() const override;

  Standard_EXPORT void Restore(const occ::handle<TDF_Attribute>& With) override;

  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;

  Standard_EXPORT void Paste(const occ::handle<TDF_Attribute>&       Into,
                             const occ::handle<TDF_RelocationTable>& RT) const override;

  //! Dumps the content of me into the stream
  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_STANDARD_RTTIEXT(XCAFDoc_Location, TDF_Attribute)

private:
  TopLoc_Location myLocation;
};

