#pragma once

#include <BRepMesh_NURBSRangeSplitter.hpp>

class BRepMesh_ExtrusionRangeSplitter : public BRepMesh_NURBSRangeSplitter
{
public:
  BRepMesh_ExtrusionRangeSplitter() = default;

  ~BRepMesh_ExtrusionRangeSplitter() override = default;

protected:
  Standard_EXPORT int getUndefinedIntervalNb(const occ::handle<Adaptor3d_Surface>& theSurface,
                                             const bool                            isU,
                                             const GeomAbs_Shape theContinuity) const override;
};
