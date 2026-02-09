#include <StepGeom_CartesianPoint.hpp>
#include <StepToTopoDS_PointPair.hpp>

StepToTopoDS_PointPair::StepToTopoDS_PointPair(const occ::handle<StepGeom_CartesianPoint>& P1,
                                               const occ::handle<StepGeom_CartesianPoint>& P2)
    : myP1(P1),
      myP2(P2)
{
}
