

#include <IntPatch_SpecialPoints.hpp>

#include <Adaptor3d_Surface.hpp>
#include <ElCLib.hpp>
#include <Extrema_ExtPS.hpp>
#include <Extrema_GenLocateExtPS.hpp>
#include <IntPatch_Point.hpp>
#include <IntSurf.hpp>
#include <IntSurf_PntOn2S.hpp>
#include <Standard_TypeMismatch.hpp>
#include <math_FunctionSetRoot.hpp>
#include <math_FunctionSetWithDerivatives.hpp>
#include <math_Matrix.hpp>

class FuncPreciseSeam : public math_FunctionSetWithDerivatives
{
public:
  FuncPreciseSeam(const occ::handle<Adaptor3d_Surface>& theQSurf,
                  const occ::handle<Adaptor3d_Surface>& thePSurf,
                  const bool                            isTheUSeam,
                  const double                          theIsoParameter)
      : myQSurf(theQSurf),
        myPSurf(thePSurf),
        mySeamCoordInd(isTheUSeam ? 1 : 0),
        myIsoParameter(theIsoParameter) {};

  int NbVariables() const override { return 3; };

  int NbEquations() const override { return 3; }

  bool Value(const math_Vector& theX, math_Vector& theF) override
  {
    try
    {
      const int anIndX = theX.Lower(), anIndF = theF.Lower();
      double    aUV[]     = {myIsoParameter, myIsoParameter};
      aUV[mySeamCoordInd] = theX(anIndX + 2);
      const gp_Pnt aP1(myPSurf->Value(theX(anIndX), theX(anIndX + 1)));
      const gp_Pnt aP2(myQSurf->Value(aUV[0], aUV[1]));

      (aP1.XYZ() - aP2.XYZ()).Coord(theF(anIndF), theF(anIndF + 1), theF(anIndF + 2));
    }
    catch (Standard_Failure const&)
    {
      return false;
    }

    return true;
  };

  bool Derivatives(const math_Vector& theX, math_Matrix& theD) override
  {
    try
    {
      const int anIndX = theX.Lower(), anIndRD = theD.LowerRow(), anIndCD = theD.LowerCol();
      double    aUV[]     = {myIsoParameter, myIsoParameter};
      aUV[mySeamCoordInd] = theX(anIndX + 2);

      gp_Pnt aPt;

      gp_Vec aD1[2], aD2[2];
      myPSurf->D1(theX(anIndX), theX(anIndX + 1), aPt, aD1[0], aD1[1]);
      myQSurf->D1(aUV[0], aUV[1], aPt, aD2[0], aD2[1]);

      aD1[0].Coord(theD(anIndRD, anIndCD), theD(anIndRD + 1, anIndCD), theD(anIndRD + 2, anIndCD));

      aD1[1].Coord(theD(anIndRD, anIndCD + 1),
                   theD(anIndRD + 1, anIndCD + 1),
                   theD(anIndRD + 2, anIndCD + 1));

      aD2[mySeamCoordInd].Reversed().Coord(theD(anIndRD, anIndCD + 2),
                                           theD(anIndRD + 1, anIndCD + 2),
                                           theD(anIndRD + 2, anIndCD + 2));
    }
    catch (Standard_Failure const&)
    {
      return false;
    }

    return true;
  };

  bool Values(const math_Vector& theX, math_Vector& theF, math_Matrix& theD) override
  {
    if (!Value(theX, theF))
      return false;

    if (!Derivatives(theX, theD))
      return false;

    return true;
  }

protected:
  FuncPreciseSeam operator=(FuncPreciseSeam&);

private:
  const occ::handle<Adaptor3d_Surface>& myQSurf;
  const occ::handle<Adaptor3d_Surface>& myPSurf;

  const int mySeamCoordInd;

  const double myIsoParameter;
};

static inline void GetTangent(const double theConeSemiAngle,
                              const double theParameter,
                              gp_XYZ&      theResult)
{
  const double aW2    = theParameter * theParameter;
  const double aCosUn = (1.0 - aW2) / (1.0 + aW2);
  const double aSinUn = 2.0 * theParameter / (1.0 + aW2);

  const double aTanA = std::tan(theConeSemiAngle);
  theResult.SetCoord(aTanA * aCosUn, aTanA * aSinUn, 1.0);
}

