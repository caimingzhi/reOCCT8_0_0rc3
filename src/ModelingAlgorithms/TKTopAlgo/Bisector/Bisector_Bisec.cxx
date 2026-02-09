#include <Bisector.hpp>
#include <Bisector_Bisec.hpp>
#include <Bisector_BisecAna.hpp>
#include <Bisector_BisecCC.hpp>
#include <Bisector_BisecPC.hpp>
#include <Bisector_Curve.hpp>
#include <GCE2d_MakeSegment.hpp>
#include <Geom2d_BSplineCurve.hpp>
#include <Geom2d_CartesianPoint.hpp>
#include <Geom2d_Circle.hpp>
#include <Geom2d_Curve.hpp>
#include <Geom2d_Line.hpp>
#include <Geom2d_Point.hpp>
#include <Geom2d_TrimmedCurve.hpp>
#include <gp.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Vec2d.hpp>
#include <Precision.hpp>
#include <StdFail_NotDone.hpp>

#ifdef OCCT_DEBUG
#endif

static bool IsMaxRC(const occ::handle<Geom2d_Curve>& C, double U, double& R);

static void ReplaceByLineIfIsToSmall(occ::handle<Bisector_Curve>& Bis,
                                     double&                      UFirst,
                                     double&                      ULast);

Bisector_Bisec::Bisector_Bisec() = default;

