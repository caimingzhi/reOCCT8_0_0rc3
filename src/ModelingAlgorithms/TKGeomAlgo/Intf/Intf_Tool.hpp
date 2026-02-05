#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Standard_Integer.hpp>
class gp_Lin2d;
class Bnd_Box2d;
class gp_Hypr2d;
class gp_Parab2d;
class gp_Lin;
class Bnd_Box;
class gp_Hypr;
class gp_Parab;

//! Provides services to create box for infinites
//! lines in a given contexte.
class Intf_Tool
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Intf_Tool();

  Standard_EXPORT void Lin2dBox(const gp_Lin2d&  theLin2d,
                                const Bnd_Box2d& bounding,
                                Bnd_Box2d&       boxLin);

  Standard_EXPORT void Hypr2dBox(const gp_Hypr2d& theHypr2d,
                                 const Bnd_Box2d& bounding,
                                 Bnd_Box2d&       boxHypr);

  Standard_EXPORT void Parab2dBox(const gp_Parab2d& theParab2d,
                                  const Bnd_Box2d&  bounding,
                                  Bnd_Box2d&        boxHypr);

  Standard_EXPORT void LinBox(const gp_Lin& theLin, const Bnd_Box& bounding, Bnd_Box& boxLin);

  Standard_EXPORT void HyprBox(const gp_Hypr& theHypr, const Bnd_Box& bounding, Bnd_Box& boxHypr);

  Standard_EXPORT void ParabBox(const gp_Parab& theParab,
                                const Bnd_Box&  bounding,
                                Bnd_Box&        boxHypr);

  Standard_EXPORT int NbSegments() const;

  Standard_EXPORT double BeginParam(const int SegmentNum) const;

  Standard_EXPORT double EndParam(const int SegmentNum) const;

private:
  Standard_EXPORT int Inters2d(const gp_Hypr2d& theCurve, const Bnd_Box2d& Domain);

  Standard_EXPORT int Inters2d(const gp_Parab2d& theCurve, const Bnd_Box2d& Domain);

  Standard_EXPORT int Inters3d(const gp_Hypr& theCurve, const Bnd_Box& Domain);

  Standard_EXPORT int Inters3d(const gp_Parab& theCurve, const Bnd_Box& Domain);

  int    nbSeg;
  double beginOnCurve[6];
  double endOnCurve[6];
  int    bord[12];
  double xint[12];
  double yint[12];
  double zint[12];
  double parint[12];
};
