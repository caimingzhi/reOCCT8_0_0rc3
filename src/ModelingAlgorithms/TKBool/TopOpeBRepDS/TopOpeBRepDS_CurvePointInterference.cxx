#include <TopOpeBRepDS_CurvePointInterference.hpp>
#include <TopOpeBRepDS_Transition.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TopOpeBRepDS_CurvePointInterference, TopOpeBRepDS_Interference)

TopOpeBRepDS_CurvePointInterference::TopOpeBRepDS_CurvePointInterference(
  const TopOpeBRepDS_Transition& T,
  const TopOpeBRepDS_Kind        ST,
  const int                      S,
  const TopOpeBRepDS_Kind        GT,
  const int                      G,
  const double                   P)
    : TopOpeBRepDS_Interference(T, ST, S, GT, G),
      myParam(P)
{
}

double TopOpeBRepDS_CurvePointInterference::Parameter() const
{
  return myParam;
}

void TopOpeBRepDS_CurvePointInterference::Parameter(const double P)
{
  myParam = P;
}
