#include <Adaptor3d_Curve.hpp>
#include <Approx_CurvlinFunc.hpp>
#include <GeomAdaptor_Curve.hpp>
#include <GeomFill_Frenet.hpp>
#include <GeomFill_GuideTrihedronAC.hpp>
#include <GeomFill_TrihedronLaw.hpp>
#include <GeomLib.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <Precision.hpp>
#include <Standard_Type.hpp>
#include <NCollection_Sequence.hpp>

IMPLEMENT_STANDARD_RTTIEXT(GeomFill_GuideTrihedronAC, GeomFill_TrihedronWithGuide)

GeomFill_GuideTrihedronAC::GeomFill_GuideTrihedronAC(const occ::handle<Adaptor3d_Curve>& guide)
{
  myCurve.Nullify();
  myGuide   = guide;
  myTrimG   = guide;
  myGuideAC = new (Approx_CurvlinFunc)(myGuide, 1.e-7);
  Lguide    = myGuideAC->GetLength();
  UTol = STol = Precision::PConfusion();
  Orig1       = 0;
  Orig2       = 1;
}

occ::handle<Adaptor3d_Curve> GeomFill_GuideTrihedronAC::Guide() const
{
  return myGuide;
}

bool GeomFill_GuideTrihedronAC::D0(const double Param,
                                   gp_Vec&      Tangent,
                                   gp_Vec&      Normal,
                                   gp_Vec&      BiNormal)
{
  double s     = myCurveAC->GetSParameter(Param);
  double OrigG = Orig1 + s * (Orig2 - Orig1);
  double tG    = myGuideAC->GetUParameter(*myGuide, OrigG, 1);

  gp_Pnt P, PG;
  gp_Vec To, B;
  myTrimmed->D1(Param, P, To);
  myTrimG->D0(tG, PG);
  myCurPointOnGuide = PG;

  gp_Vec n(P, PG);

  Normal   = n.Normalized();
  B        = To.Crossed(Normal);
  BiNormal = B / B.Magnitude();
  Tangent  = Normal.Crossed(BiNormal);
  Tangent.Normalize();

  return true;
}

bool GeomFill_GuideTrihedronAC::D1(const double Param,
                                   gp_Vec&      Tangent,
                                   gp_Vec&      DTangent,
                                   gp_Vec&      Normal,
                                   gp_Vec&      DNormal,
                                   gp_Vec&      BiNormal,
                                   gp_Vec&      DBiNormal)
{

  double s, OrigG, tG, dtg;

  s = myCurveAC->GetSParameter(Param);

  OrigG = Orig1 + s * (Orig2 - Orig1);

  tG = myGuideAC->GetUParameter(*myGuide, OrigG, 1);

  gp_Pnt P, PG;
  gp_Vec To, DTo, TG, B, BPrim;

  myTrimmed->D2(Param, P, To, DTo);
  myTrimG->D1(tG, PG, TG);
  myCurPointOnGuide = PG;

  gp_Vec n(P, PG), dn;
  double Norm = n.Magnitude();
  if (Norm < 1.e-12)
  {
    Norm = 1;
#ifdef OCCT_DEBUG
    std::cout << "GuideTrihedronAC : Normal indefinie" << std::endl;
#endif
  }

  n /= Norm;

  dtg = (Orig2 - Orig1) * (To.Magnitude() / TG.Magnitude()) * (Lguide / L);
  dn.SetLinearForm(dtg, TG, -1, To);
  dn /= Norm;

  Normal       = n;
  B            = To.Crossed(Normal);
  double NormB = B.Magnitude();
  B /= NormB;

  BiNormal = B;

  Tangent = Normal.Crossed(BiNormal);
  Tangent.Normalize();

  DNormal.SetLinearForm(-(n.Dot(dn)), n, dn);

  BPrim.SetLinearForm(DTo.Crossed(Normal), To.Crossed(DNormal));

  DBiNormal.SetLinearForm(-(B.Dot(BPrim)), B, BPrim);
  DBiNormal /= NormB;

  DTangent.SetLinearForm(Normal.Crossed(DBiNormal), DNormal.Crossed(BiNormal));

  return true;
}

