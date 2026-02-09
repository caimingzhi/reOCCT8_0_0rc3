#include <TopOpeBRepDS.hpp>
#include <TopOpeBRepDS_ShapeShapeInterference.hpp>
#include <TopOpeBRepDS_Transition.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TopOpeBRepDS_ShapeShapeInterference, TopOpeBRepDS_Interference)

TopOpeBRepDS_ShapeShapeInterference::TopOpeBRepDS_ShapeShapeInterference(
  const TopOpeBRepDS_Transition& T,
  const TopOpeBRepDS_Kind        ST,
  const int                      S,
  const TopOpeBRepDS_Kind        GT,
  const int                      G,
  const bool                     GBound,
  const TopOpeBRepDS_Config      C)
    : TopOpeBRepDS_Interference(T, ST, S, GT, G),
      myGBound(GBound),
      myC(C)
{
}

TopOpeBRepDS_Config TopOpeBRepDS_ShapeShapeInterference::Config() const
{
  return myC;
}

bool TopOpeBRepDS_ShapeShapeInterference::GBound() const
{
  return myGBound;
}

void TopOpeBRepDS_ShapeShapeInterference::SetGBound(const bool b)
{
  myGBound = b;
}
