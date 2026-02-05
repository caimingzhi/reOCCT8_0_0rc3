#pragma once

#include <Standard.hpp>

#include <TopOpeBRepDS_ShapeShapeInterference.hpp>
#include <Standard_Integer.hpp>
#include <Standard_Boolean.hpp>
#include <TopOpeBRepDS_Config.hpp>
#include <Standard_OStream.hpp>
class TopOpeBRepDS_Transition;

//! ShapeShapeInterference
class TopOpeBRepDS_FaceEdgeInterference : public TopOpeBRepDS_ShapeShapeInterference
{

public:
  //! Create an interference of EDGE <G> on FACE <S>.
  Standard_EXPORT TopOpeBRepDS_FaceEdgeInterference(const TopOpeBRepDS_Transition& T,
                                                    const int                      S,
                                                    const int                      G,
                                                    const bool                     GIsBound,
                                                    const TopOpeBRepDS_Config      C);

  DEFINE_STANDARD_RTTIEXT(TopOpeBRepDS_FaceEdgeInterference, TopOpeBRepDS_ShapeShapeInterference)
};
