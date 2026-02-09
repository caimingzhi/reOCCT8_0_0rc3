#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <gp_Pnt.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Integer.hpp>
class GeomFill_Boundary;
class Law_Function;
class gp_Vec;

class GeomFill_CoonsAlgPatch : public Standard_Transient
{

public:
  Standard_EXPORT GeomFill_CoonsAlgPatch(const occ::handle<GeomFill_Boundary>& B1,
                                         const occ::handle<GeomFill_Boundary>& B2,
                                         const occ::handle<GeomFill_Boundary>& B3,
                                         const occ::handle<GeomFill_Boundary>& B4);

  Standard_EXPORT void Func(occ::handle<Law_Function>& f1, occ::handle<Law_Function>& f2) const;

  Standard_EXPORT void SetFunc(const occ::handle<Law_Function>& f1,
                               const occ::handle<Law_Function>& f2);

  Standard_EXPORT gp_Pnt Value(const double U, const double V) const;

  Standard_EXPORT gp_Vec D1U(const double U, const double V) const;

  Standard_EXPORT gp_Vec D1V(const double U, const double V) const;

  Standard_EXPORT gp_Vec DUV(const double U, const double V) const;

  Standard_EXPORT const gp_Pnt& Corner(const int I) const;

  Standard_EXPORT const occ::handle<GeomFill_Boundary>& Bound(const int I) const;

  Standard_EXPORT const occ::handle<Law_Function>& Func(const int I) const;

  DEFINE_STANDARD_RTTIEXT(GeomFill_CoonsAlgPatch, Standard_Transient)

private:
  occ::handle<GeomFill_Boundary> bound[4];
  gp_Pnt                         c[4];
  occ::handle<Law_Function>      a[2];
};
