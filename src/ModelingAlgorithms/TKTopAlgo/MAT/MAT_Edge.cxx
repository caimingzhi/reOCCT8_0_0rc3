#include <MAT_Bisector.hpp>
#include <MAT_Edge.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(MAT_Edge, Standard_Transient)

MAT_Edge::MAT_Edge()
    : theedgenumber(0),
      thedistance(0.0),
      theintersectionpoint(0)
{
}

void MAT_Edge::EdgeNumber(const int anumber)
{
  theedgenumber = anumber;
}

void MAT_Edge::FirstBisector(const occ::handle<MAT_Bisector>& abisector)
{
  thefirstbisector = abisector;
}

void MAT_Edge::SecondBisector(const occ::handle<MAT_Bisector>& abisector)
{
  thesecondbisector = abisector;
}

void MAT_Edge::Distance(const double adistance)
{
  thedistance = adistance;
}

void MAT_Edge::IntersectionPoint(const int apoint)
{
  theintersectionpoint = apoint;
}

int MAT_Edge::EdgeNumber() const
{
  return theedgenumber;
}

occ::handle<MAT_Bisector> MAT_Edge::FirstBisector() const
{
  return thefirstbisector;
}

occ::handle<MAT_Bisector> MAT_Edge::SecondBisector() const
{
  return thesecondbisector;
}

double MAT_Edge::Distance() const
{
  return thedistance;
}

int MAT_Edge::IntersectionPoint() const
{
  return theintersectionpoint;
}

void MAT_Edge::Dump(const int, const int) const {}
