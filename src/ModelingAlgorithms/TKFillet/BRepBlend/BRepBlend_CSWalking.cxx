

#include <BRepBlend_CSWalking.hpp>

#include <Adaptor2d_Curve2d.hpp>
#include <Adaptor3d_Curve.hpp>
#include <Adaptor3d_HSurfaceTool.hpp>
#include <Adaptor3d_HVertex.hpp>
#include <Adaptor3d_Surface.hpp>
#include <Adaptor3d_TopolTool.hpp>
#include <BRepBlend_BlendTool.hpp>
#include <BRepBlend_Extremity.hpp>
#include <BRepBlend_HCurve2dTool.hpp>
#include <BRepBlend_HCurveTool.hpp>
#include <BRepBlend_Line.hpp>
#include <BRepBlend_PointOnRst.hpp>
#include <Blend_CSFunction.hpp>
#include <IntSurf.hpp>
#include <IntSurf_Transition.hpp>
#include <Precision.hpp>
#include <StdFail_NotDone.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Array1.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Vec.hpp>
#include <gp_Vec2d.hpp>
#include <math_FunctionSetRoot.hpp>
#include <math_Gauss.hpp>

#ifdef OCCT_DEBUG
  #include <Geom_BSplineCurve.hpp>
  #include <Standard_Integer.hpp>

  #include <stdio.h>

static int  IndexOfSection = 0;
extern bool Blend_GettraceDRAWSECT();

static void Drawsect(const occ::handle<Adaptor3d_Surface>& surf,
                     const occ::handle<Adaptor3d_Curve>&   curv,
                     const double                          param,
                     Blend_CSFunction&                     Func)
{
  gp_Pnt2d    p2d = Func.Pnt2d();
  double      pc  = Func.ParameterOnC();
  Blend_Point BP(Adaptor3d_HSurfaceTool::Value(surf, p2d.X(), p2d.Y()),
                 BRepBlend_HCurveTool::Value(curv, pc),
                 param,
                 p2d.X(),
                 p2d.Y(),
                 pc);

  int hp, hk, hd, hp2d;
  Func.GetShape(hp, hk, hd, hp2d);
  NCollection_Array1<double> TK(1, hk);
  Func.Knots(TK);
  NCollection_Array1<int> TMul(1, hk);
  Func.Mults(TMul);
  NCollection_Array1<gp_Pnt>   TP(1, hp);
  NCollection_Array1<gp_Pnt2d> TP2d(1, hp2d);
  NCollection_Array1<double>   TW(1, hp);
  Func.Section(BP, TP, TP2d, TW);
  occ::handle<Geom_BSplineCurve> sect = new Geom_BSplineCurve(TP, TW, TK, TMul, hd);
  IndexOfSection++;

  char* name = new char[100];
  Sprintf(name, "%s_%d", "Section", IndexOfSection);
}

#endif

BRepBlend_CSWalking::BRepBlend_CSWalking(const occ::handle<Adaptor3d_Curve>&     Curv,
                                         const occ::handle<Adaptor3d_Surface>&   Surf,
                                         const occ::handle<Adaptor3d_TopolTool>& Domain)
    : done(false),
      surf(Surf),
      curv(Curv)
{
  domain = Domain;
}

