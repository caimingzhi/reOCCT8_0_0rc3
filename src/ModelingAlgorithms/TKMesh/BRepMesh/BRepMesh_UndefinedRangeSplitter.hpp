#pragma once

#include <BRepMesh_NURBSRangeSplitter.hpp>

class BRepMesh_UndefinedRangeSplitter : public BRepMesh_NURBSRangeSplitter
{
public:
  BRepMesh_UndefinedRangeSplitter() = default;

  ~BRepMesh_UndefinedRangeSplitter() override = default;

protected:
  Standard_EXPORT int getUndefinedIntervalNb(const occ::handle<Adaptor3d_Surface>& theSurface,
                                             const bool                            isU,
                                             const GeomAbs_Shape theContinuity) const override;
};
