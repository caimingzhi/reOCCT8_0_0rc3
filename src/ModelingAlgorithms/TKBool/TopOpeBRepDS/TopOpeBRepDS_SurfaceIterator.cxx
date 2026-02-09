#include <TopOpeBRepDS_SurfaceIterator.hpp>

TopOpeBRepDS_SurfaceIterator::TopOpeBRepDS_SurfaceIterator(
  const NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& L)
    : TopOpeBRepDS_InterferenceIterator(L)
{
  TopOpeBRepDS_InterferenceIterator::GeometryKind(TopOpeBRepDS_SURFACE);
}

int TopOpeBRepDS_SurfaceIterator::Current() const
{
  occ::handle<TopOpeBRepDS_Interference> i = Value();
  int                                    g = i->Geometry();
  return g;
}

TopAbs_Orientation TopOpeBRepDS_SurfaceIterator::Orientation(const TopAbs_State S) const
{
  occ::handle<TopOpeBRepDS_Interference> i = Value();
  const TopOpeBRepDS_Transition&         t = i->Transition();
  TopAbs_Orientation                     o = t.Orientation(S);
  return o;
}
