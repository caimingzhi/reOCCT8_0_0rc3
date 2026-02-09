#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

class Adaptor3d_Curve;
class Bnd_Box;

class BndLib_Add3dCurve
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void Add(const Adaptor3d_Curve& C, const double Tol, Bnd_Box& B);

  Standard_EXPORT static void Add(const Adaptor3d_Curve& C,
                                  const double           U1,
                                  const double           U2,
                                  const double           Tol,
                                  Bnd_Box&               B);

  Standard_EXPORT static void AddOptimal(const Adaptor3d_Curve& C, const double Tol, Bnd_Box& B);
  Standard_EXPORT static void AddOptimal(const Adaptor3d_Curve& C,
                                         const double           U1,
                                         const double           U2,
                                         const double           Tol,
                                         Bnd_Box&               B);

  Standard_EXPORT static void AddGenCurv(const Adaptor3d_Curve& C,
                                         const double           UMin,
                                         const double           UMax,
                                         const double           Tol,
                                         Bnd_Box&               B);
};
