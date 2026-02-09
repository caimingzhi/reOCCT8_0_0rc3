

#include <Hatch_Hatcher.hpp>
#include <Graphic3d_Group.hpp>
#include <Prs3d_IsoAspect.hpp>
#include <Adaptor3d_IsoCurve.hpp>
#include <Bnd_Box2d.hpp>
#include <BndLib_Add2dCurve.hpp>
#include <Precision.hpp>
#include <GeomAdaptor_Curve.hpp>
#include <Geom_BezierSurface.hpp>
#include <Geom_BSplineSurface.hpp>
#include <GeomAbs_SurfaceType.hpp>
#include <StdPrs_WFRestrictedFace.hpp>
#include <StdPrs_ToolRFace.hpp>
#include <StdPrs_Curve.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <NCollection_List.hpp>

void StdPrs_WFRestrictedFace::Add(
  const occ::handle<Prs3d_Presentation>&                        thePresentation,
  const occ::handle<BRepAdaptor_Surface>&                       theFace,
  const bool                                                    theDrawUIso,
  const bool                                                    theDrawVIso,
  const int                                                     theNbUIso,
  const int                                                     theNBVIso,
  const occ::handle<Prs3d_Drawer>&                              theDrawer,
  NCollection_List<occ::handle<NCollection_HSequence<gp_Pnt>>>& theCurves)
{
  int              aNbPoints = theDrawer->Discretisation();
  StdPrs_ToolRFace aToolRst(theFace);

  double    aUMin, aUMax, aVMin, aVMax;
  int       anI;
  gp_Pnt2d  aPoint1, aPoint2;
  Bnd_Box2d aBndBox;

  for (aToolRst.Init(); aToolRst.More(); aToolRst.Next())
  {
    const Adaptor2d_Curve2d& aRCurve = aToolRst.Value();
    BndLib_Add2dCurve::Add(aRCurve, Precision::PConfusion(), aBndBox);
  }
  if (!aBndBox.IsVoid())
    aBndBox.Get(aUMin, aVMin, aUMax, aVMax);
  else
  {
    aUMin = theFace->Surface().FirstUParameter();
    aVMin = theFace->Surface().FirstVParameter();
    aUMax = theFace->Surface().LastUParameter();
    aVMax = theFace->Surface().LastVParameter();
  }

  Hatch_Hatcher anIsoBuild(1.e-5, aToolRst.IsOriented());
  bool          isFaceUClosed = theFace->IsUClosed();
  bool          isFaceVClosed = theFace->IsVClosed();

  if (!isFaceUClosed)
  {
    aUMin = aUMin + (aUMax - aUMin) / 1000.;
    aUMax = aUMax - (aUMax - aUMin) / 1000.;
  }

  if (!isFaceVClosed)
  {
    aVMin = aVMin + (aVMax - aVMin) / 1000.;
    aVMax = aVMax - (aVMax - aVMin) / 1000.;
  }

  if (theDrawUIso)
  {
    if (theNbUIso > 0)
    {
      isFaceUClosed = false;
      double du = isFaceUClosed ? (aUMax - aUMin) / theNbUIso : (aUMax - aUMin) / (1 + theNbUIso);
      for (anI = 1; anI <= theNbUIso; anI++)
      {
        anIsoBuild.AddXLine(aUMin + du * anI);
      }
    }
  }
  if (theDrawVIso)
  {
    if (theNBVIso > 0)
    {
      isFaceVClosed = false;
      double dv = isFaceVClosed ? (aVMax - aVMin) / theNBVIso : (aVMax - aVMin) / (1 + theNBVIso);
      for (anI = 1; anI <= theNBVIso; anI++)
      {
        anIsoBuild.AddYLine(aVMin + dv * anI);
      }
    }
  }

  double anU1, anU2, anU, aDU;

  for (aToolRst.Init(); aToolRst.More(); aToolRst.Next())
  {
    TopAbs_Orientation       anOrientation = aToolRst.Orientation();
    const Adaptor2d_Curve2d* aRCurve       = &aToolRst.Value();
    anU1                                   = aRCurve->FirstParameter();
    anU2                                   = aRCurve->LastParameter();
    if (aRCurve->GetType() != GeomAbs_Line)
    {
      aDU     = (anU2 - anU1) / (aNbPoints - 1);
      aPoint2 = aRCurve->Value(anU1);
      for (anI = 2; anI <= aNbPoints; ++anI)
      {
        anU     = anU1 + (anI - 1) * aDU;
        aPoint1 = aPoint2;
        aPoint2 = aRCurve->Value(anU);
        if (anOrientation == TopAbs_FORWARD)
          anIsoBuild.Trim(aPoint1, aPoint2);
        else
          anIsoBuild.Trim(aPoint2, aPoint1);
      }
    }
    else
    {
      aPoint1 = aRCurve->Value(anU1);
      aPoint2 = aRCurve->Value(anU2);
      if (anOrientation == TopAbs_FORWARD)
        anIsoBuild.Trim(aPoint1, aPoint2);
      else
        anIsoBuild.Trim(aPoint2, aPoint1);
    }
  }

  Adaptor3d_IsoCurve anIsoCurve;
  anIsoCurve.Load(theFace);
  occ::handle<Geom_Curve>    aBCurve;
  const BRepAdaptor_Surface& aBSurface = *theFace;
  GeomAbs_SurfaceType        aFaceType = theFace->GetType();

  int                       aNbLines = anIsoBuild.NbLines();
  occ::handle<Geom_Surface> aGeomBSurface;
  if (aFaceType == GeomAbs_BezierSurface)
  {
    aGeomBSurface = aBSurface.Bezier();
  }
  else if (aFaceType == GeomAbs_BSplineSurface)
  {
    aGeomBSurface = aBSurface.BSpline();
  }

  for (anI = 1; anI <= aNbLines; ++anI)
  {
    int    NumberOfIntervals = anIsoBuild.NbIntervals(anI);
    double anIsoCoord        = anIsoBuild.Coordinate(anI);
    for (int aJ = 1; aJ <= NumberOfIntervals; aJ++)
    {
      double b1 = anIsoBuild.Start(anI, aJ), b2 = anIsoBuild.End(anI, aJ);

      if (b1 == RealFirst() || b2 == RealLast())
        continue;

      occ::handle<NCollection_HSequence<gp_Pnt>> aPoints = new NCollection_HSequence<gp_Pnt>;
      if (!aGeomBSurface.IsNull())
      {
        if (anIsoBuild.IsXLine(anI))
        {
          aBCurve = aGeomBSurface->UIso(anIsoCoord);
        }
        else
        {
          aBCurve = aGeomBSurface->VIso(anIsoCoord);
        }

        StdPrs_Curve::Add(thePresentation,
                          GeomAdaptor_Curve(aBCurve),
                          b1,
                          b2,
                          aPoints->ChangeSequence(),
                          30,
                          false);
        theCurves.Append(aPoints);
      }
      else
      {
        if (anIsoBuild.IsXLine(anI))
        {
          anIsoCurve.Load(GeomAbs_IsoU, anIsoCoord, b1, b2);
        }
        else
        {
          anIsoCurve.Load(GeomAbs_IsoV, anIsoCoord, b1, b2);
        }
        StdPrs_Curve::Add(thePresentation, anIsoCurve, theDrawer, aPoints->ChangeSequence(), false);
        theCurves.Append(aPoints);
      }
    }
  }
}

