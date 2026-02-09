#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GC_Root.hpp>
#include <Geom_TrimmedCurve.hpp>

class gp_Pnt;
class gp_Lin;

class GC_MakeSegment : public GC_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GC_MakeSegment(const gp_Pnt& P1, const gp_Pnt& P2);

  Standard_EXPORT GC_MakeSegment(const gp_Lin& Line, const double U1, const double U2);

  Standard_EXPORT GC_MakeSegment(const gp_Lin& Line, const gp_Pnt& Point, const double Ulast);

  Standard_EXPORT GC_MakeSegment(const gp_Lin& Line, const gp_Pnt& P1, const gp_Pnt& P2);

  Standard_EXPORT const occ::handle<Geom_TrimmedCurve>& Value() const;

  operator const occ::handle<Geom_TrimmedCurve>&() const { return Value(); }

private:
  occ::handle<Geom_TrimmedCurve> TheSegment;
};
