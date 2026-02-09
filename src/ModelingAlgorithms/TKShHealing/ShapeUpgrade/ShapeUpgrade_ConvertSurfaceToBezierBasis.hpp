#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <ShapeUpgrade_SplitSurface.hpp>
class ShapeExtend_CompositeSurface;

class ShapeUpgrade_ConvertSurfaceToBezierBasis : public ShapeUpgrade_SplitSurface
{

public:
  Standard_EXPORT ShapeUpgrade_ConvertSurfaceToBezierBasis();

  Standard_EXPORT void Build(const bool Segment) override;

  Standard_EXPORT void Compute(const bool Segment) override;

  Standard_EXPORT occ::handle<ShapeExtend_CompositeSurface> Segments() const;

  void SetPlaneMode(const bool mode);

  bool GetPlaneMode() const;

  void SetRevolutionMode(const bool mode);

  bool GetRevolutionMode() const;

  void SetExtrusionMode(const bool mode);

  bool GetExtrusionMode() const;

  void SetBSplineMode(const bool mode);

  bool GetBSplineMode() const;

  DEFINE_STANDARD_RTTIEXT(ShapeUpgrade_ConvertSurfaceToBezierBasis, ShapeUpgrade_SplitSurface)

private:
  occ::handle<ShapeExtend_CompositeSurface> mySegments;
  bool                                      myPlaneMode;
  bool                                      myRevolutionMode;
  bool                                      myExtrusionMode;
  bool                                      myBSplineMode;
};

inline void ShapeUpgrade_ConvertSurfaceToBezierBasis::SetPlaneMode(const bool mode)
{
  myPlaneMode = mode;
}

inline bool ShapeUpgrade_ConvertSurfaceToBezierBasis::GetPlaneMode() const
{
  return myPlaneMode;
}

inline void ShapeUpgrade_ConvertSurfaceToBezierBasis::SetRevolutionMode(const bool mode)
{
  myRevolutionMode = mode;
}

inline bool ShapeUpgrade_ConvertSurfaceToBezierBasis::GetRevolutionMode() const
{
  return myRevolutionMode;
}

inline void ShapeUpgrade_ConvertSurfaceToBezierBasis::SetExtrusionMode(const bool mode)
{
  myExtrusionMode = mode;
}

inline bool ShapeUpgrade_ConvertSurfaceToBezierBasis::GetExtrusionMode() const
{
  return myExtrusionMode;
}

inline void ShapeUpgrade_ConvertSurfaceToBezierBasis::SetBSplineMode(const bool mode)
{
  myBSplineMode = mode;
}

inline bool ShapeUpgrade_ConvertSurfaceToBezierBasis::GetBSplineMode() const
{
  return myBSplineMode;
}
