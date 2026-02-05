#include <IGESBasic_HArray1OfHArray1OfXYZ.hpp>

#include <Standard_Type.hpp>

IGESBasic_HArray1OfHArray1OfXYZ::IGESBasic_HArray1OfHArray1OfXYZ(const int low, const int up)
    : thelist(low, up)
{
  occ::handle<Standard_Transient> nulo;
  thelist.Init(nulo);
}

int IGESBasic_HArray1OfHArray1OfXYZ::Lower() const
{
  return thelist.Lower();
}

int IGESBasic_HArray1OfHArray1OfXYZ::Upper() const
{
  return thelist.Upper();
}

int IGESBasic_HArray1OfHArray1OfXYZ::Length() const
{
  return thelist.Length();
}

void IGESBasic_HArray1OfHArray1OfXYZ::SetValue(const int                                       num,
                                               const occ::handle<NCollection_HArray1<gp_XYZ>>& val)
{
  thelist.SetValue(num, val);
}

occ::handle<NCollection_HArray1<gp_XYZ>> IGESBasic_HArray1OfHArray1OfXYZ::Value(const int num) const
{
  return occ::down_cast<NCollection_HArray1<gp_XYZ>>(thelist.Value(num));
}
