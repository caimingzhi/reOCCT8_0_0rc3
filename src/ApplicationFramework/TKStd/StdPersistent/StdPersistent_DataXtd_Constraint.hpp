#pragma once

#include <StdObjMgt_Attribute.hpp>
#include <StdLPersistent_HArray1.hpp>

#include <TDataXtd_Constraint.hpp>

class StdPersistent_DataXtd_Constraint : public StdObjMgt_Attribute<TDataXtd_Constraint>
{
public:
  //! Read persistent data from a file.
  inline void Read(StdObjMgt_ReadData& theReadData)
  {
    theReadData >> myType >> myGeometries >> myValue >> myIsReversed >> myIsInverted >> myIsVerified
      >> myPlane;
  }

  //! Write persistent data to a file.
  inline void Write(StdObjMgt_WriteData& theWriteData) const
  {
    theWriteData << myType << myGeometries << myValue << myIsReversed << myIsInverted
                 << myIsVerified << myPlane;
  }

  //! Gets persistent child objects
  inline void PChildren(StdObjMgt_Persistent::SequenceOfPersistent& theChildren) const
  {
    theChildren.Append(myGeometries);
    theChildren.Append(myValue);
    theChildren.Append(myPlane);
  }

  //! Returns persistent type name
  inline const char* PName() const { return "PDataXtd_Constraint"; }

  //! Import transient attribute from the persistent data.
  void Import(const occ::handle<TDataXtd_Constraint>& theAttribute) const;

private:
  int                                        myType;
  Handle(StdLPersistent_HArray1::Persistent) myGeometries;
  occ::handle<StdObjMgt_Persistent>          myValue;
  bool                                       myIsReversed;
  bool                                       myIsInverted;
  bool                                       myIsVerified;
  occ::handle<StdObjMgt_Persistent>          myPlane;
};
