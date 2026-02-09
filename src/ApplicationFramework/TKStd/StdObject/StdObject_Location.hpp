#pragma once

#include <StdObjMgt_ReadData.hpp>
#include <StdObjMgt_WriteData.hpp>
#include <StdObjMgt_Persistent.hpp>
#include <NCollection_DataMap.hpp>

#include <TopLoc_Location.hpp>
class Standard_Transient;
class StdObjMgt_Persistent;

class StdObject_Location
{
public:
  Standard_EXPORT void PChildren(StdObjMgt_Persistent::SequenceOfPersistent& theChildren) const;

  TopLoc_Location Import() const;

  Standard_EXPORT static StdObject_Location Translate(
    const TopLoc_Location& theLoc,
    NCollection_DataMap<occ::handle<Standard_Transient>, occ::handle<StdObjMgt_Persistent>>&
      theMap);

private:
  occ::handle<StdObjMgt_Persistent> myData;

  friend StdObjMgt_ReadData&  operator>>(StdObjMgt_ReadData&, StdObject_Location&);
  friend StdObjMgt_WriteData& operator<<(StdObjMgt_WriteData&, const StdObject_Location&);
};

inline StdObjMgt_ReadData& operator>>(StdObjMgt_ReadData& theReadData,
                                      StdObject_Location& theLocation)
{
  StdObjMgt_ReadData::ObjectSentry aSentry(theReadData);
  return theReadData >> theLocation.myData;
}

inline StdObjMgt_WriteData& operator<<(StdObjMgt_WriteData&      theWriteData,
                                       const StdObject_Location& theLocation)
{
  StdObjMgt_WriteData::ObjectSentry aSentry(theWriteData);
  return theWriteData << theLocation.myData;
}
