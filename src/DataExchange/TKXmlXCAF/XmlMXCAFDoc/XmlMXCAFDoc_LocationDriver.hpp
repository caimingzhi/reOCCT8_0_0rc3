#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

class TopTools_LocationSet;
typedef TopTools_LocationSet* TopTools_LocationSetPtr;

#include <XmlMDF_ADriver.hpp>
#include <XmlObjMgt_RRelocationTable.hpp>
#include <XmlObjMgt_SRelocationTable.hpp>
#include <XmlObjMgt_Element.hpp>
class Message_Messenger;
class TDF_Attribute;
class XmlObjMgt_Persistent;
class TopLoc_Location;

//! Attribute Driver.
class XmlMXCAFDoc_LocationDriver : public XmlMDF_ADriver
{

public:
  Standard_EXPORT XmlMXCAFDoc_LocationDriver(
    const occ::handle<Message_Messenger>& theMessageDriver);

  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;

  Standard_EXPORT bool Paste(const XmlObjMgt_Persistent&       Source,
                             const occ::handle<TDF_Attribute>& Target,
                             XmlObjMgt_RRelocationTable&       RelocTable) const override;

  Standard_EXPORT void Paste(const occ::handle<TDF_Attribute>& Source,
                             XmlObjMgt_Persistent&             Target,
                             XmlObjMgt_SRelocationTable&       RelocTable) const override;

  //! Translate a non storable Location to a storable Location.
  Standard_EXPORT void Translate(const TopLoc_Location&      theLoc,
                                 XmlObjMgt_Element&          theParent,
                                 XmlObjMgt_SRelocationTable& theMap) const;

  //! Translate a storable Location to a non storable Location.
  Standard_EXPORT bool Translate(const XmlObjMgt_Element&    theParent,
                                 TopLoc_Location&            theLoc,
                                 XmlObjMgt_RRelocationTable& theMap) const;

  void SetSharedLocations(const TopTools_LocationSetPtr& theLocations);

  DEFINE_STANDARD_RTTIEXT(XmlMXCAFDoc_LocationDriver, XmlMDF_ADriver)

private:
  TopTools_LocationSetPtr myLocations;
};

inline void XmlMXCAFDoc_LocationDriver::SetSharedLocations(
  const TopTools_LocationSetPtr& theLocations)
{
  if (myLocations != theLocations)
  {
    myLocations = theLocations;
  }
}
