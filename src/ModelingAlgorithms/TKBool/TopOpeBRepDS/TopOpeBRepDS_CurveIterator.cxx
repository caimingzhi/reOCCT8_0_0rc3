#include <Geom2d_Curve.hpp>
#include <TopOpeBRepDS_CurveIterator.hpp>
#include <TopOpeBRepDS_Interference.hpp>
#include <TopOpeBRepDS_SurfaceCurveInterference.hpp>

TopOpeBRepDS_CurveIterator::TopOpeBRepDS_CurveIterator(
  const NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& L)
    : TopOpeBRepDS_InterferenceIterator(L)
{
  Match();
}

bool TopOpeBRepDS_CurveIterator::MatchInterference(
  const occ::handle<TopOpeBRepDS_Interference>& I) const
{
  TopOpeBRepDS_Kind GT = I->GeometryType();
  bool              r  = (GT == TopOpeBRepDS_CURVE);
  return r;
}

int TopOpeBRepDS_CurveIterator::Current() const
{
  occ::handle<TopOpeBRepDS_Interference> I = Value();
  int                                    G = I->Geometry();
  return G;
}

TopAbs_Orientation TopOpeBRepDS_CurveIterator::Orientation(const TopAbs_State S) const
{
  occ::handle<TopOpeBRepDS_Interference> I = Value();
  const TopOpeBRepDS_Transition&         T = I->Transition();
  TopAbs_Orientation                     o = T.Orientation(S);
  return o;
}

const occ::handle<Geom2d_Curve>& TopOpeBRepDS_CurveIterator::PCurve() const
{
  return (*((occ::handle<TopOpeBRepDS_SurfaceCurveInterference>*)&Value()))->PCurve();
}
