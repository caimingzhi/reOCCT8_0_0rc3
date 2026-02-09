

#include <StdLPersistent_Data.hpp>
#include <StdObjMgt_ReadData.hpp>
#include <StdObjMgt_WriteData.hpp>

#include <TDF_Data.hpp>
#include <TDF_Attribute.hpp>

class StdLPersistent_Data::Parser
{
public:
  Parser(const NCollection_HArray1<int>&                               theLabels,
         const NCollection_HArray1<occ::handle<StdObjMgt_Persistent>>& theAttributes)
      : myLabelsIter(theLabels),
        myAttribIter(theAttributes)
  {
  }

  void FillLabel(TDF_Label theLabel)
  {
    int i;

    myLabelsIter.Next();
    int anAttribCount = myLabelsIter.Value();

    for (i = 0; i < anAttribCount; i++)
    {

      occ::handle<StdObjMgt_Persistent>& aPAttrib = myAttribIter.ChangeValue();
      myAttribIter.Next();

      if (aPAttrib)
      {
        occ::handle<TDF_Attribute> anAtt = aPAttrib->CreateAttribute();
        anAtt->SetID();
        theLabel.AddAttribute(anAtt);
      }
    }

    myLabelsIter.Next();
    int aSubLabelsCount = myLabelsIter.Value();

    for (i = 0; i < aSubLabelsCount; i++)
    {

      myLabelsIter.Next();
      int aSubLabelTag = myLabelsIter.Value();

      TDF_Label aSubLabel = theLabel.FindChild(aSubLabelTag, true);
      FillLabel(aSubLabel);
    }
  }

private:
  NCollection_HArray1<int>::Iterator                               myLabelsIter;
  NCollection_HArray1<occ::handle<StdObjMgt_Persistent>>::Iterator myAttribIter;
};

void StdLPersistent_Data::Read(StdObjMgt_ReadData& theReadData)
{
  theReadData >> myVersion >> myLabels >> myAttributes;
}

void StdLPersistent_Data::Write(StdObjMgt_WriteData& theWriteData) const
{
  theWriteData << myVersion << myLabels << myAttributes;
}

occ::handle<TDF_Data> StdLPersistent_Data::Import() const
{
  if (myLabels.IsNull() || myAttributes.IsNull())
    return nullptr;

  occ::handle<TDF_Data> aData = new TDF_Data;
  Parser(*myLabels->Array(), *myAttributes->Array()).FillLabel(aData->Root());

  NCollection_HArray1<occ::handle<StdObjMgt_Persistent>>::Iterator anAttribIter(
    *myAttributes->Array());
  for (; anAttribIter.More(); anAttribIter.Next())
  {
    occ::handle<StdObjMgt_Persistent>& aPAttrib = anAttribIter.ChangeValue();
    if (aPAttrib)
      aPAttrib->ImportAttribute();
  }

  return aData;
}
