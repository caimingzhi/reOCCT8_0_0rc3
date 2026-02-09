#define No_Standard_NoSuchObject

#include <gp_Trsf.hpp>
#include <Standard_Dump.hpp>
#include <TopLoc_Datum3D.hpp>
#include <TopLoc_Location.hpp>
#include <TopLoc_SListOfItemLocation.hpp>

TopLoc_Location::TopLoc_Location() = default;

TopLoc_Location::TopLoc_Location(const occ::handle<TopLoc_Datum3D>& D)
{
  myItems.Construct(TopLoc_ItemLocation(D, 1));
}

TopLoc_Location::TopLoc_Location(const gp_Trsf& T)
{
  occ::handle<TopLoc_Datum3D> D = new TopLoc_Datum3D(T);
  myItems.Construct(TopLoc_ItemLocation(D, 1));
}

const gp_Trsf& TopLoc_Location::Transformation() const
{
  static const gp_Trsf THE_IDENTITY_TRSF;
  if (IsIdentity())
    return THE_IDENTITY_TRSF;
  else
    return myItems.Value().myTrsf;
}

TopLoc_Location::operator gp_Trsf() const
{
  return Transformation();
}

TopLoc_Location TopLoc_Location::Inverted() const
{

  TopLoc_Location            result;
  TopLoc_SListOfItemLocation items = myItems;
  while (items.More())
  {
    result.myItems.Construct(TopLoc_ItemLocation(items.Value().myDatum, -items.Value().myPower));
    items.Next();
  }
  return result;
}

TopLoc_Location TopLoc_Location::Multiplied(const TopLoc_Location& Other) const
{

  if (IsIdentity())
    return Other;
  if (Other.IsIdentity())
    return *this;

  TopLoc_Location result = Multiplied(Other.NextLocation());

  int p = Other.FirstPower();
  if (!result.IsIdentity())
  {
    if (Other.FirstDatum() == result.FirstDatum())
    {
      p += result.FirstPower();
      result.myItems.ToTail();
    }
  }
  if (p != 0)
    result.myItems.Construct(TopLoc_ItemLocation(Other.FirstDatum(), p));
  return result;
}

TopLoc_Location TopLoc_Location::Divided(const TopLoc_Location& Other) const
{
  return Multiplied(Other.Inverted());
}

TopLoc_Location TopLoc_Location::Predivided(const TopLoc_Location& Other) const
{
  return Other.Inverted().Multiplied(*this);
}

TopLoc_Location TopLoc_Location::Powered(const int pwr) const
{
  if (IsIdentity())
    return *this;
  if (pwr == 1)
    return *this;
  if (pwr == 0)
    return TopLoc_Location();

  if (myItems.Tail().IsEmpty())
  {
    TopLoc_Location result;
    result.myItems.Construct(TopLoc_ItemLocation(FirstDatum(), FirstPower() * pwr));
    return result;
  }

  if (pwr > 0)
    return Multiplied(Powered(pwr - 1));
  else
    return Inverted().Powered(-pwr);
}

bool TopLoc_Location::IsEqual(const TopLoc_Location& Other) const
{
  const void** p = (const void**)&myItems;
  const void** q = (const void**)&Other.myItems;
  if (*p == *q)
  {
    return true;
  }
  if (IsIdentity() || Other.IsIdentity())
  {
    return false;
  }
  if (FirstDatum() != Other.FirstDatum())
  {
    return false;
  }
  if (FirstPower() != Other.FirstPower())
  {
    return false;
  }
  else
  {
    return NextLocation() == Other.NextLocation();
  }
}

bool TopLoc_Location::IsDifferent(const TopLoc_Location& Other) const
{
  return !IsEqual(Other);
}

void TopLoc_Location::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_CLASS_BEGIN(theOStream, TopLoc_Location)

  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, &Transformation())
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, IsIdentity())
}

void TopLoc_Location::ShallowDump(Standard_OStream& S) const
{
  S << "TopLoc_Location : ";
  TopLoc_SListOfItemLocation items = myItems;
  if (items.IsEmpty())
    S << "Identity" << std::endl;
  while (items.More())
  {
    S << "\n";
    S << "       Exponent : " << items.Value().myPower << std::endl;
    items.Value().myDatum->ShallowDump(S);
    items.Next();
  }
  S << "\n";
}
