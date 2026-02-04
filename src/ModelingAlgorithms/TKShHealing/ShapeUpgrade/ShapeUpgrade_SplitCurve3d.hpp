#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Geom_Curve.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <ShapeUpgrade_SplitCurve.hpp>
class Geom_Curve;

//! Splits a 3d curve with a criterion.
class ShapeUpgrade_SplitCurve3d : public ShapeUpgrade_SplitCurve
{

public:
  //! Empty constructor.
  Standard_EXPORT ShapeUpgrade_SplitCurve3d();

  //! Initializes with curve with its first and last parameters.
  Standard_EXPORT void Init(const occ::handle<Geom_Curve>& C);

  //! Initializes with curve with its parameters.
  Standard_EXPORT void Init(const occ::handle<Geom_Curve>& C,
                            const double                   First,
                            const double                   Last);

  //! If Segment is True, the result is composed with
  //! segments of the curve bounded by the SplitValues. If
  //! Segment is False, the result is composed with trimmed
  //! Curves all based on the same complete curve.
  Standard_EXPORT void Build(const bool Segment) override;

  Standard_EXPORT const occ::handle<NCollection_HArray1<occ::handle<Geom_Curve>>>& GetCurves()
    const;

  DEFINE_STANDARD_RTTIEXT(ShapeUpgrade_SplitCurve3d, ShapeUpgrade_SplitCurve)

protected:
  occ::handle<Geom_Curve>                                   myCurve;
  occ::handle<NCollection_HArray1<occ::handle<Geom_Curve>>> myResultingCurves;
};