static bool IsPointOnSurface(const occ::handle<Adaptor3d_Surface>& theSurf,
                             const gp_Pnt&                         thePt,
                             const double                          theTol,
                             gp_Pnt&                               theProjPt,
                             double&                               theUpar,
                             double&                               theVpar)
{
  bool aRetVal = false;

  switch (theSurf->GetType())
  {
    case GeomAbs_Plane:
    case GeomAbs_Cylinder:
    case GeomAbs_Cone:
    case GeomAbs_Sphere:
    case GeomAbs_Torus:
    case GeomAbs_SurfaceOfExtrusion:
    case GeomAbs_SurfaceOfRevolution:
    {
      Extrema_ExtPS anExtr(thePt,
                           *theSurf,
                           theSurf->UResolution(theTol),
                           theSurf->VResolution(theTol),
                           Extrema_ExtFlag_MIN);
      if (!anExtr.IsDone() || (anExtr.NbExt() < 1))
      {
        aRetVal = false;
      }
      else
      {
        int    anExtrIndex = 1;
        double aSqDistMin  = anExtr.SquareDistance(anExtrIndex);
        for (int i = anExtrIndex + 1; i <= anExtr.NbExt(); i++)
        {
          const double aSqD = anExtr.SquareDistance(i);
          if (aSqD < aSqDistMin)
          {
            aSqDistMin  = aSqD;
            anExtrIndex = i;
          }
        }

        if (aSqDistMin > theTol * theTol)
        {
          aRetVal = false;
        }
        else
        {
          theProjPt.SetXYZ(anExtr.Point(anExtrIndex).Value().XYZ());
          anExtr.Point(anExtrIndex).Parameter(theUpar, theVpar);
          aRetVal = true;
        }
      }
    }
    break;
    default:
    {
      Extrema_GenLocateExtPS anExtr(*theSurf);
      anExtr.Perform(thePt, theUpar, theVpar);
      if (!anExtr.IsDone() || (anExtr.SquareDistance() > theTol * theTol))
      {
        aRetVal = false;
      }
      else
      {
        anExtr.Point().Parameter(theUpar, theVpar);
        theProjPt.SetXYZ(anExtr.Point().Value().XYZ());
        aRetVal = true;
      }
    }
    break;
  }

  return aRetVal;
}

bool IntPatch_SpecialPoints::AddCrossUVIsoPoint(const occ::handle<Adaptor3d_Surface>& theQSurf,
                                                const occ::handle<Adaptor3d_Surface>& thePSurf,
                                                const IntSurf_PntOn2S&                theRefPt,
                                                const double                          theTol,
                                                IntSurf_PntOn2S&                      theAddedPoint,
                                                const bool                            theIsReversed)
{
  double anArrOfPeriod[4] = {0.0, 0.0, 0.0, 0.0};
  IntSurf::SetPeriod(theIsReversed ? thePSurf : theQSurf,
                     theIsReversed ? theQSurf : thePSurf,
                     anArrOfPeriod);

  gp_Pnt aPQuad;

  double aU0 = 0.0, aV0 = 0.0;
  if (theIsReversed)
    theRefPt.ParametersOnS1(aU0, aV0);
  else
    theRefPt.ParametersOnS2(aU0, aV0);

  double aUquad = 0.0, aVquad = 0.0;

  theQSurf->D0(aUquad, aVquad, aPQuad);

  Extrema_GenLocateExtPS anExtr(*thePSurf);
  anExtr.Perform(aPQuad, aU0, aV0);

  if (!anExtr.IsDone())
  {
    return false;
  }

  if (anExtr.SquareDistance() > theTol * theTol)
  {
    return false;
  }

  anExtr.Point().Parameter(aU0, aV0);
  gp_Pnt aP0(anExtr.Point().Value());

  if (theIsReversed)
    theAddedPoint.SetValue(0.5 * (aP0.XYZ() + aPQuad.XYZ()), aU0, aV0, aUquad, aVquad);
  else
    theAddedPoint.SetValue(0.5 * (aP0.XYZ() + aPQuad.XYZ()), aUquad, aVquad, aU0, aV0);

  AdjustPointAndVertex(theRefPt, anArrOfPeriod, theAddedPoint);

  return true;
}

