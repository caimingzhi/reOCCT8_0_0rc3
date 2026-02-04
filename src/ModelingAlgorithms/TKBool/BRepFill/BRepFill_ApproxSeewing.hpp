#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <BRepFill_MultiLine.hpp>
class Geom_Curve;
class Geom2d_Curve;

//! Evaluate the 3dCurve and the PCurves described in a MultiLine from BRepFill.
//! The parametrization of those curves is not imposed by the Bissectrice.
//! The parametrization is given approximately by the abscissa of the curve3d.
class BRepFill_ApproxSeewing
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepFill_ApproxSeewing();

  Standard_EXPORT BRepFill_ApproxSeewing(const BRepFill_MultiLine& ML);

  Standard_EXPORT void Perform(const BRepFill_MultiLine& ML);

  Standard_EXPORT bool IsDone() const;

  //! returns the approximation of the 3d Curve
  Standard_EXPORT const occ::handle<Geom_Curve>& Curve() const;

  //! returns the approximation of the PCurve on the
  //! first face of the MultiLine
  Standard_EXPORT const occ::handle<Geom2d_Curve>& CurveOnF1() const;

  //! returns the approximation of the PCurve on the
  //! first face of the MultiLine
  Standard_EXPORT const occ::handle<Geom2d_Curve>& CurveOnF2() const;

private:
  BRepFill_MultiLine        myML;
  bool                      myIsDone;
  occ::handle<Geom_Curve>   myCurve;
  occ::handle<Geom2d_Curve> myPCurve1;
  occ::handle<Geom2d_Curve> myPCurve2;
};

