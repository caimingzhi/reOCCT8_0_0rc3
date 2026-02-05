#include <IGESBasic_HArray1OfHArray1OfXY.hpp>

#include <Standard_Type.hpp>

IGESBasic_HArray1OfHArray1OfXY::IGESBasic_HArray1OfHArray1OfXY(const int low, const int up)
    : thelist(low, up)
{
  occ::handle<Standard_Transient> nulo;
  thelist.Init(nulo);
}

int IGESBasic_HArray1OfHArray1OfXY::Lower() const
{
  return thelist.Lower();
}

int IGESBasic_HArray1OfHArray1OfXY::Upper() const
{
  return thelist.Upper();
}

int IGESBasic_HArray1OfHArray1OfXY::Length() const
{
  return thelist.Length();
}

void IGESBasic_HArray1OfHArray1OfXY::SetValue(const int                                      num,
                                              const occ::handle<NCollection_HArray1<gp_XY>>& val)
{
  thelist.SetValue(num, val);
}

occ::handle<NCollection_HArray1<gp_XY>> IGESBasic_HArray1OfHArray1OfXY::Value(const int num) const
{
  return occ::down_cast<NCollection_HArray1<gp_XY>>(thelist.Value(num));
}
