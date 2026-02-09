#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
class Geom2d_Curve;
class gp_Pnt2d;
class gp_Vec2d;

class Geom2dLProp_Curve2dTool
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void Value(const occ::handle<Geom2d_Curve>& C,
                                    const double                     U,
                                    gp_Pnt2d&                        P);

  Standard_EXPORT static void D1(const occ::handle<Geom2d_Curve>& C,
                                 const double                     U,
                                 gp_Pnt2d&                        P,
                                 gp_Vec2d&                        V1);

  Standard_EXPORT static void D2(const occ::handle<Geom2d_Curve>& C,
                                 const double                     U,
                                 gp_Pnt2d&                        P,
                                 gp_Vec2d&                        V1,
                                 gp_Vec2d&                        V2);

  Standard_EXPORT static void D3(const occ::handle<Geom2d_Curve>& C,
                                 const double                     U,
                                 gp_Pnt2d&                        P,
                                 gp_Vec2d&                        V1,
                                 gp_Vec2d&                        V2,
                                 gp_Vec2d&                        V3);

  Standard_EXPORT static int Continuity(const occ::handle<Geom2d_Curve>& C);

  Standard_EXPORT static double FirstParameter(const occ::handle<Geom2d_Curve>& C);

  Standard_EXPORT static double LastParameter(const occ::handle<Geom2d_Curve>& C);
};
