#include <TopOpeBRepDS_Surface.hpp>
#include <TopOpeBRepDS_SurfaceData.hpp>

TopOpeBRepDS_SurfaceData::TopOpeBRepDS_SurfaceData() = default;

TopOpeBRepDS_SurfaceData::TopOpeBRepDS_SurfaceData(const TopOpeBRepDS_Surface& S)
    : mySurface(S)
{
}
