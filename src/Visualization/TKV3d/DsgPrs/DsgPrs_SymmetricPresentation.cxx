#include <DsgPrs_SymmetricPresentation.hpp>
#include <ElCLib.hpp>
#include <gce_MakeLin.hpp>
#include <gp_Ax1.hpp>
#include <gp_Ax2.hpp>
#include <gp_Circ.hpp>
#include <gp_Dir.hpp>
#include <gp_Lin.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <Graphic3d_ArrayOfPoints.hpp>
#include <Graphic3d_ArrayOfPolylines.hpp>
#include <Graphic3d_AspectLine3d.hpp>
#include <Graphic3d_AspectMarker3d.hpp>
#include <Graphic3d_Group.hpp>
#include <Precision.hpp>
#include <Prs3d_Arrow.hpp>
#include <Prs3d_DimensionAspect.hpp>
#include <Prs3d_LineAspect.hpp>
#include <Prs3d_Presentation.hpp>

void DsgPrs_SymmetricPresentation::Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                       const occ::handle<Prs3d_Drawer>&       aDrawer,
                                       const gp_Pnt&                          AttachmentPoint1,
                                       const gp_Pnt&                          AttachmentPoint2,
                                       const gp_Dir&                          aDirection1,
                                       const gp_Lin&                          aAxis,
                                       const gp_Pnt&                          OffsetPoint)
{
  occ::handle<Prs3d_DimensionAspect> LA = aDrawer->DimensionAspect();
  aPresentation->CurrentGroup()->SetPrimitivesAspect(LA->LineAspect()->Aspect());

  gp_Pnt ProjOffsetPoint = ElCLib::Value(ElCLib::Parameter(aAxis, OffsetPoint), aAxis);
  gp_Pnt PjAttachPnt1    = ElCLib::Value(ElCLib::Parameter(aAxis, AttachmentPoint1), aAxis);
  gp_Dir aDirectionAxis  = aAxis.Direction();
  double h = fabs(ProjOffsetPoint.Distance(PjAttachPnt1) / cos(aDirectionAxis.Angle(aDirection1)));

  gp_Vec VL1(aDirection1);
  gp_Vec VLa(PjAttachPnt1, ProjOffsetPoint);
  double scal;
  scal = VL1.Dot(VLa);
  if (scal < 0)
    VL1.Reverse();
  VL1.Multiply(h);

  gp_Pnt P1, P2;

  if (VLa.Dot(VL1) == 0)
  {
    P1 = AttachmentPoint1.Translated(VLa);
    gp_Vec VPntat2Axe(PjAttachPnt1, AttachmentPoint2);
    P2 = ProjOffsetPoint.Translated(VPntat2Axe);
  }
  else
  {
    P1 = AttachmentPoint1.Translated(VL1);
    gp_Vec VPntat1Axe(P1, ProjOffsetPoint);
    P2 = ProjOffsetPoint.Translated(VPntat1Axe);
  }

  gp_Lin L3 = gce_MakeLin(P1, P2);
  double parmin, parmax, parcur;
  parmin      = ElCLib::Parameter(L3, P1);
  parmax      = parmin;
  parcur      = ElCLib::Parameter(L3, P2);
  double dist = std::abs(parmin - parcur);
  if (parcur < parmin)
    parmin = parcur;
  if (parcur > parmax)
    parmax = parcur;
  parcur      = ElCLib::Parameter(L3, OffsetPoint);
  gp_Pnt offp = ElCLib::Value(parcur, L3);

  bool outside = false;
  if (parcur < parmin)
  {
    parmin  = parcur;
    outside = true;
  }
  if (parcur > parmax)
  {
    parmax  = parcur;
    outside = true;
  }

  gp_Pnt PointMin = ElCLib::Value(parmin, L3);
  gp_Pnt PointMax = ElCLib::Value(parmax, L3);

  double X, Y, Z;
  double D1(aAxis.Distance(AttachmentPoint1)), coeff(.5);
  gp_Pnt pint, Pj_P1, P1Previous = P1;

  bool   Cross = false;
  gp_Vec Attch1_PjAttch1(AttachmentPoint1, PjAttachPnt1);
  gp_Vec v(P1, ProjOffsetPoint);
  if (v.IsOpposite((Attch1_PjAttch1), Precision::Confusion()))
  {
    Cross = true;
    gp_Pnt PntTempo;
    PntTempo = P1;
    P1       = P2;
    P2       = PntTempo;
  }

  gp_Vec Vfix;
  double alpha, b;

  if (aAxis.Distance(P1) > D1 * (1 + coeff) && !Cross)
  {

    aPresentation->NewGroup();
    aPresentation->CurrentGroup()->SetPrimitivesAspect(LA->LineAspect()->Aspect());

    Pj_P1 = ElCLib::Value(ElCLib::Parameter(aAxis, P1), aAxis);
    gp_Vec Vp(Pj_P1, P1);
    Vfix = Vp.Divided(Vp.Magnitude()).Multiplied(D1 * (1 + coeff));
    P1   = Pj_P1.Translated(Vfix);
    P2   = Pj_P1.Translated(Vfix.Reversed());

    L3     = gce_MakeLin(P1, P2);
    parmin = ElCLib::Parameter(L3, P1);
    parmax = parmin;
    parcur = ElCLib::Parameter(L3, P2);
    dist   = std::abs(parmin - parcur);
    if (parcur < parmin)
      parmin = parcur;
    if (parcur > parmax)
      parmax = parcur;
    parcur  = ElCLib::Parameter(L3, OffsetPoint);
    offp    = ElCLib::Value(parcur, L3);
    outside = false;
    if (parcur < parmin)
    {
      parmin  = parcur;
      outside = true;
    }
    if (parcur > parmax)
    {
      parmax  = parcur;
      outside = true;
    }
    PointMin = ElCLib::Value(parmin, L3);
    PointMax = ElCLib::Value(parmax, L3);

    occ::handle<Graphic3d_ArrayOfPolylines> aPrims = new Graphic3d_ArrayOfPolylines(8, 3);

    aPrims->AddBound(2);
    aPrims->AddVertex(PointMin);
    aPrims->AddVertex(PointMax);

    alpha = aDirectionAxis.Angle(aDirection1);
    b     = (coeff * D1) / sin(alpha);
    gp_Vec Vpint(AttachmentPoint1, P1Previous);
    pint = AttachmentPoint1.Translated(Vpint.Divided(Vpint.Magnitude()).Multiplied(b));

    aPrims->AddBound(3);
    aPrims->AddVertex(AttachmentPoint1);
    aPrims->AddVertex(pint);
    aPrims->AddVertex(P1);

    gp_Pnt Pj_pint = ElCLib::Value(ElCLib::Parameter(aAxis, pint), aAxis);
    gp_Vec V_int(pint, Pj_pint);
    gp_Pnt Sym_pint = Pj_pint.Translated(V_int);

    aPrims->AddBound(3);
    aPrims->AddVertex(AttachmentPoint2);
    aPrims->AddVertex(Sym_pint);
    aPrims->AddVertex(P2);

    aPresentation->CurrentGroup()->AddPrimitiveArray(aPrims);
  }

  else if (aAxis.Distance(P1) < D1 * (1 - coeff) || Cross)
  {

    aPresentation->NewGroup();
    aPresentation->CurrentGroup()->SetPrimitivesAspect(LA->LineAspect()->Aspect());

    Pj_P1 = ElCLib::Value(ElCLib::Parameter(aAxis, P1), aAxis);
    gp_Vec VpInf(Pj_P1, P1);
    Vfix = VpInf.Divided(VpInf.Magnitude()).Multiplied(D1 * (1 - coeff));
    Pj_P1.Translated(Vfix).Coord(X, Y, Z);
    P1.SetCoord(X, Y, Z);
    Pj_P1.Translated(Vfix.Reversed()).Coord(X, Y, Z);
    P2.SetCoord(X, Y, Z);

    L3     = gce_MakeLin(P1, P2);
    parmin = ElCLib::Parameter(L3, P1);
    parmax = parmin;
    parcur = ElCLib::Parameter(L3, P2);
    dist   = std::abs(parmin - parcur);
    if (parcur < parmin)
      parmin = parcur;
    if (parcur > parmax)
      parmax = parcur;
    parcur  = ElCLib::Parameter(L3, OffsetPoint);
    offp    = ElCLib::Value(parcur, L3);
    outside = false;
    if (parcur < parmin)
    {
      parmin  = parcur;
      outside = true;
    }
    if (parcur > parmax)
    {
      parmax  = parcur;
      outside = true;
    }
    PointMin = ElCLib::Value(parmin, L3);
    PointMax = ElCLib::Value(parmax, L3);

    occ::handle<Graphic3d_ArrayOfPolylines> aPrims = new Graphic3d_ArrayOfPolylines(8, 3);

    aPrims->AddBound(2);
    aPrims->AddVertex(PointMin);
    aPrims->AddVertex(PointMax);

    alpha = aDirectionAxis.Angle(aDirection1);
    b     = (coeff * D1) / sin(alpha);
    gp_Vec Vpint(AttachmentPoint1, P1Previous);
    pint = AttachmentPoint1.Translated(Vpint.Divided(Vpint.Magnitude()).Multiplied(b));

    aPrims->AddBound(3);
    aPrims->AddVertex(AttachmentPoint1);
    aPrims->AddVertex(pint);
    aPrims->AddVertex(P1);

    gp_Pnt Pj_pint = ElCLib::Value(ElCLib::Parameter(aAxis, pint), aAxis);
    gp_Vec V_int(pint, Pj_pint);
    gp_Pnt Sym_pint = Pj_pint.Translated(V_int);

    aPrims->AddBound(3);
    aPrims->AddVertex(AttachmentPoint2);
    aPrims->AddVertex(Sym_pint);
    aPrims->AddVertex(P2);

    aPresentation->CurrentGroup()->AddPrimitiveArray(aPrims);
  }
  else
  {

    aPresentation->NewGroup();
    aPresentation->CurrentGroup()->SetPrimitivesAspect(LA->LineAspect()->Aspect());

    occ::handle<Graphic3d_ArrayOfSegments> aPrims = new Graphic3d_ArrayOfSegments(6);

    aPrims->AddVertex(PointMin);
    aPrims->AddVertex(PointMax);

    aPrims->AddVertex(AttachmentPoint1);
    aPrims->AddVertex(P1);

    aPrims->AddVertex(AttachmentPoint2);
    aPrims->AddVertex(P2);

    aPresentation->CurrentGroup()->AddPrimitiveArray(aPrims);
  }

  aPresentation->NewGroup();
  aPresentation->CurrentGroup()->SetPrimitivesAspect(LA->LineAspect()->Aspect());

  if (dist < (LA->ArrowAspect()->Length() + LA->ArrowAspect()->Length()))
    outside = true;
  gp_Dir arrdir = L3.Direction().Reversed();
  if (outside)
    arrdir.Reverse();

  Prs3d_Arrow::Draw(aPresentation->CurrentGroup(),
                    P1,
                    arrdir,
                    LA->ArrowAspect()->Angle(),
                    LA->ArrowAspect()->Length());

  Prs3d_Arrow::Draw(aPresentation->CurrentGroup(),
                    P2,
                    arrdir.Reversed(),
                    LA->ArrowAspect()->Angle(),
                    LA->ArrowAspect()->Length());

  gp_Vec Vvar(P1, P2);
  gp_Vec vec;
  gp_Vec Vtmp =
    Vvar.Divided(Vvar.Magnitude())
      .Multiplied((aAxis.Distance(AttachmentPoint1) + aAxis.Distance(AttachmentPoint2)));
  vec.SetCoord(Vtmp.X(), Vtmp.Y(), Vtmp.Z());
  gp_Vec vecA = vec.Multiplied(.1);

  gp_Dir DirAxis = aAxis.Direction();
  gp_Vec Vaxe(DirAxis);
  gp_Vec vecB = Vaxe.Multiplied(vecA.Magnitude());
  vecB.Multiply(.5);

  gp_Pnt pm, pOff;
  if (VLa.Dot(VL1) == 0)
  {
    gp_Vec Vper(P1, ElCLib::Value(ElCLib::Parameter(aAxis, P1), aAxis));
    pm = P1.Translated(Vper);
  }
  else
  {
    pm = P1.Translated(Vvar.Multiplied(.5));
  }
  pOff = OffsetPoint.Translated(vecB);

  gp_Vec vecAxe = vecA.Multiplied(.7);

  aPresentation->NewGroup();
  aPresentation->CurrentGroup()->SetPrimitivesAspect(LA->LineAspect()->Aspect());

  occ::handle<Graphic3d_ArrayOfPolylines> aPrims = new Graphic3d_ArrayOfPolylines(13, 5);

  aPrims->AddBound(2);
  aPrims->AddVertex(pOff.Translated(vecAxe));
  aPrims->AddVertex(pOff.Translated(vecAxe.Reversed()));

  gp_Vec vec1 = vecAxe.Multiplied(.6);
  vecAxe      = Vaxe.Multiplied(vecAxe.Magnitude());
  gp_Vec vec2 = vecAxe.Multiplied(.4);

  aPrims->AddBound(2);
  aPrims->AddVertex(pOff.Translated(vec1.Added(vec2)));
  aPrims->AddVertex(pOff.Translated(vec1.Reversed().Added(vec2)));

  aPrims->AddBound(2);
  aPrims->AddVertex(pOff.Translated(vec1.Added(vec2.Reversed())));
  aPrims->AddVertex(pOff.Translated(vec1.Reversed().Added(vec2.Reversed())));

  double Dist = (aAxis.Distance(AttachmentPoint1) + aAxis.Distance(AttachmentPoint2)) / 75;
  gp_Vec vs(aDirectionAxis);
  gp_Vec vsym(vs.Divided(vs.Magnitude()).Multiplied(Dist).XYZ());
  gp_Vec vsymper(vsym.Y(), -vsym.X(), vsym.Z());

  aPrims->AddBound(5);
  gp_Pnt pm1 = pm.Translated(vsym.Added(vsymper));
  aPrims->AddVertex(pm1);
  pm1 = pm1.Translated(vsym.Reversed().Multiplied(2).Added(vsymper.Reversed().Multiplied(2)));
  aPrims->AddVertex(pm1);
  pm1 = pm1.Translated(vsymper.Multiplied(2));
  aPrims->AddVertex(pm1);
  pm1 = pm1.Translated(vsym.Multiplied(2).Added(vsymper.Reversed().Multiplied(2)));
  aPrims->AddVertex(pm1);
  pm1 = pm1.Translated(vsymper.Multiplied(2));
  aPrims->AddVertex(pm1);

  vsym.Multiply(4);

  aPrims->AddBound(2);
  aPrims->AddVertex(pm.Translated(vsym));
  aPrims->AddVertex(pm.Translated(vsym.Reversed()));

  aPresentation->CurrentGroup()->AddPrimitiveArray(aPrims);
}

