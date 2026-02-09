#include <IGESBasic_HArray1OfHArray1OfInteger.hpp>
#include <IGESDefs_AssociativityDef.hpp>
#include <Standard_DimensionMismatch.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESDefs_AssociativityDef, IGESData_IGESEntity)

IGESDefs_AssociativityDef::IGESDefs_AssociativityDef() = default;

void IGESDefs_AssociativityDef::Init(const occ::handle<NCollection_HArray1<int>>& requirements,
                                     const occ::handle<NCollection_HArray1<int>>& orders,
                                     const occ::handle<NCollection_HArray1<int>>& numItems,
                                     const occ::handle<IGESBasic_HArray1OfHArray1OfInteger>& items)
{
  int len = requirements->Length();
  if (requirements->Lower() != 1 || (orders->Lower() != 1 || orders->Length() != len)
      || (numItems->Lower() != 1 || numItems->Length() != len)
      || (items->Lower() != 1 || items->Length() != len))
    throw Standard_DimensionMismatch("IGESDefs_AssociativityDef : Init");

  theBackPointerReqs = requirements;
  theClassOrders     = orders;
  theNbItemsPerClass = numItems;
  theItems           = items;
  InitTypeAndForm(302, FormNumber());
}

void IGESDefs_AssociativityDef::SetFormNumber(const int form)
{
  InitTypeAndForm(302, form);
}

int IGESDefs_AssociativityDef::NbClassDefs() const
{
  return theBackPointerReqs->Length();
}

bool IGESDefs_AssociativityDef::IsBackPointerReq(const int ClassNum) const
{
  return (theBackPointerReqs->Value(ClassNum) == 1);
}

int IGESDefs_AssociativityDef::BackPointerReq(const int ClassNum) const
{
  return theBackPointerReqs->Value(ClassNum);
}

bool IGESDefs_AssociativityDef::IsOrdered(const int ClassNum) const
{
  return (theClassOrders->Value(ClassNum) == 1);
}

int IGESDefs_AssociativityDef::ClassOrder(const int ClassNum) const
{
  return theClassOrders->Value(ClassNum);
}

int IGESDefs_AssociativityDef::NbItemsPerClass(const int ClassNum) const
{
  return theNbItemsPerClass->Value(ClassNum);
}

int IGESDefs_AssociativityDef::Item(const int ClassNum, const int ItemNum) const
{
  return theItems->Value(ClassNum)->Value(ItemNum);
}
