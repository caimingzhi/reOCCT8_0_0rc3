#pragma once

#include <StdObjMgt_Attribute.hpp>

#include <TDataStd_Real.hpp>

class StdLPersistent_Real : public StdObjMgt_Attribute<TDataStd_Real>
{
public:
  StdLPersistent_Real()
      : myValue(0.0),
        myDimension(0)
  {
  }

  inline void Read(StdObjMgt_ReadData& theReadData) { theReadData >> myValue >> myDimension; }

  inline void Write(StdObjMgt_WriteData& theWriteData) const
  {
    theWriteData << myValue << myDimension;
  }

  void PChildren(StdObjMgt_Persistent::SequenceOfPersistent&) const {}

  const char* PName() const { return "PDataStd_Real"; }

  void Import(const occ::handle<TDataStd_Real>& theAttribute) const
  {
    theAttribute->Set(myValue);
    Standard_DISABLE_DEPRECATION_WARNINGS theAttribute->SetDimension(
      static_cast<TDataStd_RealEnum>(myDimension));
    Standard_ENABLE_DEPRECATION_WARNINGS theAttribute->SetID(TDataStd_Real::GetID());
  }

private:
  double myValue;
  int    myDimension;
};
