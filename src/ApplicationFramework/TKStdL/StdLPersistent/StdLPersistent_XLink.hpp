#pragma once

#include <StdObjMgt_Attribute.hpp>
#include <StdLPersistent_HString.hpp>

#include <TDocStd_XLink.hpp>

class StdLPersistent_XLink : public StdObjMgt_Attribute<TDocStd_XLink>
{
public:
  inline void Read(StdObjMgt_ReadData& theReadData) { theReadData >> myDocEntry >> myLabEntry; }

  inline void Write(StdObjMgt_WriteData& theWriteData) const
  {
    theWriteData << myDocEntry << myLabEntry;
  }

  inline void PChildren(StdObjMgt_Persistent::SequenceOfPersistent& theChildren) const
  {
    theChildren.Append(myDocEntry);
    theChildren.Append(myLabEntry);
  }

  inline const char* PName() const { return "PDocStd_XLink"; }

  void Import(const occ::handle<TDocStd_XLink>& theAttribute) const
  {
    if (myDocEntry)
      theAttribute->DocumentEntry(myDocEntry->Value()->String());

    if (myLabEntry)
      theAttribute->LabelEntry(myLabEntry->Value()->String());
  }

private:
  Handle(StdLPersistent_HString::Ascii) myDocEntry;
  Handle(StdLPersistent_HString::Ascii) myLabEntry;
};
