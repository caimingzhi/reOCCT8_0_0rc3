#pragma once


#include <XmlMDF_ADriver.hpp>
#include <TDF_DerivedAttribute.hpp>

//! A universal driver for the attribute that inherits another attribute with
//! ready to used persistence mechanism implemented (already has a driver to store/retrieve).
class XmlMDF_DerivedDriver : public XmlMDF_ADriver
{
  DEFINE_STANDARD_RTTIEXT(XmlMDF_DerivedDriver, XmlMDF_ADriver)
public:
  //! Creates a derivative persistence driver for theDerivative attribute by reusage of
  //! theBaseDriver
  //! @param theDerivative an instance of the attribute, just created, detached from any label
  //! @param theBaseDriver a driver of the base attribute, called by Paste methods
  XmlMDF_DerivedDriver(const occ::handle<TDF_Attribute>&  theDerivative,
                       const occ::handle<XmlMDF_ADriver>& theBaseDriver)
      : XmlMDF_ADriver(theBaseDriver->MessageDriver(), theBaseDriver->Namespace().ToCString()),
        myDerivative(theDerivative),
        myBaseDirver(theBaseDriver)
  {
  }

  //! Creates a new instance of the derivative attribute
  occ::handle<TDF_Attribute> NewEmpty() const override { return myDerivative->NewEmpty(); }

  //! Returns the full XML tag name (including NS prefix)
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

  //! Reuses the base driver to read the base fields
  bool Paste(const XmlObjMgt_Persistent&       theSource,
             const occ::handle<TDF_Attribute>& theTarget,
             XmlObjMgt_RRelocationTable&       theRelocTable) const override
  {
    bool aResult = myBaseDirver->Paste(theSource, theTarget, theRelocTable);
    // clang-format off
    theTarget->AfterRetrieval(); // to allow synchronization of the derived attribute with the base content
    // clang-format on
    return aResult;
  }

  //! Reuses the base driver to store the base fields
  void Paste(const occ::handle<TDF_Attribute>& theSource,
             XmlObjMgt_Persistent&             theTarget,
             XmlObjMgt_SRelocationTable&       theRelocTable) const override
  {
    myBaseDirver->Paste(theSource, theTarget, theRelocTable);
  }

protected:
  occ::handle<TDF_Attribute>  myDerivative; //!< the derivative attribute that inherits the base
  occ::handle<XmlMDF_ADriver> myBaseDirver; //!< the base attribute driver to be reused here
};

