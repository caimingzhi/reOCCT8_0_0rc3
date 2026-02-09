

#include <StdLPersistent_Document.hpp>
#include <StdLPersistent_Data.hpp>
#include <StdObjMgt_ReadData.hpp>
#include <StdObjMgt_WriteData.hpp>

#include <TDocStd_Document.hpp>
#include <TDocStd_Owner.hpp>

void StdLPersistent_Document::Read(StdObjMgt_ReadData& theReadData)
{
  theReadData >> myData;
}

void StdLPersistent_Document::Write(StdObjMgt_WriteData& theWriteData) const
{
  theWriteData << myData;
}

void StdLPersistent_Document::PChildren(
  StdObjMgt_Persistent::SequenceOfPersistent& theChildren) const
{
  theChildren.Append(myData);
}

void StdLPersistent_Document::ImportDocument(const occ::handle<TDocStd_Document>& theDocument) const
{
  if (theDocument.IsNull() || myData.IsNull())
    return;

  occ::handle<TDF_Data> aData = myData->Import();
  if (aData.IsNull())
    return;

  theDocument->SetData(aData);
  TDocStd_Owner::SetDocument(aData, theDocument);
}