void Bisector_Bisec::Perform(const occ::handle<Geom2d_Curve>& afirstcurve,
                             const occ::handle<Geom2d_Curve>& asecondcurve,
                             const gp_Pnt2d&                  apoint,
                             const gp_Vec2d&                  afirstvector,
                             const gp_Vec2d&                  asecondvector,
                             const double                     adirection,
                             const GeomAbs_JoinType           ajointype,
                             const double                     tolerance,
                             const bool                       oncurve)
{
  occ::handle<Standard_Type>  Type1 = afirstcurve->DynamicType();
  occ::handle<Standard_Type>  Type2 = asecondcurve->DynamicType();
  occ::handle<Bisector_Curve> Bis;
  double                      UFirst, ULast;

  if (Type1 == STANDARD_TYPE(Geom2d_TrimmedCurve))
  {
    Type1 = occ::down_cast<Geom2d_TrimmedCurve>(afirstcurve)->BasisCurve()->DynamicType();
  }
  if (Type2 == STANDARD_TYPE(Geom2d_TrimmedCurve))
  {
    Type2 = occ::down_cast<Geom2d_TrimmedCurve>(asecondcurve)->BasisCurve()->DynamicType();
  }

  occ::handle<Geom2d_Curve> afirstcurve1  = afirstcurve;
  occ::handle<Geom2d_Curve> asecondcurve1 = asecondcurve;

  if (Type1 == STANDARD_TYPE(Geom2d_BSplineCurve))
  {
    occ::handle<Geom2d_BSplineCurve> aBS;
    if (afirstcurve->DynamicType() == STANDARD_TYPE(Geom2d_TrimmedCurve))
    {
      aBS = occ::down_cast<Geom2d_BSplineCurve>(
        occ::down_cast<Geom2d_TrimmedCurve>(afirstcurve)->BasisCurve());
    }
    else
    {
      aBS = occ::down_cast<Geom2d_BSplineCurve>(afirstcurve);
    }
    if (aBS->Degree() == 1 && aBS->NbPoles() == 2)
    {
      if (aBS->Pole(1).Distance(aBS->Pole(2)) < 1.e-4)
      {
        afirstcurve1 = GCE2d_MakeSegment(aBS->Pole(1), aBS->Pole(2)).Value();
        Type1        = STANDARD_TYPE(Geom2d_Line);
      }
    }
  }

  if (Type2 == STANDARD_TYPE(Geom2d_BSplineCurve))
  {
    occ::handle<Geom2d_BSplineCurve> aBS;
    if (asecondcurve->DynamicType() == STANDARD_TYPE(Geom2d_TrimmedCurve))
    {
      aBS = occ::down_cast<Geom2d_BSplineCurve>(
        occ::down_cast<Geom2d_TrimmedCurve>(asecondcurve)->BasisCurve());
    }
    else
    {
      aBS = occ::down_cast<Geom2d_BSplineCurve>(asecondcurve);
    }
    if (aBS->Degree() == 1 && aBS->NbPoles() == 2)
    {
      if (aBS->Pole(1).Distance(aBS->Pole(2)) < 1.e-4)
      {
        asecondcurve1 = GCE2d_MakeSegment(aBS->Pole(1), aBS->Pole(2)).Value();
        Type2         = STANDARD_TYPE(Geom2d_Line);
      }
    }
  }

  if ((Type1 == STANDARD_TYPE(Geom2d_Circle) || Type1 == STANDARD_TYPE(Geom2d_Line))
      && (Type2 == STANDARD_TYPE(Geom2d_Circle) || Type2 == STANDARD_TYPE(Geom2d_Line)))
  {

    occ::handle<Bisector_BisecAna> BisAna = new Bisector_BisecAna();
    BisAna->Perform(afirstcurve1,
                    asecondcurve1,
                    apoint,
                    afirstvector,
                    asecondvector,
                    adirection,
                    ajointype,
                    tolerance,
                    oncurve);
    UFirst = BisAna->ParameterOfStartPoint();
    ULast  = BisAna->ParameterOfEndPoint();
    Bis    = BisAna;
  }
  else
  {
    bool IsLine = false;

    if (oncurve)
    {
      gp_Dir2d Fd(afirstvector);
      gp_Dir2d Sd(asecondvector);

      if (Fd.Dot(Sd) < std::sqrt(2. * Precision::Angular()) - 1.)
        IsLine = true;
    }
    if (IsLine)
    {

      gp_Dir2d N(-adirection * afirstvector.Y(), adirection * afirstvector.X());
      occ::handle<Geom2d_CartesianPoint> PG = new Geom2d_CartesianPoint(apoint);
      occ::handle<Geom2d_Line>           L  = new Geom2d_Line(apoint, N);
      occ::handle<Geom2d_TrimmedCurve> BisL = new Geom2d_TrimmedCurve(L, 0, Precision::Infinite());
      occ::handle<Bisector_BisecAna>   BisAna = new Bisector_BisecAna();
      BisAna->Init(BisL);
      UFirst = BisAna->ParameterOfStartPoint();
      ULast  = BisAna->ParameterOfEndPoint();
      Bis    = BisAna;
    }
    else
    {

      occ::handle<Bisector_BisecCC> BisCC = new Bisector_BisecCC();
      BisCC->Perform(asecondcurve1, afirstcurve1, adirection, adirection, apoint);

      if (BisCC->IsEmpty())
      {

        gp_Pnt2d aP1 = afirstcurve1->Value(afirstcurve1->LastParameter());
        gp_Pnt2d aP2 = asecondcurve1->Value(asecondcurve1->FirstParameter());
        gp_Pnt2d aPm(.5 * (aP1.XY() + aP2.XY()));
        double   Nx, Ny;
        if (aPm.Distance(apoint) > 10. * Precision::Confusion())
        {
          Nx = apoint.X() - aPm.X();
          Ny = apoint.Y() - aPm.Y();
          if (adirection < 0)
          {
            Nx = -Nx;
            Ny = -Ny;
          }
        }
        else
        {
          gp_Dir2d dir1(afirstvector), dir2(asecondvector);
          Nx = -dir1.X() - dir2.X(), Ny = -dir1.Y() - dir2.Y();
          if (std::abs(Nx) <= gp::Resolution() && std::abs(Ny) <= gp::Resolution())
          {
            Nx = -afirstvector.Y();
            Ny = afirstvector.X();
          }
        }
        gp_Dir2d N(adirection * Nx, adirection * Ny);

        occ::handle<Geom2d_CartesianPoint> PG = new Geom2d_CartesianPoint(apoint);
        occ::handle<Geom2d_Line>           L  = new Geom2d_Line(apoint, N);
        occ::handle<Geom2d_TrimmedCurve>   BisL =
          new Geom2d_TrimmedCurve(L, 0, Precision::Infinite());
        occ::handle<Bisector_BisecAna> BisAna = new Bisector_BisecAna();
        BisAna->Init(BisL);
        UFirst = BisAna->ParameterOfStartPoint();
        ULast  = BisAna->ParameterOfEndPoint();
        Bis    = BisAna;
      }
      else
      {
        UFirst = BisCC->FirstParameter();
        ULast  = BisCC->LastParameter();
        Bis    = BisCC;
        ReplaceByLineIfIsToSmall(Bis, UFirst, ULast);
      }
    }
  }
  UFirst      = std::max(UFirst, Bis->FirstParameter());
  ULast       = std::min(ULast, Bis->LastParameter());
  thebisector = new Geom2d_TrimmedCurve(Bis, UFirst, ULast);
}

