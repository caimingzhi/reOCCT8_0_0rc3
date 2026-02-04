#pragma once


#include <StdObjMgt_Attribute.hpp>

#include <TDataStd_Real.hpp>

class StdLPersistent_Real : public StdObjMgt_Attribute<TDataStd_Real>
{
public:
  //! Empty constructor.
  StdLPersistent_Real()
      : myValue(0.0),
        myDimension(0)
  {
  }

  //! Read persistent data from a file.
  inline void Read(StdObjMgt_ReadData& theReadData) { theReadData >> myValue >> myDimension; }

  //! Write persistent data from a file.
  inline void Write(StdObjMgt_WriteData& theWriteData) const
  {
    theWriteData << myValue << myDimension;
  }

  //! Gets persistent child objects
  void PChildren(StdObjMgt_Persistent::SequenceOfPersistent&) const {}

  //! Returns persistent type name
  const char* PName() const { return "PDataStd_Real"; }

  //! Import transient attribute from the persistent data.
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