bool IntPatch_SpecialPoints::AddPointOnUorVIso(const occ::handle<Adaptor3d_Surface>& theQSurf,
                                               const occ::handle<Adaptor3d_Surface>& thePSurf,
                                               const IntSurf_PntOn2S&                theRefPt,
                                               const bool                            theIsU,
                                               const double       theIsoParameter,
                                               const math_Vector& theToler,
                                               const math_Vector& theInitPoint,
                                               const math_Vector& theInfBound,
                                               const math_Vector& theSupBound,
                                               IntSurf_PntOn2S&   theAddedPoint,
                                               const bool         theIsReversed)
{
  double anArrOfPeriod[4] = {0.0, 0.0, 0.0, 0.0};
  IntSurf::SetPeriod(theIsReversed ? thePSurf : theQSurf,
                     theIsReversed ? theQSurf : thePSurf,
                     anArrOfPeriod);

  FuncPreciseSeam aF(theQSurf, thePSurf, theIsU, theIsoParameter);

  math_FunctionSetRoot aSRF(aF, theToler);
  aSRF.Perform(aF, theInitPoint, theInfBound, theSupBound);

  if (!aSRF.IsDone())
  {
    return false;
  }

  math_Vector aRoots(theInitPoint.Lower(), theInitPoint.Upper());
  aSRF.Root(aRoots);

  double aU0 = aRoots(1), aV0 = aRoots(2);

  double       aUquad = theIsU ? 0.0 : aRoots(3);
  double       aVquad = theIsU ? aRoots(3) : 0.0;
  const gp_Pnt aPQuad(theQSurf->Value(aUquad, aVquad));
  const gp_Pnt aP0(thePSurf->Value(aU0, aV0));

  if (theIsReversed)
    theAddedPoint.SetValue(0.5 * (aP0.XYZ() + aPQuad.XYZ()), aU0, aV0, aUquad, aVquad);
  else
    theAddedPoint.SetValue(0.5 * (aP0.XYZ() + aPQuad.XYZ()), aUquad, aVquad, aU0, aV0);

  AdjustPointAndVertex(theRefPt, anArrOfPeriod, theAddedPoint);
  return true;
}

bool IntPatch_SpecialPoints::ProcessSphere(const IntSurf_PntOn2S& thePtIso,
                                           const gp_Vec&          theDUofPSurf,
                                           const gp_Vec&          theDVofPSurf,
                                           const bool             theIsReversed,
                                           const double           theVquad,
                                           double&                theUquad,
                                           bool&                  theIsIsoChoosen)
{
  theIsIsoChoosen = false;

  gp_Vec2d aV1;

  if ((std::abs(theDUofPSurf.Z()) < Precision::PConfusion())
      && (std::abs(theDVofPSurf.Z()) < Precision::PConfusion()))
  {

#ifdef INTPATCH_ADDSPECIALPOINTS_DEBUG
    std::cout << "Cannot find UV-coordinate for quadric in the pole."
                 " See considered comment above. IntPatch_SpecialPoints.cxx,"
                 " ProcessSphere(...)"
              << std::endl;
#endif
    double aUIso = 0.0, aVIso = 0.0;
    if (theIsReversed)
      thePtIso.ParametersOnS2(aUIso, aVIso);
    else
      thePtIso.ParametersOnS1(aUIso, aVIso);

    theUquad        = aUIso;
    theIsIsoChoosen = true;
  }
  else
  {
    if (std::abs(theDUofPSurf.Z()) > std::abs(theDVofPSurf.Z()))
    {
      const double aDusDvs = theDVofPSurf.Z() / theDUofPSurf.Z();
      aV1.SetCoord(theDUofPSurf.X() * aDusDvs - theDVofPSurf.X(),
                   theDUofPSurf.Y() * aDusDvs - theDVofPSurf.Y());
    }
    else
    {
      const double aDvsDus = theDUofPSurf.Z() / theDVofPSurf.Z();
      aV1.SetCoord(theDVofPSurf.X() * aDvsDus - theDUofPSurf.X(),
                   theDVofPSurf.Y() * aDvsDus - theDUofPSurf.Y());
    }

    aV1.Normalize();

    if (std::abs(aV1.X()) > std::abs(aV1.Y()))
      theUquad = std::copysign(asin(aV1.Y()), theVquad);
    else
      theUquad = std::copysign(acos(aV1.X()), theVquad);
  }

  return true;
}

