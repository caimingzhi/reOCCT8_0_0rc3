#include <BinMDataXtd_PatternStdDriver.hpp>
#include <BinObjMgt_Persistent.hpp>
#include <Message_Messenger.hpp>
#include <Standard_Type.hpp>
#include <TDataStd_Integer.hpp>
#include <TDataStd_Real.hpp>
#include <TDataXtd_PatternStd.hpp>
#include <TDF_Attribute.hpp>
#include <TNaming_NamedShape.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BinMDataXtd_PatternStdDriver, BinMDF_ADriver)

BinMDataXtd_PatternStdDriver::BinMDataXtd_PatternStdDriver(
  const occ::handle<Message_Messenger>& theMsgDriver)
    : BinMDF_ADriver(theMsgDriver, nullptr)
{
}

occ::handle<TDF_Attribute> BinMDataXtd_PatternStdDriver::NewEmpty() const
{
  return (new TDataXtd_PatternStd());
}

bool BinMDataXtd_PatternStdDriver::Paste(const BinObjMgt_Persistent&       theSource,
                                         const occ::handle<TDF_Attribute>& theTarget,
                                         BinObjMgt_RRelocationTable&       theRelocTable) const
{
  occ::handle<TDataXtd_PatternStd> aP = occ::down_cast<TDataXtd_PatternStd>(theTarget);

  int signature;
  if (!(theSource >> signature))
    return false;
  if (signature == 0)
    return true;
  aP->Signature(signature);

  int revFlags;
  if (!(theSource >> revFlags))
    return false;
  aP->Axis1Reversed((revFlags & 1) != 0);
  aP->Axis2Reversed((revFlags & 2) != 0);

  occ::handle<TNaming_NamedShape> TNS;
  int                             aNb;

  if (signature == 5)
  {
    if (!(theSource >> aNb))
      return false;
    if (theRelocTable.IsBound(aNb))
      TNS = occ::down_cast<TNaming_NamedShape>(theRelocTable.Find(aNb));
    else
    {
      TNS = new TNaming_NamedShape;
      theRelocTable.Bind(aNb, TNS);
    }
    aP->Mirror(TNS);
  }
  else
  {
    occ::handle<TDataStd_Real>    TReal;
    occ::handle<TDataStd_Integer> TInt;

    if (!(theSource >> aNb))
      return false;
    if (theRelocTable.IsBound(aNb))
      TNS = occ::down_cast<TNaming_NamedShape>(theRelocTable.Find(aNb));
    else
    {
      TNS = new TNaming_NamedShape;
      theRelocTable.Bind(aNb, TNS);
    }
    aP->Axis1(TNS);

    if (!(theSource >> aNb))
      return false;
    if (theRelocTable.IsBound(aNb))
      TReal = occ::down_cast<TDataStd_Real>(theRelocTable.Find(aNb));
    else
    {
      TReal = new TDataStd_Real;
      theRelocTable.Bind(aNb, TReal);
    }
    aP->Value1(TReal);

    if (!(theSource >> aNb))
      return false;
    if (theRelocTable.IsBound(aNb))
      TInt = occ::down_cast<TDataStd_Integer>(theRelocTable.Find(aNb));
    else
    {
      TInt = new TDataStd_Integer;
      theRelocTable.Bind(aNb, TInt);
    }
    aP->NbInstances1(TInt);

    if (signature > 2)
    {

      if (!(theSource >> aNb))
        return false;
      if (theRelocTable.IsBound(aNb))
        TNS = occ::down_cast<TNaming_NamedShape>(theRelocTable.Find(aNb));
      else
      {
        TNS = new TNaming_NamedShape;
        theRelocTable.Bind(aNb, TNS);
      }
      aP->Axis2(TNS);

      if (!(theSource >> aNb))
        return false;
      if (theRelocTable.IsBound(aNb))
        TReal = occ::down_cast<TDataStd_Real>(theRelocTable.Find(aNb));
      else
      {
        TReal = new TDataStd_Real;
        theRelocTable.Bind(aNb, TReal);
      }
      aP->Value2(TReal);

      if (!(theSource >> aNb))
        return false;
      if (theRelocTable.IsBound(aNb))
        TInt = occ::down_cast<TDataStd_Integer>(theRelocTable.Find(aNb));
      else
      {
        TInt = new TDataStd_Integer;
        theRelocTable.Bind(aNb, TInt);
      }
      aP->NbInstances2(TInt);
    }
  }

  return true;
}

void BinMDataXtd_PatternStdDriver::Paste(
  const occ::handle<TDF_Attribute>&                        theSource,
  BinObjMgt_Persistent&                                    theTarget,
  NCollection_IndexedMap<occ::handle<Standard_Transient>>& theRelocTable) const
{
  occ::handle<TDataXtd_PatternStd> aP = occ::down_cast<TDataXtd_PatternStd>(theSource);

  int signature = aP->Signature();
  if (signature < 1 || signature > 5)
    signature = 0;
  theTarget << signature;
  if (signature == 0)
    return;

  int revFlags = 0;
  if (aP->Axis1Reversed())
    revFlags |= 1;
  if (aP->Axis2Reversed())
    revFlags |= 2;
  theTarget << revFlags;

  int aNb;
  if (signature == 5)
  {
    occ::handle<TNaming_NamedShape> Plane = aP->Mirror();
    aNb                                   = theRelocTable.Add(Plane);
    theTarget << aNb;
  }
  else
  {

    occ::handle<TNaming_NamedShape> Axis = aP->Axis1();
    aNb                                  = theRelocTable.Add(Axis);
    theTarget << aNb;

    occ::handle<TDataStd_Real> Value = aP->Value1();
    aNb                              = theRelocTable.Add(Value);
    theTarget << aNb;

    occ::handle<TDataStd_Integer> NbInstances = aP->NbInstances1();
    aNb                                       = theRelocTable.Add(NbInstances);
    theTarget << aNb;

    if (signature > 2)
    {

      Axis = aP->Axis2();
      aNb  = theRelocTable.Add(Axis);
      theTarget << aNb;

      Value = aP->Value2();
      aNb   = theRelocTable.Add(Value);
      theTarget << aNb;

      NbInstances = aP->NbInstances2();
      aNb         = theRelocTable.Add(NbInstances);
      theTarget << aNb;
    }
  }
}
