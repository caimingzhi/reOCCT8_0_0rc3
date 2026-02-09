#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GCE2d_Root.hpp>
#include <Geom2d_Line.hpp>

class gp_Ax2d;
class gp_Lin2d;
class gp_Pnt2d;
class gp_Dir2d;

class GCE2d_MakeLine : public GCE2d_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GCE2d_MakeLine(const gp_Ax2d& A);

  Standard_EXPORT GCE2d_MakeLine(const gp_Lin2d& L);

  Standard_EXPORT GCE2d_MakeLine(const gp_Pnt2d& P, const gp_Dir2d& V);

  Standard_EXPORT GCE2d_MakeLine(const gp_Lin2d& Lin, const gp_Pnt2d& Point);

  Standard_EXPORT GCE2d_MakeLine(const gp_Lin2d& Lin, const double Dist);

  Standard_EXPORT GCE2d_MakeLine(const gp_Pnt2d& P1, const gp_Pnt2d& P2);

  Standard_EXPORT const occ::handle<Geom2d_Line>& Value() const;

  operator const occ::handle<Geom2d_Line>&() const { return Value(); }

private:
  occ::handle<Geom2d_Line> TheLine;
};
