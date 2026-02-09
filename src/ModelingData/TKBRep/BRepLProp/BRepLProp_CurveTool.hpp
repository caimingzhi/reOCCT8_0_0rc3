#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Standard_Integer.hpp>
class BRepAdaptor_Curve;
class gp_Pnt;
class gp_Vec;

class BRepLProp_CurveTool
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void Value(const BRepAdaptor_Curve& C, const double U, gp_Pnt& P);

  Standard_EXPORT static void D1(const BRepAdaptor_Curve& C, const double U, gp_Pnt& P, gp_Vec& V1);

  Standard_EXPORT static void D2(const BRepAdaptor_Curve& C,
                                 const double             U,
                                 gp_Pnt&                  P,
                                 gp_Vec&                  V1,
                                 gp_Vec&                  V2);

  Standard_EXPORT static void D3(const BRepAdaptor_Curve& C,
                                 const double             U,
                                 gp_Pnt&                  P,
                                 gp_Vec&                  V1,
                                 gp_Vec&                  V2,
                                 gp_Vec&                  V3);

  Standard_EXPORT static int Continuity(const BRepAdaptor_Curve& C);

  Standard_EXPORT static double FirstParameter(const BRepAdaptor_Curve& C);

  Standard_EXPORT static double LastParameter(const BRepAdaptor_Curve& C);
};
