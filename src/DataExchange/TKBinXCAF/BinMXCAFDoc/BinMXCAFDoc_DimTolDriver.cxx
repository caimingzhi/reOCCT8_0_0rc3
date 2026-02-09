#include <BinMXCAFDoc_DimTolDriver.hpp>
#include <BinObjMgt_Persistent.hpp>
#include <Message_Messenger.hpp>
#include <Standard_Type.hpp>
#include <TCollection_HAsciiString.hpp>
#include <TDF_Attribute.hpp>
#include <XCAFDoc_DimTol.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BinMXCAFDoc_DimTolDriver, BinMDF_ADriver)

BinMXCAFDoc_DimTolDriver::BinMXCAFDoc_DimTolDriver(
  const occ::handle<Message_Messenger>& theMsgDriver)
    : BinMDF_ADriver(theMsgDriver, STANDARD_TYPE(XCAFDoc_DimTol)->Name())
{
}

occ::handle<TDF_Attribute> BinMXCAFDoc_DimTolDriver::NewEmpty() const
{
  return new XCAFDoc_DimTol();
}

bool BinMXCAFDoc_DimTolDriver::Paste(const BinObjMgt_Persistent&       theSource,
                                     const occ::handle<TDF_Attribute>& theTarget,
                                     BinObjMgt_RRelocationTable&) const
{
  occ::handle<XCAFDoc_DimTol> anAtt = occ::down_cast<XCAFDoc_DimTol>(theTarget);
  int                         aKind, aFirstInd, aLastInd;
  TCollection_AsciiString     aName, aDescr;
  if (!(theSource >> aKind >> aName >> aDescr >> aFirstInd >> aLastInd))
    return false;

  occ::handle<NCollection_HArray1<double>> aHArr;
  const int                                aLength = aLastInd - aFirstInd + 1;
  if (aLength > 0)
  {
    aHArr = new NCollection_HArray1<double>(aFirstInd, aLastInd);

    NCollection_Array1<double>& aTargetArray = aHArr->ChangeArray1();
    if (!theSource.GetRealArray(&aTargetArray(aFirstInd), aLength))
      return false;
  }
  anAtt->Set(aKind,
             aHArr,
             new TCollection_HAsciiString(aName),
             new TCollection_HAsciiString(aDescr));
  return true;
}

void BinMXCAFDoc_DimTolDriver::Paste(const occ::handle<TDF_Attribute>& theSource,
                                     BinObjMgt_Persistent&             theTarget,
                                     NCollection_IndexedMap<occ::handle<Standard_Transient>>&) const
{
  occ::handle<XCAFDoc_DimTol> anAtt = occ::down_cast<XCAFDoc_DimTol>(theSource);
  theTarget << anAtt->GetKind();
  if (!anAtt->GetName().IsNull())
    theTarget << anAtt->GetName()->String();
  else
    theTarget << TCollection_AsciiString("");
  if (!anAtt->GetDescription().IsNull())
    theTarget << anAtt->GetDescription()->String();
  else
    theTarget << TCollection_AsciiString("");

  occ::handle<NCollection_HArray1<double>> aHArr     = anAtt->GetVal();
  int                                      aFirstInd = 1, aLastInd = 0;
  if (!aHArr.IsNull())
  {
    aFirstInd = aHArr->Lower();
    aLastInd  = aHArr->Upper();
  }
  theTarget << aFirstInd << aLastInd;
  if (!aHArr.IsNull())
  {
    const int                         aLength = aLastInd - aFirstInd + 1;
    const NCollection_Array1<double>& anArr   = aHArr->Array1();
    double*                           aPtr    = (double*)&anArr(aFirstInd);
    theTarget.PutRealArray(aPtr, aLength);
  }
}
