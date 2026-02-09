#include <IGESConvGeom.hpp>

#include <BSplCLib.hpp>
#include <BSplSLib.hpp>
#include <Geom2d_BSplineCurve.hpp>
#include <Geom_BSplineCurve.hpp>
#include <Geom_BSplineSurface.hpp>
#include <gp_GTrsf.hpp>
#include <gp_Trsf.hpp>
#include <IGESData_ToolLocation.hpp>
#include <IGESGeom_SplineCurve.hpp>
#include <IGESGeom_SplineSurface.hpp>
#include <PLib.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Integer.hpp>

int IGESConvGeom::SplineCurveFromIGES(const occ::handle<IGESGeom_SplineCurve>& st,
                                      const double,
                                      const double                    epsgeom,
                                      occ::handle<Geom_BSplineCurve>& res)
{
  int returned = 0;

  int degree = st->SplineType();
  if (degree > 3)
    degree = 3;

  int nbSegs = st->NbSegments();
  if (nbSegs < 1)
    return 5;

  int nbKnots = nbSegs + 1;

  NCollection_Array1<int> multi(1, nbKnots);
  multi.Init(degree);
  multi.SetValue(multi.Lower(), degree + 1);
  multi.SetValue(multi.Upper(), degree + 1);

  NCollection_Array1<double> knots(1, nbKnots);
  NCollection_Array1<double> delta(1, nbSegs);
  int                        i;
  for (i = 1; i <= nbKnots; i++)
    knots.SetValue(i, st->BreakPoint(i));

  for (i = 1; i <= nbSegs; i++)
    delta.SetValue(i, st->BreakPoint(i + 1) - st->BreakPoint(i));

  NCollection_Array1<gp_Pnt> bspoles(1, nbSegs * degree + 1);
  int                        ibspole = bspoles.Lower() - 1;

  for (i = 1; i <= nbSegs; i++)
  {
    double AX, BX, CX, DX, AY, BY, CY, DY, AZ, BZ, CZ, DZ;
    st->XCoordPolynomial(i, AX, BX, CX, DX);
    st->YCoordPolynomial(i, AY, BY, CY, DY);
    st->ZCoordPolynomial(i, AZ, BZ, CZ, DZ);
    if (st->NbDimensions() == 2)
      BZ = 0., CZ = 0., DZ = 0.;
    double Di  = delta(i);
    double Di2 = delta(i) * delta(i);
    double Di3 = delta(i) * delta(i) * delta(i);

    NCollection_Array1<gp_Pnt> coeff(0, degree);
    switch (degree)
    {
      case 3:
        coeff.SetValue(coeff.Lower() + 3, gp_Pnt(DX * Di3, DY * Di3, DZ * Di3));
        [[fallthrough]];
      case 2:
        coeff.SetValue(coeff.Lower() + 2, gp_Pnt(CX * Di2, CY * Di2, CZ * Di2));
        [[fallthrough]];
      case 1:
        coeff.SetValue(coeff.Lower() + 1, gp_Pnt(BX * Di, BY * Di, BZ * Di));
        coeff.SetValue(coeff.Lower() + 0, gp_Pnt(AX, AY, AZ));
        break;
      default:
        break;
    }

    NCollection_Array1<gp_Pnt> bzpoles(0, degree);
    PLib::CoefficientsPoles(coeff, PLib::NoWeights(), bzpoles, PLib::NoWeights());

    if (ibspole > bspoles.Lower())
    {
      int bzlow = bzpoles.Lower();
      if (!(bspoles.Value(ibspole).IsEqual(bzpoles.Value(bzlow), epsgeom)))
      {
        returned = 1;

        bspoles.SetValue(ibspole,
                         gp_Pnt((bspoles.Value(ibspole).X() + bzpoles.Value(bzlow).X()) / 2.,
                                (bspoles.Value(ibspole).Y() + bzpoles.Value(bzlow).Y()) / 2.,
                                (bspoles.Value(ibspole).Z() + bzpoles.Value(bzlow).Z()) / 2.));
      }
    }
    if (i == 1)
      bspoles.SetValue(++ibspole, bzpoles.Value(bzpoles.Lower()));

    for (int j = bzpoles.Lower() + 1; j <= bzpoles.Upper(); j++)
      bspoles.SetValue(++ibspole, bzpoles.Value(j));
  }
  if (ibspole != bspoles.Upper())
  {

    return 3;
  }

  res = new Geom_BSplineCurve(bspoles, knots, multi, degree);

  return returned;
}