bool GeomFill_GuideTrihedronAC::D2(const double Param,
                                   gp_Vec&      Tangent,
                                   gp_Vec&      DTangent,
                                   gp_Vec&      D2Tangent,
                                   gp_Vec&      Normal,
                                   gp_Vec&      DNormal,
                                   gp_Vec&      D2Normal,
                                   gp_Vec&      BiNormal,
                                   gp_Vec&      DBiNormal,
                                   gp_Vec&      D2BiNormal)
{

  double s = myCurveAC->GetSParameter(Param);

  double OrigG = Orig1 + s * (Orig2 - Orig1);
  double tG    = myGuideAC->GetUParameter(*myGuide, OrigG, 1);

  gp_Pnt P, PG;
  gp_Vec TG, DTG;

  gp_Vec To, DTo, D2To;

  myTrimmed->D3(Param, P, To, DTo, D2To);
  myTrimG->D2(tG, PG, TG, DTG);
  myCurPointOnGuide = PG;

  double NTo  = To.Magnitude();
  double N2To = To.SquareMagnitude();
  double NTG  = TG.Magnitude();
  double N2Tp = TG.SquareMagnitude();
  double d2tp_dt2, dtg_dt;
  dtg_dt = (Orig2 - Orig1) * (NTo / NTG) * (Lguide / L);

  gp_Vec n(P, PG);
  double Norm = n.Magnitude(), ndn;

  gp_Vec dn, d2n;
  dn.SetLinearForm(dtg_dt, TG, -1, To);

  d2tp_dt2 = (Orig2 - Orig1) * (Lguide / L)
             * (DTo.Dot(To) / (NTo * NTG) - N2To * TG * DTG * (Lguide / L) / (N2Tp * N2Tp));

  d2n.SetLinearForm(dtg_dt * dtg_dt, DTG, d2tp_dt2, TG, -1, DTo);

  if (Norm > 1.e-9)
  {
    n /= Norm;
    dn /= Norm;
    d2n /= Norm;
  }

  Normal = n;

  gp_Vec TN, DTN, D2TN;
  TN = To.Crossed(Normal);

  double Norma = TN.Magnitude();
  if (Norma > 1.e-9)
    TN /= Norma;

  BiNormal = TN;

  Tangent = Normal.Crossed(BiNormal);

  ndn = n.Dot(dn);
  DNormal.SetLinearForm(-ndn, n, dn);

  DTN.SetLinearForm(DTo.Crossed(Normal), To.Crossed(DNormal));
  DTN /= Norma;
  double TNDTN = TN.Dot(DTN);

  DBiNormal.SetLinearForm(-TNDTN, TN, DTN);

  DTangent.SetLinearForm(Normal.Crossed(DBiNormal), DNormal.Crossed(BiNormal));

#ifdef OCCT_DEBUG
  gp_Vec DTDN = DTo.Crossed(DNormal);
  (void)DTDN;
#endif
  double TN2 = TN.SquareMagnitude();

  D2Normal.SetLinearForm(-2 * ndn, dn, 3 * ndn * ndn - (dn.SquareMagnitude() + n.Dot(d2n)), n, d2n);

  D2TN.SetLinearForm(1, D2To.Crossed(Normal), 2, DTo.Crossed(DNormal), To.Crossed(D2Normal));
  D2TN /= Norma;

  D2BiNormal.SetLinearForm(-2 * TNDTN, DTN, 3 * TNDTN * TNDTN - (TN2 + TN.Dot(D2TN)), TN, D2TN);

  D2Tangent.SetLinearForm(1,
                          D2Normal.Crossed(BiNormal),
                          2,
                          DNormal.Crossed(DBiNormal),
                          Normal.Crossed(D2BiNormal));

  return false;
}