bool IntPatch_SpecialPoints::ProcessCone(const IntSurf_PntOn2S& thePtIso,
                                         const gp_Vec&          theDUofPSurf,
                                         const gp_Vec&          theDVofPSurf,
                                         const gp_Cone&         theCone,
                                         const bool             theIsReversed,
                                         double&                theUquad,
                                         bool&                  theIsIsoChoosen)
{
  theIsIsoChoosen = false;

  const gp_XYZ aTgPlaneZ(theDUofPSurf.Crossed(theDVofPSurf).XYZ());
  const double aSqModTg = aTgPlaneZ.SquareModulus();
  if (aSqModTg < Precision::SquareConfusion())
  {
    theIsIsoChoosen = true;
  }

  gp_XYZ    aTgILine[2];
  const int aNbTangent = !theIsIsoChoosen
                           ? GetTangentToIntLineForCone(theCone.SemiAngle(),
                                                        aTgPlaneZ.Divided(std::sqrt(aSqModTg)),
                                                        aTgILine)
                           : 0;

  if (aNbTangent == 0)
  {
    theIsIsoChoosen = true;
  }
  else
  {
    const double aPeriod = M_PI + M_PI;
    double       aUIso = 0.0, aVIso = 0.0;
    if (theIsReversed)
      thePtIso.ParametersOnS2(aUIso, aVIso);
    else
      thePtIso.ParametersOnS1(aUIso, aVIso);

    aUIso = ElCLib::InPeriod(aUIso, 0.0, aPeriod);

    double aMinDelta = RealLast();
    for (int anIdx = 0; anIdx < aNbTangent; anIdx++)
    {

      gp_Vec2d     aVecCS(aTgILine[anIdx].X(), aTgILine[anIdx].Y());
      const double aSqMod = aVecCS.SquareMagnitude();
      if (aSqMod < Precision::SquareConfusion())
      {
        theIsIsoChoosen = true;
        break;
      }

      aVecCS.Divide(std::sqrt(aSqMod));

      double anUq = (std::abs(aVecCS.X()) < std::abs(aVecCS.Y())) ? std::acos(std::abs(aVecCS.X()))
                                                                  : std::asin(std::abs(aVecCS.Y()));

      if (aVecCS.Y() < 0.0)
      {
        if (aVecCS.X() > 0.0)
        {
          anUq = -anUq;
        }
        else
        {
          anUq += M_PI;
        }
      }
      else if (aVecCS.X() < 0.0)
      {
        anUq = M_PI - anUq;
      }

      anUq          = ElCLib::InPeriod(anUq, 0.0, aPeriod);
      double aDelta = std::abs(anUq - aUIso);
      if (aDelta > M_PI)
        aDelta = aPeriod - aDelta;

      if (aDelta < aMinDelta)
      {
        aMinDelta = aDelta;
        theUquad  = anUq;
      }
    }
  }

  if (theIsIsoChoosen)
  {
#ifdef INTPATCH_ADDSPECIALPOINTS_DEBUG
    std::cout << "Cannot find UV-coordinate for quadric in the pole."
                 " IntPatch_AddSpecialPoints.cxx, ProcessCone(...)"
              << std::endl;
#endif
    theIsIsoChoosen = true;

    double aUIso = 0.0, aVIso = 0.0;
    if (theIsReversed)
      thePtIso.ParametersOnS2(aUIso, aVIso);
    else
      thePtIso.ParametersOnS1(aUIso, aVIso);

    theUquad = aUIso;
    return true;
  }
  else
  {
    return true;
  }
}

int IntPatch_SpecialPoints::GetTangentToIntLineForCone(const double  theConeSemiAngle,
                                                       const gp_XYZ& thePlnNormal,
                                                       gp_XYZ        theResult[2])
{
  const double aNullTol = Epsilon(1.0);
  const double aTanA    = std::tan(theConeSemiAngle);
  const double aA       = thePlnNormal.Z() / aTanA - thePlnNormal.X();
  const double aB       = thePlnNormal.Y();
  const double aC       = thePlnNormal.Z() / aTanA + thePlnNormal.X();

  if (std::abs(aA) < aNullTol)
  {
    if (std::abs(aB) > aNullTol)
    {

      GetTangent(theConeSemiAngle, -aC / (aB + aB), theResult[0]);
      return 1;
    }

    return 0;
  }

  double aDiscr = thePlnNormal.Z() / std::sin(theConeSemiAngle);
  aDiscr        = 1.0 - aDiscr * aDiscr;

  if (std::abs(aDiscr) < aNullTol)
  {

    GetTangent(theConeSemiAngle, -aB / aA, theResult[0]);
    return 1;
  }
  else if (aDiscr > 0.0)
  {
    const double aRD = std::sqrt(aDiscr);
    GetTangent(theConeSemiAngle, (-aB + aRD) / aA, theResult[0]);
    GetTangent(theConeSemiAngle, (-aB - aRD) / aA, theResult[1]);
    return 2;
  }

  return 0;
}

