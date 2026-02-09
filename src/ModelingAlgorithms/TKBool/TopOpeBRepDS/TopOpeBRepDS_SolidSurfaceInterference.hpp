#pragma once

#include <Standard.hpp>

#include <TopOpeBRepDS_Interference.hpp>
#include <TopOpeBRepDS_Kind.hpp>
#include <Standard_Integer.hpp>
#include <Standard_OStream.hpp>
class TopOpeBRepDS_Transition;

class TopOpeBRepDS_SolidSurfaceInterference : public TopOpeBRepDS_Interference
{

public:
  Standard_EXPORT TopOpeBRepDS_SolidSurfaceInterference(const TopOpeBRepDS_Transition& Transition,
                                                        const TopOpeBRepDS_Kind        SupportType,
                                                        const int                      Support,
                                                        const TopOpeBRepDS_Kind        GeometryType,
                                                        const int                      Geometry);

  DEFINE_STANDARD_RTTIEXT(TopOpeBRepDS_SolidSurfaceInterference, TopOpeBRepDS_Interference)
};
