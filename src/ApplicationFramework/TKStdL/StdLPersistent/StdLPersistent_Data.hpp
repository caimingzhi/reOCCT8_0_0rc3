#pragma once

#include <StdLPersistent_HArray1.hpp>

class TDF_Data;

class StdLPersistent_Data : public StdObjMgt_Persistent
{
public:
  StdLPersistent_Data()
      : myVersion(0)
  {
  }

  Standard_EXPORT void Read(StdObjMgt_ReadData& theReadData) override;

  Standard_EXPORT void Write(StdObjMgt_WriteData& theWriteData) const override;

  void PChildren(StdObjMgt_Persistent::SequenceOfPersistent& theChildren) const override
  {
    theChildren.Append(myLabels);
    theChildren.Append(myAttributes);
  }

  const char* PName() const override { return "PDF_Data"; }

  Standard_EXPORT occ::handle<TDF_Data> Import() const;

private:
  class Parser;

private:
  int                                        myVersion;
  Handle(StdLPersistent_HArray1::Integer)    myLabels;
  Handle(StdLPersistent_HArray1::Persistent) myAttributes;
};