void Bisector_Bisec::Perform(const occ::handle<Geom2d_Curve>& afirstcurve,
                             const occ::handle<Geom2d_Point>& asecondpoint,
                             const gp_Pnt2d&                  apoint,
                             const gp_Vec2d&                  afirstvector,
                             const gp_Vec2d&                  asecondvector,
                             const double                     adirection,
                             const double                     tolerance,
                             const bool                       oncurve)
{

  occ::handle<Bisector_Curve> Bis;
  occ::handle<Standard_Type>  Type1 = afirstcurve->DynamicType();
  double                      UFirst, ULast;

  if (Type1 == STANDARD_TYPE(Geom2d_TrimmedCurve))
  {
    Type1 = occ::down_cast<Geom2d_TrimmedCurve>(afirstcurve)->BasisCurve()->DynamicType();
  }

  if (Type1 == STANDARD_TYPE(Geom2d_Circle) || Type1 == STANDARD_TYPE(Geom2d_Line))
  {

    occ::handle<Bisector_BisecAna> BisAna = new Bisector_BisecAna();
    BisAna->Perform(afirstcurve,
                    asecondpoint,
                    apoint,
                    afirstvector,
                    asecondvector,
                    adirection,
                    tolerance,
                    oncurve);
    UFirst = BisAna->ParameterOfStartPoint();
    ULast  = BisAna->ParameterOfEndPoint();
    Bis    = BisAna;
  }
  else
  {
    bool   IsLine = false;
    double RC     = Precision::Infinite();

    if (oncurve)
    {
      if (Bisector::IsConvex(afirstcurve, adirection)
          || IsMaxRC(afirstcurve, afirstcurve->LastParameter(), RC))
      {
        IsLine = true;
      }
    }
    if (IsLine)
    {

      gp_Dir2d                 N(-adirection * afirstvector.Y(), adirection * afirstvector.X());
      occ::handle<Geom2d_Line> L              = new Geom2d_Line(apoint, N);
      occ::handle<Geom2d_TrimmedCurve> BisL   = new Geom2d_TrimmedCurve(L, 0, RC);
      occ::handle<Bisector_BisecAna>   BisAna = new Bisector_BisecAna();
      BisAna->Init(BisL);
      UFirst = BisAna->ParameterOfStartPoint();
      ULast  = BisAna->ParameterOfEndPoint();
      Bis    = BisAna;
    }
    else
    {

      occ::handle<Bisector_BisecPC> BisPC              = new Bisector_BisecPC();
      occ::handle<Geom2d_Curve>     afirstcurvereverse = afirstcurve->Reversed();

      BisPC->Perform(afirstcurvereverse, asecondpoint->Pnt2d(), -adirection);

      if (BisPC->IsEmpty())
      {
        gp_Dir2d dir1(afirstvector), dir2(asecondvector);
        double   Nx = -dir1.X() - dir2.X(), Ny = -dir1.Y() - dir2.Y();
        if (std::abs(Nx) <= gp::Resolution() && std::abs(Ny) <= gp::Resolution())
        {
          Nx = -afirstvector.Y();
          Ny = afirstvector.X();
        }

        gp_Dir2d                         N(adirection * Nx, adirection * Ny);
        occ::handle<Geom2d_Line>         L      = new Geom2d_Line(apoint, N);
        occ::handle<Geom2d_TrimmedCurve> BisL   = new Geom2d_TrimmedCurve(L, 0, RC);
        occ::handle<Bisector_BisecAna>   BisAna = new Bisector_BisecAna();
        BisAna->Init(BisL);
        UFirst = BisAna->ParameterOfStartPoint();
        ULast  = BisAna->ParameterOfEndPoint();
        Bis    = BisAna;
      }
      else
      {

        UFirst = BisPC->Parameter(apoint);
        ULast  = BisPC->LastParameter();
        if (UFirst >= ULast)
        {

          gp_Vec2d                 V(BisPC->Value(BisPC->FirstParameter()), BisPC->Value(ULast));
          gp_Dir2d                 N(V);
          occ::handle<Geom2d_Line> L              = new Geom2d_Line(apoint, N);
          occ::handle<Geom2d_TrimmedCurve> BisL   = new Geom2d_TrimmedCurve(L, 0, RC);
          occ::handle<Bisector_BisecAna>   BisAna = new Bisector_BisecAna();
          BisAna->Init(BisL);
          UFirst = BisAna->ParameterOfStartPoint();
          ULast  = BisAna->ParameterOfEndPoint();
          Bis    = BisAna;
        }
        else
          Bis = BisPC;
      }
    }
  }
  if (UFirst < Bis->FirstParameter())
    UFirst = Bis->FirstParameter();
  if (ULast > Bis->LastParameter())
    ULast = Bis->LastParameter();
  thebisector = new Geom2d_TrimmedCurve(Bis, UFirst, ULast);
}

