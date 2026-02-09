#include <IntPolyh_SectionLine.hpp>
#include <IntPolyh_StartPoint.hpp>
#include <IntPolyh_Triangle.hpp>

#include <cstdio>

IntPolyh_SectionLine::IntPolyh_SectionLine() = default;

IntPolyh_SectionLine::IntPolyh_SectionLine(const int N)
{
  Init(N);
}

void IntPolyh_SectionLine::Init(const int)
{

  if (!mySeqOfSPoints.Length())
    IncrementNbStartPoints();
}

int IntPolyh_SectionLine::GetN() const
{

  return mySeqOfSPoints.Length();
}

int IntPolyh_SectionLine::NbStartPoints() const
{

  return mySeqOfSPoints.Length() - 1;
}

void IntPolyh_SectionLine::IncrementNbStartPoints()
{

  IntPolyh_StartPoint aSP;
  mySeqOfSPoints.Append(aSP);
}

const IntPolyh_StartPoint& IntPolyh_SectionLine::Value(const int Index) const
{
  return mySeqOfSPoints(Index + 1);
}

IntPolyh_StartPoint& IntPolyh_SectionLine::ChangeValue(const int Index)
{
  return mySeqOfSPoints(Index + 1);
}

void IntPolyh_SectionLine::Destroy() {}

IntPolyh_SectionLine& IntPolyh_SectionLine::Copy(const IntPolyh_SectionLine& Other)
{

  mySeqOfSPoints = Other.mySeqOfSPoints;
  return (*this);
}

void IntPolyh_SectionLine::Dump() const
{
  printf("\n SectionLine 0-> %d", NbStartPoints() - 1);
  for (int i = 0; i < NbStartPoints(); i++)
  {

    Value(i).Dump(i);
  }
  printf("\n");
}

void IntPolyh_SectionLine::Prepend(const IntPolyh_StartPoint& SP)
{
  mySeqOfSPoints.Prepend(SP);
}
