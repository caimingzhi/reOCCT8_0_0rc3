#include <XmlTObjDrivers_XYZDriver.hpp>

#include <Message_Messenger.hpp>

#include <XmlObjMgt.hpp>
#include <XmlObjMgt_Persistent.hpp>
#include <XmlObjMgt_RRelocationTable.hpp>

#include <TObj_TXYZ.hpp>

IMPLEMENT_STANDARD_RTTIEXT(XmlTObjDrivers_XYZDriver, XmlMDF_ADriver)
IMPLEMENT_DOMSTRING(CoordX, "X")
IMPLEMENT_DOMSTRING(CoordY, "Y")
IMPLEMENT_DOMSTRING(CoordZ, "Z")

//=================================================================================================

XmlTObjDrivers_XYZDriver::XmlTObjDrivers_XYZDriver(
  const occ::handle<Message_Messenger>& theMessageDriver)
    : XmlMDF_ADriver(theMessageDriver, nullptr)
{
}

//=======================================================================
// function : NewEmpty
// purpose  : Creates a new attribute
//=======================================================================

occ::handle<TDF_Attribute> XmlTObjDrivers_XYZDriver::NewEmpty() const
{
  return new TObj_TXYZ;
}

//=======================================================================
// function : Paste
// purpose  : Translate the contents of <aSource> and put it
//           into <aTarget>, using the relocation table
//           <aRelocTable> to keep the sharings.
//=======================================================================

bool XmlTObjDrivers_XYZDriver::Paste(const XmlObjMgt_Persistent&       Source,
                                     const occ::handle<TDF_Attribute>& Target,
                                     XmlObjMgt_RRelocationTable& /*RelocTable*/) const
{
  const XmlObjMgt_Element& anElement = Source;

  // get coordinates
  TCollection_AsciiString CoordX = anElement.getAttribute(::CoordX());
  TCollection_AsciiString CoordY = anElement.getAttribute(::CoordY());
  TCollection_AsciiString CoordZ = anElement.getAttribute(::CoordZ());

  // creating gp_XYZ
  gp_XYZ      aXYZ;
  const char* aStr;
  double      aCoord;

  aStr = CoordX.ToCString();
  if (!XmlObjMgt::GetReal(aStr, aCoord))
    return false;
  aXYZ.SetX(aCoord);

  aStr = CoordY.ToCString();
  if (!XmlObjMgt::GetReal(aStr, aCoord))
    return false;
  aXYZ.SetY(aCoord);

  aStr = CoordZ.ToCString();
  if (!XmlObjMgt::GetReal(aStr, aCoord))
    return false;
  aXYZ.SetZ(aCoord);

  // setting gp_XYZ
  occ::handle<TObj_TXYZ> aTarget = occ::down_cast<TObj_TXYZ>(Target);
  aTarget->Set(aXYZ);

  return true;
}

//=======================================================================
// function : Paste
// purpose  : Translate the contents of <aSource> and put it
//           into <aTarget>, using the relocation table
//           <aRelocTable> to keep the sharings.
//           Store master and referred labels as entry, the other model referred
//           as entry in model-container
//=======================================================================

void XmlTObjDrivers_XYZDriver::Paste(const occ::handle<TDF_Attribute>& Source,
                                     XmlObjMgt_Persistent&             Target,
                                     XmlObjMgt_SRelocationTable& /*RelocTable*/) const
{
  occ::handle<TObj_TXYZ> aSource = occ::down_cast<TObj_TXYZ>(Source);

  if (aSource.IsNull())
    return;

  gp_XYZ aXYZ = aSource->Get();

  TCollection_AsciiString aCoord;

  // coordinate X
  aCoord = TCollection_AsciiString(aXYZ.X());
  Target.Element().setAttribute(::CoordX(), aCoord.ToCString());

  // coordinate Y
  aCoord = TCollection_AsciiString(aXYZ.Y());
  Target.Element().setAttribute(::CoordY(), aCoord.ToCString());

  // coordinate Z
  aCoord = TCollection_AsciiString(aXYZ.Z());
  Target.Element().setAttribute(::CoordZ(), aCoord.ToCString());
}
