#pragma once


#include <Adaptor3d_Curve.hpp>
#include <Adaptor3d_Surface.hpp>
#include <BRepBlend_PointOnRst.hpp>
#include <NCollection_Sequence.hpp>
#include <Blend_Point.hpp>
#include <Blend_Status.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <math_Vector.hpp>

class BRepBlend_Line;
class Adaptor3d_TopolTool;
class StdFail_NotDone;
class Adaptor3d_HVertex;
class BRepBlend_HCurve2dTool;
class Adaptor3d_HSurfaceTool;
class BRepBlend_HCurveTool;
class BRepBlend_BlendTool;
class BRepBlend_PointOnRst;
class BRepBlend_Extremity;
class Blend_CSFunction;
class IntSurf_Transition;
class gp_Pnt;
class gp_Pnt2d;
class gp_Vec;
class gp_Vec2d;

class BRepBlend_CSWalking
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepBlend_CSWalking(const occ::handle<Adaptor3d_Curve>&     Curv,
                                      const occ::handle<Adaptor3d_Surface>&   Surf,
                                      const occ::handle<Adaptor3d_TopolTool>& Domain);

  Standard_EXPORT void Perform(Blend_CSFunction&  F,
                               const double       Pdep,
                               const double       Pmax,
                               const double       MaxStep,
                               const double       Tol3d,
                               const double       TolGuide,
                               const math_Vector& Soldep,
                               const double       Fleche,
                               const bool         Appro = false);

  Standard_EXPORT bool Complete(Blend_CSFunction& F, const double Pmin);

  bool IsDone() const;

  const occ::handle<BRepBlend_Line>& Line() const;

private:
  Standard_EXPORT void InternalPerform(Blend_CSFunction& F, math_Vector& Sol, const double Bound);

  Standard_EXPORT void Transition(const occ::handle<Adaptor2d_Curve2d>& A,
                                  const double                          Param,
                                  IntSurf_Transition&                   TLine,
                                  IntSurf_Transition&                   TArc);

  Standard_EXPORT void MakeExtremity(BRepBlend_Extremity&                  Extrem,
                                     const int                             Index,
                                     const double                          Param,
                                     const bool                            IsVtx,
                                     const occ::handle<Adaptor3d_HVertex>& Vtx);

  Standard_EXPORT Blend_Status CheckDeflectionOnSurf(const gp_Pnt&   Psurf,
                                                     const gp_Pnt2d& Ponsurf,
                                                     const gp_Vec&   Tgsurf,
                                                     const gp_Vec2d& Tgonsurf);

  Standard_EXPORT Blend_Status CheckDeflectionOnCurv(const gp_Pnt& Pcurv,
                                                     const double  Poncurv,
                                                     const gp_Vec& Tgcurv);

  Standard_EXPORT Blend_Status TestArret(Blend_CSFunction&  F,
                                         const math_Vector& Sol,
                                         const bool         TestDeflection,
                                         const Blend_Status State);

  bool                                     done;
  occ::handle<BRepBlend_Line>              line;
  occ::handle<Adaptor3d_Surface>           surf;
  occ::handle<Adaptor3d_Curve>             curv;
  occ::handle<Adaptor3d_TopolTool>         domain;
  double                                   tolpoint3d;
  double                                   tolgui;
  double                                   pasmax;
  double                                   fleche;
  double                                   param;
  double                                   firstparam;
  occ::handle<NCollection_HArray1<double>> firstsol;
  Blend_Point                              previousP;
  bool                                     rebrou;
  bool                                     iscomplete;
  bool                                     comptra;
  double                                   sens;
};

