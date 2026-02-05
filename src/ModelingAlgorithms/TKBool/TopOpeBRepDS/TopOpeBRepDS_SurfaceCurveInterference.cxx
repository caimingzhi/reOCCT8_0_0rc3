#include <Geom2d_Curve.hpp>
#include <Standard_Type.hpp>
#include <TopOpeBRepDS_SurfaceCurveInterference.hpp>
#include <TopOpeBRepDS_Transition.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TopOpeBRepDS_SurfaceCurveInterference, TopOpeBRepDS_Interference)

//=================================================================================================

TopOpeBRepDS_SurfaceCurveInterference::TopOpeBRepDS_SurfaceCurveInterference() = default;

//=================================================================================================

TopOpeBRepDS_SurfaceCurveInterference::TopOpeBRepDS_SurfaceCurveInterference(
  const TopOpeBRepDS_Transition&   T,
  const TopOpeBRepDS_Kind          ST,
  const int                        S,
  const TopOpeBRepDS_Kind          GT,
  const int                        G,
  const occ::handle<Geom2d_Curve>& PC)
    : TopOpeBRepDS_Interference(T, ST, S, GT, G),
      myPCurve(PC)
{
}

//=================================================================================================

TopOpeBRepDS_SurfaceCurveInterference::TopOpeBRepDS_SurfaceCurveInterference(
  const occ::handle<TopOpeBRepDS_Interference>& I)
    : TopOpeBRepDS_Interference(I)
{
}

//=================================================================================================

const occ::handle<Geom2d_Curve>& TopOpeBRepDS_SurfaceCurveInterference::PCurve() const
{
  return myPCurve;
}

//=================================================================================================

void TopOpeBRepDS_SurfaceCurveInterference::PCurve(const occ::handle<Geom2d_Curve>& PC)
{
  myPCurve = PC;
}
