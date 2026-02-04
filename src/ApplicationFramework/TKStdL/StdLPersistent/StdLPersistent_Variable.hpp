#pragma once


#include <StdObjMgt_Attribute.hpp>
#include <StdLPersistent_HString.hpp>

#include <TDataStd_Variable.hpp>

class StdLPersistent_Variable : public StdObjMgt_Attribute<TDataStd_Variable>
{
public:
  //! Empty constructor.
  StdLPersistent_Variable()
      : myIsConstant(false)
  {
  }

  //! Read persistent data from a file.
  inline void Read(StdObjMgt_ReadData& theReadData) { theReadData >> myIsConstant >> myUnit; }

  //! Write persistent data to a file.
  inline void Write(StdObjMgt_WriteData& theWriteData) const
  {
    theWriteData << myIsConstant << myUnit;
  }

  //! Gets persistent child objects
  inline void PChildren(StdObjMgt_Persistent::SequenceOfPersistent& theChildren) const
  {
    theChildren.Append(myUnit);
  }

  //! Returns persistent type name
  inline const char* PName() const { return "PDataStd_Variable"; }

  //! Import transient attribute from the persistent data.
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

