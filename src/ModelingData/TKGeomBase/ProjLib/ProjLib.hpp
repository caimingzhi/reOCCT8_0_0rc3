#pragma once

#include <Adaptor3d_Surface.hpp>
#include <Geom2d_Curve.hpp>

class gp_Pnt2d;
class gp_Pln;
class gp_Pnt;
class gp_Lin2d;
class gp_Lin;
class gp_Circ2d;
class gp_Circ;
class gp_Elips2d;
class gp_Elips;
class gp_Parab2d;
class gp_Parab;
class gp_Hypr2d;
class gp_Hypr;
class gp_Cylinder;
class gp_Cone;
class gp_Sphere;
class gp_Torus;
class ProjLib_ProjectedCurve;

class ProjLib
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static gp_Pnt2d Project(const gp_Pln& Pl, const gp_Pnt& P);

  Standard_EXPORT static gp_Lin2d Project(const gp_Pln& Pl, const gp_Lin& L);

  Standard_EXPORT static gp_Circ2d Project(const gp_Pln& Pl, const gp_Circ& C);

  Standard_EXPORT static gp_Elips2d Project(const gp_Pln& Pl, const gp_Elips& E);

  Standard_EXPORT static gp_Parab2d Project(const gp_Pln& Pl, const gp_Parab& P);

  Standard_EXPORT static gp_Hypr2d Project(const gp_Pln& Pl, const gp_Hypr& H);

  Standard_EXPORT static gp_Pnt2d Project(const gp_Cylinder& Cy, const gp_Pnt& P);

  Standard_EXPORT static gp_Lin2d Project(const gp_Cylinder& Cy, const gp_Lin& L);

  Standard_EXPORT static gp_Lin2d Project(const gp_Cylinder& Cy, const gp_Circ& Ci);

  Standard_EXPORT static gp_Pnt2d Project(const gp_Cone& Co, const gp_Pnt& P);

  Standard_EXPORT static gp_Lin2d Project(const gp_Cone& Co, const gp_Lin& L);

  Standard_EXPORT static gp_Lin2d Project(const gp_Cone& Co, const gp_Circ& Ci);

  Standard_EXPORT static gp_Pnt2d Project(const gp_Sphere& Sp, const gp_Pnt& P);

  Standard_EXPORT static gp_Lin2d Project(const gp_Sphere& Sp, const gp_Circ& Ci);

  Standard_EXPORT static gp_Pnt2d Project(const gp_Torus& To, const gp_Pnt& P);

  Standard_EXPORT static gp_Lin2d Project(const gp_Torus& To, const gp_Circ& Ci);

  Standard_EXPORT static void MakePCurveOfType(const ProjLib_ProjectedCurve& PC,
                                               occ::handle<Geom2d_Curve>&    aC);

  Standard_EXPORT static bool IsAnaSurf(const occ::handle<Adaptor3d_Surface>& theAS);
};
