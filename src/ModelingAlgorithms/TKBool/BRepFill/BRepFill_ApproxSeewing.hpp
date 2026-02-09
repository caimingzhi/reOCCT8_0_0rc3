#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <BRepFill_MultiLine.hpp>
class Geom_Curve;
class Geom2d_Curve;

class BRepFill_ApproxSeewing
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepFill_ApproxSeewing();

  Standard_EXPORT BRepFill_ApproxSeewing(const BRepFill_MultiLine& ML);

  Standard_EXPORT void Perform(const BRepFill_MultiLine& ML);

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT const occ::handle<Geom_Curve>& Curve() const;

  Standard_EXPORT const occ::handle<Geom2d_Curve>& CurveOnF1() const;

  Standard_EXPORT const occ::handle<Geom2d_Curve>& CurveOnF2() const;

private:
  BRepFill_MultiLine        myML;
  bool                      myIsDone;
  occ::handle<Geom_Curve>   myCurve;
  occ::handle<Geom2d_Curve> myPCurve1;
  occ::handle<Geom2d_Curve> myPCurve2;
};