bool StdPrs_WFRestrictedFace::Match(const double                            theX,
                                    const double                            theY,
                                    const double                            theZ,
                                    const double                            theDistance,
                                    const occ::handle<BRepAdaptor_Surface>& theFace,
                                    const bool                              theDrawUIso,
                                    const bool                              theDrawVIso,
                                    const double                            theDeflection,
                                    const int                               theNbUIso,
                                    const int                               theNBVIso,
                                    const occ::handle<Prs3d_Drawer>&        theDrawer)
{
  double           aLimit    = theDrawer->MaximalParameterValue();
  int              aNbPoints = theDrawer->Discretisation();
  StdPrs_ToolRFace aToolRst(theFace);

  double anUMin, anUMax, aVMin, aVMax;
  double anU, aV, aStep;
  int    anI, anNbP = 10;
  anUMin = aVMin = RealLast();
  anUMax = aVMax = RealFirst();
  gp_Pnt2d aPoint1, aPoint2;

  for (aToolRst.Init(); aToolRst.More(); aToolRst.Next())
  {
    const Adaptor2d_Curve2d* aRCurve = &aToolRst.Value();
    anU                              = aRCurve->FirstParameter();
    aV                               = aRCurve->LastParameter();
    if (aRCurve->GetType() != GeomAbs_Line)
    {
      aStep = (aV - anU) / anNbP;
      for (anI = 0; anI <= anNbP; ++anI)
      {
        gp_Pnt2d aRCurvePoint = aRCurve->Value(anU);
        if (aRCurvePoint.X() < anUMin)
          anUMin = aRCurvePoint.X();
        if (aRCurvePoint.X() > anUMax)
          anUMax = aRCurvePoint.X();
        if (aRCurvePoint.Y() < aVMin)
          aVMin = aRCurvePoint.Y();
        if (aRCurvePoint.Y() > aVMax)
          aVMax = aRCurvePoint.Y();
        anU += aStep;
      }
    }
    else
    {
      aPoint1 = aRCurve->Value(anU);
      if (aPoint1.X() < anUMin)
        anUMin = aPoint1.X();
      if (aPoint1.X() > anUMax)
        anUMax = aPoint1.X();
      if (aPoint1.Y() < aVMin)
        aVMin = aPoint1.Y();
      if (aPoint1.Y() > aVMax)
        aVMax = aPoint1.Y();

      aPoint2 = aRCurve->Value(aV);
      if (aPoint2.X() < anUMin)
        anUMin = aPoint2.X();
      if (aPoint2.X() > anUMax)
        anUMax = aPoint2.X();
      if (aPoint2.Y() < aVMin)
        aVMin = aPoint2.Y();
      if (aPoint2.Y() > aVMax)
        aVMax = aPoint2.Y();
    }
  }

  Hatch_Hatcher anIsoBuild(1.e-5, aToolRst.IsOriented());
  bool          anUClosed = theFace->IsUClosed();
  bool          aVClosed  = theFace->IsVClosed();

  if (!anUClosed)
  {
    anUMin = anUMin + (anUMax - anUMin) / 1000.;
    anUMax = anUMax - (anUMax - anUMin) / 1000.;
  }

  if (!aVClosed)
  {
    aVMin = aVMin + (aVMax - aVMin) / 1000.;
    aVMax = aVMax - (aVMax - aVMin) / 1000.;
  }

  if (theDrawUIso)
  {
    if (theNbUIso > 0)
    {
      anUClosed = false;
      double du = anUClosed ? (anUMax - anUMin) / theNbUIso : (anUMax - anUMin) / (1 + theNbUIso);
      for (anI = 1; anI <= theNbUIso; anI++)
      {
        anIsoBuild.AddXLine(anUMin + du * anI);
      }
    }
  }
  if (theDrawVIso)
  {
    if (theNBVIso > 0)
    {
      aVClosed  = false;
      double dv = aVClosed ? (aVMax - aVMin) / theNBVIso : (aVMax - aVMin) / (1 + theNBVIso);
      for (anI = 1; anI <= theNBVIso; anI++)
      {
        anIsoBuild.AddYLine(aVMin + dv * anI);
      }
    }
  }

  double anU1, anU2, aDU;

  for (aToolRst.Init(); aToolRst.More(); aToolRst.Next())
  {
    TopAbs_Orientation       Orient  = aToolRst.Orientation();
    const Adaptor2d_Curve2d* aRCurve = &aToolRst.Value();
    anU1                             = aRCurve->FirstParameter();
    anU2                             = aRCurve->LastParameter();
    if (aRCurve->GetType() != GeomAbs_Line)
    {
      aDU     = (anU2 - anU1) / (aNbPoints - 1);
      aPoint2 = aRCurve->Value(anU1);
      for (anI = 2; anI <= aNbPoints; anI++)
      {
        anU     = anU1 + (anI - 1) * aDU;
        aPoint1 = aPoint2;
        aPoint2 = aRCurve->Value(anU);
        if (Orient == TopAbs_FORWARD)
          anIsoBuild.Trim(aPoint1, aPoint2);
        else
          anIsoBuild.Trim(aPoint2, aPoint1);
      }
    }
    else
    {
      aPoint1 = aRCurve->Value(anU1);
      aPoint2 = aRCurve->Value(anU2);
      if (Orient == TopAbs_FORWARD)
        anIsoBuild.Trim(aPoint1, aPoint2);
      else
        anIsoBuild.Trim(aPoint2, aPoint1);
    }
  }

  Adaptor3d_IsoCurve anIso;
  anIso.Load(theFace);
  int aNbLines = anIsoBuild.NbLines();

  for (anI = 1; anI <= aNbLines; anI++)
  {
    int    aNbIntervals = anIsoBuild.NbIntervals(anI);
    double aCoord       = anIsoBuild.Coordinate(anI);
    for (int j = 1; j <= aNbIntervals; j++)
    {
      double anIsoStart = anIsoBuild.Start(anI, j), anIsoEnd = anIsoBuild.End(anI, j);

      anIsoStart = anIsoStart == RealFirst() ? -aLimit : anIsoStart;
      anIsoEnd   = anIsoEnd == RealLast() ? aLimit : anIsoEnd;

      if (anIsoBuild.IsXLine(anI))
        anIso.Load(GeomAbs_IsoU, aCoord, anIsoStart, anIsoEnd);
      else
        anIso.Load(GeomAbs_IsoV, aCoord, anIsoStart, anIsoEnd);

      if (StdPrs_Curve::Match(theX,
                              theY,
                              theZ,
                              theDistance,
                              anIso,
                              theDeflection,
                              aLimit,
                              aNbPoints))
        return true;
    }
  }
  return false;
}

