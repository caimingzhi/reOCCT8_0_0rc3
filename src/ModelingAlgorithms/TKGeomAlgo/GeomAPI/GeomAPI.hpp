#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Geom2d_Curve.hpp>
#include <Geom_Curve.hpp>

class gp_Pln;

class GeomAPI
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static occ::handle<Geom2d_Curve> To2d(const occ::handle<Geom_Curve>& C,
                                                        const gp_Pln&                  P);

  Standard_EXPORT static occ::handle<Geom_Curve> To3d(const occ::handle<Geom2d_Curve>& C,
                                                      const gp_Pln&                    P);
};
