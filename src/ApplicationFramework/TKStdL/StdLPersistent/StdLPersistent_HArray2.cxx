

#include <StdLPersistent_HArray2.hpp>

void StdLPersistent_HArray2::base::Read(StdObjMgt_ReadData& theReadData)
{
  int aLowerRow, aLowerCol, anUpperRow, anUpperCol;
  theReadData >> aLowerRow >> aLowerCol >> anUpperRow >> anUpperCol;
  createArray(aLowerRow, aLowerCol, anUpperRow, anUpperCol);

  StdObjMgt_ReadData::ObjectSentry aSentry(theReadData);

  int aSize;
  theReadData >> aSize;

  for (int aRow = aLowerRow; aRow <= anUpperRow; aRow++)
    for (int aCol = aLowerCol; aCol <= anUpperCol; aCol++)
      readValue(theReadData, aRow, aCol);
}

void StdLPersistent_HArray2::base::Write(StdObjMgt_WriteData& theWriteData) const
{
  int aLowerRow, aLowerCol, anUpperRow, anUpperCol;
  lowerBound(aLowerRow, aLowerCol);
  upperBound(anUpperRow, anUpperCol);
  theWriteData << aLowerRow << aLowerCol << anUpperRow << anUpperCol;

  StdObjMgt_WriteData::ObjectSentry aSentry(theWriteData);

  int aSize = (anUpperRow - aLowerRow + 1) * (anUpperCol - aLowerCol + 1);
  theWriteData << aSize;

  for (int aRow = aLowerRow; aRow <= anUpperRow; aRow++)
    for (int aCol = aLowerCol; aCol <= anUpperCol; aCol++)
      writeValue(theWriteData, aRow, aCol);
}
