#include <BRepMesh_UndefinedRangeSplitter.hpp>

int BRepMesh_UndefinedRangeSplitter::getUndefinedIntervalNb(const occ::handle<Adaptor3d_Surface>&,
                                                            const bool,
                                                            const GeomAbs_Shape) const
{
  return 1;
}
