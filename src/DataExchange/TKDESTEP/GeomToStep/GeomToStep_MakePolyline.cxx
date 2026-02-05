#include <GeomToStep_MakeCartesianPoint.hpp>
#include <GeomToStep_MakePolyline.hpp>
#include <gp_Pnt.hpp>
#include <gp_Pnt2d.hpp>
#include <StdFail_NotDone.hpp>
#include <StepData_Factors.hpp>
#include <StepGeom_Polyline.hpp>
#include <NCollection_Array1.hpp>
#include <TCollection_HAsciiString.hpp>

//=============================================================================
// Creation d' une polyline Step a partir d' une Array1OfPnt
//=============================================================================
GeomToStep_MakePolyline::GeomToStep_MakePolyline(const NCollection_Array1<gp_Pnt>& P,
                                                 const StepData_Factors&           theLocalFactors)
{
  gp_Pnt P1;
#include "GeomToStep_MakePolyline_gen.hpp"
}

//=============================================================================
// Creation d' une polyline Step a partir d' une Array1OfPnt2d
//=============================================================================

GeomToStep_MakePolyline::GeomToStep_MakePolyline(const NCollection_Array1<gp_Pnt2d>& P,
                                                 const StepData_Factors& theLocalFactors)
{
  gp_Pnt2d P1;
#include "GeomToStep_MakePolyline_gen.hpp"
}

//=============================================================================
// renvoi des valeurs
//=============================================================================

const occ::handle<StepGeom_Polyline>& GeomToStep_MakePolyline::Value() const
{
  StdFail_NotDone_Raise_if(!done, "GeomToStep_MakePolyline::Value() - no result");
  return thePolyline;
}
