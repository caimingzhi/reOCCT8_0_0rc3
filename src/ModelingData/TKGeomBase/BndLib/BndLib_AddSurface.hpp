#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

class Adaptor3d_Surface;
class Bnd_Box;

class BndLib_AddSurface
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void Add(const Adaptor3d_Surface& S, const double Tol, Bnd_Box& B);

  Standard_EXPORT static void Add(const Adaptor3d_Surface& S,
                                  const double             UMin,
                                  const double             UMax,
                                  const double             VMin,
                                  const double             VMax,
                                  const double             Tol,
                                  Bnd_Box&                 B);

  Standard_EXPORT static void AddOptimal(const Adaptor3d_Surface& S, const double Tol, Bnd_Box& B);

  Standard_EXPORT static void AddOptimal(const Adaptor3d_Surface& S,
                                         const double             UMin,
                                         const double             UMax,
                                         const double             VMin,
                                         const double             VMax,
                                         const double             Tol,
                                         Bnd_Box&                 B);

  Standard_EXPORT static void AddGenSurf(const Adaptor3d_Surface& S,
                                         const double             UMin,
                                         const double             UMax,
                                         const double             VMin,
                                         const double             VMax,
                                         const double             Tol,
                                         Bnd_Box&                 B);
};
