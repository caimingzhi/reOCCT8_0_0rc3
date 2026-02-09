#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_Vec.hpp>
#include <NCollection_Array1.hpp>
#include <gp_Mat.hpp>
#include <Standard_Integer.hpp>
class GeomFill_LocationLaw;

class GeomFill_LocFunction
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomFill_LocFunction(const occ::handle<GeomFill_LocationLaw>& Law);

  Standard_EXPORT bool D0(const double Param, const double First, const double Last);

  Standard_EXPORT bool D1(const double Param, const double First, const double Last);

  Standard_EXPORT bool D2(const double Param, const double First, const double Last);

  Standard_EXPORT void DN(const double Param,
                          const double First,
                          const double Last,
                          const int    Order,
                          double&      Result,
                          int&         Ier);

private:
  occ::handle<GeomFill_LocationLaw> myLaw;
  NCollection_Array1<gp_Vec>        V;
  NCollection_Array1<gp_Vec>        DV;
  NCollection_Array1<gp_Vec>        D2V;
  gp_Mat                            M;
  gp_Mat                            DM;
  gp_Mat                            D2M;
};
