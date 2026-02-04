#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Standard_Integer.hpp>
class Geom2dAdaptor_Curve;
class gp_Pnt2d;
class gp_Vec2d;

class Geom2dGcc_CurveTool
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static double FirstParameter(const Geom2dAdaptor_Curve& C);

  Standard_EXPORT static double LastParameter(const Geom2dAdaptor_Curve& C);

  Standard_EXPORT static double EpsX(const Geom2dAdaptor_Curve& C, const double Tol);

  Standard_EXPORT static int NbSamples(const Geom2dAdaptor_Curve& C);

  Standard_EXPORT static gp_Pnt2d Value(const Geom2dAdaptor_Curve& C, const double X);

  Standard_EXPORT static void D1(const Geom2dAdaptor_Curve& C,
                                 const double               U,
                                 gp_Pnt2d&                  P,
                                 gp_Vec2d&                  T);

  Standard_EXPORT static void D2(const Geom2dAdaptor_Curve& C,
                                 const double               U,
                                 gp_Pnt2d&                  P,
                                 gp_Vec2d&                  T,
                                 gp_Vec2d&                  N);

  Standard_EXPORT static void D3(const Geom2dAdaptor_Curve& C,
                                 const double               U,
                                 gp_Pnt2d&                  P,
                                 gp_Vec2d&                  T,
                                 gp_Vec2d&                  N,
                                 gp_Vec2d&                  dN);
};

