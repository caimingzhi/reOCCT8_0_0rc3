#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GCE2d_Root.hpp>
#include <Geom2d_TrimmedCurve.hpp>

class gp_Pnt2d;
class gp_Dir2d;
class gp_Lin2d;

class GCE2d_MakeSegment : public GCE2d_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GCE2d_MakeSegment(const gp_Pnt2d& P1, const gp_Pnt2d& P2);

  Standard_EXPORT GCE2d_MakeSegment(const gp_Pnt2d& P1, const gp_Dir2d& V, const gp_Pnt2d& P2);

  Standard_EXPORT GCE2d_MakeSegment(const gp_Lin2d& Line, const double U1, const double U2);

  Standard_EXPORT GCE2d_MakeSegment(const gp_Lin2d& Line,
                                    const gp_Pnt2d& Point,
                                    const double    Ulast);

  Standard_EXPORT GCE2d_MakeSegment(const gp_Lin2d& Line, const gp_Pnt2d& P1, const gp_Pnt2d& P2);

  Standard_EXPORT const occ::handle<Geom2d_TrimmedCurve>& Value() const;

  operator const occ::handle<Geom2d_TrimmedCurve>&() const { return Value(); }

private:
  occ::handle<Geom2d_TrimmedCurve> TheSegment;
};
