#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Geom_Curve.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <ShapeUpgrade_SplitCurve.hpp>
class Geom_Curve;

class ShapeUpgrade_SplitCurve3d : public ShapeUpgrade_SplitCurve
{

public:
  Standard_EXPORT ShapeUpgrade_SplitCurve3d();

  Standard_EXPORT void Init(const occ::handle<Geom_Curve>& C);

  Standard_EXPORT void Init(const occ::handle<Geom_Curve>& C,
                            const double                   First,
                            const double                   Last);

  Standard_EXPORT void Build(const bool Segment) override;

  Standard_EXPORT const occ::handle<NCollection_HArray1<occ::handle<Geom_Curve>>>& GetCurves()
    const;

  DEFINE_STANDARD_RTTIEXT(ShapeUpgrade_SplitCurve3d, ShapeUpgrade_SplitCurve)

protected:
  occ::handle<Geom_Curve>                                   myCurve;
  occ::handle<NCollection_HArray1<occ::handle<Geom_Curve>>> myResultingCurves;
};