void Bisector_Bisec::Perform(const occ::handle<Geom2d_Point>& afirstpoint,
                             const occ::handle<Geom2d_Curve>& asecondcurve,
                             const gp_Pnt2d&                  apoint,
                             const gp_Vec2d&                  afirstvector,
                             const gp_Vec2d&                  asecondvector,
                             const double                     adirection,
                             const double                     tolerance,
                             const bool                       oncurve)

{

  occ::handle<Bisector_Curve> Bis;
  occ::handle<Standard_Type>  Type1 = asecondcurve->DynamicType();
  double                      UFirst, ULast;

  if (Type1 == STANDARD_TYPE(Geom2d_TrimmedCurve))
  {
    Type1 = occ::down_cast<Geom2d_TrimmedCurve>(asecondcurve)->BasisCurve()->DynamicType();
  }

  if (Type1 == STANDARD_TYPE(Geom2d_Circle) || Type1 == STANDARD_TYPE(Geom2d_Line))
  {

    occ::handle<Bisector_BisecAna> BisAna = new Bisector_BisecAna();
    BisAna->Perform(afirstpoint,
                    asecondcurve,
                    apoint,
                    afirstvector,
                    asecondvector,
                    adirection,
                    tolerance,
                    oncurve);
    UFirst = BisAna->ParameterOfStartPoint();
    ULast  = BisAna->ParameterOfEndPoint();
    Bis    = BisAna;
  }
  else
  {

    bool   IsLine = false;
    double RC     = Precision::Infinite();

    if (oncurve)
    {
      if (Bisector::IsConvex(asecondcurve, adirection)
          || IsMaxRC(asecondcurve, asecondcurve->FirstParameter(), RC))
      {
        IsLine = true;
      }
    }
    if (IsLine)
    {

      gp_Dir2d                 N(-adirection * afirstvector.Y(), adirection * afirstvector.X());
      occ::handle<Geom2d_Line> L              = new Geom2d_Line(apoint, N);
      occ::handle<Geom2d_TrimmedCurve> BisL   = new Geom2d_TrimmedCurve(L, 0, RC);
      occ::handle<Bisector_BisecAna>   BisAna = new Bisector_BisecAna();
      BisAna->Init(BisL);
      UFirst = BisAna->ParameterOfStartPoint();
      ULast  = BisAna->ParameterOfEndPoint();
      Bis    = BisAna;
    }
    else
    {

      occ::handle<Bisector_BisecPC> BisPC = new Bisector_BisecPC();
      BisPC->Perform(asecondcurve, afirstpoint->Pnt2d(), adirection);

      if (BisPC->IsEmpty())
      {
        gp_Dir2d dir1(afirstvector), dir2(asecondvector);
        double   Nx = -dir1.X() - dir2.X(), Ny = -dir1.Y() - dir2.Y();
        if (std::abs(Nx) <= gp::Resolution() && std::abs(Ny) <= gp::Resolution())
        {
          Nx = -afirstvector.Y();
          Ny = afirstvector.X();
        }

        gp_Dir2d                         N(adirection * Nx, adirection * Ny);
        occ::handle<Geom2d_Line>         L      = new Geom2d_Line(apoint, N);
        occ::handle<Geom2d_TrimmedCurve> BisL   = new Geom2d_TrimmedCurve(L, 0, RC);
        occ::handle<Bisector_BisecAna>   BisAna = new Bisector_BisecAna();
        BisAna->Init(BisL);
        UFirst = BisAna->ParameterOfStartPoint();
        ULast  = BisAna->ParameterOfEndPoint();
        Bis    = BisAna;
      }
      else
      {

        UFirst = BisPC->Parameter(apoint);
        ULast  = BisPC->LastParameter();
        if (UFirst >= ULast)
        {

          gp_Vec2d                 V(BisPC->Value(BisPC->FirstParameter()), BisPC->Value(ULast));
          gp_Dir2d                 N(V);
          occ::handle<Geom2d_Line> L              = new Geom2d_Line(apoint, N);
          occ::handle<Geom2d_TrimmedCurve> BisL   = new Geom2d_TrimmedCurve(L, 0, RC);
          occ::handle<Bisector_BisecAna>   BisAna = new Bisector_BisecAna();
          BisAna->Init(BisL);
          UFirst = BisAna->ParameterOfStartPoint();
          ULast  = BisAna->ParameterOfEndPoint();
          Bis    = BisAna;
        }
        else
          Bis = BisPC;
      }
    }
  }

  UFirst      = std::max(UFirst, Bis->FirstParameter());
  ULast       = std::min(ULast, Bis->LastParameter());
  thebisector = new Geom2d_TrimmedCurve(Bis, UFirst, ULast);
}

