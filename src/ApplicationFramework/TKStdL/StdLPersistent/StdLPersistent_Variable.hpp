#pragma once

#include <StdObjMgt_Attribute.hpp>
#include <StdLPersistent_HString.hpp>

#include <TDataStd_Variable.hpp>

class StdLPersistent_Variable : public StdObjMgt_Attribute<TDataStd_Variable>
{
public:
  StdLPersistent_Variable()
      : myIsConstant(false)
  {
  }

  inline void Read(StdObjMgt_ReadData& theReadData) { theReadData >> myIsConstant >> myUnit; }

  inline void Write(StdObjMgt_WriteData& theWriteData) const
  {
    theWriteData << myIsConstant << myUnit;
  }

  inline void PChildren(StdObjMgt_Persistent::SequenceOfPersistent& theChildren) const
  {
    theChildren.Append(myUnit);
  }

  inline const char* PName() const { return "PDataStd_Variable"; }

  void Import(const occ::handle<TDataStd_Variable>& theAttribute) const
  {
    theAttribute->Constant(myIsConstant);
    if (myUnit)
      theAttribute->Unit(myUnit->Value()->String());
  }

private:
  bool                                  myIsConstant;
  Handle(StdLPersistent_HString::Ascii) myUnit;
};
