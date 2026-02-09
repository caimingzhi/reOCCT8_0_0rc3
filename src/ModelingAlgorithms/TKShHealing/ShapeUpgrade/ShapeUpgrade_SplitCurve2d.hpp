#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Geom2d_Curve.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <ShapeUpgrade_SplitCurve.hpp>
class Geom2d_Curve;

class ShapeUpgrade_SplitCurve2d : public ShapeUpgrade_SplitCurve
{

public:
  Standard_EXPORT ShapeUpgrade_SplitCurve2d();

  Standard_EXPORT void Init(const occ::handle<Geom2d_Curve>& C);

  Standard_EXPORT void Init(const occ::handle<Geom2d_Curve>& C,
                            const double                     First,
                            const double                     Last);

  Standard_EXPORT void Build(const bool Segment) override;

  Standard_EXPORT const occ::handle<NCollection_HArray1<occ::handle<Geom2d_Curve>>>& GetCurves()
    const;

  DEFINE_STANDARD_RTTIEXT(ShapeUpgrade_SplitCurve2d, ShapeUpgrade_SplitCurve)

protected:
  occ::handle<Geom2d_Curve>                                   myCurve;
  occ::handle<NCollection_HArray1<occ::handle<Geom2d_Curve>>> myResultingCurves;
};
