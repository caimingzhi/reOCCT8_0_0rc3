#include <TopOpeBRepDS_FaceEdgeInterference.hpp>
#include <TopOpeBRepDS_Kind.hpp>
#include <TopOpeBRepDS_Transition.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TopOpeBRepDS_FaceEdgeInterference, TopOpeBRepDS_ShapeShapeInterference)

TopOpeBRepDS_FaceEdgeInterference::TopOpeBRepDS_FaceEdgeInterference(
  const TopOpeBRepDS_Transition& T,
  const int                      S,
  const int                      G,
  const bool                     GIsBound,
  const TopOpeBRepDS_Config      C)
    : TopOpeBRepDS_ShapeShapeInterference(T,
                                          TopOpeBRepDS_FACE,
                                          S,
                                          TopOpeBRepDS_EDGE,
                                          G,
                                          GIsBound,
                                          C)
{
}
