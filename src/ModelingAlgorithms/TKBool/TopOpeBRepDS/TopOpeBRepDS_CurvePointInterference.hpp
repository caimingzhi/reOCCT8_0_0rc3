#pragma once

#include <Standard.hpp>

#include <Standard_Real.hpp>
#include <TopOpeBRepDS_Interference.hpp>
#include <TopOpeBRepDS_Kind.hpp>
#include <Standard_Integer.hpp>
#include <Standard_OStream.hpp>
class TopOpeBRepDS_Transition;

//! An interference with a parameter.
class TopOpeBRepDS_CurvePointInterference : public TopOpeBRepDS_Interference
{

public:
  Standard_EXPORT TopOpeBRepDS_CurvePointInterference(const TopOpeBRepDS_Transition& T,
                                                      const TopOpeBRepDS_Kind        ST,
                                                      const int                      S,
                                                      const TopOpeBRepDS_Kind        GT,
                                                      const int                      G,
                                                      const double                   P);

  Standard_EXPORT double Parameter() const;

  Standard_EXPORT void Parameter(const double P);

  DEFINE_STANDARD_RTTIEXT(TopOpeBRepDS_CurvePointInterference, TopOpeBRepDS_Interference)

private:
  double myParam;
};
