#include <Intf_TangentZone.hpp>

#define DEBUG_TANGENTZONE 0

Intf_TangentZone::Intf_TangentZone()
{
  ParamOnFirstMin = ParamOnSecondMin = RealLast();
  ParamOnFirstMax = ParamOnSecondMax = RealFirst();
}

void Intf_TangentZone::Append(const Intf_SectionPoint& Pi)
{
  Result.Append(Pi);
  if (ParamOnFirstMin > Pi.ParamOnFirst())
    ParamOnFirstMin = Pi.ParamOnFirst();
  if (ParamOnSecondMin > Pi.ParamOnSecond())
    ParamOnSecondMin = Pi.ParamOnSecond();

  if (ParamOnFirstMax < Pi.ParamOnFirst())
    ParamOnFirstMax = Pi.ParamOnFirst();
  if (ParamOnSecondMax < Pi.ParamOnSecond())
    ParamOnSecondMax = Pi.ParamOnSecond();
}

void Intf_TangentZone::Append(const Intf_TangentZone& Tzi)
{
  int Tzi_NumberOfPoints = Tzi.NumberOfPoints();
  for (int ipi = 1; ipi <= Tzi_NumberOfPoints; ipi++)
  {
    PolygonInsert(Tzi.GetPoint(ipi));
  }
}

bool Intf_TangentZone::Insert(const Intf_SectionPoint&)
{
#if DEBUG_TANGENTZONE
  std::cout << " bool Intf_TangentZone::Insert (const Intf_SectionPoint& Pi) ???? " << std::endl;
#endif
  bool Inserted = false;

  return Inserted;
}

void Intf_TangentZone::PolygonInsert(const Intf_SectionPoint& Pi)
{

  int nbpTz = NumberOfPoints();

  if (nbpTz == 0)
  {
    Append(Pi);
    return;
  }
  if (Pi.ParamOnFirst() >= ParamOnFirstMax)
  {
    Append(Pi);
  }
  else if (Pi.ParamOnFirst() >= ParamOnFirstMin)
  {
    InsertBefore(1, Pi);
  }
  else
  {

    Append(Pi);
  }
}

void Intf_TangentZone::InsertAfter(const int Index, const Intf_SectionPoint& Pi)
{
  Result.InsertAfter(Index, Pi);
  if (ParamOnFirstMin > Pi.ParamOnFirst())
    ParamOnFirstMin = Pi.ParamOnFirst();
  if (ParamOnSecondMin > Pi.ParamOnSecond())
    ParamOnSecondMin = Pi.ParamOnSecond();

  if (ParamOnFirstMax < Pi.ParamOnFirst())
    ParamOnFirstMax = Pi.ParamOnFirst();
  if (ParamOnSecondMax < Pi.ParamOnSecond())
    ParamOnSecondMax = Pi.ParamOnSecond();
}

void Intf_TangentZone::InsertBefore(const int Index, const Intf_SectionPoint& Pi)
{
  Result.InsertBefore(Index, Pi);
  if (ParamOnFirstMin > Pi.ParamOnFirst())
    ParamOnFirstMin = Pi.ParamOnFirst();
  if (ParamOnSecondMin > Pi.ParamOnSecond())
    ParamOnSecondMin = Pi.ParamOnSecond();

  if (ParamOnFirstMax < Pi.ParamOnFirst())
    ParamOnFirstMax = Pi.ParamOnFirst();
  if (ParamOnSecondMax < Pi.ParamOnSecond())
    ParamOnSecondMax = Pi.ParamOnSecond();
}

const Intf_SectionPoint& Intf_TangentZone::GetPoint(const int Index) const
{
  return Result(Index);
}

bool Intf_TangentZone::IsEqual(const Intf_TangentZone& Other) const
{
  if (Result.Length() != Other.Result.Length())
    return false;
  int i;
  for (i = 1; i <= Result.Length(); i++)
  {
    if (!Result(i).IsEqual(Other.Result(i)))
      return false;
  }
  return true;
}

bool Intf_TangentZone::Contains(const Intf_SectionPoint& ThePI) const
{
  int i;
  for (i = 1; i <= Result.Length(); i++)
    if (ThePI.IsEqual(Result(i)))
      return true;
  return false;
}

void Intf_TangentZone::InfoFirst(int& segMin, double& paraMin, int& segMax, double& paraMax) const
{
  ParamOnFirst(paraMin, paraMax);
  segMin  = (int)(std::trunc(paraMin));
  paraMin = paraMin - (double)segMin;
  segMax  = (int)(std::trunc(paraMax));
  paraMax = paraMax - (double)segMax;
}

void Intf_TangentZone::InfoSecond(int& segMin, double& paraMin, int& segMax, double& paraMax) const
{
  ParamOnSecond(paraMin, paraMax);
  segMin  = (int)(std::trunc(paraMin));
  paraMin = paraMin - (double)segMin;
  segMax  = (int)(std::trunc(paraMax));
  paraMax = paraMax - (double)segMax;
}

bool Intf_TangentZone::RangeContains(const Intf_SectionPoint& ThePI) const
{
  double a, b, c, d;
  ParamOnFirst(a, b);
  ParamOnSecond(c, d);
  return a <= ThePI.ParamOnFirst() && ThePI.ParamOnFirst() <= b && c <= ThePI.ParamOnSecond()
         && ThePI.ParamOnSecond() <= d;
}

bool Intf_TangentZone::HasCommonRange(const Intf_TangentZone& Other) const
{
  double a1, b1, c1, d1;
  double a2, b2, c2, d2;
  ParamOnFirst(a1, b1);
  ParamOnSecond(a2, b2);
  Other.ParamOnFirst(c1, d1);
  Other.ParamOnSecond(c2, d2);

  return ((c1 <= a1 && a1 <= d1) || (c1 <= b1 && b1 <= d1) || (a1 <= c1 && c1 <= b1))
         && ((c2 <= a2 && a2 <= d2) || (c2 <= b2 && b2 <= d2) || (a2 <= c2 && c2 <= b2));
}

void Intf_TangentZone::Dump(const int) const
{
#if DEBUG_TANGENTZONE
  for (int id = 0; id < Indent; id++)
    std::cout << " ";
  std::cout << "TZ \n";
  std::cout << "  ParamOnFirstMin Max    : " << ParamOnFirstMin << " " << ParamOnFirstMax
            << std::endl;
  std::cout << "  ParamOnSecondMin Max   : " << ParamOnSecondMin << " " << ParamOnSecondMax
            << std::endl;
  for (int p = 1; p <= Result.Length(); p++)
  {
    Result(p).Dump(Indent + 2);
  }
#endif
}
