#pragma once

#include <StdObjMgt_Attribute.hpp>

#include <TDataXtd_PatternStd.hpp>

class StdPersistent_DataXtd_PatternStd : public StdObjMgt_Attribute<TDataXtd_PatternStd>
{
public:
  inline void Read(StdObjMgt_ReadData& theReadData)
  {
    theReadData >> mySignature >> myAxis1Reversed >> myAxis2Reversed >> myAxis1 >> myAxis2
      >> myValue1 >> myValue2 >> myNb1 >> myNb2 >> myMirror;
  }

  inline void Write(StdObjMgt_WriteData& theWriteData)
  {
    theWriteData << mySignature << myAxis1Reversed << myAxis2Reversed << myAxis1 << myAxis2
                 << myValue1 << myValue2 << myNb1 << myNb2 << myMirror;
  }

  inline void PChildren(StdObjMgt_Persistent::SequenceOfPersistent& theChildren) const
  {
    theChildren.Append(myAxis1);
    theChildren.Append(myAxis2);
    theChildren.Append(myValue1);
    theChildren.Append(myValue2);
    theChildren.Append(myNb1);
    theChildren.Append(myNb2);
    theChildren.Append(myMirror);
  }

  inline const char* PName() const { return "PDataXtd_PatternStd"; }

  void Import(const occ::handle<TDataXtd_PatternStd>& theAttribute) const;

private:
  int                               mySignature;
  bool                              myAxis1Reversed;
  bool                              myAxis2Reversed;
  occ::handle<StdObjMgt_Persistent> myAxis1;
  occ::handle<StdObjMgt_Persistent> myAxis2;
  occ::handle<StdObjMgt_Persistent> myValue1;
  occ::handle<StdObjMgt_Persistent> myValue2;
  occ::handle<StdObjMgt_Persistent> myNb1;
  occ::handle<StdObjMgt_Persistent> myNb2;
  occ::handle<StdObjMgt_Persistent> myMirror;
};