void DsgPrs_SymmetricPresentation::Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                       const occ::handle<Prs3d_Drawer>&       aDrawer,
                                       const gp_Pnt&                          AttachmentPoint1,
                                       const gp_Pnt&                          AttachmentPoint2,
                                       const gp_Circ&                         aCircle1,
                                       const gp_Lin&                          aAxis,
                                       const gp_Pnt&                          OffsetPoint)
{
  occ::handle<Prs3d_DimensionAspect> LA = aDrawer->DimensionAspect();
  aPresentation->CurrentGroup()->SetPrimitivesAspect(LA->LineAspect()->Aspect());

  gp_Pnt OffsetPnt(OffsetPoint.X(), OffsetPoint.Y(), OffsetPoint.Z());
  gp_Pnt Center1         = aCircle1.Location();
  gp_Pnt ProjOffsetPoint = ElCLib::Value(ElCLib::Parameter(aAxis, OffsetPnt), aAxis);
  gp_Pnt ProjCenter1     = ElCLib::Value(ElCLib::Parameter(aAxis, Center1), aAxis);
  gp_Vec Vp(ProjCenter1, Center1);
  if (Vp.Magnitude() <= Precision::Confusion())
    Vp = gp_Vec(aAxis.Direction()) ^ aCircle1.Position().Direction();

  double Dt, R, h;
  Dt = ProjCenter1.Distance(ProjOffsetPoint);
  R  = aCircle1.Radius();
  if (Dt > .999 * R)
  {
    Dt = .999 * R;
    gp_Vec Vout(ProjCenter1, ProjOffsetPoint);
    ProjOffsetPoint = ProjCenter1.Translated(Vout.Divided(Vout.Magnitude()).Multiplied(Dt));
    OffsetPnt       = ProjOffsetPoint;
  }
  h         = std::sqrt(R * R - Dt * Dt);
  gp_Pnt P1 = ProjOffsetPoint.Translated(Vp.Added(Vp.Divided(Vp.Magnitude()).Multiplied(h)));
  gp_Vec v(P1, ProjOffsetPoint);
  gp_Pnt P2 = ProjOffsetPoint.Translated(v);

  gp_Lin L3 = gce_MakeLin(P1, P2);
  double parmin, parmax, parcur;
  parmin      = ElCLib::Parameter(L3, P1);
  parmax      = parmin;
  parcur      = ElCLib::Parameter(L3, P2);
  double dist = std::abs(parmin - parcur);
  if (parcur < parmin)
    parmin = parcur;
  if (parcur > parmax)
    parmax = parcur;
  parcur = ElCLib::Parameter(L3, OffsetPnt);

  bool outside = false;
  if (parcur < parmin)
  {
    parmin  = parcur;
    outside = true;
  }
  if (parcur > parmax)
  {
    parmax  = parcur;
    outside = true;
  }
  gp_Pnt PointMin = ElCLib::Value(parmin, L3);
  gp_Pnt PointMax = ElCLib::Value(parmax, L3);

  occ::handle<Graphic3d_ArrayOfPrimitives> aPrims = new Graphic3d_ArrayOfSegments(2);
  aPrims->AddVertex(PointMin);
  aPrims->AddVertex(PointMax);
  aPresentation->CurrentGroup()->AddPrimitiveArray(aPrims);

  int    nbp           = 10;
  double ParamP1       = ElCLib::Parameter(aCircle1, P1);
  double ParamPAttach1 = ElCLib::Parameter(aCircle1, AttachmentPoint1);
  double alpha, Dalpha, alphaIter;

  alpha = fabs(ParamP1 - ParamPAttach1);
  if (ParamP1 < ParamPAttach1)
  {
    if (alpha > M_PI)
    {
      alpha  = (2. * M_PI) - alpha;
      nbp    = (int)std::trunc(alpha / (alpha * .02));
      Dalpha = alpha / (nbp - 1);
    }
    else
    {
      nbp    = (int)std::trunc(alpha / (alpha * .02));
      Dalpha = -alpha / (nbp - 1);
    }
  }
  else
  {
    if (alpha > M_PI)
    {
      alpha  = (2. * M_PI) - alpha;
      nbp    = (int)std::trunc(alpha / (alpha * .02));
      Dalpha = -alpha / (nbp - 1);
    }
    else
    {
      nbp    = (int)std::trunc(alpha / (alpha * .02));
      Dalpha = alpha / (nbp - 1);
    }
  }

  aPrims = new Graphic3d_ArrayOfPolylines(nbp);
  aPrims->AddVertex(AttachmentPoint1);
  alphaIter = Dalpha;
  int i;
  for (i = 2; i <= nbp; i++, alphaIter += Dalpha)
    aPrims->AddVertex(ElCLib::Value(ParamPAttach1 + alphaIter, aCircle1));
  aPresentation->CurrentGroup()->AddPrimitiveArray(aPrims);

  gp_Pnt  Center2 = ProjCenter1.Translated(Vp.Reversed());
  gp_Dir  DirC2   = aCircle1.Axis().Direction();
  gp_Ax2  AxeC2(Center2, DirC2);
  gp_Circ aCircle2(AxeC2, aCircle1.Radius());
  double  ParamP2       = ElCLib::Parameter(aCircle2, P2);
  double  ParamPAttach2 = ElCLib::Parameter(aCircle2, AttachmentPoint2);

  alpha = fabs(ParamP2 - ParamPAttach2);
  if (alpha <= Precision::Confusion())
    alpha = 1.e-5;
  if (ParamP2 < ParamPAttach2)
  {
    if (alpha > M_PI)
    {
      alpha  = (2 * M_PI) - alpha;
      nbp    = (int)std::trunc(alpha / (alpha * .02));
      Dalpha = alpha / (nbp - 1);
    }
    else
    {
      nbp    = (int)std::trunc(alpha / (alpha * .02));
      Dalpha = -alpha / (nbp - 1);
    }
  }
  else
  {
    if (alpha > M_PI)
    {
      alpha  = (2 * M_PI) - alpha;
      nbp    = (int)std::trunc(alpha / (alpha * .02));
      Dalpha = -alpha / (nbp - 1);
    }
    else
    {
      nbp    = (int)std::trunc(alpha / (alpha * .02));
      Dalpha = alpha / (nbp - 1);
    }
  }

  aPrims = new Graphic3d_ArrayOfPolylines(nbp);
  aPrims->AddVertex(AttachmentPoint2);
  alphaIter = Dalpha;
  for (i = 2; i <= nbp; i++, alphaIter += Dalpha)
    aPrims->AddVertex(ElCLib::Value(ParamPAttach2 + alphaIter, aCircle2));
  aPresentation->CurrentGroup()->AddPrimitiveArray(aPrims);

  aPresentation->NewGroup();
  aPresentation->CurrentGroup()->SetPrimitivesAspect(LA->LineAspect()->Aspect());

  if (dist < (LA->ArrowAspect()->Length() + LA->ArrowAspect()->Length()))
    outside = true;
  gp_Dir arrdir = L3.Direction().Reversed();
  if (outside)
    arrdir.Reverse();

  Prs3d_Arrow::Draw(aPresentation->CurrentGroup(),
                    P1,
                    arrdir,
                    LA->ArrowAspect()->Angle(),
                    LA->ArrowAspect()->Length());

  Prs3d_Arrow::Draw(aPresentation->CurrentGroup(),
                    P2,
                    arrdir.Reversed(),
                    LA->ArrowAspect()->Angle(),
                    LA->ArrowAspect()->Length());

  gp_Vec Vvar(P1, P2);
  gp_Vec Vtmp = Vvar.Divided(Vvar.Magnitude()).Multiplied(2 * (aAxis.Distance(Center1)));
  gp_Vec vec  = Vtmp;
  gp_Vec vecA = vec.Multiplied(.1);

  gp_Dir DirAxis = aAxis.Direction();
  gp_Vec Vaxe(DirAxis);
  gp_Vec vecB = Vaxe.Multiplied(vecA.Magnitude());
  vecB.Multiply(.5);

  gp_Pnt pm   = P1.Translated(Vvar.Multiplied(.5));
  gp_Pnt pOff = OffsetPnt.Translated(vecB);

  gp_Vec vecAxe = vecA.Multiplied(.7);

  aPresentation->NewGroup();
  aPresentation->CurrentGroup()->SetPrimitivesAspect(LA->LineAspect()->Aspect());

  aPrims = new Graphic3d_ArrayOfPolylines(13, 5);

  aPrims->AddBound(2);
  aPrims->AddVertex(pOff.Translated(vecAxe));
  aPrims->AddVertex(pOff.Translated(vecAxe.Reversed()));

  gp_Vec vec1 = vecAxe.Multiplied(.6);
  vecAxe      = Vaxe.Multiplied(vecAxe.Magnitude());
  gp_Vec vec2 = vecAxe.Multiplied(.4);

  aPrims->AddBound(2);
  aPrims->AddVertex(pOff.Translated(vec1.Added(vec2)));
  aPrims->AddVertex(pOff.Translated(vec1.Reversed().Added(vec2)));

  aPrims->AddBound(2);
  aPrims->AddVertex(pOff.Translated(vec1.Added(vec2.Reversed())));
  aPrims->AddVertex(pOff.Translated(vec1.Reversed().Added(vec2.Reversed())));

  double Dist           = aAxis.Distance(Center1) / 37;
  gp_Dir aDirectionAxis = aAxis.Direction();
  gp_Vec vs(aDirectionAxis);
  gp_Vec vsym(vs.Divided(vs.Magnitude()).Multiplied(Dist).XYZ());
  gp_Vec vsymper(vsym.Y(), -vsym.X(), vsym.Z());

  aPrims->AddBound(5);
  gp_Pnt pm1 = pm.Translated(vsym.Added(vsymper));
  aPrims->AddVertex(pm1);
  pm1 = pm1.Translated(vsym.Reversed().Multiplied(2).Added(vsymper.Reversed().Multiplied(2)));
  aPrims->AddVertex(pm1);
  pm1 = pm1.Translated(vsymper.Multiplied(2));
  aPrims->AddVertex(pm1);
  pm1 = pm1.Translated(vsym.Multiplied(2).Added(vsymper.Reversed().Multiplied(2)));
  aPrims->AddVertex(pm1);
  pm1 = pm1.Translated(vsymper.Multiplied(2));
  aPrims->AddVertex(pm1);

  vsym.Multiply(4);

  aPrims->AddBound(2);
  aPrims->AddVertex(pm.Translated(vsym));
  aPrims->AddVertex(pm.Translated(vsym.Reversed()));

  aPresentation->CurrentGroup()->AddPrimitiveArray(aPrims);
}

