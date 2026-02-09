#pragma once

#include <StdObjMgt_Persistent.hpp>

class TDocStd_Document;
class StdLPersistent_Data;

class StdLPersistent_Document : public StdObjMgt_Persistent
{
public:
  Standard_EXPORT void Read(StdObjMgt_ReadData& theReadData) override;

  Standard_EXPORT void Write(StdObjMgt_WriteData& theWriteData) const override;

  Standard_EXPORT void PChildren(StdObjMgt_Persistent::SequenceOfPersistent&) const override;

  const char* PName() const override { return "PDocStd_Document"; }

  Standard_EXPORT void ImportDocument(
    const occ::handle<TDocStd_Document>& theDocument) const override;

private:
  occ::handle<StdLPersistent_Data> myData;
};