void StdPrs_WFRestrictedFace::Add(const occ::handle<Prs3d_Presentation>&  thePresentation,
                                  const occ::handle<BRepAdaptor_Surface>& theFace,
                                  const occ::handle<Prs3d_Drawer>&        theDrawer)
{
  NCollection_List<occ::handle<NCollection_HSequence<gp_Pnt>>> aCurves;
  StdPrs_WFRestrictedFace::Add(thePresentation,
                               theFace,
                               true,
                               true,
                               theDrawer->UIsoAspect()->Number(),
                               theDrawer->VIsoAspect()->Number(),
                               theDrawer,
                               aCurves);
}

void StdPrs_WFRestrictedFace::AddUIso(const occ::handle<Prs3d_Presentation>&  thePresentation,
                                      const occ::handle<BRepAdaptor_Surface>& theFace,
                                      const occ::handle<Prs3d_Drawer>&        theDrawer)
{
  NCollection_List<occ::handle<NCollection_HSequence<gp_Pnt>>> aCurves;
  StdPrs_WFRestrictedFace::Add(thePresentation,
                               theFace,
                               true,
                               false,
                               theDrawer->UIsoAspect()->Number(),
                               theDrawer->VIsoAspect()->Number(),
                               theDrawer,
                               aCurves);
}

