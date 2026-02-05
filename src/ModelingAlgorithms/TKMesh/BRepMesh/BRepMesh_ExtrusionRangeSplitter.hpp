#pragma once

#include <BRepMesh_NURBSRangeSplitter.hpp>

//! Auxiliary class analysing extrusion surface in order to generate internal nodes.
class BRepMesh_ExtrusionRangeSplitter : public BRepMesh_NURBSRangeSplitter
{
public:
  //! Constructor.
  BRepMesh_ExtrusionRangeSplitter() = default;

  //! Destructor.
  ~BRepMesh_ExtrusionRangeSplitter() override = default;

protected:
  //! Returns number of intervals computed using available geometrical parameters.
  Standard_EXPORT int getUndefinedIntervalNb(const occ::handle<Adaptor3d_Surface>& theSurface,
                                             const bool                            isU,
                                             const GeomAbs_Shape theContinuity) const override;
};
