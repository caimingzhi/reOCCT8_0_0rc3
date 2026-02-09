#pragma once

#include <XmlMDF_ADriver.hpp>
#include <TDF_DerivedAttribute.hpp>

class XmlMDF_DerivedDriver : public XmlMDF_ADriver
{
  DEFINE_STANDARD_RTTIEXT(XmlMDF_DerivedDriver, XmlMDF_ADriver)
public:
  XmlMDF_DerivedDriver(const occ::handle<TDF_Attribute>&  theDerivative,
                       const occ::handle<XmlMDF_ADriver>& theBaseDriver)
      : XmlMDF_ADriver(theBaseDriver->MessageDriver(), theBaseDriver->Namespace().ToCString()),
        myDerivative(theDerivative),
        myBaseDirver(theBaseDriver)
  {
  }

  occ::handle<TDF_Attribute> NewEmpty() const override { return myDerivative->NewEmpty(); }

  const TCollection_AsciiString& TypeName() const
  {
    const TCollection_AsciiString& aRegistered =
      TDF_DerivedAttribute::TypeName(myDerivative->DynamicType()->Name());
    if (aRegistered.IsEmpty())
    {
      return XmlMDF_ADriver::TypeName();
    }
    return aRegistered;
  }

  bool Paste(const XmlObjMgt_Persistent&       theSource,
             const occ::handle<TDF_Attribute>& theTarget,
             XmlObjMgt_RRelocationTable&       theRelocTable) const override
  {
    bool aResult = myBaseDirver->Paste(theSource, theTarget, theRelocTable);

    theTarget->AfterRetrieval();

    return aResult;
  }

  void Paste(const occ::handle<TDF_Attribute>& theSource,
             XmlObjMgt_Persistent&             theTarget,
             XmlObjMgt_SRelocationTable&       theRelocTable) const override
  {
    myBaseDirver->Paste(theSource, theTarget, theRelocTable);
  }

protected:
  occ::handle<TDF_Attribute>  myDerivative;
  occ::handle<XmlMDF_ADriver> myBaseDirver;
};
