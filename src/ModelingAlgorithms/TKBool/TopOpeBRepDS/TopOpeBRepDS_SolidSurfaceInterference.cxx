#include <TopOpeBRepDS_SolidSurfaceInterference.hpp>
#include <TopOpeBRepDS_Transition.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TopOpeBRepDS_SolidSurfaceInterference, TopOpeBRepDS_Interference)

//=================================================================================================

TopOpeBRepDS_SolidSurfaceInterference::TopOpeBRepDS_SolidSurfaceInterference(
  const TopOpeBRepDS_Transition& T,
  const TopOpeBRepDS_Kind        ST,
  const int                      S,
  const TopOpeBRepDS_Kind        GT,
  const int                      G)
    : TopOpeBRepDS_Interference(T, ST, S, GT, G)
{
}
