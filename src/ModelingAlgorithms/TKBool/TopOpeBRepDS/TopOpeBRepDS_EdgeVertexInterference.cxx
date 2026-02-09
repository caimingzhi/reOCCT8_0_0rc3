#include <TopOpeBRepDS_EdgeVertexInterference.hpp>
#include <TopOpeBRepDS_Kind.hpp>
#include <TopOpeBRepDS_Transition.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TopOpeBRepDS_EdgeVertexInterference, TopOpeBRepDS_ShapeShapeInterference)

TopOpeBRepDS_EdgeVertexInterference::TopOpeBRepDS_EdgeVertexInterference(
  const TopOpeBRepDS_Transition& T,
  const TopOpeBRepDS_Kind        ST,
  const int                      S,
  const int                      G,
  const bool                     GIsBound,
  const TopOpeBRepDS_Config      C,
  const double                   P)
    : TopOpeBRepDS_ShapeShapeInterference(T, ST, S, TopOpeBRepDS_VERTEX, G, GIsBound, C),
      myParam(P)
{
}

TopOpeBRepDS_EdgeVertexInterference::TopOpeBRepDS_EdgeVertexInterference(
  const TopOpeBRepDS_Transition& T,
  const int                      S,
  const int                      G,
  const bool                     GIsBound,
  const TopOpeBRepDS_Config      C,
  const double                   P)
    : TopOpeBRepDS_ShapeShapeInterference(T,
                                          TopOpeBRepDS_EDGE,
                                          S,
                                          TopOpeBRepDS_VERTEX,
                                          G,
                                          GIsBound,
                                          C),
      myParam(P)
{
}

double TopOpeBRepDS_EdgeVertexInterference::Parameter() const
{
  return myParam;
}

void TopOpeBRepDS_EdgeVertexInterference::Parameter(const double P)
{
  myParam = P;
}