void StdPrs_WFRestrictedFace::AddVIso(const occ::handle<Prs3d_Presentation>&  thePresentation,
                                      const occ::handle<BRepAdaptor_Surface>& theFace,
                                      const occ::handle<Prs3d_Drawer>&        theDrawer)
{
  NCollection_List<occ::handle<NCollection_HSequence<gp_Pnt>>> aCurves;
  StdPrs_WFRestrictedFace::Add(thePresentation,
                               theFace,
                               false,
                               true,
                               theDrawer->UIsoAspect()->Number(),
                               theDrawer->VIsoAspect()->Number(),
                               theDrawer,
                               aCurves);
}

bool StdPrs_WFRestrictedFace::Match(const double                            theX,
                                    const double                            theY,
                                    const double                            theZ,
                                    const double                            theDistance,
                                    const occ::handle<BRepAdaptor_Surface>& theFace,
                                    const occ::handle<Prs3d_Drawer>&        theDrawer)
{
  return StdPrs_WFRestrictedFace::Match(theX,
                                        theY,
                                        theZ,
                                        theDistance,
                                        theFace,
                                        true,
                                        true,
                                        theDrawer->MaximalChordialDeviation(),
                                        theDrawer->UIsoAspect()->Number(),
                                        theDrawer->VIsoAspect()->Number(),
                                        theDrawer);
}

bool StdPrs_WFRestrictedFace::MatchUIso(const double                            theX,
                                        const double                            theY,
                                        const double                            theZ,
                                        const double                            theDistance,
                                        const occ::handle<BRepAdaptor_Surface>& theFace,
                                        const occ::handle<Prs3d_Drawer>&        theDrawer)
{
  return StdPrs_WFRestrictedFace::Match(theX,
                                        theY,
                                        theZ,
                                        theDistance,
                                        theFace,
                                        true,
                                        false,
                                        theDrawer->MaximalChordialDeviation(),
                                        theDrawer->UIsoAspect()->Number(),
                                        theDrawer->VIsoAspect()->Number(),
                                        theDrawer);
}

bool StdPrs_WFRestrictedFace::MatchVIso(const double                            theX,
                                        const double                            theY,
                                        const double                            theZ,
                                        const double                            theDistance,
                                        const occ::handle<BRepAdaptor_Surface>& theFace,
                                        const occ::handle<Prs3d_Drawer>&        theDrawer)
{
  return StdPrs_WFRestrictedFace::Match(theX,
                                        theY,
                                        theZ,
                                        theDistance,
                                        theFace,
                                        false,
                                        true,
                                        theDrawer->MaximalChordialDeviation(),
                                        theDrawer->UIsoAspect()->Number(),
                                        theDrawer->VIsoAspect()->Number(),
                                        theDrawer);
}
