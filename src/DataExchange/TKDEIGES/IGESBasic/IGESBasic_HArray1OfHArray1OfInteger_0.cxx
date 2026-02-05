#include <IGESBasic_HArray1OfHArray1OfInteger.hpp>

#include <Standard_Type.hpp>

IGESBasic_HArray1OfHArray1OfInteger::IGESBasic_HArray1OfHArray1OfInteger(const int low,
                                                                         const int up)
    : thelist(low, up)
{
  occ::handle<Standard_Transient> nulo;
  thelist.Init(nulo);
}

int IGESBasic_HArray1OfHArray1OfInteger::Lower() const
{
  return thelist.Lower();
}

int IGESBasic_HArray1OfHArray1OfInteger::Upper() const
{
  return thelist.Upper();
}

int IGESBasic_HArray1OfHArray1OfInteger::Length() const
{
  return thelist.Length();
}

void IGESBasic_HArray1OfHArray1OfInteger::SetValue(const int                                    num,
                                                   const occ::handle<NCollection_HArray1<int>>& val)
{
  thelist.SetValue(num, val);
}

occ::handle<NCollection_HArray1<int>> IGESBasic_HArray1OfHArray1OfInteger::Value(
  const int num) const
{
  return occ::down_cast<NCollection_HArray1<int>>(thelist.Value(num));
}
