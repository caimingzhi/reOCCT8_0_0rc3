#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
class Geom_Curve;
class gp_Pnt;
class gp_Vec;

class GeomLProp_CurveTool
{
public:
  DEFINE_STANDARD_ALLOC

  //! Computes the point <P> of parameter <U> on the curve <C>.
  Standard_EXPORT static void Value(const occ::handle<Geom_Curve>& C, const double U, gp_Pnt& P);

  //! Computes the point <P> and first derivative <V1> of
  //! parameter <U> on the curve <C>.
  Standard_EXPORT static void D1(const occ::handle<Geom_Curve>& C,
                                 const double                   U,
                                 gp_Pnt&                        P,
                                 gp_Vec&                        V1);

  //! Computes the point <P>, the first derivative <V1> and second
  //! derivative <V2> of parameter <U> on the curve <C>.
  Standard_EXPORT static void D2(const occ::handle<Geom_Curve>& C,
                                 const double                   U,
                                 gp_Pnt&                        P,
                                 gp_Vec&                        V1,
                                 gp_Vec&                        V2);

  //! Computes the point <P>, the first derivative <V1>, the
  //! second derivative <V2> and third derivative <V3> of
  //! parameter <U> on the curve <C>.
  Standard_EXPORT static void D3(const occ::handle<Geom_Curve>& C,
                                 const double                   U,
                                 gp_Pnt&                        P,
                                 gp_Vec&                        V1,
                                 gp_Vec&                        V2,
                                 gp_Vec&                        V3);

  //! returns the order of continuity of the curve <C>.
  //! returns 1 : first derivative only is computable
  //! returns 2 : first and second derivative only are computable.
  //! returns 3 : first, second and third are computable.
  Standard_EXPORT static int Continuity(const occ::handle<Geom_Curve>& C);

  //! returns the first parameter bound of the curve.
  Standard_EXPORT static double FirstParameter(const occ::handle<Geom_Curve>& C);

  //! returns the last parameter bound of the curve.
  //! FirstParameter must be less than LastParamenter.
  Standard_EXPORT static double LastParameter(const occ::handle<Geom_Curve>& C);
};

