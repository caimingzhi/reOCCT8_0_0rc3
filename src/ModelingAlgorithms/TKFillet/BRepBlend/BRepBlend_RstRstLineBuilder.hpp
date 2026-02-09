#pragma once

#include <Adaptor3d_Surface.hpp>
#include <math_Vector.hpp>
#include <Blend_Point.hpp>
#include <Blend_DecrochStatus.hpp>
#include <Blend_Status.hpp>
#include <TopAbs_State.hpp>

class BRepBlend_Line;
class Adaptor3d_TopolTool;
class Blend_RstRstFunction;
class Blend_SurfCurvFuncInv;
class Blend_CurvPointFuncInv;
class Adaptor3d_HVertex;
class IntSurf_Transition;
class BRepBlend_Extremity;

class BRepBlend_RstRstLineBuilder
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepBlend_RstRstLineBuilder(const occ::handle<Adaptor3d_Surface>&   Surf1,
                                              const occ::handle<Adaptor2d_Curve2d>&   Rst1,
                                              const occ::handle<Adaptor3d_TopolTool>& Domain1,
                                              const occ::handle<Adaptor3d_Surface>&   Surf2,
                                              const occ::handle<Adaptor2d_Curve2d>&   Rst2,
                                              const occ::handle<Adaptor3d_TopolTool>& Domain2);

  Standard_EXPORT void Perform(Blend_RstRstFunction&   Func,
                               Blend_SurfCurvFuncInv&  Finv1,
                               Blend_CurvPointFuncInv& FinvP1,
                               Blend_SurfCurvFuncInv&  Finv2,
                               Blend_CurvPointFuncInv& FinvP2,
                               const double            Pdep,
                               const double            Pmax,
                               const double            MaxStep,
                               const double            Tol3d,
                               const double            TolGuide,
                               const math_Vector&      Soldep,
                               const double            Fleche,
                               const bool              Appro = false);

  Standard_EXPORT bool PerformFirstSection(Blend_RstRstFunction&   Func,
                                           Blend_SurfCurvFuncInv&  Finv1,
                                           Blend_CurvPointFuncInv& FinvP1,
                                           Blend_SurfCurvFuncInv&  Finv2,
                                           Blend_CurvPointFuncInv& FinvP2,
                                           const double            Pdep,
                                           const double            Pmax,
                                           const math_Vector&      Soldep,
                                           const double            Tol3d,
                                           const double            TolGuide,
                                           const bool              RecRst1,
                                           const bool              RecP1,
                                           const bool              RecRst2,
                                           const bool              RecP2,
                                           double&                 Psol,
                                           math_Vector&            ParSol);

  Standard_EXPORT bool Complete(Blend_RstRstFunction&   Func,
                                Blend_SurfCurvFuncInv&  Finv1,
                                Blend_CurvPointFuncInv& FinvP1,
                                Blend_SurfCurvFuncInv&  Finv2,
                                Blend_CurvPointFuncInv& FinvP2,
                                const double            Pmin);

  bool IsDone() const;

  const occ::handle<BRepBlend_Line>& Line() const;

  bool Decroch1Start() const;

  bool Decroch1End() const;

  bool Decroch2Start() const;

  bool Decroch2End() const;