int IGESConvGeom::IncreaseCurveContinuity(const occ::handle<Geom_BSplineCurve>& res,
                                          const double                          epsgeom,
                                          const int                             continuity)
{
  if (continuity < 1)
    return continuity;
  bool isC1 = true, isC2 = true;
  int  degree = res->Degree();

  bool isModified;
  do
  {
    isModified = false;
    for (int i = res->FirstUKnotIndex() + 1; i < res->LastUKnotIndex(); i++)
      if (degree - res->Multiplicity(i) < continuity)
      {
        if (continuity >= 2)
        {
          if (!res->RemoveKnot(i, degree - 2, epsgeom))
          {
            isC2       = false;
            bool locOK = res->RemoveKnot(i, degree - 1, epsgeom);
            isC1 &= locOK;
            isModified |= locOK;
          }
          else
            isModified = true;
        }
        else
        {
          bool locOK = res->RemoveKnot(i, degree - 1, epsgeom);
          isC1 &= locOK;
          isModified |= locOK;
        }
      }
  } while (isModified);

  if (!isC1)
    return 0;
  if (continuity >= 2 && !isC2)
    return 1;
  return continuity;
}

int IGESConvGeom::IncreaseCurveContinuity(const occ::handle<Geom2d_BSplineCurve>& res,
                                          const double                            epsgeom,
                                          const int                               continuity)
{
  if (continuity < 1)
    return continuity;
  bool isC1 = true, isC2 = true;
  int  degree = res->Degree();

  bool isModified;
  do
  {
    isModified = false;
    for (int i = res->FirstUKnotIndex() + 1; i < res->LastUKnotIndex(); i++)
      if (degree - res->Multiplicity(i) < continuity)
      {
        if (continuity >= 2)
        {
          if (!res->RemoveKnot(i, degree - 2, epsgeom))
          {
            isC2       = false;
            bool locOK = res->RemoveKnot(i, degree - 1, epsgeom);
            isC1 &= locOK;
            isModified |= locOK;
          }
          else
            isModified = true;
        }
        else
        {
          bool locOK = res->RemoveKnot(i, degree - 1, epsgeom);
          isC1 &= locOK;
          isModified |= locOK;
        }
      }
  } while (isModified);

  if (!isC1)
    return 0;
  if (continuity >= 2 && !isC2)
    return 1;
  return continuity;
}

