#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Standard_Integer.hpp>
#include <IntAna_ResultType.hpp>
#include <gp_Pnt.hpp>
#include <gp_Dir.hpp>
class gp_Pln;
class gp_Cylinder;
class gp_Sphere;
class gp_Cone;
class gp_Torus;
class gp_Lin;
class gp_Circ;
class gp_Elips;
class gp_Parab;
class gp_Hypr;

class IntAna_QuadQuadGeo
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IntAna_QuadQuadGeo();

  Standard_EXPORT IntAna_QuadQuadGeo(const gp_Pln& P1,
                                     const gp_Pln& P2,
                                     const double  TolAng,
                                     const double  Tol);

  Standard_EXPORT void Perform(const gp_Pln& P1,
                               const gp_Pln& P2,
                               const double  TolAng,
                               const double  Tol);

  Standard_EXPORT IntAna_QuadQuadGeo(const gp_Pln&      P,
                                     const gp_Cylinder& C,
                                     const double       Tolang,
                                     const double       Tol,
                                     const double       H = 0);

  Standard_EXPORT void Perform(const gp_Pln&      P,
                               const gp_Cylinder& C,
                               const double       Tolang,
                               const double       Tol,
                               const double       H = 0);

  Standard_EXPORT IntAna_QuadQuadGeo(const gp_Pln& P, const gp_Sphere& S);

  Standard_EXPORT void Perform(const gp_Pln& P, const gp_Sphere& S);

  Standard_EXPORT IntAna_QuadQuadGeo(const gp_Pln&  P,
                                     const gp_Cone& C,
                                     const double   Tolang,
                                     const double   Tol);

  Standard_EXPORT void Perform(const gp_Pln&  P,
                               const gp_Cone& C,
                               const double   Tolang,
                               const double   Tol);

  Standard_EXPORT IntAna_QuadQuadGeo(const gp_Cylinder& Cyl1,
                                     const gp_Cylinder& Cyl2,
                                     const double       Tol);

  Standard_EXPORT void Perform(const gp_Cylinder& Cyl1, const gp_Cylinder& Cyl2, const double Tol);

  Standard_EXPORT IntAna_QuadQuadGeo(const gp_Cylinder& Cyl,
                                     const gp_Sphere&   Sph,
                                     const double       Tol);

  Standard_EXPORT void Perform(const gp_Cylinder& Cyl, const gp_Sphere& Sph, const double Tol);

  Standard_EXPORT IntAna_QuadQuadGeo(const gp_Cylinder& Cyl, const gp_Cone& Con, const double Tol);

  Standard_EXPORT void Perform(const gp_Cylinder& Cyl, const gp_Cone& Con, const double Tol);

  Standard_EXPORT IntAna_QuadQuadGeo(const gp_Sphere& Sph1,
                                     const gp_Sphere& Sph2,
                                     const double     Tol);

  Standard_EXPORT void Perform(const gp_Sphere& Sph1, const gp_Sphere& Sph2, const double Tol);

  Standard_EXPORT IntAna_QuadQuadGeo(const gp_Sphere& Sph, const gp_Cone& Con, const double Tol);

  Standard_EXPORT void Perform(const gp_Sphere& Sph, const gp_Cone& Con, const double Tol);

  Standard_EXPORT IntAna_QuadQuadGeo(const gp_Cone& Con1, const gp_Cone& Con2, const double Tol);

  Standard_EXPORT void Perform(const gp_Cone& Con1, const gp_Cone& Con2, const double Tol);

  Standard_EXPORT IntAna_QuadQuadGeo(const gp_Pln& Pln, const gp_Torus& Tor, const double Tol);

  Standard_EXPORT void Perform(const gp_Pln& Pln, const gp_Torus& Tor, const double Tol);

  Standard_EXPORT IntAna_QuadQuadGeo(const gp_Cylinder& Cyl, const gp_Torus& Tor, const double Tol);

  Standard_EXPORT void Perform(const gp_Cylinder& Cyl, const gp_Torus& Tor, const double Tol);

  Standard_EXPORT IntAna_QuadQuadGeo(const gp_Cone& Con, const gp_Torus& Tor, const double Tol);

  Standard_EXPORT void Perform(const gp_Cone& Con, const gp_Torus& Tor, const double Tol);

  Standard_EXPORT IntAna_QuadQuadGeo(const gp_Sphere& Sph, const gp_Torus& Tor, const double Tol);

  Standard_EXPORT void Perform(const gp_Sphere& Sph, const gp_Torus& Tor, const double Tol);

  Standard_EXPORT IntAna_QuadQuadGeo(const gp_Torus& Tor1, const gp_Torus& Tor2, const double Tol);

  Standard_EXPORT void Perform(const gp_Torus& Tor1, const gp_Torus& Tor2, const double Tol);

  bool IsDone() const;

  IntAna_ResultType TypeInter() const;

  int NbSolutions() const;

  Standard_EXPORT gp_Pnt Point(const int Num) const;

  Standard_EXPORT gp_Lin Line(const int Num) const;

  Standard_EXPORT gp_Circ Circle(const int Num) const;

  Standard_EXPORT gp_Elips Ellipse(const int Num) const;

  Standard_EXPORT gp_Parab Parabola(const int Num) const;

  Standard_EXPORT gp_Hypr Hyperbola(const int Num) const;

  Standard_EXPORT bool HasCommonGen() const;

  Standard_EXPORT const gp_Pnt& PChar() const;

protected:
  Standard_EXPORT void InitTolerances();

  bool              done;
  int               nbint;
  IntAna_ResultType typeres;
  gp_Pnt            pt1;
  gp_Pnt            pt2;
  gp_Pnt            pt3;
  gp_Pnt            pt4;
  gp_Dir            dir1;
  gp_Dir            dir2;
  gp_Dir            dir3;
  gp_Dir            dir4;
  double            param1;
  double            param2;
  double            param3;
  double            param4;
  double            param1bis;
  double            param2bis;
  double            myEPSILON_DISTANCE;
  double            myEPSILON_ANGLE_CONE;
  double            myEPSILON_MINI_CIRCLE_RADIUS;
  double            myEPSILON_CYLINDER_DELTA_RADIUS;
  double            myEPSILON_CYLINDER_DELTA_DISTANCE;
  double            myEPSILON_AXES_PARA;
  bool              myCommonGen;
  gp_Pnt            myPChar;
};

#include <StdFail_NotDone.hpp>

inline bool IntAna_QuadQuadGeo::IsDone() const
{
  return (done);
}

inline IntAna_ResultType IntAna_QuadQuadGeo::TypeInter() const
{
  if (!done)
  {
    throw StdFail_NotDone();
  }
  return (typeres);
}

inline int IntAna_QuadQuadGeo::NbSolutions() const
{
  if (!done)
  {
    throw StdFail_NotDone();
  }
  return (nbint);
}