void BRepBlend_CSWalking::Perform(Blend_CSFunction& Func,

                                  const double       Pdep,
                                  const double       Pmax,
                                  const double       MaxStep,
                                  const double       Tol3d,
                                  const double       TolGuide,
                                  const math_Vector& ParDep,
                                  const double       Fleche,
                                  const bool         Appro)
{
  done       = false;
  iscomplete = false;
  comptra    = false;
  line       = new BRepBlend_Line();
  int Nbvar  = Func.NbVariables();
  tolpoint3d = Tol3d;
  tolgui     = std::abs(TolGuide);
  fleche     = std::abs(Fleche);
  rebrou     = false;
  pasmax     = std::abs(MaxStep);
  math_Vector sol(1, Nbvar);

  firstsol = new NCollection_HArray1<double>(1, Nbvar);

  if (Pmax - Pdep >= 0.)
  {
    sens = 1.;
  }
  else
  {
    sens = -1.;
  }

  Blend_Status        State;
  BRepBlend_Extremity ptf1, ptf2;

  param      = Pdep;
  firstparam = Pdep;
  Func.Set(param);

  if (Appro)
  {
    TopAbs_State situ;

    math_Vector tolerance(1, Nbvar), infbound(1, Nbvar), supbound(1, Nbvar);
    Func.GetTolerance(tolerance, tolpoint3d);
    Func.GetBounds(infbound, supbound);
    math_FunctionSetRoot rsnld(Func, tolerance, 30);

    rsnld.Perform(Func, ParDep, infbound, supbound);

    if (!rsnld.IsDone())
    {
      return;
    }
    rsnld.Root(sol);

    situ = domain->Classify(Func.Pnt2d(), std::min(tolerance(1), tolerance(2)));

    if (situ != TopAbs_IN)
    {
      return;
    }
  }
  else
  {
    sol = ParDep;
  }

  for (int i = 1; i <= Nbvar; i++)
  {
    firstsol->ChangeValue(i) = sol(i);
  }
  State = TestArret(Func, sol, false, Blend_OK);
  if (State != Blend_OK)
  {
    return;
  }
#ifdef OCCT_DEBUG
  if (Blend_GettraceDRAWSECT())
  {
    Drawsect(surf, curv, param, Func);
  }
#endif

  line->Append(previousP);
  double U, V, W;
  previousP.ParametersOnS(U, V);
  W = previousP.ParameterOnC();
  BRepBlend_Extremity P1(previousP.PointOnS(), U, V, previousP.Parameter(), tolpoint3d);
  BRepBlend_Extremity P2(previousP.PointOnC(), W, previousP.Parameter(), tolpoint3d);
  if (sens > 0.)
  {
    line->SetStartPoints(P1, P2);
  }
  else
  {
    line->SetEndPoints(P1, P2);
  }

  InternalPerform(Func, sol, Pmax);

  done = true;
}

bool BRepBlend_CSWalking::Complete(Blend_CSFunction& Func,

                                   const double Pmin)
{
  if (!done)
  {
    throw StdFail_NotDone();
  }
  if (iscomplete)
  {
    return true;
  }

  sens = -sens;

  int         Nbvar = Func.NbVariables();
  math_Vector sol(1, Nbvar);
  for (int i = 1; i <= Nbvar; i++)
  {
    sol(i) = firstsol->Value(i);
  }

  param = firstparam;

  InternalPerform(Func, sol, Pmin);

  sens       = -sens;
  iscomplete = true;
  return true;
}

Blend_Status BRepBlend_CSWalking::TestArret(Blend_CSFunction&  Function,
                                            const math_Vector& Sol,
                                            const bool         TestDefl,
                                            const Blend_Status State)

