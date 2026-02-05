#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Geom2d_Curve.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <ShapeUpgrade_SplitCurve2d.hpp>

//! converts/splits a 2d curve to a list of beziers
class ShapeUpgrade_ConvertCurve2dToBezier : public ShapeUpgrade_SplitCurve2d
{

public:
  //! Empty constructor.
  Standard_EXPORT ShapeUpgrade_ConvertCurve2dToBezier();

  //! Converts curve into a list of beziers, and stores the
  //! splitting parameters on original curve.
  Standard_EXPORT void Compute() override;

  //! Splits a list of beziers computed by Compute method according
  //! the split values and splitting parameters.
  Standard_EXPORT void Build(const bool Segment) override;

  //! Returns the list of split parameters in original curve parametrisation.
  Standard_EXPORT occ::handle<NCollection_HSequence<double>> SplitParams() const;

  DEFINE_STANDARD_RTTIEXT(ShapeUpgrade_ConvertCurve2dToBezier, ShapeUpgrade_SplitCurve2d)

private:
  //! Returns the list of bezier curves correspondent to original
  //! curve.
  Standard_EXPORT occ::handle<NCollection_HSequence<occ::handle<Geom2d_Curve>>> Segments() const;

  occ::handle<NCollection_HSequence<occ::handle<Geom2d_Curve>>> mySegments;
  occ::handle<NCollection_HSequence<double>>                    mySplitParams;
};
