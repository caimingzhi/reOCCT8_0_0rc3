#pragma once


#include <BRepMesh_NURBSRangeSplitter.hpp>

//! Auxiliary class provides safe value for surfaces that looks like NURBS
//! but has no poles or other characteristics.
class BRepMesh_UndefinedRangeSplitter : public BRepMesh_NURBSRangeSplitter
{
public:
  //! Constructor.
  BRepMesh_UndefinedRangeSplitter() = default;

  //! Destructor.
  ~BRepMesh_UndefinedRangeSplitter() override = default;

protected:
  //! Returns number of intervals computed using available geometrical parameters.
  Standard_EXPORT int getUndefinedIntervalNb(const occ::handle<Adaptor3d_Surface>& theSurface,
                                             const bool                            isU,
                                             const GeomAbs_Shape theContinuity) const override;
};

