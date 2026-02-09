#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <BRepPrim_Revolution.hpp>
#include <BRepPrimAPI_MakeOneAxis.hpp>
class Geom_Curve;
class gp_Ax2;

class BRepPrimAPI_MakeRevolution : public BRepPrimAPI_MakeOneAxis
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepPrimAPI_MakeRevolution(const occ::handle<Geom_Curve>& Meridian);

  Standard_EXPORT BRepPrimAPI_MakeRevolution(const occ::handle<Geom_Curve>& Meridian,
                                             const double                   angle);

  Standard_EXPORT BRepPrimAPI_MakeRevolution(const occ::handle<Geom_Curve>& Meridian,
                                             const double                   VMin,
                                             const double                   VMax);

  Standard_EXPORT BRepPrimAPI_MakeRevolution(const occ::handle<Geom_Curve>& Meridian,
                                             const double                   VMin,
                                             const double                   VMax,
                                             const double                   angle);

  Standard_EXPORT BRepPrimAPI_MakeRevolution(const gp_Ax2&                  Axes,
                                             const occ::handle<Geom_Curve>& Meridian);

  Standard_EXPORT BRepPrimAPI_MakeRevolution(const gp_Ax2&                  Axes,
                                             const occ::handle<Geom_Curve>& Meridian,
                                             const double                   angle);

  Standard_EXPORT BRepPrimAPI_MakeRevolution(const gp_Ax2&                  Axes,
                                             const occ::handle<Geom_Curve>& Meridian,
                                             const double                   VMin,
                                             const double                   VMax);

  Standard_EXPORT BRepPrimAPI_MakeRevolution(const gp_Ax2&                  Axes,
                                             const occ::handle<Geom_Curve>& Meridian,
                                             const double                   VMin,
                                             const double                   VMax,
                                             const double                   angle);

  Standard_EXPORT void* OneAxis() override;

  Standard_EXPORT BRepPrim_Revolution& Revolution();

private:
  BRepPrim_Revolution myRevolution;
};
