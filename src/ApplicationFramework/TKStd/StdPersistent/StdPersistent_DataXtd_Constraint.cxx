

#include <StdPersistent_DataXtd_Constraint.hpp>

#include <TNaming_NamedShape.hpp>
#include <TDataStd_Real.hpp>

void StdPersistent_DataXtd_Constraint::Import(
  const occ::handle<TDataXtd_Constraint>& theAttribute) const
{
  theAttribute->SetType(static_cast<TDataXtd_ConstraintEnum>(myType));
  theAttribute->Reversed(myIsReversed);
  theAttribute->Inverted(myIsInverted);
  theAttribute->Verified(myIsVerified);

  if (myGeometries)
  {
    occ::handle<NCollection_HArray1<occ::handle<StdObjMgt_Persistent>>> aGeometries =
      myGeometries->Array();
    for (int i = 1; i <= aGeometries->Length(); i++)
    {
      occ::handle<StdObjMgt_Persistent> aPGeometry = aGeometries->Value(i);
      if (aPGeometry)
      {
        occ::handle<TDF_Attribute> aTGeometry = aPGeometry->GetAttribute();
        theAttribute->SetGeometry(i, occ::down_cast<TNaming_NamedShape>(aTGeometry));
      }
    }
  }

  if (myValue)
  {
    occ::handle<TDF_Attribute> aValue = myValue->GetAttribute();
    theAttribute->SetValue(occ::down_cast<TDataStd_Real>(aValue));
  }

  if (myPlane)
  {
    occ::handle<TDF_Attribute> aPlane = myPlane->GetAttribute();
    theAttribute->SetPlane(occ::down_cast<TNaming_NamedShape>(aPlane));
  }
}
