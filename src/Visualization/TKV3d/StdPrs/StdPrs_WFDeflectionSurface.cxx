#include <Adaptor3d_IsoCurve.hpp>
#include <BndLib_AddSurface.hpp>
#include <GeomAbs_IsoType.hpp>
#include <gp_Pnt.hpp>
#include <Precision.hpp>
#include <Prs3d_IsoAspect.hpp>
#include <StdPrs_DeflectionCurve.hpp>
#include <StdPrs_WFDeflectionSurface.hpp>

static void FindLimits(const occ::handle<Adaptor3d_Surface>& surf,
                       const double                          aLimit,
                       double&                               UFirst,
                       double&                               ULast,
                       double&                               VFirst,
                       double&                               VLast)
{
  UFirst = surf->FirstUParameter();
  ULast  = surf->LastUParameter();
  VFirst = surf->FirstVParameter();
  VLast  = surf->LastVParameter();

  bool UfirstInf = Precision::IsNegativeInfinite(UFirst);
  bool UlastInf  = Precision::IsPositiveInfinite(ULast);
  bool VfirstInf = Precision::IsNegativeInfinite(VFirst);
  bool VlastInf  = Precision::IsPositiveInfinite(VLast);

  if (UfirstInf || UlastInf)
  {
    gp_Pnt P1, P2;
    double v;
    if (VfirstInf && VlastInf)
      v = 0;
    else if (VfirstInf)
      v = VLast;
    else if (VlastInf)
      v = VFirst;
    else
      v = (VFirst + VLast) / 2;

    double delta = aLimit * 2;

    if (UfirstInf && UlastInf)
    {
      do
      {
        delta /= 2;
        UFirst = -delta;
        ULast  = delta;
        surf->D0(UFirst, v, P1);
        surf->D0(ULast, v, P2);
      } while (P1.Distance(P2) > aLimit);
    }
    else if (UfirstInf)
    {
      surf->D0(ULast, v, P2);
      do
      {
        delta /= 2;
        UFirst = ULast - delta;
        surf->D0(UFirst, v, P1);
      } while (P1.Distance(P2) > aLimit);
    }
    else if (UlastInf)
    {
      surf->D0(UFirst, v, P1);
      do
      {
        delta /= 2;
        ULast = UFirst + delta;
        surf->D0(ULast, v, P2);
      } while (P1.Distance(P2) > aLimit);
    }
  }

  if (VfirstInf || VlastInf)
  {
    gp_Pnt P1, P2;
    double u = (UFirst + ULast) / 2;

    double delta = aLimit * 2;

    if (VfirstInf && VlastInf)
    {
      do
      {
        delta /= 2;
        VFirst = -delta;
        VLast  = delta;
        surf->D0(u, VFirst, P1);
        surf->D0(u, VLast, P2);
      } while (P1.Distance(P2) > aLimit);
    }
    else if (VfirstInf)
    {
      surf->D0(u, VLast, P2);
      do
      {
        delta /= 2;
        VFirst = VLast - delta;
        surf->D0(u, VFirst, P1);
      } while (P1.Distance(P2) > aLimit);
    }
    else if (VlastInf)
    {
      surf->D0(u, VFirst, P1);
      do
      {
        delta /= 2;
        VLast = VFirst + delta;
        surf->D0(u, VLast, P2);
      } while (P1.Distance(P2) > aLimit);
    }
  }
}

void StdPrs_WFDeflectionSurface::Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                     const occ::handle<Adaptor3d_Surface>&  aSurface,
                                     const occ::handle<Prs3d_Drawer>&       aDrawer)
{
  double U1, U2, V1, V2;
  double MaxP = aDrawer->MaximalParameterValue();
  FindLimits(aSurface, MaxP, U1, U2, V1, V2);

  bool UClosed = aSurface->IsUClosed();
  bool VClosed = aSurface->IsVClosed();

  double                  TheDeflection;
  Aspect_TypeOfDeflection TOD = aDrawer->TypeOfDeflection();
  if (TOD == Aspect_TOD_RELATIVE)
  {

    Bnd_Box Total;
    BndLib_AddSurface::Add(*aSurface, U1, U2, V1, V2, 0., Total);
    double m = aDrawer->MaximalChordialDeviation() / aDrawer->DeviationCoefficient();
    double aXmin, aYmin, aZmin, aXmax, aYmax, aZmax;
    Total.Get(aXmin, aYmin, aZmin, aXmax, aYmax, aZmax);
    if (!(Total.IsOpenXmin() || Total.IsOpenXmax()))
      m = std::min(m, std::abs(aXmax - aXmin));
    if (!(Total.IsOpenYmin() || Total.IsOpenYmax()))
      m = std::min(m, std::abs(aYmax - aYmin));
    if (!(Total.IsOpenZmin() || Total.IsOpenZmax()))
      m = std::min(m, std::abs(aZmax - aZmin));

    TheDeflection = m * aDrawer->DeviationCoefficient();
  }
  else
    TheDeflection = aDrawer->MaximalChordialDeviation();

  Adaptor3d_IsoCurve anIso;
  anIso.Load(aSurface);

  if (!(UClosed && VClosed))
  {
    aPresentation->CurrentGroup()->SetPrimitivesAspect(aDrawer->FreeBoundaryAspect()->Aspect());
    if (!UClosed)
    {
      anIso.Load(GeomAbs_IsoU, U1, V1, V2);
      StdPrs_DeflectionCurve::Add(aPresentation, anIso, TheDeflection, MaxP);
      anIso.Load(GeomAbs_IsoU, U2, V1, V2);
      StdPrs_DeflectionCurve::Add(aPresentation, anIso, TheDeflection, MaxP);
    }
    if (!VClosed)
    {
      anIso.Load(GeomAbs_IsoV, V1, U1, U2);
      StdPrs_DeflectionCurve::Add(aPresentation, anIso, TheDeflection, MaxP);
      anIso.Load(GeomAbs_IsoV, V2, U1, U2);
      StdPrs_DeflectionCurve::Add(aPresentation, anIso, TheDeflection, MaxP);
    }
  }

  int fin = aDrawer->UIsoAspect()->Number();
  if (fin != 0)
  {
    aPresentation->CurrentGroup()->SetPrimitivesAspect(aDrawer->UIsoAspect()->Aspect());

    double du = UClosed ? (U2 - U1) / fin : (U2 - U1) / (1 + fin);
    for (int i = 1; i <= fin; i++)
    {
      anIso.Load(GeomAbs_IsoU, U1 + du * i, V1, V2);
      StdPrs_DeflectionCurve::Add(aPresentation, anIso, TheDeflection, MaxP);
    }
  }
  fin = aDrawer->VIsoAspect()->Number();
  if (fin != 0)
  {
    aPresentation->CurrentGroup()->SetPrimitivesAspect(aDrawer->VIsoAspect()->Aspect());

    double dv = VClosed ? (V2 - V1) / fin : (V2 - V1) / (1 + fin);
    for (int i = 1; i <= fin; i++)
    {
      anIso.Load(GeomAbs_IsoV, V1 + dv * i, U1, U2);
      StdPrs_DeflectionCurve::Add(aPresentation, anIso, TheDeflection, MaxP);
    }
  }
}
