#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <ShapeFix_Root.hpp>
class TopoDS_Shape;
class ShapeBuild_ReShape;

class ShapeFix_FixSmallSolid : public ShapeFix_Root
{

public:
  Standard_EXPORT ShapeFix_FixSmallSolid();

  Standard_EXPORT void SetFixMode(const int theMode);

  Standard_EXPORT void SetVolumeThreshold(const double theThreshold = -1.0);

  Standard_EXPORT void SetWidthFactorThreshold(const double theThreshold = -1.0);

  Standard_EXPORT TopoDS_Shape Remove(const TopoDS_Shape&                    theShape,
                                      const occ::handle<ShapeBuild_ReShape>& theContext) const;

  Standard_EXPORT TopoDS_Shape Merge(const TopoDS_Shape&                    theShape,
                                     const occ::handle<ShapeBuild_ReShape>& theContext) const;

  DEFINE_STANDARD_RTTIEXT(ShapeFix_FixSmallSolid, ShapeFix_Root)

private:
  Standard_EXPORT bool IsThresholdsSet() const;

  Standard_EXPORT bool IsSmall(const TopoDS_Shape& theSolid) const;

  Standard_EXPORT bool IsUsedWidthFactorThreshold() const;

  Standard_EXPORT bool IsUsedVolumeThreshold() const;

  int    myFixMode;
  double myVolumeThreshold;
  double myWidthFactorThreshold;
};