int IGESConvGeom::SplineSurfaceFromIGES(const occ::handle<IGESGeom_SplineSurface>& st,
                                        const double,
                                        const double                      epsgeom,
                                        occ::handle<Geom_BSplineSurface>& res)
{
  int returned = 0;
  int degree   = st->BoundaryType();
  if (degree > 3)
    degree = 3;
  int DegreeU = degree;
  int DegreeV = degree;

  int NbUSeg = st->NbUSegments();
  int NbVSeg = st->NbVSegments();

  if ((NbUSeg < 1) || (NbVSeg < 1))
    return 5;

  NCollection_Array1<double> UKnot(1, NbUSeg + 1);
  NCollection_Array1<double> VKnot(1, NbVSeg + 1);
  NCollection_Array1<double> deltaU(1, NbUSeg);
  NCollection_Array1<double> deltaV(1, NbVSeg);

  int i;
  for (i = 1; i <= NbUSeg + 1; i++)
    UKnot.SetValue(i, st->UBreakPoint(i));

  for (i = 1; i <= NbUSeg; i++)
    deltaU.SetValue(i, st->UBreakPoint(i + 1) - st->UBreakPoint(i));

  for (i = 1; i <= NbVSeg + 1; i++)
    VKnot.SetValue(i, st->VBreakPoint(i));

  for (i = 1; i <= NbVSeg; i++)
    deltaV.SetValue(i, st->VBreakPoint(i + 1) - st->VBreakPoint(i));

  NCollection_Array1<int> UMult(1, NbUSeg + 1);
  UMult.Init(DegreeU);
  UMult.SetValue(UMult.Lower(), DegreeU + 1);
  UMult.SetValue(UMult.Upper(), DegreeU + 1);

  NCollection_Array1<int> VMult(1, NbVSeg + 1);
  VMult.Init(DegreeV);
  VMult.SetValue(VMult.Lower(), DegreeV + 1);
  VMult.SetValue(VMult.Upper(), DegreeV + 1);

  int NbUPoles = NbUSeg * DegreeU + 1;
  int NbVPoles = NbVSeg * DegreeV + 1;

  NCollection_Array2<gp_Pnt> BsPole(1, NbUPoles, 1, NbVPoles);

  int  iBs, jBs, iBz, jBz;
  bool wasC0 = true;

  int USeg, VSeg, j;
  USeg = 1;
  VSeg = 1;

  occ::handle<NCollection_HArray1<double>> XPoly = st->XPolynomial(USeg, VSeg);
  occ::handle<NCollection_HArray1<double>> YPoly = st->YPolynomial(USeg, VSeg);
  occ::handle<NCollection_HArray1<double>> ZPoly = st->ZPolynomial(USeg, VSeg);

  NCollection_Array2<gp_Pnt> Coef(1, DegreeU + 1, 1, DegreeV + 1);
  double                     ParamU, ParamV;
  ParamU = 1.;
  for (i = 1; i <= DegreeU + 1; i++)
  {
    ParamV = 1.;
    for (j = 1; j <= DegreeV + 1; j++)
    {
      int    PolyIndex = i + 4 * (j - 1);
      gp_Pnt aPoint(XPoly->Value(PolyIndex) * ParamU * ParamV,
                    YPoly->Value(PolyIndex) * ParamU * ParamV,
                    ZPoly->Value(PolyIndex) * ParamU * ParamV);
      Coef.SetValue(i, j, aPoint);
      ParamV = ParamV * deltaV(VSeg);
    }
    ParamU = ParamU * deltaU(USeg);
  }
  NCollection_Array2<gp_Pnt> BzPole(1, DegreeU + 1, 1, DegreeV + 1);
  PLib::CoefficientsPoles(Coef, PLib::NoWeights2(), BzPole, PLib::NoWeights2());

  iBs = BsPole.LowerRow();
  jBs = BsPole.LowerCol();

  for (iBz = BzPole.LowerRow(); iBz <= BzPole.UpperRow(); iBz++)
  {
    for (jBz = BzPole.LowerCol(); jBz <= BzPole.UpperCol(); jBz++)
      BsPole.SetValue(iBs, jBs++, BzPole.Value(iBz, jBz));
    jBs = BsPole.LowerCol();
    iBs++;
  }

  VSeg = 1;
  for (USeg = 2; USeg <= NbUSeg; USeg++)
  {
    XPoly  = st->XPolynomial(USeg, VSeg);
    YPoly  = st->YPolynomial(USeg, VSeg);
    ZPoly  = st->ZPolynomial(USeg, VSeg);
    ParamU = 1.;
    for (i = Coef.LowerRow(); i <= Coef.UpperRow(); i++)
    {
      ParamV = 1.;
      for (j = Coef.LowerCol(); j <= Coef.UpperCol(); j++)
      {
        int    PolyIndex = i + 4 * (j - 1);
        gp_Pnt aPoint;
        aPoint.SetCoord(XPoly->Value(PolyIndex) * ParamU * ParamV,
                        YPoly->Value(PolyIndex) * ParamU * ParamV,
                        ZPoly->Value(PolyIndex) * ParamU * ParamV);
        Coef.SetValue(i, j, aPoint);
        ParamV = ParamV * deltaV(VSeg);
      }
      ParamU = ParamU * deltaU(USeg);
    }
    PLib::CoefficientsPoles(Coef, PLib::NoWeights2(), BzPole, PLib::NoWeights2());

    int iBsPole = BsPole.LowerRow() + (USeg - 1) * DegreeU;
    int jBsPole = BsPole.LowerCol();
    iBz         = BzPole.LowerRow();
    for (jBz = BzPole.LowerCol(); jBz <= BzPole.UpperCol(); jBz++)
    {
      if (!BzPole.Value(iBz, jBz).IsEqual(BsPole.Value(iBsPole, jBsPole), epsgeom))
      {
        wasC0 = false;
        gp_Pnt MidPoint;
        double XCoord = 0.5 * (BzPole.Value(iBz, jBz).X() + BsPole.Value(iBsPole, jBsPole).X());
        double YCoord = 0.5 * (BzPole.Value(iBz, jBz).Y() + BsPole.Value(iBsPole, jBsPole).Y());
        double ZCoord = 0.5 * (BzPole.Value(iBz, jBz).Z() + BsPole.Value(iBsPole, jBsPole).Z());
        MidPoint.SetCoord(XCoord, YCoord, ZCoord);
        BsPole.SetValue(iBsPole, jBsPole++, MidPoint);
      }
      else
      {
        BsPole.SetValue(iBsPole, jBsPole++, BzPole.Value(iBz, jBz));
      }
    }

    iBsPole++;
    jBsPole = BsPole.LowerCol();
    for (iBz = BzPole.LowerRow() + 1; iBz <= BzPole.UpperRow(); iBz++)
    {
      for (jBz = BzPole.LowerCol(); jBz <= BzPole.UpperCol(); jBz++)
        BsPole.SetValue(iBsPole, jBsPole++, BzPole.Value(iBz, jBz));
      iBsPole++;
      jBsPole = BsPole.LowerCol();
    }
  }

  USeg = 1;
  for (VSeg = 2; VSeg <= NbVSeg; VSeg++)
  {
    XPoly  = st->XPolynomial(USeg, VSeg);
    YPoly  = st->YPolynomial(USeg, VSeg);
    ZPoly  = st->ZPolynomial(USeg, VSeg);
    ParamU = 1.;
    for (i = Coef.LowerRow(); i <= Coef.UpperRow(); i++)
    {
      ParamV = 1.;
      for (j = Coef.LowerCol(); j <= Coef.UpperCol(); j++)
      {
        int    PolyIndex = i + 4 * (j - 1);
        gp_Pnt aPoint;
        aPoint.SetCoord(XPoly->Value(PolyIndex) * ParamU * ParamV,
                        YPoly->Value(PolyIndex) * ParamU * ParamV,
                        ZPoly->Value(PolyIndex) * ParamU * ParamV);
        Coef.SetValue(i, j, aPoint);
        ParamV = ParamV * deltaV(VSeg);
      }
      ParamU = ParamU * deltaU(USeg);
    }
    PLib::CoefficientsPoles(Coef, PLib::NoWeights2(), BzPole, PLib::NoWeights2());

    iBs = BsPole.LowerRow();
    jBs = BsPole.LowerCol() + (VSeg - 1) * DegreeV;
    jBz = BzPole.LowerCol();
    for (iBz = BzPole.LowerRow(); iBz <= BzPole.UpperRow(); iBz++)
    {
      if (!BzPole.Value(iBz, jBz).IsEqual(BsPole.Value(iBs, jBs), epsgeom))
      {
        wasC0 = false;
        gp_Pnt MidPoint;
        double XCoord = 0.5 * (BzPole.Value(iBz, jBz).X() + BsPole.Value(iBs, jBs).X());
        double YCoord = 0.5 * (BzPole.Value(iBz, jBz).Y() + BsPole.Value(iBs, jBs).Y());
        double ZCoord = 0.5 * (BzPole.Value(iBz, jBz).Z() + BsPole.Value(iBs, jBs).Z());
        MidPoint.SetCoord(XCoord, YCoord, ZCoord);
        BsPole.SetValue(iBs++, jBs, MidPoint);
      }
      else
      {
        BsPole.SetValue(iBs++, jBs, BzPole.Value(iBz, jBz));
      }
    }

    jBs++;
    iBs = BsPole.LowerRow();
    for (jBz = BzPole.LowerCol() + 1; jBz <= BzPole.UpperCol(); jBz++)
    {
      for (iBz = BzPole.LowerRow(); iBz <= BzPole.UpperRow(); iBz++)
        BsPole.SetValue(iBs++, jBs, BzPole.Value(iBz, jBz));
      iBs = BsPole.LowerRow();
      jBs++;
    }
  }

  for (VSeg = 2; VSeg <= NbVSeg; VSeg++)
  {
    for (USeg = 2; USeg <= NbUSeg; USeg++)
    {
      XPoly  = st->XPolynomial(USeg, VSeg);
      YPoly  = st->YPolynomial(USeg, VSeg);
      ZPoly  = st->ZPolynomial(USeg, VSeg);
      ParamU = 1.;
      for (i = Coef.LowerRow(); i <= Coef.UpperRow(); i++)
      {
        ParamV = 1.;
        for (j = Coef.LowerCol(); j <= Coef.UpperCol(); j++)
        {
          int    PolyIndex = i + 4 * (j - 1);
          gp_Pnt aPoint;
          aPoint.SetCoord(XPoly->Value(PolyIndex) * ParamU * ParamV,
                          YPoly->Value(PolyIndex) * ParamU * ParamV,
                          ZPoly->Value(PolyIndex) * ParamU * ParamV);
          Coef.SetValue(i, j, aPoint);
          ParamV = ParamV * deltaV(VSeg);
        }
        ParamU = ParamU * deltaU(USeg);
      }
      PLib::CoefficientsPoles(Coef, PLib::NoWeights2(), BzPole, PLib::NoWeights2());

      iBs = (USeg - 1) * DegreeU + BsPole.LowerRow();
      jBs = (VSeg - 1) * DegreeV + BsPole.LowerCol();
      jBz = BzPole.LowerCol();
      for (iBz = BzPole.LowerRow(); iBz <= BzPole.UpperRow(); iBz++)
      {
        if (!BzPole.Value(iBz, jBz).IsEqual(BsPole.Value(iBs, jBs), epsgeom))
        {
          wasC0 = false;
          gp_Pnt MidPoint;
          double XCoord = 0.5 * (BzPole.Value(iBz, jBz).X() + BsPole.Value(iBs, jBs).X());
          double YCoord = 0.5 * (BzPole.Value(iBz, jBz).Y() + BsPole.Value(iBs, jBs).Y());
          double ZCoord = 0.5 * (BzPole.Value(iBz, jBz).Z() + BsPole.Value(iBs, jBs).Z());
          MidPoint.SetCoord(XCoord, YCoord, ZCoord);
          BsPole.SetValue(iBs++, jBs, MidPoint);
        }
        else
          BsPole.SetValue(iBs++, jBs, BzPole.Value(iBz, jBz));
      }

      iBs = (USeg - 1) * DegreeU + BsPole.LowerRow();
      iBz = BzPole.LowerRow();
      for (jBz = BzPole.LowerCol(); jBz <= BzPole.UpperCol(); jBz++)
      {

        if (!BzPole.Value(iBz, jBz).IsEqual(BsPole.Value(iBs, jBs), epsgeom))
        {
          wasC0 = false;
          gp_Pnt MidPoint;
          double XCoord = 0.5 * (BzPole.Value(iBz, jBz).X() + BsPole.Value(iBs, jBs).X());
          double YCoord = 0.5 * (BzPole.Value(iBz, jBz).Y() + BsPole.Value(iBs, jBs).Y());
          double ZCoord = 0.5 * (BzPole.Value(iBz, jBz).Z() + BsPole.Value(iBs, jBs).Z());
          MidPoint.SetCoord(XCoord, YCoord, ZCoord);
          BsPole.SetValue(iBs, jBs++, MidPoint);
        }
        else
          BsPole.SetValue(iBs, jBs++, BzPole.Value(iBz, jBz));
      }

      iBs = BsPole.LowerRow() + (USeg - 1) * DegreeU + 1;
      jBs = BsPole.LowerCol() + (VSeg - 1) * DegreeV + 1;
      for (iBz = BzPole.LowerRow() + 1; iBz <= BzPole.UpperRow(); iBz++)
      {
        for (jBz = BzPole.LowerCol() + 1; jBz <= BzPole.UpperCol(); jBz++)
          BsPole.SetValue(iBs, jBs++, BzPole.Value(iBz, jBz));
        jBs = BsPole.LowerCol() + (VSeg - 1) * DegreeV + 1;
        iBs++;
      }
    }
  }

  if (st->HasTransf())
  {
    gp_GTrsf GSplTrsf(st->CompoundLocation());
    gp_Trsf  SplTrsf;
    double   epsilon = 1.E-04;
    if (IGESData_ToolLocation::ConvertLocation(epsilon, GSplTrsf, SplTrsf))
      for (iBs = BsPole.LowerRow(); iBs <= BsPole.UpperRow(); iBs++)
        for (jBs = BsPole.LowerCol(); jBs <= BsPole.UpperCol(); jBs++)
          BsPole.SetValue(iBs, jBs, BsPole.Value(iBs, jBs).Transformed(SplTrsf));
  }

  res = new Geom_BSplineSurface(BsPole, UKnot, VKnot, UMult, VMult, DegreeU, DegreeV);
  if (wasC0)
    returned += 1;
  return returned;
}