{
  gp_Pnt            pt1, pt2;
  gp_Vec            V1, V2;
  gp_Vec            Tgp1, Nor1;
  gp_Vec2d          V12d;
  gp_Pnt2d          pt2d;
  double            pOnC;
  Blend_Status      State1, State2;
  IntSurf_TypeTrans tras = IntSurf_Undecided;

  if (Function.IsSolution(Sol, tolpoint3d))
  {
    pt1  = Function.PointOnS();
    pt2  = Function.PointOnC();
    pt2d = Function.Pnt2d();
    pOnC = Function.ParameterOnC();
    V1   = Function.TangentOnS();
    V2   = Function.TangentOnC();
    V12d = Function.Tangent2d();

    if (TestDefl)
    {

      State1 = CheckDeflectionOnSurf(pt1,

                                     pt2d,
                                     V1,
                                     V12d);

      State2 = Blend_StepTooSmall;
    }
    else
    {
      State1 = Blend_OK;
      State2 = Blend_OK;
    }

    if (State1 == Blend_Backward)
    {
      State1 = Blend_StepTooLarge;
      rebrou = true;
    }

    if (State2 == Blend_Backward)
    {
      State2 = Blend_StepTooLarge;
      rebrou = true;
    }

    if (State1 == Blend_StepTooLarge || State2 == Blend_StepTooLarge)
    {
      return Blend_StepTooLarge;
    }

    if (!comptra)
    {

      Function.Tangent(pt2d.X(), pt2d.Y(), Tgp1, Nor1);
      double testra = Tgp1.Dot(Nor1.Crossed(V1));
      if (std::abs(testra) > Precision::Confusion())
      {
        if (testra < 0.)
        {
          tras = IntSurf_In;
        }
        else if (testra > 0.)
        {
          tras = IntSurf_Out;
        }
        comptra = true;
        line->Set(tras);
      }
    }

    if (State1 == Blend_OK || State2 == Blend_OK)
    {
      previousP.SetValue(Function.PointOnS(),
                         Function.PointOnC(),
                         param,

                         pt2d.X(),
                         pt2d.Y(),
                         pOnC,
                         V1,
                         V2,
                         V12d);

      return State;
    }
    if (State1 == Blend_StepTooSmall && State2 == Blend_StepTooSmall)
    {
      previousP.SetValue(Function.PointOnS(),
                         Function.PointOnC(),
                         param,

                         pt2d.X(),
                         pt2d.Y(),
                         pOnC,
                         V1,
                         V2,
                         V12d);
      if (State == Blend_OK)
      {
        return Blend_StepTooSmall;
      }
      else
      {
        return State;
      }
    }

    if (State == Blend_OK)
    {
      return Blend_SamePoints;
    }
    else
    {
      return State;
    }
  }
  else
  {
    return Blend_StepTooLarge;
  }
}

Blend_Status BRepBlend_CSWalking::CheckDeflectionOnSurf(const gp_Pnt&   Psurf,
                                                        const gp_Pnt2d& Ponsurf,
                                                        const gp_Vec&   Tgsurf,
                                                        const gp_Vec2d& Tgonsurf)
{

  const double CosRef3D = 0.98;

  const double CosRef2D = 0.88;

  double Norme, prevNorme, Cosi, Cosi2;
  double FlecheCourante;
  double Du, Dv, Duv;
  double paramu, paramv, tolu, tolv;

  gp_Pnt   prevP;
  gp_Vec   prevTg;
  gp_Vec2d previousd2d;

  prevP  = previousP.PointOnS();
  prevTg = previousP.TangentOnS();
  tolu   = Adaptor3d_HSurfaceTool::UResolution(surf, tolpoint3d);
  tolv   = Adaptor3d_HSurfaceTool::VResolution(surf, tolpoint3d);

  gp_Vec Corde(prevP, Psurf);
  Norme     = Corde.SquareMagnitude();
  prevNorme = prevTg.SquareMagnitude();

  const double toler3d = tolpoint3d;
  if (Norme <= toler3d * toler3d || prevNorme <= toler3d * toler3d)
  {

    return Blend_SamePoints;
  }
  Cosi = sens * Corde * prevTg;
  if (Cosi < 0.)
  {
    return Blend_Backward;
  }

  Cosi2 = Cosi * Cosi / prevNorme / Norme;
  if (Cosi2 < CosRef3D)
  {
    return Blend_StepTooLarge;
  }

  previousP.ParametersOnS(paramu, paramv);
  previousd2d = previousP.Tangent2d();

  Du  = Ponsurf.X() - paramu;
  Dv  = Ponsurf.Y() - paramv;
  Duv = Du * Du + Dv * Dv;
  if ((std::abs(Du) < tolu && std::abs(Dv) < tolv)
      || (std::abs(previousd2d.X()) < tolu && std::abs(previousd2d.Y()) < tolv))
  {

    return Blend_SamePoints;
  }
  Cosi = sens * (Du * previousd2d.X() + Dv * previousd2d.Y());
  if (Cosi < 0)
  {
    return Blend_Backward;
  }

  Cosi  = sens * Corde * Tgsurf;
  Cosi2 = Cosi * Cosi / Tgsurf.SquareMagnitude() / Norme;
  if (Cosi2 < CosRef3D || Cosi < 0.)
  {
    return Blend_StepTooLarge;
  }

  Cosi  = sens * (Du * Tgonsurf.X() + Dv * Tgonsurf.Y()) / Tgonsurf.Magnitude();
  Cosi2 = Cosi * Cosi / Duv;
  if (Cosi2 < CosRef2D || Cosi < 0.)
  {
    return Blend_StepTooLarge;
  }

  FlecheCourante =
    (prevTg.Normalized().XYZ() - Tgsurf.Normalized().XYZ()).SquareModulus() * Norme / 64.;

  if (FlecheCourante <= 0.25 * fleche * fleche)
  {
    return Blend_StepTooSmall;
  }
  if (FlecheCourante > fleche * fleche)
  {

    return Blend_StepTooLarge;
  }

  return Blend_OK;
}