void Bisector_Bisec::Perform(const occ::handle<Geom2d_Point>& afirstpoint,
                             const occ::handle<Geom2d_Point>& asecondpoint,
                             const gp_Pnt2d&                  apoint,
                             const gp_Vec2d&                  afirstvector,
                             const gp_Vec2d&                  asecondvector,
                             const double                     adirection,
                             const double                     tolerance,
                             const bool                       oncurve)
{
  occ::handle<Bisector_BisecAna> Bis = new Bisector_BisecAna();

  Bis->Perform(afirstpoint,
               asecondpoint,
               apoint,
               afirstvector,
               asecondvector,
               adirection,
               tolerance,
               oncurve);
  thebisector =
    new Geom2d_TrimmedCurve(Bis, Bis->ParameterOfStartPoint(), Bis->ParameterOfEndPoint());
}

const occ::handle<Geom2d_TrimmedCurve>& Bisector_Bisec::Value() const
{
  return thebisector;
}

const occ::handle<Geom2d_TrimmedCurve>& Bisector_Bisec::ChangeValue()
{
  return thebisector;
}

static void ReplaceByLineIfIsToSmall(occ::handle<Bisector_Curve>& Bis,
                                     double&                      UFirst,
                                     double&                      ULast)

{
  if (std::abs(ULast - UFirst) > 2. * Precision::PConfusion() * 10.)
    return;

  gp_Pnt2d PF = Bis->Value(UFirst);
  gp_Pnt2d PL = Bis->Value(ULast);

  if (PF.Distance(PL) > Precision::Confusion() * 10.)
    return;

  gp_Vec2d T1 = Bis->DN(UFirst, 1);

  occ::handle<Geom2d_CartesianPoint> PG     = new Geom2d_CartesianPoint(PF);
  occ::handle<Geom2d_Line>           L      = new Geom2d_Line(PF, T1);
  occ::handle<Geom2d_TrimmedCurve>   BisL   = new Geom2d_TrimmedCurve(L, 0, Precision::Infinite());
  occ::handle<Bisector_BisecAna>     BisAna = new Bisector_BisecAna();
  BisAna->Init(BisL);
  UFirst = BisAna->ParameterOfStartPoint();
  ULast  = BisAna->ParameterOfEndPoint();
  Bis    = BisAna;
}

static bool IsMaxRC(const occ::handle<Geom2d_Curve>& C, double U, double& R)
{
  double KF, KL;
  double US = C->FirstParameter();
  double UL = C->LastParameter();

  gp_Vec2d D1, D2;
  gp_Pnt2d P;
  double   Norm2;

  C->D2(US, P, D1, D2);
  Norm2 = D1.SquareMagnitude();
  if (Norm2 < gp::Resolution())
  {
    KF = 0.0;
  }
  else
  {
    KF = std::abs(D1 ^ D2) / (Norm2 * sqrt(Norm2));
  }

  C->D2(UL, P, D1, D2);
  Norm2 = D1.SquareMagnitude();
  if (Norm2 < gp::Resolution())
  {
    KL = 0.0;
  }
  else
  {
    KL = std::abs(D1 ^ D2) / (Norm2 * sqrt(Norm2));
  }

  bool IsMax = false;

  if (U == UL)
  {
    if (KL < KF)
    {
      if (KL == 0.0)
        R = Precision::Infinite();
      else
        R = 1 / KL;
      IsMax = true;
    }
  }
  else
  {
    if (KF < KL)
    {
      if (KF == 0.0)
        R = Precision::Infinite();
      else
        R = 1 / KF;
      IsMax = true;
    }
  }
  return IsMax;
}