private:
  Standard_EXPORT void InternalPerform(Blend_RstRstFunction&   Func,
                                       Blend_SurfCurvFuncInv&  Finv1,
                                       Blend_CurvPointFuncInv& FinvP1,
                                       Blend_SurfCurvFuncInv&  Finv2,
                                       Blend_CurvPointFuncInv& FinvP2,
                                       const double            Bound);

  Standard_EXPORT bool Recadre1(Blend_RstRstFunction&           Func,
                                Blend_SurfCurvFuncInv&          Finv,
                                math_Vector&                    Solinv,
                                bool&                           IsVtx,
                                occ::handle<Adaptor3d_HVertex>& Vtx);

  Standard_EXPORT bool Recadre2(Blend_RstRstFunction&           Func,
                                Blend_SurfCurvFuncInv&          Finv,
                                math_Vector&                    Solinv,
                                bool&                           IsVtx,
                                occ::handle<Adaptor3d_HVertex>& Vtx);

  Standard_EXPORT bool Recadre1(Blend_CurvPointFuncInv&         FinvP,
                                math_Vector&                    Solinv,
                                bool&                           IsVtx,
                                occ::handle<Adaptor3d_HVertex>& Vtx);

  Standard_EXPORT bool Recadre2(Blend_CurvPointFuncInv&         FinvP,
                                math_Vector&                    Solinv,
                                bool&                           IsVtx,
                                occ::handle<Adaptor3d_HVertex>& Vtx);

  Standard_EXPORT void Transition(const bool                            OnFirst,
                                  const occ::handle<Adaptor2d_Curve2d>& Arc,
                                  const double                          Param,
                                  IntSurf_Transition&                   TLine,
                                  IntSurf_Transition&                   TArc);

  Standard_EXPORT void MakeExtremity(BRepBlend_Extremity&                  Extrem,
                                     const bool                            OnFirst,
                                     const occ::handle<Adaptor2d_Curve2d>& Arc,
                                     const double                          Param,
                                     const bool                            IsVtx,
                                     const occ::handle<Adaptor3d_HVertex>& Vtx);

  Standard_EXPORT Blend_Status CheckDeflectionOnRst1(const Blend_Point& CurPoint);

  Standard_EXPORT Blend_Status CheckDeflectionOnRst2(const Blend_Point& CurPoint);

  Standard_EXPORT Blend_Status TestArret(Blend_RstRstFunction& Func,
                                         const bool            TestDeflection,
                                         const Blend_Status    State);

  Standard_EXPORT bool CheckInside(Blend_RstRstFunction& Func,
                                   TopAbs_State&         SituOnC1,
                                   TopAbs_State&         SituOnC2,
                                   Blend_DecrochStatus&  Decroch);

  bool                             done;
  occ::handle<BRepBlend_Line>      line;
  math_Vector                      sol;
  occ::handle<Adaptor3d_Surface>   surf1;
  occ::handle<Adaptor3d_TopolTool> domain1;
  occ::handle<Adaptor3d_Surface>   surf2;
  occ::handle<Adaptor3d_TopolTool> domain2;
  occ::handle<Adaptor2d_Curve2d>   rst1;
  occ::handle<Adaptor2d_Curve2d>   rst2;
  double                           tolpoint3d;
  double                           tolgui;
  double                           pasmax;
  double                           fleche;
  double                           param;
  Blend_Point                      previousP;
  bool                             rebrou;
  bool                             iscomplete;
  bool                             comptra;
  double                           sens;
  Blend_DecrochStatus              decrochdeb;
  Blend_DecrochStatus              decrochfin;
};

#include <StdFail_NotDone.hpp>

inline bool BRepBlend_RstRstLineBuilder::IsDone() const
{
  return done;
}

inline const occ::handle<BRepBlend_Line>& BRepBlend_RstRstLineBuilder::Line() const
{
  if (!done)
  {
    throw StdFail_NotDone();
  }
  return line;
}

inline bool BRepBlend_RstRstLineBuilder::Decroch1Start() const
{
  return decrochdeb == Blend_DecrochRst1 || decrochdeb == Blend_DecrochBoth;
}

inline bool BRepBlend_RstRstLineBuilder::Decroch1End() const
{
  return decrochfin == Blend_DecrochRst1 || decrochfin == Blend_DecrochBoth;
}

inline bool BRepBlend_RstRstLineBuilder::Decroch2Start() const
{
  return decrochdeb == Blend_DecrochRst2 || decrochdeb == Blend_DecrochBoth;
}

inline bool BRepBlend_RstRstLineBuilder::Decroch2End() const
{
  return decrochfin == Blend_DecrochRst2 || decrochfin == Blend_DecrochBoth;
}