Blend_Status BRepBlend_CSWalking::CheckDeflectionOnCurv(const gp_Pnt& Pcurv,
                                                        const double  Param,
                                                        const gp_Vec& Tgcurv)
{

  const double CosRef3D = 0.98;

  double Norme, prevNorme, Cosi, Cosi2;
  double FlecheCourante;
  double Du, paramu, tolu;

  gp_Pnt prevP;
  gp_Vec prevTg;

  prevP  = previousP.PointOnC();
  prevTg = previousP.TangentOnC();
  tolu   = BRepBlend_HCurveTool::Resolution(curv, tolpoint3d);

  gp_Vec Corde(prevP, Pcurv);
  Norme     = Corde.SquareMagnitude();
  prevNorme = prevTg.SquareMagnitude();

  const double toler3d = tolpoint3d;

  if (Norme <= toler3d * toler3d)
  {

    return Blend_SamePoints;
  }
  else if (prevNorme > toler3d * toler3d)
  {
    Cosi = sens * Corde * prevTg;
    if (Cosi < 0.)
    {
      return Blend_Backward;
    }

    Cosi2 = Cosi * Cosi / prevNorme / Norme;
    if (Cosi2 < CosRef3D)
    {
      return Blend_StepTooLarge;
    }
  }

  paramu = previousP.ParameterOnC();
  Du     = Param - paramu;
  if (std::abs(Du) < tolu)
  {

    return Blend_SamePoints;
  }

  if (Tgcurv.Magnitude() <= tolpoint3d)
  {
    return Blend_SamePoints;
  }

  Cosi  = sens * Corde * Tgcurv;
  Cosi2 = Cosi * Cosi / Tgcurv.SquareMagnitude() / Norme;
  if (Cosi2 < CosRef3D || Cosi < 0.)
  {
    return Blend_StepTooLarge;
  }

  if (prevNorme > toler3d * toler3d)
  {
    FlecheCourante =
      (prevTg.Normalized().XYZ() - Tgcurv.Normalized().XYZ()).SquareModulus() * Norme / 64.;

    if (FlecheCourante <= 0.25 * fleche * fleche)
    {
      return Blend_StepTooSmall;
    }
    if (FlecheCourante > fleche * fleche)
    {

      return Blend_StepTooLarge;
    }
  }
  return Blend_OK;
}

void BRepBlend_CSWalking::Transition(const occ::handle<Adaptor2d_Curve2d>& A,
                                     const double                          Param,
                                     IntSurf_Transition&                   TLine,
                                     IntSurf_Transition&                   TArc)
{
  gp_Pnt2d p2d;
  gp_Vec2d dp2d;

  gp_Pnt pbid;
  gp_Vec d1u, d1v, normale, tgrst;

  BRepBlend_HCurve2dTool::D1(A, Param, p2d, dp2d);
  Adaptor3d_HSurfaceTool::D1(surf, p2d.X(), p2d.Y(), pbid, d1u, d1v);

  tgrst.SetLinearForm(dp2d.X(), d1u, dp2d.Y(), d1v);
  normale = d1u.Crossed(d1v);

  IntSurf::MakeTransition(previousP.TangentOnS(), tgrst, normale, TLine, TArc);
}

