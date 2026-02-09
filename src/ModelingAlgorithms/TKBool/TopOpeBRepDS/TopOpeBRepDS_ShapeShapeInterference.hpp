#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TopOpeBRepDS_Config.hpp>
#include <TopOpeBRepDS_Interference.hpp>
#include <TopOpeBRepDS_Kind.hpp>
#include <Standard_Integer.hpp>
#include <Standard_OStream.hpp>
class TopOpeBRepDS_Transition;

class TopOpeBRepDS_ShapeShapeInterference : public TopOpeBRepDS_Interference
{

public:
  Standard_EXPORT TopOpeBRepDS_ShapeShapeInterference(const TopOpeBRepDS_Transition& T,
                                                      const TopOpeBRepDS_Kind        ST,
                                                      const int                      S,
                                                      const TopOpeBRepDS_Kind        GT,
                                                      const int                      G,
                                                      const bool                     GBound,
                                                      const TopOpeBRepDS_Config      C);

  Standard_EXPORT TopOpeBRepDS_Config Config() const;

  Standard_EXPORT bool GBound() const;

  Standard_EXPORT void SetGBound(const bool b);

  DEFINE_STANDARD_RTTIEXT(TopOpeBRepDS_ShapeShapeInterference, TopOpeBRepDS_Interference)

private:
  bool                myGBound;
  TopOpeBRepDS_Config myC;
};
