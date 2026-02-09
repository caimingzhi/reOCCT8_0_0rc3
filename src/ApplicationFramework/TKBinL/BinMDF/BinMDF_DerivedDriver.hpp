#pragma once

#include <BinMDF_ADriver.hpp>

class BinMDF_DerivedDriver : public BinMDF_ADriver
{
  DEFINE_STANDARD_RTTIEXT(BinMDF_DerivedDriver, BinMDF_ADriver)
public:
  BinMDF_DerivedDriver(const occ::handle<TDF_Attribute>&  theDerivative,
                       const occ::handle<BinMDF_ADriver>& theBaseDriver)
      : BinMDF_ADriver(theBaseDriver->MessageDriver()),
        myDerivative(theDerivative),
        myBaseDirver(theBaseDriver)
  {
  }

  occ::handle<TDF_Attribute> NewEmpty() const override { return myDerivative->NewEmpty(); }

  bool Paste(const BinObjMgt_Persistent&       theSource,
             const occ::handle<TDF_Attribute>& theTarget,
             BinObjMgt_RRelocationTable&       theRelocTable) const override
  {
    bool aResult = myBaseDirver->Paste(theSource, theTarget, theRelocTable);

    theTarget->AfterRetrieval();

    return aResult;
  }

  void Paste(const occ::handle<TDF_Attribute>&                        theSource,
             BinObjMgt_Persistent&                                    theTarget,
             NCollection_IndexedMap<occ::handle<Standard_Transient>>& theRelocTable) const override
  {
    myBaseDirver->Paste(theSource, theTarget, theRelocTable);
  }

protected:
  occ::handle<TDF_Attribute>  myDerivative;
  occ::handle<BinMDF_ADriver> myBaseDirver;
};
