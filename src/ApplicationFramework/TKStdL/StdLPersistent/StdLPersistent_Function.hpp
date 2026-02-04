#pragma once


#include <StdObjMgt_Attribute.hpp>

#include <TFunction_Function.hpp>
#include <Standard_GUID.hpp>

class StdLPersistent_Function : public StdObjMgt_Attribute<TFunction_Function>
{
public:
  //! Empty constructor.
  StdLPersistent_Function()
      : myFailure(0)
  {
  }

  //! Read persistent data from a file.
  inline void Read(StdObjMgt_ReadData& theReadData) { theReadData >> myDriverGUID >> myFailure; }

  //! Write persistent data to a file.
  inline void Write(StdObjMgt_WriteData& theWriteData) const
  {
    theWriteData << myDriverGUID << myFailure;
  }

  //! Gets persistent child objects
  inline void PChildren(StdObjMgt_Persistent::SequenceOfPersistent&) const {}

  //! Returns persistent type name
  inline const char* PName() const { return "PFunction_Function"; }

  //! Import transient attribute from the persistent data.
  void Import(const occ::handle<TFunction_Function>& theAttribute) const
  {
    theAttribute->SetDriverGUID(myDriverGUID);
    theAttribute->SetFailure(myFailure);
  }

private:
  Standard_GUID myDriverGUID;
  int           myFailure;
};