void DsgPrs_SymmetricPresentation::Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                       const occ::handle<Prs3d_Drawer>&       aDrawer,
                                       const gp_Pnt&                          AttachmentPoint1,
                                       const gp_Pnt&                          AttachmentPoint2,
                                       const gp_Lin&                          aAxis,
                                       const gp_Pnt&                          OffsetPoint)
{
  occ::handle<Prs3d_DimensionAspect> LA = aDrawer->DimensionAspect();
  aPresentation->CurrentGroup()->SetPrimitivesAspect(LA->LineAspect()->Aspect());

  if (AttachmentPoint1.IsEqual(AttachmentPoint2, Precision::Confusion()))
  {

    Quantity_Color                        aColor = LA->LineAspect()->Aspect()->Color();
    occ::handle<Graphic3d_AspectMarker3d> aMarkerAsp =
      new Graphic3d_AspectMarker3d(Aspect_TOM_O, aColor, 1.0);
    aPresentation->CurrentGroup()->SetPrimitivesAspect(aMarkerAsp);
    occ::handle<Graphic3d_ArrayOfPoints> anArrayOfPoints = new Graphic3d_ArrayOfPoints(1);
    anArrayOfPoints->AddVertex(AttachmentPoint1.X(), AttachmentPoint1.Y(), AttachmentPoint1.Z());
    aPresentation->CurrentGroup()->AddPrimitiveArray(anArrayOfPoints);

    aPresentation->NewGroup();
    aPresentation->CurrentGroup()->SetPrimitivesAspect(LA->LineAspect()->Aspect());

    occ::handle<Graphic3d_ArrayOfSegments> aPrims = new Graphic3d_ArrayOfSegments(8);

    aPrims->AddVertex(AttachmentPoint1);
    aPrims->AddVertex(OffsetPoint);

    gp_Vec VAO(AttachmentPoint1, OffsetPoint);
    gp_Vec uVAO  = VAO.Divided(VAO.Magnitude());
    gp_Pnt pDaxe = OffsetPoint.Translated(uVAO.Multiplied(3.));
    gp_Pnt pFaxe = pDaxe.Translated(uVAO.Multiplied(12.));

    aPrims->AddVertex(pDaxe);
    aPrims->AddVertex(pFaxe);

    gp_Vec nVAO(-uVAO.Y(), uVAO.X(), uVAO.Z());
    gp_Pnt sgP11 = pDaxe.Translated(uVAO.Multiplied(2.).Added(nVAO.Multiplied(2.)));
    gp_Pnt sgP12 = sgP11.Translated(uVAO.Multiplied(8.));

    aPrims->AddVertex(sgP11);
    aPrims->AddVertex(sgP12);

    gp_Vec nVAOr = nVAO.Reversed();
    gp_Pnt sgP21 = pDaxe.Translated(uVAO.Multiplied(2.).Added(nVAOr.Multiplied(2.)));
    gp_Pnt sgP22 = sgP21.Translated(uVAO.Multiplied(8.));

    aPrims->AddVertex(sgP21);
    aPrims->AddVertex(sgP22);

    aPresentation->CurrentGroup()->AddPrimitiveArray(aPrims);
  }

  else
  {
    gp_Pnt ProjOffsetPoint      = ElCLib::Value(ElCLib::Parameter(aAxis, OffsetPoint), aAxis);
    gp_Pnt ProjAttachmentPoint1 = ElCLib::Value(ElCLib::Parameter(aAxis, AttachmentPoint1), aAxis);
    gp_Vec PjAtt1_Att1(ProjAttachmentPoint1, AttachmentPoint1);
    gp_Pnt P1 = ProjOffsetPoint.Translated(PjAtt1_Att1);
    gp_Pnt P2 = ProjOffsetPoint.Translated(PjAtt1_Att1.Reversed());

    gp_Lin L3 = gce_MakeLin(P1, P2);
    double parmin, parmax, parcur;
    parmin      = ElCLib::Parameter(L3, P1);
    parmax      = parmin;
    parcur      = ElCLib::Parameter(L3, P2);
    double dist = std::abs(parmin - parcur);
    if (parcur < parmin)
      parmin = parcur;
    if (parcur > parmax)
      parmax = parcur;
    parcur = ElCLib::Parameter(L3, OffsetPoint);

    bool outside = false;
    if (parcur < parmin)
    {
      parmin  = parcur;
      outside = true;
    }
    if (parcur > parmax)
    {
      parmax  = parcur;
      outside = true;
    }
    gp_Pnt PointMin = ElCLib::Value(parmin, L3);
    gp_Pnt PointMax = ElCLib::Value(parmax, L3);

    aPresentation->NewGroup();
    aPresentation->CurrentGroup()->SetPrimitivesAspect(LA->LineAspect()->Aspect());

    occ::handle<Graphic3d_ArrayOfPrimitives> aPrims = new Graphic3d_ArrayOfSegments(6);

    aPrims->AddVertex(PointMin);
    aPrims->AddVertex(PointMax);

    aPrims->AddVertex(AttachmentPoint1);
    aPrims->AddVertex(P1);

    aPrims->AddVertex(AttachmentPoint2);
    aPrims->AddVertex(P2);

    aPresentation->CurrentGroup()->AddPrimitiveArray(aPrims);

    if (dist < (LA->ArrowAspect()->Length() + LA->ArrowAspect()->Length()))
      outside = true;
    gp_Dir arrdir = L3.Direction().Reversed();
    if (outside)
      arrdir.Reverse();

    Prs3d_Arrow::Draw(aPresentation->CurrentGroup(),
                      P1,
                      arrdir,
                      LA->ArrowAspect()->Angle(),
                      LA->ArrowAspect()->Length());

    Prs3d_Arrow::Draw(aPresentation->CurrentGroup(),
                      P2,
                      arrdir.Reversed(),
                      LA->ArrowAspect()->Angle(),
                      LA->ArrowAspect()->Length());

    aPresentation->NewGroup();
    aPresentation->CurrentGroup()->SetPrimitivesAspect(LA->LineAspect()->Aspect());

    Quantity_Color                        aColor = LA->LineAspect()->Aspect()->Color();
    occ::handle<Graphic3d_AspectMarker3d> aMarkerAspAtt =
      new Graphic3d_AspectMarker3d(Aspect_TOM_O, aColor, 1.0);
    aPresentation->CurrentGroup()->SetPrimitivesAspect(aMarkerAspAtt);
    occ::handle<Graphic3d_ArrayOfPoints> anArrayOfPoints1 = new Graphic3d_ArrayOfPoints(1);
    anArrayOfPoints1->AddVertex(AttachmentPoint1.X(), AttachmentPoint1.Y(), AttachmentPoint1.Z());
    aPresentation->CurrentGroup()->AddPrimitiveArray(anArrayOfPoints1);

    aPresentation->NewGroup();
    aPresentation->CurrentGroup()->SetPrimitivesAspect(LA->LineAspect()->Aspect());
    aPresentation->CurrentGroup()->SetPrimitivesAspect(aMarkerAspAtt);
    occ::handle<Graphic3d_ArrayOfPoints> anArrayOfPoints2 = new Graphic3d_ArrayOfPoints(1);
    anArrayOfPoints2->AddVertex(AttachmentPoint2.X(), AttachmentPoint2.Y(), AttachmentPoint2.Z());
    aPresentation->CurrentGroup()->AddPrimitiveArray(anArrayOfPoints2);

    gp_Vec vec(P1, P2);
    gp_Vec vecA = vec.Multiplied(.1);

    gp_Dir DirAxis = aAxis.Direction();
    gp_Vec Vaxe(DirAxis);
    gp_Vec vecB = Vaxe.Multiplied(vecA.Magnitude());
    vecB.Multiply(.5);

    gp_Pnt pm   = P1.Translated(vec.Multiplied(.5));
    gp_Pnt pOff = OffsetPoint.Translated(vecB);

    gp_Vec vecAxe = vecA.Multiplied(.7);

    aPresentation->NewGroup();
    aPresentation->CurrentGroup()->SetPrimitivesAspect(LA->LineAspect()->Aspect());

    aPrims = new Graphic3d_ArrayOfPolylines(13, 5);

    aPrims->AddBound(2);
    aPrims->AddVertex(pOff.Translated(vecAxe));
    aPrims->AddVertex(pOff.Translated(vecAxe.Reversed()));

    gp_Vec vec1 = vecAxe.Multiplied(.6);
    vecAxe      = Vaxe.Multiplied(vecAxe.Magnitude());
    gp_Vec vec2 = vecAxe.Multiplied(.4);

    aPrims->AddBound(2);
    aPrims->AddVertex(pOff.Translated(vec1.Added(vec2)));
    aPrims->AddVertex(pOff.Translated(vec1.Reversed().Added(vec2)));

    aPrims->AddBound(2);
    aPrims->AddVertex(pOff.Translated(vec1.Added(vec2.Reversed())));
    aPrims->AddVertex(pOff.Translated(vec1.Reversed().Added(vec2.Reversed())));

    double Dist           = P1.Distance(P2) / 75;
    gp_Dir aDirectionAxis = aAxis.Direction();
    gp_Vec vs(aDirectionAxis);
    gp_Vec vsym(vs.Divided(vs.Magnitude()).Multiplied(Dist).XYZ());
    gp_Vec vsymper(vsym.Y(), -vsym.X(), vsym.Z());

    aPrims->AddBound(5);
    gp_Pnt pm1 = pm.Translated(vsym.Added(vsymper));
    aPrims->AddVertex(pm1);
    pm1 = pm1.Translated(vsym.Reversed().Multiplied(2).Added(vsymper.Reversed().Multiplied(2)));
    aPrims->AddVertex(pm1);
    pm1 = pm1.Translated(vsymper.Multiplied(2));
    aPrims->AddVertex(pm1);
    pm1 = pm1.Translated(vsym.Multiplied(2).Added(vsymper.Reversed().Multiplied(2)));
    aPrims->AddVertex(pm1);
    pm1 = pm1.Translated(vsymper.Multiplied(2));
    aPrims->AddVertex(pm1);

    vsym.Multiply(4);

    aPrims->AddBound(2);
    aPrims->AddVertex(pm.Translated(vsym));
    aPrims->AddVertex(pm.Translated(vsym.Reversed()));

    aPresentation->CurrentGroup()->AddPrimitiveArray(aPrims);
  }
}