occ::handle<GeomFill_TrihedronLaw> GeomFill_GuideTrihedronAC::Copy() const
{
  occ::handle<GeomFill_GuideTrihedronAC> copy = new (GeomFill_GuideTrihedronAC)(myGuide);
  copy->SetCurve(myCurve);
  copy->Origine(Orig1, Orig2);
  return copy;
}

bool GeomFill_GuideTrihedronAC::SetCurve(const occ::handle<Adaptor3d_Curve>& C)
{
  myCurve   = C;
  myTrimmed = C;
  if (!myCurve.IsNull())
  {
    myCurveAC = new (Approx_CurvlinFunc)(C, 1.e-7);
    L         = myCurveAC->GetLength();
  }
  return true;
}

int GeomFill_GuideTrihedronAC::NbIntervals(const GeomAbs_Shape S) const
{
  int Nb;
  Nb = myCurveAC->NbIntervals(S);
  NCollection_Array1<double> DiscC(1, Nb + 1);
  myCurveAC->Intervals(DiscC, S);
  Nb = myGuideAC->NbIntervals(S);
  NCollection_Array1<double> DiscG(1, Nb + 1);
  myGuideAC->Intervals(DiscG, S);

  NCollection_Sequence<double> Seq;
  GeomLib::FuseIntervals(DiscC, DiscG, Seq);

  return Seq.Length() - 1;
}

void GeomFill_GuideTrihedronAC::Intervals(NCollection_Array1<double>& TT,
                                          const GeomAbs_Shape         S) const
{
  int Nb, ii;
  Nb = myCurveAC->NbIntervals(S);
  NCollection_Array1<double> DiscC(1, Nb + 1);
  myCurveAC->Intervals(DiscC, S);
  Nb = myGuideAC->NbIntervals(S);
  NCollection_Array1<double> DiscG(1, Nb + 1);
  myGuideAC->Intervals(DiscG, S);

  NCollection_Sequence<double> Seq;
  GeomLib::FuseIntervals(DiscC, DiscG, Seq);
  Nb = Seq.Length();

  for (ii = 1; ii <= Nb; ii++)
  {
    TT(ii) = myCurveAC->GetUParameter(*myCurve, Seq(ii), 1);
  }
}

void GeomFill_GuideTrihedronAC::SetInterval(const double First, const double Last)
{
  myTrimmed = myCurve->Trim(First, Last, UTol);
  double Sf, Sl, U;

  Sf = myCurveAC->GetSParameter(First);
  Sl = myCurveAC->GetSParameter(Last);

  U       = Orig1 + Sf * (Orig2 - Orig1);
  Sf      = myGuideAC->GetUParameter(*myGuide, U, 1);
  U       = Orig1 + Sl * (Orig2 - Orig1);
  Sl      = myGuideAC->GetUParameter(*myGuide, U, 1);
  myTrimG = myGuide->Trim(Sf, Sl, UTol);
}

void GeomFill_GuideTrihedronAC::GetAverageLaw(gp_Vec& ATangent, gp_Vec& ANormal, gp_Vec& ABiNormal)
{
  int    ii;
  double t, Delta = (myCurve->LastParameter() - myCurve->FirstParameter()) / 20.001;

  ATangent.SetCoord(0., 0., 0.);
  ANormal.SetCoord(0., 0., 0.);
  ABiNormal.SetCoord(0., 0., 0.);
  gp_Vec T, N, B;

  for (ii = 1; ii <= 20; ii++)
  {
    t = myCurve->FirstParameter() + (ii - 1) * Delta;
    D0(t, T, N, B);
    ATangent += T;
    ANormal += N;
    ABiNormal += B;
  }
  ATangent /= 20;
  ANormal /= 20;
  ABiNormal /= 20;
}

bool GeomFill_GuideTrihedronAC::IsConstant() const
{
  return false;
}

bool GeomFill_GuideTrihedronAC::IsOnlyBy3dCurve() const
{
  return false;
}

void GeomFill_GuideTrihedronAC::Origine(const double OrACR1, const double OrACR2)
{
  Orig1 = OrACR1;
  Orig2 = OrACR2;
}