void BRepBlend_CSWalking::MakeExtremity(BRepBlend_Extremity&                  Extrem,
                                        const int                             Index,
                                        const double                          Param,
                                        const bool                            IsVtx,
                                        const occ::handle<Adaptor3d_HVertex>& Vtx)
{
  IntSurf_Transition               Tline, Tarc;
  double                           prm, U, V;
  int                              nbarc;
  occ::handle<Adaptor3d_TopolTool> Iter;

  previousP.ParametersOnS(U, V);
  Extrem.SetValue(previousP.PointOnS(), U, V, previousP.Parameter(), tolpoint3d);
  Iter = domain;

  Iter->Init();
  nbarc = 1;

  if (!IsVtx)
  {
    while (nbarc < Index)
    {
      nbarc++;
      Iter->Next();
    }
    Transition(Iter->Value(), Param, Tline, Tarc);
    Extrem.AddArc(Iter->Value(), Param, Tline, Tarc);
  }

  else
  {
    Extrem.SetVertex(Vtx);
    while (Iter->More())
    {
      occ::handle<Adaptor2d_Curve2d> arc = Iter->Value();
      if (nbarc != Index)
      {
        Iter->Initialize(arc);
        Iter->InitVertexIterator();
        while (Iter->MoreVertex())
        {

          if (Iter->Identical(Vtx, Iter->Vertex()))
          {
            prm = BRepBlend_BlendTool::Parameter(Vtx, arc);
            Transition(arc, prm, Tline, Tarc);
            Extrem.AddArc(arc, prm, Tline, Tarc);
          }
          Iter->NextVertex();
        }
      }
      else
      {
        Transition(arc, Param, Tline, Tarc);
        Extrem.AddArc(arc, Param, Tline, Tarc);
      }
      nbarc++;
      Iter->Next();
    }
  }
}

