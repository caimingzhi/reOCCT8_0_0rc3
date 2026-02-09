#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GC_Root.hpp>
#include <Geom_Ellipse.hpp>

class gp_Elips;
class gp_Ax2;
class gp_Pnt;

class GC_MakeEllipse : public GC_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GC_MakeEllipse(const gp_Elips& E);

  Standard_EXPORT GC_MakeEllipse(const gp_Ax2& A2,
                                 const double  MajorRadius,
                                 const double  MinorRadius);

  Standard_EXPORT GC_MakeEllipse(const gp_Pnt& S1, const gp_Pnt& S2, const gp_Pnt& Center);

  Standard_EXPORT const occ::handle<Geom_Ellipse>& Value() const;

  operator const occ::handle<Geom_Ellipse>&() const { return Value(); }

private:
  occ::handle<Geom_Ellipse> TheEllipse;
};
