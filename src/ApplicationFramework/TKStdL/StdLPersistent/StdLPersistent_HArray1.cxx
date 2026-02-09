

#include <StdLPersistent_HArray1.hpp>

void StdLPersistent_HArray1::base::Read(StdObjMgt_ReadData& theReadData)
{
  int aLowerBound, anUpperBound;
  theReadData >> aLowerBound >> anUpperBound;
  createArray(aLowerBound, anUpperBound);

  StdObjMgt_ReadData::ObjectSentry aSentry(theReadData);

  int aSize;
  theReadData >> aSize;

  for (int i = aLowerBound; i <= anUpperBound; i++)
    readValue(theReadData, i);
}

void StdLPersistent_HArray1::base::Write(StdObjMgt_WriteData& theWriteData) const
{
  int aLowerBound = lowerBound(), anUpperBound = upperBound();
  theWriteData << aLowerBound << anUpperBound;

  StdObjMgt_WriteData::ObjectSentry aSentry(theWriteData);

  int aSize = anUpperBound - aLowerBound + 1;
  theWriteData << aSize;

  for (int i = aLowerBound; i <= anUpperBound; i++)
    writeValue(theWriteData, i);
}
