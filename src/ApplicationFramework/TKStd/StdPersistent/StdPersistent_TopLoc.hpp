#pragma once

#include <StdObjMgt_SharedObject.hpp>
#include <StdObjMgt_Persistent.hpp>
#include <StdObject_Location.hpp>
#include <NCollection_DataMap.hpp>

#include <TopLoc_Datum3D.hpp>
#include <TopLoc_Location.hpp>
class Standard_Transient;
class StdObjMgt_Persistent;

class StdPersistent_TopLoc
{
public:
  class Datum3D : public StdObjMgt_SharedObject::SharedBase<TopLoc_Datum3D>
  {
  public:
    void Read(StdObjMgt_ReadData& theReadData) override;

    void Write(StdObjMgt_WriteData& theWriteData) const override;

    void PChildren(SequenceOfPersistent&) const override {}

    const char* PName() const override { return "PTopLoc_Datum3D"; }
  };

  class ItemLocation : public StdObjMgt_Persistent
  {
    friend class StdPersistent_TopLoc;

  public:
    Standard_EXPORT void Read(StdObjMgt_ReadData& theReadData) override;

    Standard_EXPORT void Write(StdObjMgt_WriteData& theWriteData) const override;

    Standard_EXPORT void PChildren(SequenceOfPersistent& theChildren) const override;

    const char* PName() const override { return "PTopLoc_ItemLocation"; }

    Standard_EXPORT TopLoc_Location Import() const;

  private:
    occ::handle<Datum3D> myDatum;
    int                  myPower;
    StdObject_Location   myNext;
  };

public:
  Standard_EXPORT static occ::handle<ItemLocation> Translate(
    const TopLoc_Location& theLoc,
    NCollection_DataMap<occ::handle<Standard_Transient>, occ::handle<StdObjMgt_Persistent>>&
      theMap);
  Standard_EXPORT static occ::handle<Datum3D> Translate(
    const occ::handle<TopLoc_Datum3D>& theDatum,
    NCollection_DataMap<occ::handle<Standard_Transient>, occ::handle<StdObjMgt_Persistent>>&
      theMap);
};