bool IntPatch_SpecialPoints::AddSingularPole(const occ::handle<Adaptor3d_Surface>& theQSurf,
                                             const occ::handle<Adaptor3d_Surface>& thePSurf,
                                             const IntSurf_PntOn2S&                thePtIso,
                                             IntPatch_Point&                       theVertex,
                                             IntSurf_PntOn2S&                      theAddedPoint,
                                             const bool                            theIsReversed,
                                             const bool                            theIsReqRefCheck)
{

  double aU0 = 0.0, aV0 = 0.0;

  gp_Pnt aPQuad, aP0;
  double aUquad = 0.0, aVquad = 0.0;
  if (theIsReversed)
    theVertex.Parameters(aU0, aV0, aUquad, aVquad);
  else
    theVertex.Parameters(aUquad, aVquad, aU0, aV0);

  aUquad = 0.0;

  if (theQSurf->GetType() == GeomAbs_Sphere)
  {
    aVquad = std::copysign(M_PI_2, aVquad);
  }
  else if (theQSurf->GetType() == GeomAbs_Cone)
  {
    const gp_Cone aCo        = theQSurf->Cone();
    const double  aRadius    = aCo.RefRadius();
    const double  aSemiAngle = aCo.SemiAngle();
    aVquad                   = -aRadius / sin(aSemiAngle);
  }
  else
  {
    throw Standard_TypeMismatch("IntPatch_SpecialPoints::AddSingularPole(),"
                                "Unsupported quadric with Pole");
  }

  theQSurf->D0(aUquad, aVquad, aPQuad);
  const double aTol = theVertex.Tolerance();
  if (theIsReqRefCheck && (aPQuad.SquareDistance(theVertex.Value()) >= aTol * aTol))
  {
    return false;
  }

  if (!IsPointOnSurface(thePSurf, aPQuad, aTol, aP0, aU0, aV0))
  {
    return false;
  }

  if (theIsReversed)
    theAddedPoint.SetValue(0.5 * (aP0.XYZ() + aPQuad.XYZ()), aU0, aV0, aUquad, aVquad);
  else
    theAddedPoint.SetValue(0.5 * (aP0.XYZ() + aPQuad.XYZ()), aUquad, aVquad, aU0, aV0);

  const bool isSame = theAddedPoint.IsSame(theVertex.PntOn2S(), Precision::Confusion());

  gp_Pnt aPtemp;
  gp_Vec aVecDu, aVecDv;
  thePSurf->D1(aU0, aV0, aPtemp, aVecDu, aVecDv);

  gp_Trsf aTr;
  aTr.SetTransformation((theQSurf->GetType() == GeomAbs_Sphere) ? theQSurf->Sphere().Position()
                                                                : theQSurf->Cone().Position());

  aVecDu.Transform(aTr);
  aVecDv.Transform(aTr);

  bool isIsoChoosen = false;

  if (theQSurf->GetType() == GeomAbs_Sphere)
  {
    if (!ProcessSphere(thePtIso, aVecDu, aVecDv, theIsReversed, aVquad, aUquad, isIsoChoosen))
    {
      return false;
    }
  }
  else
  {
    if (!ProcessCone(thePtIso,
                     aVecDu,
                     aVecDv,
                     theQSurf->Cone(),
                     theIsReversed,
                     aUquad,
                     isIsoChoosen))
    {
      return false;
    }
  }

  if (theIsReversed)
    theAddedPoint.SetValue(0.5 * (aP0.XYZ() + aPQuad.XYZ()), aU0, aV0, aUquad, aVquad);
  else
    theAddedPoint.SetValue(0.5 * (aP0.XYZ() + aPQuad.XYZ()), aUquad, aVquad, aU0, aV0);

  if (isSame)
  {
    theVertex.SetValue(theAddedPoint);
    return true;
  }

  if (!isIsoChoosen)
  {
    double anArrOfPeriod[4];
    if (theIsReversed)
    {
      IntSurf::SetPeriod(thePSurf, theQSurf, anArrOfPeriod);
    }
    else
    {
      IntSurf::SetPeriod(theQSurf, thePSurf, anArrOfPeriod);
    }

    AdjustPointAndVertex(theVertex.PntOn2S(), anArrOfPeriod, theAddedPoint);
  }
  else
  {
    theVertex.SetValue(theAddedPoint);
  }

  return true;
}

