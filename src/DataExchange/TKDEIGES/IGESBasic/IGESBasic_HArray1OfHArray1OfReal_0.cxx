#include <IGESBasic_HArray1OfHArray1OfReal.hpp>

#include <Standard_Type.hpp>

IGESBasic_HArray1OfHArray1OfReal::IGESBasic_HArray1OfHArray1OfReal(const int low, const int up)
    : thelist(low, up)
{
  occ::handle<Standard_Transient> nulo;
  thelist.Init(nulo);
}

int IGESBasic_HArray1OfHArray1OfReal::Lower() const
{
  return thelist.Lower();
}

int IGESBasic_HArray1OfHArray1OfReal::Upper() const
{
  return thelist.Upper();
}

int IGESBasic_HArray1OfHArray1OfReal::Length() const
{
  return thelist.Length();
}

void IGESBasic_HArray1OfHArray1OfReal::SetValue(const int                                       num,
                                                const occ::handle<NCollection_HArray1<double>>& val)
{
  thelist.SetValue(num, val);
}

occ::handle<NCollection_HArray1<double>> IGESBasic_HArray1OfHArray1OfReal::Value(
  const int num) const
{
  return occ::down_cast<NCollection_HArray1<double>>(thelist.Value(num));
}
