#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Geom2d_Curve.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <ShapeUpgrade_SplitCurve2d.hpp>

class ShapeUpgrade_ConvertCurve2dToBezier : public ShapeUpgrade_SplitCurve2d
{

public:
  Standard_EXPORT ShapeUpgrade_ConvertCurve2dToBezier();

  Standard_EXPORT void Compute() override;

  Standard_EXPORT void Build(const bool Segment) override;

  Standard_EXPORT occ::handle<NCollection_HSequence<double>> SplitParams() const;

  DEFINE_STANDARD_RTTIEXT(ShapeUpgrade_ConvertCurve2dToBezier, ShapeUpgrade_SplitCurve2d)

private:
  Standard_EXPORT occ::handle<NCollection_HSequence<occ::handle<Geom2d_Curve>>> Segments() const;

  occ::handle<NCollection_HSequence<occ::handle<Geom2d_Curve>>> mySegments;
  occ::handle<NCollection_HSequence<double>>                    mySplitParams;
};
