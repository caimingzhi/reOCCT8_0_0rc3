#include <IntTools_Range.hpp>

//=================================================================================================

IntTools_Range::IntTools_Range()
    : myFirst(0.),
      myLast(0.)
{
}

//=================================================================================================

IntTools_Range::IntTools_Range(const double aFirst, const double aLast)
{
  myFirst = aFirst;
  myLast  = aLast;
}

//=================================================================================================

void IntTools_Range::SetFirst(const double aFirst)
{
  myFirst = aFirst;
}

//=================================================================================================

void IntTools_Range::SetLast(const double aLast)
{
  myLast = aLast;
}

//=================================================================================================

double IntTools_Range::First() const
{
  return myFirst;
}

//=================================================================================================

double IntTools_Range::Last() const
{
  return myLast;
}

//=================================================================================================

void IntTools_Range::Range(double& aFirst, double& aLast) const
{
  aFirst = myFirst;
  aLast  = myLast;
}