int IGESConvGeom::IncreaseSurfaceContinuity(const occ::handle<Geom_BSplineSurface>& res,
                                            const double                            epsgeom,
                                            const int                               continuity)
{
  if (continuity < 1)
    return continuity;
  bool isC1 = true, isC2 = true;
  int  DegreeU = res->UDegree();

  bool isModified;
  do
  {
    isModified = false;
    for (int i = res->FirstUKnotIndex() + 1; i < res->LastUKnotIndex(); i++)
      if (DegreeU - res->UMultiplicity(i) < continuity)
      {
        if (continuity >= 2)
        {
          if (!res->RemoveUKnot(i, DegreeU - 2, epsgeom))
          {
            isC2       = false;
            bool locOK = res->RemoveUKnot(i, DegreeU - 1, epsgeom);
            isC1 &= locOK;
            isModified |= locOK;
          }
          else
            isModified = true;
        }
        else
        {
          bool locOK = res->RemoveUKnot(i, DegreeU - 1, epsgeom);
          isC1 &= locOK;
          isModified |= locOK;
        }
      }
  } while (isModified);

  int DegreeV = res->VDegree();
  do
  {
    isModified = false;
    for (int i = res->FirstVKnotIndex() + 1; i < res->LastVKnotIndex(); i++)
      if (DegreeV - res->VMultiplicity(i) < continuity)
      {
        if (continuity >= 2)
        {
          if (!res->RemoveVKnot(i, DegreeV - 2, epsgeom))
          {
            isC2       = false;
            bool locOK = res->RemoveVKnot(i, DegreeV - 1, epsgeom);
            isC1 &= locOK;
            isModified |= locOK;
          }
          else
            isModified = true;
        }
        else
        {
          bool locOK = res->RemoveVKnot(i, DegreeV - 1, epsgeom);
          isC1 &= locOK;
          isModified |= locOK;
        }
      }
  } while (isModified);

  if (!isC1)
    return 0;
  if (continuity >= 2 && !isC2)
    return 1;
  return continuity;
}
