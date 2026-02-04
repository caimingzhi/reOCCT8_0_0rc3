#pragma once


#include <StdLPersistent_HArray1.hpp>

class TDF_Data;

class StdLPersistent_Data : public StdObjMgt_Persistent
{
public:
  //! Empty constructor.
  StdLPersistent_Data()
      : myVersion(0)
  {
  }

  //! Read persistent data from a file.
  Standard_EXPORT void Read(StdObjMgt_ReadData& theReadData) override;
  //! Write persistent data to a file.
  Standard_EXPORT void Write(StdObjMgt_WriteData& theWriteData) const override;

  //! Gets persistent child objects
  void PChildren(StdObjMgt_Persistent::SequenceOfPersistent& theChildren) const override
  {
    theChildren.Append(myLabels);
    theChildren.Append(myAttributes);
  }

  //! Returns persistent type name
  const char* PName() const override { return "PDF_Data"; }

  //! Import transient data from the persistent data.
  Standard_EXPORT occ::handle<TDF_Data> Import() const;

private:
  class Parser;

private:
  int                                        myVersion;
  Handle(StdLPersistent_HArray1::Integer)    myLabels;
  Handle(StdLPersistent_HArray1::Persistent) myAttributes;
};

