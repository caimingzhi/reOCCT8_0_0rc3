#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Real.hpp>
class gp_Lin;
class Bnd_Box;
class gp_Lin2d;
class Bnd_Box2d;
class gp_Circ;
class gp_Circ2d;
class gp_Elips;
class gp_Elips2d;
class gp_Parab;
class gp_Parab2d;
class gp_Hypr;
class gp_Hypr2d;
class gp_Cylinder;
class gp_Cone;
class gp_Sphere;
class gp_Torus;

class BndLib
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void Add(const gp_Lin& L,
                                  const double  P1,
                                  const double  P2,
                                  const double  Tol,
                                  Bnd_Box&      B);

  Standard_EXPORT static void Add(const gp_Lin2d& L,
                                  const double    P1,
                                  const double    P2,
                                  const double    Tol,
                                  Bnd_Box2d&      B);

  Standard_EXPORT static void Add(const gp_Circ& C, const double Tol, Bnd_Box& B);

  Standard_EXPORT static void Add(const gp_Circ& C,
                                  const double   P1,
                                  const double   P2,
                                  const double   Tol,
                                  Bnd_Box&       B);

  Standard_EXPORT static void Add(const gp_Circ2d& C, const double Tol, Bnd_Box2d& B);

  Standard_EXPORT static void Add(const gp_Circ2d& C,
                                  const double     P1,
                                  const double     P2,
                                  const double     Tol,
                                  Bnd_Box2d&       B);

  Standard_EXPORT static void Add(const gp_Elips& C, const double Tol, Bnd_Box& B);

  Standard_EXPORT static void Add(const gp_Elips& C,
                                  const double    P1,
                                  const double    P2,
                                  const double    Tol,
                                  Bnd_Box&        B);

  Standard_EXPORT static void Add(const gp_Elips2d& C, const double Tol, Bnd_Box2d& B);

  Standard_EXPORT static void Add(const gp_Elips2d& C,
                                  const double      P1,
                                  const double      P2,
                                  const double      Tol,
                                  Bnd_Box2d&        B);

  Standard_EXPORT static void Add(const gp_Parab& P,
                                  const double    P1,
                                  const double    P2,
                                  const double    Tol,
                                  Bnd_Box&        B);

  Standard_EXPORT static void Add(const gp_Parab2d& P,
                                  const double      P1,
                                  const double      P2,
                                  const double      Tol,
                                  Bnd_Box2d&        B);

  Standard_EXPORT static void Add(const gp_Hypr& H,
                                  const double   P1,
                                  const double   P2,
                                  const double   Tol,
                                  Bnd_Box&       B);

  Standard_EXPORT static void Add(const gp_Hypr2d& H,
                                  const double     P1,
                                  const double     P2,
                                  const double     Tol,
                                  Bnd_Box2d&       B);

  Standard_EXPORT static void Add(const gp_Cylinder& S,
                                  const double       UMin,
                                  const double       UMax,
                                  const double       VMin,
                                  const double       VMax,
                                  const double       Tol,
                                  Bnd_Box&           B);

  Standard_EXPORT static void Add(const gp_Cylinder& S,
                                  const double       VMin,
                                  const double       VMax,
                                  const double       Tol,
                                  Bnd_Box&           B);

  Standard_EXPORT static void Add(const gp_Cone& S,
                                  const double   UMin,
                                  const double   UMax,
                                  const double   VMin,
                                  const double   VMax,
                                  const double   Tol,
                                  Bnd_Box&       B);

  Standard_EXPORT static void Add(const gp_Cone& S,
                                  const double   VMin,
                                  const double   VMax,
                                  const double   Tol,
                                  Bnd_Box&       B);

  Standard_EXPORT static void Add(const gp_Sphere& S, const double Tol, Bnd_Box& B);

  Standard_EXPORT static void Add(const gp_Sphere& S,
                                  const double     UMin,
                                  const double     UMax,
                                  const double     VMin,
                                  const double     VMax,
                                  const double     Tol,
                                  Bnd_Box&         B);

  Standard_EXPORT static void Add(const gp_Torus& P, const double Tol, Bnd_Box& B);

  Standard_EXPORT static void Add(const gp_Torus& P,
                                  const double    UMin,
                                  const double    UMax,
                                  const double    VMin,
                                  const double    VMax,
                                  const double    Tol,
                                  Bnd_Box&        B);
};
