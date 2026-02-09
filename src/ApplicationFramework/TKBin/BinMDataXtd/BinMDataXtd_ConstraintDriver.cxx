#include <BinMDataXtd_ConstraintDriver.hpp>
#include <BinObjMgt_Persistent.hpp>
#include <Message_Messenger.hpp>
#include <Standard_Type.hpp>
#include <TDataStd_Real.hpp>
#include <TDataXtd_Constraint.hpp>
#include <TDF_Attribute.hpp>
#include <TNaming_NamedShape.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BinMDataXtd_ConstraintDriver, BinMDF_ADriver)

BinMDataXtd_ConstraintDriver::BinMDataXtd_ConstraintDriver(
  const occ::handle<Message_Messenger>& theMsgDriver)
    : BinMDF_ADriver(theMsgDriver, nullptr)
{
}

occ::handle<TDF_Attribute> BinMDataXtd_ConstraintDriver::NewEmpty() const
{
  return (new TDataXtd_Constraint());
}

bool BinMDataXtd_ConstraintDriver::Paste(const BinObjMgt_Persistent&       theSource,
                                         const occ::handle<TDF_Attribute>& theTarget,
                                         BinObjMgt_RRelocationTable&       theRelocTable) const
{
  occ::handle<TDataXtd_Constraint> aC = occ::down_cast<TDataXtd_Constraint>(theTarget);

  int aNb;

  if (!(theSource >> aNb))
    return false;
  if (aNb > 0)
  {
    occ::handle<TDataStd_Real> aTValue;
    if (theRelocTable.IsBound(aNb))
      aTValue = occ::down_cast<TDataStd_Real>(theRelocTable.Find(aNb));
    else
    {
      aTValue = new TDataStd_Real;
      theRelocTable.Bind(aNb, aTValue);
    }
    aC->SetValue(aTValue);
  }

  int NbGeom;
  if (!(theSource >> NbGeom))
    return false;
  int iG = 1;
  while (iG <= NbGeom)
  {
    if (!(theSource >> aNb))
      return false;
    if (aNb > 0)
    {
      occ::handle<TNaming_NamedShape> aG;
      if (theRelocTable.IsBound(aNb))
        aG = occ::down_cast<TNaming_NamedShape>(theRelocTable.Find(aNb));
      else
      {
        aG = new TNaming_NamedShape;
        theRelocTable.Bind(aNb, aG);
      }
      aC->SetGeometry(iG++, aG);
    }
  }

  if (!(theSource >> aNb))
    return false;
  if (aNb > 0)
  {
    occ::handle<TNaming_NamedShape> aTPlane;
    if (theRelocTable.IsBound(aNb))
      aTPlane = occ::down_cast<TNaming_NamedShape>(theRelocTable.Find(aNb));
    else
    {
      aTPlane = new TNaming_NamedShape;
      theRelocTable.Bind(aNb, aTPlane);
    }
    aC->SetPlane(aTPlane);
  }

  int aType;
  if (!(theSource >> aType))
    return false;
  aC->SetType((TDataXtd_ConstraintEnum)aType);

  int flags;
  if (!(theSource >> flags))
    return false;
  aC->Verified((flags & 1) != 0);
  aC->Inverted((flags & 2) != 0);
  aC->Reversed((flags & 4) != 0);

  return true;
}

void BinMDataXtd_ConstraintDriver::Paste(
  const occ::handle<TDF_Attribute>&                        theSource,
  BinObjMgt_Persistent&                                    theTarget,
  NCollection_IndexedMap<occ::handle<Standard_Transient>>& theRelocTable) const
{
  occ::handle<TDataXtd_Constraint> aC = occ::down_cast<TDataXtd_Constraint>(theSource);

  int aNb;

  occ::handle<TDataStd_Real> aValue = aC->GetValue();
  if (!aValue.IsNull())
    aNb = theRelocTable.Add(aValue);
  else
    aNb = -1;
  theTarget << aNb;

  int NbGeom = aC->NbGeometries();
  theTarget << NbGeom;
  int iG;
  for (iG = 1; iG <= NbGeom; iG++)
  {
    occ::handle<TNaming_NamedShape> aG = aC->GetGeometry(iG);
    if (!aG.IsNull())
      aNb = theRelocTable.Add(aG);
    else
      aNb = -1;
    theTarget << aNb;
  }

  occ::handle<TNaming_NamedShape> aTPlane = aC->GetPlane();
  if (!aTPlane.IsNull())
    aNb = theRelocTable.Add(aTPlane);
  else
    aNb = -1;
  theTarget << aNb;

  theTarget << (int)aC->GetType();

  int flags = 0;
  if (aC->Verified())
    flags |= 1;
  if (aC->Inverted())
    flags |= 2;
  if (aC->Reversed())
    flags |= 4;
  theTarget << flags;
}
