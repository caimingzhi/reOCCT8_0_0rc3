

#include <StdObjMgt_Persistent.hpp>

StdObjMgt_Persistent::StdObjMgt_Persistent()
    : myTypeNum(0),
      myRefNum(0)
{
}

void StdObjMgt_Persistent::ImportDocument(const occ::handle<TDocStd_Document>&) const {}

occ::handle<TDF_Attribute> StdObjMgt_Persistent::CreateAttribute()
{
  return occ::handle<TDF_Attribute>();
}

occ::handle<TDF_Attribute> StdObjMgt_Persistent::GetAttribute() const
{
  return occ::handle<TDF_Attribute>();
}

void StdObjMgt_Persistent::ImportAttribute() {}

occ::handle<TCollection_HAsciiString> StdObjMgt_Persistent::AsciiString() const
{
  return occ::handle<TCollection_HAsciiString>();
}

occ::handle<TCollection_HExtendedString> StdObjMgt_Persistent::ExtString() const
{
  return occ::handle<TCollection_HExtendedString>();
}

TDF_Label StdObjMgt_Persistent::Label(const occ::handle<TDF_Data>&) const
{
  return TDF_Label();
}
