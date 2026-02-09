#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class Adaptor2d_Curve2d;
class Bnd_Box2d;
class Geom2d_Curve;

class BndLib_Add2dCurve
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void Add(const Adaptor2d_Curve2d& C, const double Tol, Bnd_Box2d& B);

  Standard_EXPORT static void Add(const Adaptor2d_Curve2d& C,
                                  const double             U1,
                                  const double             U2,
                                  const double             Tol,
                                  Bnd_Box2d&               B);

  Standard_EXPORT static void Add(const occ::handle<Geom2d_Curve>& C,
                                  const double                     Tol,
                                  Bnd_Box2d&                       Box);

  Standard_EXPORT static void Add(const occ::handle<Geom2d_Curve>& C,
                                  const double                     U1,
                                  const double                     U2,
                                  const double                     Tol,
                                  Bnd_Box2d&                       B);

  Standard_EXPORT static void AddOptimal(const occ::handle<Geom2d_Curve>& C,
                                         const double                     U1,
                                         const double                     U2,
                                         const double                     Tol,
                                         Bnd_Box2d&                       B);
};
