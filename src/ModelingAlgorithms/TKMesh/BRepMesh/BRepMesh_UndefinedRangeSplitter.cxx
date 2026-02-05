#include <BRepMesh_UndefinedRangeSplitter.hpp>

//=================================================================================================

int BRepMesh_UndefinedRangeSplitter::getUndefinedIntervalNb(
  const occ::handle<Adaptor3d_Surface>& /*theSurface*/,
  const bool /*isU*/,
  const GeomAbs_Shape /*theContinuity*/) const
{
  return 1;
}
