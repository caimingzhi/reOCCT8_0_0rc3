#include <Geom2d_BSplineCurve.hpp>
#include <Geom_BSplineCurve.hpp>
#include <GeomAbs_BSplKnotDistribution.hpp>
#include <GeomToStep_MakeBSplineCurveWithKnotsAndRationalBSplineCurve.hpp>
#include <GeomToStep_MakeCartesianPoint.hpp>
#include <StdFail_NotDone.hpp>
#include <StepData_Factors.hpp>
#include <StepGeom_BSplineCurveWithKnotsAndRationalBSplineCurve.hpp>
#include <StepGeom_CartesianPoint.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepGeom_KnotType.hpp>
#include <gp_Pnt.hpp>
#include <gp_Pnt2d.hpp>
#include <TCollection_HAsciiString.hpp>
#include <Standard_Integer.hpp>

GeomToStep_MakeBSplineCurveWithKnotsAndRationalBSplineCurve::
  GeomToStep_MakeBSplineCurveWithKnotsAndRationalBSplineCurve(
    const occ::handle<Geom_BSplineCurve>& BS,
    const StepData_Factors&               theLocalFactors)
{
#define Array1OfPnt_gen NCollection_Array1<gp_Pnt>
#include "GeomToStep_MakeBSplineCurveWithKnotsAndRationalBSplineCurve_gen.hpp"
#undef Array1OfPnt_gen
}

GeomToStep_MakeBSplineCurveWithKnotsAndRationalBSplineCurve::
  GeomToStep_MakeBSplineCurveWithKnotsAndRationalBSplineCurve(
    const occ::handle<Geom2d_BSplineCurve>& BS,
    const StepData_Factors&                 theLocalFactors)

{
#define Array1OfPnt_gen NCollection_Array1<gp_Pnt2d>
#include "GeomToStep_MakeBSplineCurveWithKnotsAndRationalBSplineCurve_gen.hpp"
#undef Array1OfPnt_gen
}

const occ::handle<StepGeom_BSplineCurveWithKnotsAndRationalBSplineCurve>&
  GeomToStep_MakeBSplineCurveWithKnotsAndRationalBSplineCurve::Value() const
{
  StdFail_NotDone_Raise_if(
    !done,
    "GeomToStep_MakeBSplineCurveWithKnotsAndRationalBSplineCurve::Value() - no result");
  return theBSplineCurveWithKnotsAndRationalBSplineCurve;
}
