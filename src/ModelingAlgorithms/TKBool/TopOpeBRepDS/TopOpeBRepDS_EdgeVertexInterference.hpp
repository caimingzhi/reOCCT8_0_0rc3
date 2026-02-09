#pragma once

#include <Standard.hpp>

#include <Standard_Real.hpp>
#include <TopOpeBRepDS_ShapeShapeInterference.hpp>
#include <TopOpeBRepDS_Kind.hpp>
#include <Standard_Integer.hpp>
#include <Standard_Boolean.hpp>
#include <TopOpeBRepDS_Config.hpp>
#include <Standard_OStream.hpp>
class TopOpeBRepDS_Transition;

class TopOpeBRepDS_EdgeVertexInterference : public TopOpeBRepDS_ShapeShapeInterference
{

public:
  Standard_EXPORT TopOpeBRepDS_EdgeVertexInterference(const TopOpeBRepDS_Transition& T,
                                                      const TopOpeBRepDS_Kind        ST,
                                                      const int                      S,
                                                      const int                      G,
                                                      const bool                     GIsBound,
                                                      const TopOpeBRepDS_Config      C,
                                                      const double                   P);

  Standard_EXPORT TopOpeBRepDS_EdgeVertexInterference(const TopOpeBRepDS_Transition& T,
                                                      const int                      S,
                                                      const int                      G,
                                                      const bool                     GIsBound,
                                                      const TopOpeBRepDS_Config      C,
                                                      const double                   P);

  Standard_EXPORT double Parameter() const;

  Standard_EXPORT void Parameter(const double P);

  DEFINE_STANDARD_RTTIEXT(TopOpeBRepDS_EdgeVertexInterference, TopOpeBRepDS_ShapeShapeInterference)

private:
  double myParam;
};
