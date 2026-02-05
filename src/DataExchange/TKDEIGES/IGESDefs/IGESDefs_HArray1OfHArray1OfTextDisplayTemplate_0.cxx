#include <IGESDefs_HArray1OfHArray1OfTextDisplayTemplate.hpp>

#include <Standard_Type.hpp>

IGESDefs_HArray1OfHArray1OfTextDisplayTemplate::IGESDefs_HArray1OfHArray1OfTextDisplayTemplate(
  const int low,
  const int up)
    : thelist(low, up)
{
  occ::handle<Standard_Transient> nulo;
  thelist.Init(nulo);
}

int IGESDefs_HArray1OfHArray1OfTextDisplayTemplate::Lower() const
{
  return thelist.Lower();
}

int IGESDefs_HArray1OfHArray1OfTextDisplayTemplate::Upper() const
{
  return thelist.Upper();
}

int IGESDefs_HArray1OfHArray1OfTextDisplayTemplate::Length() const
{
  return thelist.Length();
}

void IGESDefs_HArray1OfHArray1OfTextDisplayTemplate::SetValue(
  const int                                                                           num,
  const occ::handle<NCollection_HArray1<occ::handle<IGESGraph_TextDisplayTemplate>>>& val)
{
  thelist.SetValue(num, val);
}

occ::handle<NCollection_HArray1<occ::handle<IGESGraph_TextDisplayTemplate>>>
  IGESDefs_HArray1OfHArray1OfTextDisplayTemplate::Value(const int num) const
{
  return occ::down_cast<NCollection_HArray1<occ::handle<IGESGraph_TextDisplayTemplate>>>(
    thelist.Value(num));
}
