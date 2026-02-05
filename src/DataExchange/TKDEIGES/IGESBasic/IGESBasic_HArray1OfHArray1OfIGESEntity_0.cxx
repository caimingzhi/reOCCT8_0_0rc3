#include <IGESBasic_HArray1OfHArray1OfIGESEntity.hpp>

#include <Standard_Type.hpp>

IGESBasic_HArray1OfHArray1OfIGESEntity::IGESBasic_HArray1OfHArray1OfIGESEntity(const int low,
                                                                               const int up)
    : thelist(low, up)
{
  occ::handle<Standard_Transient> nulo;
  thelist.Init(nulo);
}

int IGESBasic_HArray1OfHArray1OfIGESEntity::Lower() const
{
  return thelist.Lower();
}

int IGESBasic_HArray1OfHArray1OfIGESEntity::Upper() const
{
  return thelist.Upper();
}

int IGESBasic_HArray1OfHArray1OfIGESEntity::Length() const
{
  return thelist.Length();
}

void IGESBasic_HArray1OfHArray1OfIGESEntity::SetValue(
  const int                                                                 num,
  const occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>& val)
{
  thelist.SetValue(num, val);
}

occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>
  IGESBasic_HArray1OfHArray1OfIGESEntity::Value(const int num) const
{
  return occ::down_cast<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>(thelist.Value(num));
}