bool IntPatch_SpecialPoints::ContinueAfterSpecialPoint(
  const occ::handle<Adaptor3d_Surface>& theQSurf,
  const occ::handle<Adaptor3d_Surface>& thePSurf,
  const IntSurf_PntOn2S&                theRefPt,
  const IntPatch_SpecPntType            theSPType,
  const double                          theTol2D,
  IntSurf_PntOn2S&                      theNewPoint,
  const bool                            theIsReversed)
{
  if (theSPType == IntPatch_SPntNone)
    return false;

  if (theNewPoint.IsSame(theRefPt, Precision::Confusion(), theTol2D))
  {
    return false;
  }

  if ((theSPType == IntPatch_SPntPole) && (theQSurf->GetType() == GeomAbs_Cone))
  {

    double aU0 = 0.0, aV0 = 0.0;

    double aUquad = 0.0, aVquad = 0.0;

    if (theIsReversed)
      theNewPoint.Parameters(aU0, aV0, aUquad, aVquad);
    else
      theNewPoint.Parameters(aUquad, aVquad, aU0, aV0);

    gp_Pnt aPtemp;
    gp_Vec aVecDu, aVecDv;
    thePSurf->D1(aU0, aV0, aPtemp, aVecDu, aVecDv);

    gp_Trsf aTr;
    aTr.SetTransformation(theQSurf->Cone().Position());

    aVecDu.Transform(aTr);
    aVecDv.Transform(aTr);

    bool isIsoChoosen = false;
    ProcessCone(theRefPt, aVecDu, aVecDv, theQSurf->Cone(), theIsReversed, aUquad, isIsoChoosen);

    theNewPoint.SetValue(!theIsReversed, aUquad, aVquad);
  }

  const double aPeriod = (theSPType == IntPatch_SPntPole) ? M_PI_2 : 2.0 * M_PI;

  const double aUpPeriod = thePSurf->IsUPeriodic() ? thePSurf->UPeriod() : 0.0;
  const double aUqPeriod = theQSurf->IsUPeriodic() ? aPeriod : 0.0;
  const double aVpPeriod = thePSurf->IsVPeriodic() ? thePSurf->VPeriod() : 0.0;
  const double aVqPeriod = theQSurf->IsVPeriodic() ? aPeriod : 0.0;

  const double anArrOfPeriod[4] = {theIsReversed ? aUpPeriod : aUqPeriod,
                                   theIsReversed ? aVpPeriod : aVqPeriod,
                                   theIsReversed ? aUqPeriod : aUpPeriod,
                                   theIsReversed ? aVqPeriod : aVpPeriod};

  AdjustPointAndVertex(theRefPt, anArrOfPeriod, theNewPoint);
  return true;
}

void IntPatch_SpecialPoints::AdjustPointAndVertex(const IntSurf_PntOn2S& theRefPoint,
                                                  const double           theArrPeriods[4],
                                                  IntSurf_PntOn2S&       theNewPoint,
                                                  IntPatch_Point* const  theVertex)
{
  double aRefPar[2] = {0.0, 0.0};
  double aPar[4]    = {0.0, 0.0, 0.0, 0.0};
  theNewPoint.Parameters(aPar[0], aPar[1], aPar[2], aPar[3]);

  for (int i = 0; i < 4; i++)
  {
    if (theArrPeriods[i] == 0)
      continue;

    const double aPeriod = theArrPeriods[i], aHalfPeriod = 0.5 * theArrPeriods[i];

    if (i < 2)
    {
      theRefPoint.ParametersOnS1(aRefPar[0], aRefPar[1]);
    }
    else
    {
      theRefPoint.ParametersOnS2(aRefPar[0], aRefPar[1]);
    }

    const int aRefInd = i % 2;

    {
      double       aDeltaPar = aRefPar[aRefInd] - aPar[i];
      const double anIncr    = std::copysign(aPeriod, aDeltaPar);
      while ((aDeltaPar > aHalfPeriod) || (aDeltaPar < -aHalfPeriod))
      {
        aPar[i] += anIncr;
        aDeltaPar = aRefPar[aRefInd] - aPar[i];
      }
    }
  }

  if (theVertex)
    (*theVertex).SetParameters(aPar[0], aPar[1], aPar[2], aPar[3]);

  theNewPoint.SetValue(aPar[0], aPar[1], aPar[2], aPar[3]);
}
