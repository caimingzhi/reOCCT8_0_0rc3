#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GC_Root.hpp>
#include <Geom_Line.hpp>

class gp_Ax1;
class gp_Lin;
class gp_Pnt;
class gp_Dir;

class GC_MakeLine : public GC_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GC_MakeLine(const gp_Ax1& A1);

  Standard_EXPORT GC_MakeLine(const gp_Lin& L);

  Standard_EXPORT GC_MakeLine(const gp_Pnt& P, const gp_Dir& V);

  Standard_EXPORT GC_MakeLine(const gp_Lin& Lin, const gp_Pnt& Point);

  Standard_EXPORT GC_MakeLine(const gp_Pnt& P1, const gp_Pnt& P2);

  Standard_EXPORT const occ::handle<Geom_Line>& Value() const;

  operator const occ::handle<Geom_Line>&() const { return Value(); }

private:
  occ::handle<Geom_Line> TheLine;
};
