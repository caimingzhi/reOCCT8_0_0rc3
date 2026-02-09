#pragma once

#include <StdObjMgt_Attribute.hpp>

#include <TFunction_Function.hpp>
#include <Standard_GUID.hpp>

class StdLPersistent_Function : public StdObjMgt_Attribute<TFunction_Function>
{
public:
  StdLPersistent_Function()
      : myFailure(0)
  {
  }

  inline void Read(StdObjMgt_ReadData& theReadData) { theReadData >> myDriverGUID >> myFailure; }

  inline void Write(StdObjMgt_WriteData& theWriteData) const
  {
    theWriteData << myDriverGUID << myFailure;
  }

  inline void PChildren(StdObjMgt_Persistent::SequenceOfPersistent&) const {}

  inline const char* PName() const { return "PFunction_Function"; }

  void Import(const occ::handle<TFunction_Function>& theAttribute) const
  {
    theAttribute->SetDriverGUID(myDriverGUID);
    theAttribute->SetFailure(myFailure);
  }

private:
  Standard_GUID myDriverGUID;
  int           myFailure;
};
