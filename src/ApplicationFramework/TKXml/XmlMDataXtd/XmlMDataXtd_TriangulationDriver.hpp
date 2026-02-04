#pragma once


#include <Standard.hpp>

#include <XmlMDF_ADriver.hpp>
#include <XmlObjMgt_RRelocationTable.hpp>
#include <XmlObjMgt_SRelocationTable.hpp>
class Message_Messenger;
class TDF_Attribute;
class XmlObjMgt_Persistent;

//! TDataStd_Mesh attribute XML Driver.
class XmlMDataXtd_TriangulationDriver : public XmlMDF_ADriver
{

public:
  Standard_EXPORT XmlMDataXtd_TriangulationDriver(
    const occ::handle<Message_Messenger>& theMessageDriver);

  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;

  Standard_EXPORT bool Paste(const XmlObjMgt_Persistent&       Source,
                             const occ::handle<TDF_Attribute>& Target,
                             XmlObjMgt_RRelocationTable&       RelocTable) const override;

  Standard_EXPORT void Paste(const occ::handle<TDF_Attribute>& Source,
                             XmlObjMgt_Persistent&             Target,
                             XmlObjMgt_SRelocationTable&       RelocTable) const override;

  DEFINE_STANDARD_RTTIEXT(XmlMDataXtd_TriangulationDriver, XmlMDF_ADriver)

private:
  void GetReal(Standard_IStream& IS, double& theValue) const;
};

