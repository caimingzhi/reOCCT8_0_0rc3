

#include <StdPersistent_DataXtd_PatternStd.hpp>

#include <TNaming_NamedShape.hpp>
#include <TDataStd_Real.hpp>
#include <TDataStd_Integer.hpp>

void StdPersistent_DataXtd_PatternStd::Import(
  const occ::handle<TDataXtd_PatternStd>& theAttribute) const
{
  theAttribute->Signature(mySignature);
  theAttribute->Axis1Reversed(myAxis1Reversed);
  theAttribute->Axis2Reversed(myAxis2Reversed);

  if (mySignature < 5)
  {
    theAttribute->Axis1(occ::down_cast<TNaming_NamedShape>(myAxis1->GetAttribute()));

    theAttribute->Value1(occ::down_cast<TDataStd_Real>(myValue1->GetAttribute()));

    theAttribute->NbInstances1(occ::down_cast<TDataStd_Integer>(myNb1->GetAttribute()));

    if (mySignature > 2)
    {
      theAttribute->Axis2(occ::down_cast<TNaming_NamedShape>(myAxis2->GetAttribute()));

      theAttribute->Value2(occ::down_cast<TDataStd_Real>(myValue2->GetAttribute()));

      theAttribute->NbInstances2(occ::down_cast<TDataStd_Integer>(myNb2->GetAttribute()));
    }
  }
  else
  {
    theAttribute->Mirror(occ::down_cast<TNaming_NamedShape>(myMirror->GetAttribute()));
  }
}
