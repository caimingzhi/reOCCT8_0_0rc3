#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TopOpeBRepDS_Interference.hpp>
#include <TopOpeBRepDS_Kind.hpp>
#include <Standard_Integer.hpp>
class Geom2d_Curve;
class TopOpeBRepDS_Transition;

class TopOpeBRepDS_SurfaceCurveInterference : public TopOpeBRepDS_Interference
{

public:
  Standard_EXPORT TopOpeBRepDS_SurfaceCurveInterference();

  Standard_EXPORT TopOpeBRepDS_SurfaceCurveInterference(const TopOpeBRepDS_Transition& Transition,
                                                        const TopOpeBRepDS_Kind        SupportType,
                                                        const int                      Support,
                                                        const TopOpeBRepDS_Kind        GeometryType,
                                                        const int                      Geometry,
                                                        const occ::handle<Geom2d_Curve>& PC);

  Standard_EXPORT TopOpeBRepDS_SurfaceCurveInterference(
    const occ::handle<TopOpeBRepDS_Interference>& I);

  Standard_EXPORT const occ::handle<Geom2d_Curve>& PCurve() const;

  Standard_EXPORT void PCurve(const occ::handle<Geom2d_Curve>& PC);

  DEFINE_STANDARD_RTTIEXT(TopOpeBRepDS_SurfaceCurveInterference, TopOpeBRepDS_Interference)

private:
  occ::handle<Geom2d_Curve> myPCurve;
};