void BRepBlend_CSWalking::InternalPerform(Blend_CSFunction& Func,

                                          math_Vector& sol,
                                          const double Bound)
{
  double stepw   = pasmax;
  double parprec = param;

  Blend_Status State;
  TopAbs_State situ;
  double       w, U, V;
  int          nbarc;
  int          Index = 0;
  bool         Isvtx = false;
  int          Nbvar = Func.NbVariables();
  bool         Arrive, recad, echecrecad;
  gp_Pnt2d     p2d;

  math_Vector tolerance(1, Nbvar), infbound(1, Nbvar), supbound(1, Nbvar), parinit(1, Nbvar);
  math_Vector solrst(1, Nbvar);
  occ::handle<Adaptor3d_HVertex> Vtx;
  BRepBlend_Extremity            Exts, Extc;

  Func.GetTolerance(tolerance, tolpoint3d);
  Func.GetBounds(infbound, supbound);

  math_FunctionSetRoot rsnld(Func, tolerance, 30);
  parinit = sol;

  param  = parprec + sens * stepw;
  Arrive = (sens * (param - Bound) > 0.);

  while (!Arrive)
  {
    Func.Set(param);
    rsnld.Perform(Func, parinit, infbound, supbound);

    if (!rsnld.IsDone())
    {
      State = Blend_StepTooLarge;
    }
    else
    {
      rsnld.Root(sol);

      situ = domain->Classify(Func.Pnt2d(), std::min(tolerance(1), tolerance(2)));

      w          = Bound;
      recad      = false;
      echecrecad = false;

      if (situ == TopAbs_OUT || situ == TopAbs_ON)
      {

        Isvtx = false;
        if (recad)
        {
          w = solrst(2);
        }
        else
        {
          echecrecad = true;
        }
      }
      if (!echecrecad)
      {
        if (recad)
        {

          State = Blend_OnRst1;
          param = w;
          domain->Init();
          nbarc = 1;
          while (nbarc < Index)
          {
            nbarc++;
            domain->Next();
          }
          p2d    = BRepBlend_HCurve2dTool::Value(domain->Value(), solrst(1));
          sol(1) = p2d.X();
          sol(2) = p2d.Y();
          sol(3) = solrst(3);
          Func.Set(param);
        }
        else
        {
          State = Blend_OK;
        }
        State = TestArret(Func, sol, true, State);
      }
      else
      {

        State = Blend_SamePoints;
      }
    }

    switch (State)
    {
      case Blend_OK:
      {
#ifdef OCCT_DEBUG
        if (Blend_GettraceDRAWSECT())
        {
          Drawsect(surf, curv, param, Func);
        }
#endif

        if (sens > 0.)
        {
          line->Append(previousP);
        }
        else
        {
          line->Prepend(previousP);
        }
        parinit = sol;
        parprec = param;

        if (param == Bound)
        {
          Arrive = true;

          previousP.ParametersOnS(U, V);
          Exts.SetValue(previousP.PointOnS(), U, V, previousP.Parameter(), tolpoint3d);
          Extc.SetValue(previousP.PointOnC(),
                        previousP.ParameterOnC(),
                        previousP.Parameter(),
                        tolpoint3d);
        }
        else
        {
          param = param + sens * stepw;
          if (sens * (param - Bound) > -tolgui)
          {
            param = Bound;
          }
        }
      }
      break;

      case Blend_StepTooLarge:
      {
        stepw = stepw / 2.;
        if (std::abs(stepw) < tolgui)
        {

          previousP.ParametersOnS(U, V);
          Exts.SetValue(previousP.PointOnS(), U, V, previousP.Parameter(), tolpoint3d);
          Extc.SetValue(previousP.PointOnC(),
                        previousP.ParameterOnC(),
                        previousP.Parameter(),
                        tolpoint3d);
          Arrive = true;
          if (line->NbPoints() >= 2)
          {
          }
        }
        else
        {
          param = parprec + sens * stepw;
        }
      }
      break;

      case Blend_StepTooSmall:
      {
#ifdef OCCT_DEBUG
        if (Blend_GettraceDRAWSECT())
        {
          Drawsect(surf, curv, param, Func);
        }
#endif

        if (sens > 0.)
        {
          line->Append(previousP);
        }
        else
        {
          line->Prepend(previousP);
        }
        parinit = sol;
        parprec = param;

        stepw = std::min(1.5 * stepw, pasmax);
        if (param == Bound)
        {
          Arrive = true;

          previousP.ParametersOnS(U, V);
          Exts.SetValue(previousP.PointOnS(), U, V, previousP.Parameter(), tolpoint3d);
          Extc.SetValue(previousP.PointOnC(),
                        previousP.ParameterOnC(),
                        previousP.Parameter(),
                        tolpoint3d);
        }
        else
        {
          param = param + sens * stepw;
          if (sens * (param - Bound) > -tolgui)
          {
            param = Bound;
          }
        }
      }
      break;

      case Blend_OnRst1:
      {
#ifdef OCCT_DEBUG
        if (Blend_GettraceDRAWSECT())
        {
          Drawsect(surf, curv, param, Func);
        }
#endif
        if (sens > 0.)
        {
          line->Append(previousP);
        }
        else
        {
          line->Prepend(previousP);
        }
        MakeExtremity(Exts, Index, solrst(1), Isvtx, Vtx);

        Extc.SetValue(previousP.PointOnC(),
                      previousP.ParameterOnC(),
                      previousP.Parameter(),
                      tolpoint3d);
        Arrive = true;
      }
      break;

      case Blend_SamePoints:
      {

        std::cout << " Points confondus dans le cheminement" << std::endl;

        previousP.ParametersOnS(U, V);
        Exts.SetValue(previousP.PointOnS(), U, V, previousP.Parameter(), tolpoint3d);
        Extc.SetValue(previousP.PointOnC(),
                      previousP.ParameterOnC(),
                      previousP.Parameter(),
                      tolpoint3d);
        Arrive = true;
      }
      break;

      default:
        break;
    }
    if (Arrive)
    {
      if (sens > 0.)
      {
        line->SetEndPoints(Exts, Extc);
      }
      else
      {
        line->SetStartPoints(Exts, Extc);
      }
    }
  }
}
