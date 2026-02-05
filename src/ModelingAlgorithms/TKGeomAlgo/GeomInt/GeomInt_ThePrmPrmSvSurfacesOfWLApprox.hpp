#pragma once

#include <Adaptor3d_Surface.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec2d.hpp>
#include <gp_Vec.hpp>
#include <GeomInt_TheInt2SOfThePrmPrmSvSurfacesOfWLApprox.hpp>
#include <ApproxInt_SvSurfaces.hpp>

class Adaptor3d_HSurfaceTool;
class IntPatch_WLine;
class GeomInt_TheInt2SOfThePrmPrmSvSurfacesOfWLApprox;
class GeomInt_TheFunctionOfTheInt2SOfThePrmPrmSvSurfacesOfWLApprox;

class GeomInt_ThePrmPrmSvSurfacesOfWLApprox : public ApproxInt_SvSurfaces
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomInt_ThePrmPrmSvSurfacesOfWLApprox(
    const occ::handle<Adaptor3d_Surface>& Surf1,
    const occ::handle<Adaptor3d_Surface>& Surf2);

  //! returns True if Tg,Tguv1 Tguv2 can be computed.
  Standard_EXPORT bool Compute(double&   u1,
                               double&   v1,
                               double&   u2,
                               double&   v2,
                               gp_Pnt&   Pt,
                               gp_Vec&   Tg,
                               gp_Vec2d& Tguv1,
                               gp_Vec2d& Tguv2) override;

  Standard_EXPORT void Pnt(const double u1,
                           const double v1,
                           const double u2,
                           const double v2,
                           gp_Pnt&      P) override;

  Standard_EXPORT bool SeekPoint(const double     u1,
                                 const double     v1,
                                 const double     u2,
                                 const double     v2,
                                 IntSurf_PntOn2S& Point) override;

  Standard_EXPORT bool Tangency(const double u1,
                                const double v1,
                                const double u2,
                                const double v2,
                                gp_Vec&      Tg) override;

  Standard_EXPORT bool TangencyOnSurf1(const double u1,
                                       const double v1,
                                       const double u2,
                                       const double v2,
                                       gp_Vec2d&    Tg) override;

  Standard_EXPORT bool TangencyOnSurf2(const double u1,
                                       const double v1,
                                       const double u2,
                                       const double v2,
                                       gp_Vec2d&    Tg) override;

private:
  gp_Pnt2d                                        MyParOnS1;
  gp_Pnt2d                                        MyParOnS2;
  gp_Pnt                                          MyPnt;
  gp_Vec2d                                        MyTguv1;
  gp_Vec2d                                        MyTguv2;
  gp_Vec                                          MyTg;
  bool                                            MyIsTangent;
  bool                                            MyHasBeenComputed;
  gp_Pnt2d                                        MyParOnS1bis;
  gp_Pnt2d                                        MyParOnS2bis;
  gp_Pnt                                          MyPntbis;
  gp_Vec2d                                        MyTguv1bis;
  gp_Vec2d                                        MyTguv2bis;
  gp_Vec                                          MyTgbis;
  bool                                            MyIsTangentbis;
  bool                                            MyHasBeenComputedbis;
  GeomInt_TheInt2SOfThePrmPrmSvSurfacesOfWLApprox MyIntersectionOn2S;
};
