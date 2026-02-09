#include <ProjLib_ProjectOnPlane.hpp>
#include <Approx_FitAndDivide.hpp>
#include <AppParCurves_MultiCurve.hpp>
#include <Standard_NoSuchObject.hpp>
#include <Standard_NotImplemented.hpp>
#include <Precision.hpp>
#include <BSplCLib.hpp>
#include <Geom_BezierCurve.hpp>
#include <ElCLib.hpp>
#include <Adaptor3d_Curve.hpp>
#include <GeomAdaptor_Curve.hpp>
#include <Geom_Line.hpp>
#include <GeomConvert.hpp>
#include <Geom_TrimmedCurve.hpp>
#include <Geom_Circle.hpp>
#include <Geom_Parabola.hpp>
#include <Geom_Hyperbola.hpp>
#include <Geom_Ellipse.hpp>
#include <GeomLib_Tool.hpp>
#include <math_Jacobi.hpp>
#include <math_Matrix.hpp>
#include <gce_MakeParab.hpp>
#include <gce_MakeDir.hpp>
#include <LProp3d_CLProps.hpp>
#include <math_Function.hpp>
#include <math_BrentMinimum.hpp>

const double aParabolaLimit  = 20000.;
const double aHyperbolaLimit = 10.;

static gp_Pnt OnPlane_Value(const double                        U,
                            const occ::handle<Adaptor3d_Curve>& aCurvePtr,
                            const gp_Ax3&                       Pl,
                            const gp_Dir&                       D)
{

  gp_Pnt Point = aCurvePtr->Value(U);

  gp_Vec PO(Point, Pl.Location());

  double Alpha = PO * gp_Vec(Pl.Direction());
  Alpha /= D * Pl.Direction();
  Point.SetXYZ(Point.XYZ() + Alpha * D.XYZ());

  return Point;
}

static gp_Vec OnPlane_DN(const double                        U,
                         const int                           DerivativeRequest,
                         const occ::handle<Adaptor3d_Curve>& aCurvePtr,
                         const gp_Ax3&                       Pl,
                         const gp_Dir&                       D)
{

  gp_Vec Vector = aCurvePtr->DN(U, DerivativeRequest);

  gp_Dir Z = Pl.Direction();

  double Alpha = Vector * gp_Vec(Z);
  Alpha /= D * Z;

  Vector.SetXYZ(Vector.XYZ() - Alpha * D.XYZ());
  return Vector;
}

static bool OnPlane_D1(const double                        U,
                       gp_Pnt&                             P,
                       gp_Vec&                             V,
                       const occ::handle<Adaptor3d_Curve>& aCurvePtr,
                       const gp_Ax3&                       Pl,
                       const gp_Dir&                       D)
{
  double Alpha;
  gp_Pnt Point;
  gp_Vec Vector;

  gp_Dir Z = Pl.Direction();

  aCurvePtr->D1(U, Point, Vector);

  gp_Vec PO(Point, Pl.Location());
  Alpha = PO * gp_Vec(Z);
  Alpha /= D * Z;
  P.SetXYZ(Point.XYZ() + Alpha * D.XYZ());

  Alpha = Vector * gp_Vec(Z);
  Alpha /= D * Z;

  V.SetXYZ(Vector.XYZ() - Alpha * D.XYZ());

  return true;
}

static bool OnPlane_D2(const double                        U,
                       gp_Pnt&                             P,
                       gp_Vec&                             V1,
                       gp_Vec&                             V2,
                       const occ::handle<Adaptor3d_Curve>& aCurvePtr,
                       const gp_Ax3&                       Pl,
                       const gp_Dir&                       D)
{
  double Alpha;
  gp_Pnt Point;
  gp_Vec Vector1, Vector2;

  gp_Dir Z = Pl.Direction();

  aCurvePtr->D2(U, Point, Vector1, Vector2);

  gp_Vec PO(Point, Pl.Location());
  Alpha = PO * gp_Vec(Z);
  Alpha /= D * Z;
  P.SetXYZ(Point.XYZ() + Alpha * D.XYZ());

  Alpha = Vector1 * gp_Vec(Z);
  Alpha /= D * Z;

  V1.SetXYZ(Vector1.XYZ() - Alpha * D.XYZ());

  Alpha = Vector2 * gp_Vec(Z);
  Alpha /= D * Z;

  V2.SetXYZ(Vector2.XYZ() - Alpha * D.XYZ());
  return true;
}

static bool OnPlane_D3(const double                        U,
                       gp_Pnt&                             P,
                       gp_Vec&                             V1,
                       gp_Vec&                             V2,
                       gp_Vec&                             V3,
                       const occ::handle<Adaptor3d_Curve>& aCurvePtr,
                       const gp_Ax3&                       Pl,
                       const gp_Dir&                       D)
{
  double Alpha;
  gp_Pnt Point;
  gp_Vec Vector1, Vector2, Vector3;

  gp_Dir Z = Pl.Direction();

  aCurvePtr->D3(U, Point, Vector1, Vector2, Vector3);

  gp_Vec PO(Point, Pl.Location());
  Alpha = PO * gp_Vec(Z);
  Alpha /= D * Z;
  P.SetXYZ(Point.XYZ() + Alpha * D.XYZ());

  Alpha = Vector1 * gp_Vec(Z);
  Alpha /= D * Z;

  V1.SetXYZ(Vector1.XYZ() - Alpha * D.XYZ());

  Alpha = Vector2 * gp_Vec(Z);
  Alpha /= D * Z;

  V2.SetXYZ(Vector2.XYZ() - Alpha * D.XYZ());
  Alpha = Vector3 * gp_Vec(Z);
  Alpha /= D * Z;

  V3.SetXYZ(Vector3.XYZ() - Alpha * D.XYZ());
  return true;
}

class ProjLib_OnPlane : public AppCont_Function

{
  occ::handle<Adaptor3d_Curve> myCurve;
  gp_Ax3                       myPlane;
  gp_Dir                       myDirection;

public:
  ProjLib_OnPlane(const occ::handle<Adaptor3d_Curve>& C, const gp_Ax3& Pl, const gp_Dir& D)
      : myCurve(C),
        myPlane(Pl),
        myDirection(D)
  {
    myNbPnt   = 1;
    myNbPnt2d = 0;
  }

  double FirstParameter() const override { return myCurve->FirstParameter(); }

  double LastParameter() const override { return myCurve->LastParameter(); }

  bool Value(const double theT,
             NCollection_Array1<gp_Pnt2d>&,
             NCollection_Array1<gp_Pnt>& thePnt) const override
  {
    thePnt(1) = OnPlane_Value(theT, myCurve, myPlane, myDirection);
    return true;
  }

  bool D1(const double theT,
          NCollection_Array1<gp_Vec2d>&,
          NCollection_Array1<gp_Vec>& theVec) const override
  {
    gp_Pnt aDummyPnt;
    return OnPlane_D1(theT, aDummyPnt, theVec(1), myCurve, myPlane, myDirection);
  }
};

class ProjLib_MaxCurvature : public math_Function

{

public:
  ProjLib_MaxCurvature(LProp3d_CLProps& theProps)
      : myProps(&theProps)
  {
  }

  bool Value(const double X, double& F) override
  {
    myProps->SetParameter(X);
    F = -myProps->Curvature();
    return true;
  }

private:
  LProp3d_CLProps* myProps;
};

static void PerformApprox(const occ::handle<Adaptor3d_Curve>& C,
                          const gp_Ax3&                       Pl,
                          const gp_Dir&                       D,
                          occ::handle<Geom_BSplineCurve>&     BSplineCurvePtr)

{
  ProjLib_OnPlane F(C, Pl, D);

  int Deg1, Deg2;
  Deg1 = 8;
  Deg2 = 8;
  if (C->GetType() == GeomAbs_Parabola)
  {
    Deg1 = 2;
    Deg2 = 2;
  }
  int aNbSegm = 100;
  if (C->GetType() == GeomAbs_Hyperbola)
  {
    Deg1    = 14;
    Deg2    = 14;
    aNbSegm = 1000;
  }
  Approx_FitAndDivide Fit(Deg1,
                          Deg2,
                          Precision::Approximation(),
                          Precision::PApproximation(),
                          true);
  Fit.SetMaxSegments(aNbSegm);
  Fit.Perform(F);
  if (!Fit.IsAllApproximated())
  {
    return;
  }
  int i;
  int NbCurves = Fit.NbMultiCurves();
  int MaxDeg   = 0;

  int NbPoles = 1;
  for (i = 1; i <= NbCurves; i++)
  {
    int Deg = Fit.Value(i).Degree();
    MaxDeg  = std::max(MaxDeg, Deg);
  }
  NbPoles = MaxDeg * NbCurves + 1;

  NCollection_Array1<gp_Pnt> Poles(1, NbPoles);

  NCollection_Array1<gp_Pnt> TempPoles(1, MaxDeg + 1);

  NCollection_Array1<double> Knots(1, NbCurves + 1);

  int    Compt    = 1;
  double anErrMax = 0., anErr3d, anErr2d;
  for (i = 1; i <= Fit.NbMultiCurves(); i++)
  {
    Fit.Parameters(i, Knots(i), Knots(i + 1));
    Fit.Error(i, anErr3d, anErr2d);
    anErrMax                      = std::max(anErrMax, anErr3d);
    AppParCurves_MultiCurve    MC = Fit.Value(i);
    NCollection_Array1<gp_Pnt> LocalPoles(1, MC.Degree() + 1);
    MC.Curve(1, LocalPoles);

    if (MaxDeg > MC.Degree())
    {
      BSplCLib::IncreaseDegree(MaxDeg,
                               LocalPoles,
                               BSplCLib::NoWeights(),
                               TempPoles,
                               BSplCLib::NoWeights());

      for (int j = 1; j <= MaxDeg + 1; j++)
      {
        Poles.SetValue(Compt, TempPoles(j));
        Compt++;
      }
    }
    else
    {

      for (int j = 1; j <= MaxDeg + 1; j++)
      {
        Poles.SetValue(Compt, LocalPoles(j));
        Compt++;
      }
    }

    Compt--;
  }

  int NbKnots = NbCurves + 1;

  NCollection_Array1<int> Mults(1, NbKnots);
  Mults.SetValue(1, MaxDeg + 1);
  for (i = 2; i <= NbCurves; i++)
  {
    Mults.SetValue(i, MaxDeg);
  }
  Mults.SetValue(NbKnots, MaxDeg + 1);
  BSplineCurvePtr = new Geom_BSplineCurve(Poles, Knots, Mults, MaxDeg, false);

  int m1 = MaxDeg - 1;
  for (i = 2; i < NbKnots; ++i)
  {
    if (BSplineCurvePtr->Multiplicity(i) == MaxDeg)
    {
      BSplineCurvePtr->RemoveKnot(i, m1, anErrMax);
    }
  }
}

ProjLib_ProjectOnPlane::ProjLib_ProjectOnPlane()
    : myKeepParam(false),
      myFirstPar(0.),
      myLastPar(0.),
      myTolerance(0.),
      myType(GeomAbs_OtherCurve),
      myIsApprox(false)
{
}

ProjLib_ProjectOnPlane::ProjLib_ProjectOnPlane(const gp_Ax3& Pl)
    : myPlane(Pl),
      myDirection(Pl.Direction()),
      myKeepParam(false),
      myFirstPar(0.),
      myLastPar(0.),
      myTolerance(0.),
      myType(GeomAbs_OtherCurve),
      myIsApprox(false)
{
}

ProjLib_ProjectOnPlane::ProjLib_ProjectOnPlane(const gp_Ax3& Pl, const gp_Dir& D)
    : myPlane(Pl),
      myDirection(D),
      myKeepParam(false),
      myFirstPar(0.),
      myLastPar(0.),
      myTolerance(0.),
      myType(GeomAbs_OtherCurve),
      myIsApprox(false)
{
}

occ::handle<Adaptor3d_Curve> ProjLib_ProjectOnPlane::ShallowCopy() const
{
  occ::handle<ProjLib_ProjectOnPlane> aCopy = new ProjLib_ProjectOnPlane();

  if (!myCurve.IsNull())
  {
    aCopy->myCurve = myCurve->ShallowCopy();
  }
  aCopy->myPlane     = myPlane;
  aCopy->myDirection = myDirection;
  aCopy->myKeepParam = myKeepParam;
  aCopy->myFirstPar  = myFirstPar;
  aCopy->myLastPar   = myLastPar;
  aCopy->myTolerance = myTolerance;
  aCopy->myType      = myType;
  if (!myResult.IsNull())
  {
    aCopy->myResult = occ::down_cast<GeomAdaptor_Curve>(myResult->ShallowCopy());
  }
  aCopy->myIsApprox = myIsApprox;

  return aCopy;
}

static gp_Pnt ProjectPnt(const gp_Ax3& ThePlane, const gp_Dir& TheDir, const gp_Pnt& Point)
{
  gp_Vec PO(Point, ThePlane.Location());

  double Alpha = PO * gp_Vec(ThePlane.Direction());
  Alpha /= TheDir * ThePlane.Direction();

  gp_Pnt P;
  P.SetXYZ(Point.XYZ() + Alpha * TheDir.XYZ());

  return P;
}

static gp_Vec ProjectVec(const gp_Ax3& ThePlane, const gp_Dir& TheDir, const gp_Vec& Vec)
{
  gp_Vec D = Vec;
  gp_Vec Z = ThePlane.Direction();

  D -= ((Vec * Z) / (TheDir * Z)) * TheDir;

  return D;
}

void ProjLib_ProjectOnPlane::Load(const occ::handle<Adaptor3d_Curve>& C,
                                  const double                        Tolerance,
                                  const bool                          KeepParametrization)

{
  myCurve     = C;
  myType      = GeomAbs_OtherCurve;
  myIsApprox  = false;
  myTolerance = Tolerance;

  occ::handle<Geom_BSplineCurve> ApproxCurve;
  occ::handle<GeomAdaptor_Curve> aGAHCurve;

  occ::handle<Geom_Line>      GeomLinePtr;
  occ::handle<Geom_Circle>    GeomCirclePtr;
  occ::handle<Geom_Ellipse>   GeomEllipsePtr;
  occ::handle<Geom_Hyperbola> GeomHyperbolaPtr;
  occ::handle<Geom_Parabola>  GeomParabolaPtr;

  gp_Lin   aLine;
  gp_Elips Elips;

  int               num_knots;
  GeomAbs_CurveType Type = C->GetType();

  gp_Ax2 Axis;
  double R1 = 0., R2 = 0.;

  myKeepParam = KeepParametrization;

  switch (Type)
  {
    case GeomAbs_Line:
    {

      gp_Lin L  = myCurve->Line();
      gp_Vec Xc = ProjectVec(myPlane, myDirection, gp_Vec(L.Direction()));

      if (Xc.Magnitude() < Precision::Confusion())
      {
        myType                    = GeomAbs_BSplineCurve;
        gp_Pnt                  P = ProjectPnt(myPlane, myDirection, L.Location());
        NCollection_Array1<int> Mults(1, 2);
        Mults.Init(2);
        NCollection_Array1<gp_Pnt> Poles(1, 2);
        Poles.Init(P);
        NCollection_Array1<double> Knots(1, 2);
        Knots(1)                           = myCurve->FirstParameter();
        Knots(2)                           = myCurve->LastParameter();
        occ::handle<Geom_BSplineCurve> BSP = new Geom_BSplineCurve(Poles, Knots, Mults, 1);

        GeomAdaptor_Curve aGACurve(BSP);
        myResult = new GeomAdaptor_Curve(aGACurve);
      }
      else if (std::abs(Xc.Magnitude() - 1.) < Precision::Confusion())
      {
        myType      = GeomAbs_Line;
        gp_Pnt P    = ProjectPnt(myPlane, myDirection, L.Location());
        myFirstPar  = myCurve->FirstParameter();
        myLastPar   = myCurve->LastParameter();
        aLine       = gp_Lin(P, gp_Dir(Xc));
        GeomLinePtr = new Geom_Line(aLine);

        GeomAdaptor_Curve aGACurve(GeomLinePtr,
                                   myCurve->FirstParameter(),
                                   myCurve->LastParameter());
        myResult = new GeomAdaptor_Curve(aGACurve);
      }
      else
      {
        myType   = GeomAbs_Line;
        gp_Pnt P = ProjectPnt(myPlane, myDirection, L.Location());
        aLine    = gp_Lin(P, gp_Dir(Xc));
        double Udeb, Ufin;

        Udeb        = myCurve->FirstParameter();
        Ufin        = myCurve->LastParameter();
        gp_Pnt P1   = ProjectPnt(myPlane, myDirection, myCurve->Value(Udeb));
        gp_Pnt P2   = ProjectPnt(myPlane, myDirection, myCurve->Value(Ufin));
        myFirstPar  = gp_Vec(aLine.Direction()).Dot(gp_Vec(P, P1));
        myLastPar   = gp_Vec(aLine.Direction()).Dot(gp_Vec(P, P2));
        GeomLinePtr = new Geom_Line(aLine);
        if (!myKeepParam)
        {

          GeomAdaptor_Curve aGACurve(GeomLinePtr, myFirstPar, myLastPar);
          myResult = new GeomAdaptor_Curve(aGACurve);
        }
        else
        {
          myType = GeomAbs_BSplineCurve;

          occ::handle<Geom_TrimmedCurve> NewTrimCurvePtr =
            new Geom_TrimmedCurve(GeomLinePtr, myFirstPar, myLastPar);

          occ::handle<Geom_BSplineCurve> NewCurvePtr =
            GeomConvert::CurveToBSplineCurve(NewTrimCurvePtr);
          num_knots = NewCurvePtr->NbKnots();
          NCollection_Array1<double> BsplineKnots(1, num_knots);
          NewCurvePtr->Knots(BsplineKnots);

          BSplCLib::Reparametrize(myCurve->FirstParameter(),
                                  myCurve->LastParameter(),
                                  BsplineKnots);

          NewCurvePtr->SetKnots(BsplineKnots);

          GeomAdaptor_Curve aGACurve(NewCurvePtr);
          myResult = new GeomAdaptor_Curve(aGACurve);
        }
      }
      break;
    }
    case GeomAbs_Circle:
    {

      gp_Circ Circ = myCurve->Circle();
      Axis         = Circ.Position();
      R1 = R2 = Circ.Radius();
    }
      [[fallthrough]];
    case GeomAbs_Ellipse:
    {
      if (Type == GeomAbs_Ellipse)
      {
        gp_Elips E = myCurve->Ellipse();
        Axis       = E.Position();
        R1         = E.MajorRadius();
        R2         = E.MinorRadius();
      }

      gp_Dir X   = Axis.XDirection();
      gp_Dir Y   = Axis.YDirection();
      gp_Vec VDx = ProjectVec(myPlane, myDirection, X);
      gp_Vec VDy = ProjectVec(myPlane, myDirection, Y);
      gp_Dir Dx, Dy;

      double Tol2 = myTolerance * myTolerance;
      if (VDx.SquareMagnitude() < Tol2 || VDy.SquareMagnitude() < Tol2
          || VDx.CrossSquareMagnitude(VDy) < Tol2)
      {
        myIsApprox = true;
      }

      if (!myIsApprox)
      {
        Dx           = gp_Dir(VDx);
        Dy           = gp_Dir(VDy);
        gp_Pnt O     = Axis.Location();
        gp_Pnt P     = ProjectPnt(myPlane, myDirection, O);
        gp_Pnt Px    = ProjectPnt(myPlane, myDirection, O.Translated(R1 * gp_Vec(X)));
        gp_Pnt Py    = ProjectPnt(myPlane, myDirection, O.Translated(R2 * gp_Vec(Y)));
        double Major = P.Distance(Px);
        double Minor = P.Distance(Py);

        if (myKeepParam)
        {
          myIsApprox = !gp_Dir(VDx).IsNormal(gp_Dir(VDy), Precision::Angular());
        }
        else
        {

          math_Matrix aMatrA(1, 2, 1, 2);

          aMatrA(1, 1) = myPlane.XDirection().XYZ().Dot(VDx.XYZ());
          aMatrA(1, 2) = myPlane.XDirection().XYZ().Dot(VDy.XYZ());
          aMatrA(2, 1) = myPlane.YDirection().XYZ().Dot(VDx.XYZ());
          aMatrA(2, 2) = myPlane.YDirection().XYZ().Dot(VDy.XYZ());

          math_Matrix aMatrDelta2(1, 2, 1, 2, 0.0);

          aMatrDelta2(1, 1) = 1.0 / (R1 * R1);
          aMatrDelta2(2, 2) = 1.0 / (R2 * R2);

          math_Matrix aMatrAInv = aMatrA.Inverse();
          math_Matrix aMatrM    = aMatrAInv.Transposed() * aMatrDelta2 * aMatrAInv;

          math_Jacobi anEigenCalc(aMatrM);
          if (anEigenCalc.IsDone())
          {

            Minor = 1.0 / std::sqrt(anEigenCalc.Value(1));
            Major = 1.0 / std::sqrt(anEigenCalc.Value(2));

            const math_Matrix& anEigenVec = anEigenCalc.Vectors();
            gp_Trsf2d          aTrsfInPlane;
            aTrsfInPlane.SetValues(anEigenVec(1, 2),
                                   anEigenVec(1, 1),
                                   0.0,
                                   anEigenVec(2, 2),
                                   anEigenVec(2, 1),
                                   0.0);
            gp_Trsf aRot;
            aRot.SetRotation(gp_Ax1(P, myPlane.Direction()), aTrsfInPlane.RotationPart());

            Dx = myPlane.XDirection().Transformed(aRot);
            Dy = myPlane.YDirection().Transformed(aRot);
          }
          else
          {
            myIsApprox = true;
          }
        }

        if (!myIsApprox)
        {
          gp_Ax2 Axe(P, Dx ^ Dy, Dx);

          if (std::abs(Major - Minor) < Precision::Confusion())
          {
            myType = GeomAbs_Circle;
            gp_Circ Circ(Axe, Major);
            GeomCirclePtr = new Geom_Circle(Circ);

            GeomAdaptor_Curve aGACurve(GeomCirclePtr);
            myResult = new GeomAdaptor_Curve(aGACurve);
          }
          else if (Major > Minor)
          {
            myType = GeomAbs_Ellipse;
            Elips  = gp_Elips(Axe, Major, Minor);

            GeomEllipsePtr = new Geom_Ellipse(Elips);

            GeomAdaptor_Curve aGACurve(GeomEllipsePtr);
            myResult = new GeomAdaptor_Curve(aGACurve);
          }
          else
          {
            myIsApprox = true;
          }
        }
      }

      if (myIsApprox)
      {
        myType = GeomAbs_BSplineCurve;
        PerformApprox(myCurve, myPlane, myDirection, ApproxCurve);

        GeomAdaptor_Curve aGACurve(ApproxCurve);
        myResult = new GeomAdaptor_Curve(aGACurve);
      }
      else if (GeomCirclePtr || GeomEllipsePtr)
      {
        occ::handle<Geom_Curve> aResultCurve = GeomCirclePtr;
        if (aResultCurve.IsNull())
          aResultCurve = GeomEllipsePtr;

        double aParFirst = myCurve->FirstParameter();
        double aParLast  = myCurve->LastParameter();
        gp_Pnt aPntFirst = ProjectPnt(myPlane, myDirection, myCurve->Value(aParFirst));
        gp_Pnt aPntLast  = ProjectPnt(myPlane, myDirection, myCurve->Value(aParLast));
        GeomLib_Tool::Parameter(aResultCurve, aPntFirst, Precision::Confusion(), myFirstPar);
        GeomLib_Tool::Parameter(aResultCurve, aPntLast, Precision::Confusion(), myLastPar);
        while (myLastPar <= myFirstPar)
          myLastPar += myResult->Period();
      }
    }
    break;
    case GeomAbs_Parabola:
    {

      gp_Parab Parab  = myCurve->Parabola();
      gp_Ax2   AxeRef = Parab.Position();
      gp_Vec   Xc     = ProjectVec(myPlane, myDirection, gp_Vec(AxeRef.XDirection()));
      gp_Vec   Yc     = ProjectVec(myPlane, myDirection, gp_Vec(AxeRef.YDirection()));
      gp_Pnt   P      = ProjectPnt(myPlane, myDirection, AxeRef.Location());

      myIsApprox = false;

      if ((std::abs(Yc.Magnitude() - 1.) < Precision::Confusion())
          && (Xc.Magnitude() < Precision::Confusion()))
      {
        myType      = GeomAbs_Line;
        aLine       = gp_Lin(P, gp_Dir(Yc));
        GeomLinePtr = new Geom_Line(aLine);
      }
      else if (Xc.IsNormal(Yc, Precision::Angular()))
      {
        myType              = GeomAbs_Parabola;
        double   F          = Parab.Focal() / Xc.Magnitude();
        gp_Parab aProjParab = gp_Parab(gp_Ax2(P, Xc ^ Yc, Xc), F);
        GeomParabolaPtr     = new Geom_Parabola(aProjParab);
      }
      else if (Yc.Magnitude() < Precision::Confusion() || Yc.IsParallel(Xc, Precision::Angular()))
      {
        myIsApprox = true;
      }
      else if (!myKeepParam)
      {

        myIsApprox = !BuildParabolaByApex(GeomParabolaPtr);
      }
      else
      {
        myIsApprox = true;
      }

      if (!myIsApprox)
      {
        GetTrimmedResult(GeomParabolaPtr);
      }
      else
      {
        BuildByApprox(aParabolaLimit);
      }
    }
    break;
    case GeomAbs_Hyperbola:
    {

      gp_Hypr Hypr   = myCurve->Hyperbola();
      gp_Ax2  AxeRef = Hypr.Position();
      gp_Vec  Xc     = ProjectVec(myPlane, myDirection, gp_Vec(AxeRef.XDirection()));
      gp_Vec  Yc     = ProjectVec(myPlane, myDirection, gp_Vec(AxeRef.YDirection()));
      gp_Pnt  P      = ProjectPnt(myPlane, myDirection, AxeRef.Location());
      double  aR1    = Hypr.MajorRadius();
      double  aR2    = Hypr.MinorRadius();
      gp_Dir  Z      = myPlane.Direction();
      myIsApprox     = false;

      if (Xc.Magnitude() < Precision::Confusion())
      {
        myType           = GeomAbs_Hyperbola;
        gp_Dir X         = gp_Dir(Yc) ^ Z;
        Hypr             = gp_Hypr(gp_Ax2(P, Z, X), 0., aR2 * Yc.Magnitude());
        GeomHyperbolaPtr = new Geom_Hyperbola(Hypr);
      }
      else if (Yc.Magnitude() < Precision::Confusion())
      {
        myType           = GeomAbs_Hyperbola;
        Hypr             = gp_Hypr(gp_Ax2(P, Z, gp_Dir(Xc)), aR1 * Xc.Magnitude(), 0.);
        GeomHyperbolaPtr = new Geom_Hyperbola(Hypr);
      }
      else if (Xc.IsNormal(Yc, Precision::Angular()))
      {
        myType           = GeomAbs_Hyperbola;
        Hypr             = gp_Hypr(gp_Ax2(P, gp_Dir(Xc ^ Yc), gp_Dir(Xc)),
                       aR1 * Xc.Magnitude(),
                       aR2 * Yc.Magnitude());
        GeomHyperbolaPtr = new Geom_Hyperbola(Hypr);
      }
      else if (Yc.Magnitude() < Precision::Confusion() || Yc.IsParallel(Xc, Precision::Angular()))
      {
        myIsApprox = true;
      }
      else if (!myKeepParam)
      {
        myIsApprox = !BuildHyperbolaByApex(GeomHyperbolaPtr);
      }
      else
      {
        myIsApprox = true;
      }
      if (!myIsApprox)
      {
        GetTrimmedResult(GeomHyperbolaPtr);
      }
      else
      {
        BuildByApprox(aHyperbolaLimit);
      }
    }
    break;
    case GeomAbs_BezierCurve:
    {
      occ::handle<Geom_BezierCurve> BezierCurvePtr = myCurve->Bezier();
      int                           NbPoles        = BezierCurvePtr->NbPoles();

      occ::handle<Geom_BezierCurve> ProjCu =
        occ::down_cast<Geom_BezierCurve>(BezierCurvePtr->Copy());

      myKeepParam = true;
      myIsApprox  = false;
      myType      = Type;
      for (int i = 1; i <= NbPoles; i++)
      {
        ProjCu->SetPole(i, ProjectPnt(myPlane, myDirection, BezierCurvePtr->Pole(i)));
      }

      GeomAdaptor_Curve aGACurve(ProjCu);
      myResult = new GeomAdaptor_Curve(aGACurve);
    }
    break;
    case GeomAbs_BSplineCurve:
    {
      occ::handle<Geom_BSplineCurve> BSplineCurvePtr = myCurve->BSpline();

      occ::handle<Geom_BSplineCurve> ProjectedBSplinePtr =
        occ::down_cast<Geom_BSplineCurve>(BSplineCurvePtr->Copy());

      myKeepParam = true;
      myIsApprox  = false;
      myType      = Type;
      for (int i = 1; i <= BSplineCurvePtr->NbPoles(); i++)
      {
        ProjectedBSplinePtr->SetPole(i, ProjectPnt(myPlane, myDirection, BSplineCurvePtr->Pole(i)));
      }

      GeomAdaptor_Curve aGACurve(ProjectedBSplinePtr);
      myResult = new GeomAdaptor_Curve(aGACurve);
    }
    break;
    default:
    {
      myKeepParam = true;
      myIsApprox  = true;
      myType      = GeomAbs_BSplineCurve;
      PerformApprox(myCurve, myPlane, myDirection, ApproxCurve);

      GeomAdaptor_Curve aGACurve(ApproxCurve);
      myResult = new GeomAdaptor_Curve(aGACurve);
    }
    break;
  }
}

const gp_Ax3& ProjLib_ProjectOnPlane::GetPlane() const
{
  return myPlane;
}

const gp_Dir& ProjLib_ProjectOnPlane::GetDirection() const
{
  return myDirection;
}

const occ::handle<Adaptor3d_Curve>& ProjLib_ProjectOnPlane::GetCurve() const
{
  return myCurve;
}

const occ::handle<GeomAdaptor_Curve>& ProjLib_ProjectOnPlane::GetResult() const
{
  return myResult;
}

double ProjLib_ProjectOnPlane::FirstParameter() const
{
  if (myKeepParam || myIsApprox)
    return myCurve->FirstParameter();
  else
    return myFirstPar;
}

double ProjLib_ProjectOnPlane::LastParameter() const
{
  if (myKeepParam || myIsApprox)
    return myCurve->LastParameter();
  else
    return myLastPar;
}

GeomAbs_Shape ProjLib_ProjectOnPlane::Continuity() const
{
  return myCurve->Continuity();
}

int ProjLib_ProjectOnPlane::NbIntervals(const GeomAbs_Shape S) const
{
  return myCurve->NbIntervals(S);
}

void ProjLib_ProjectOnPlane::Intervals(NCollection_Array1<double>& T, const GeomAbs_Shape S) const
{
  myCurve->Intervals(T, S);
}

occ::handle<Adaptor3d_Curve> ProjLib_ProjectOnPlane::Trim(const double First,
                                                          const double Last,
                                                          const double Tolerance) const
{
  if (myType != GeomAbs_OtherCurve)
  {
    return myResult->Trim(First, Last, Tolerance);
  }
  else
  {
    throw Standard_NotImplemented("ProjLib_ProjectOnPlane::Trim() - curve of unsupported type");
  }
}

bool ProjLib_ProjectOnPlane::IsClosed() const
{
  return myCurve->IsClosed();
}

bool ProjLib_ProjectOnPlane::IsPeriodic() const
{
  if (myIsApprox)
    return false;
  else
    return myCurve->IsPeriodic();
}

double ProjLib_ProjectOnPlane::Period() const
{
  if (!IsPeriodic())
  {
    throw Standard_NoSuchObject("ProjLib_ProjectOnPlane::Period");
  }

  if (myIsApprox)
    return false;
  else
    return myCurve->Period();
}

gp_Pnt ProjLib_ProjectOnPlane::Value(const double U) const
{
  if (myType != GeomAbs_OtherCurve)
  {
    return myResult->Value(U);
  }
  else
  {
    return OnPlane_Value(U, myCurve, myPlane, myDirection);
  }
}

void ProjLib_ProjectOnPlane::D0(const double U, gp_Pnt& P) const
{
  if (myType != GeomAbs_OtherCurve)
  {
    myResult->D0(U, P);
  }
  else
  {
    P = OnPlane_Value(U, myCurve, myPlane, myDirection);
  }
}

void ProjLib_ProjectOnPlane::D1(const double U, gp_Pnt& P, gp_Vec& V) const
{
  if (myType != GeomAbs_OtherCurve)
  {
    myResult->D1(U, P, V);
  }
  else
  {
    OnPlane_D1(U, P, V, myCurve, myPlane, myDirection);
  }
}

void ProjLib_ProjectOnPlane::D2(const double U, gp_Pnt& P, gp_Vec& V1, gp_Vec& V2) const
{
  if (myType != GeomAbs_OtherCurve)
  {
    myResult->D2(U, P, V1, V2);
  }
  else
  {
    OnPlane_D2(U, P, V1, V2, myCurve, myPlane, myDirection);
  }
}

void ProjLib_ProjectOnPlane::D3(const double U, gp_Pnt& P, gp_Vec& V1, gp_Vec& V2, gp_Vec& V3) const
{
  if (myType != GeomAbs_OtherCurve)
  {
    myResult->D3(U, P, V1, V2, V3);
  }
  else
  {
    OnPlane_D3(U, P, V1, V2, V3, myCurve, myPlane, myDirection);
  }
}

gp_Vec ProjLib_ProjectOnPlane::DN(const double U, const int DerivativeRequest) const
{
  if (myType != GeomAbs_OtherCurve)
  {
    return myResult->DN(U, DerivativeRequest);
  }
  else
  {
    return OnPlane_DN(U, DerivativeRequest, myCurve, myPlane, myDirection);
  }
}

double ProjLib_ProjectOnPlane::Resolution(const double Tolerance) const
{
  if (myType != GeomAbs_OtherCurve)
  {
    return myResult->Resolution(Tolerance);
  }
  else
  {
    return 0;
  }
}

GeomAbs_CurveType ProjLib_ProjectOnPlane::GetType() const
{
  return myType;
}

gp_Lin ProjLib_ProjectOnPlane::Line() const
{
  if (myType != GeomAbs_Line)
    throw Standard_NoSuchObject("ProjLib_ProjectOnPlane:Line");

  return myResult->Line();
}

gp_Circ ProjLib_ProjectOnPlane::Circle() const
{
  if (myType != GeomAbs_Circle)
    throw Standard_NoSuchObject("ProjLib_ProjectOnPlane:Circle");

  return myResult->Circle();
}

gp_Elips ProjLib_ProjectOnPlane::Ellipse() const
{
  if (myType != GeomAbs_Ellipse)
    throw Standard_NoSuchObject("ProjLib_ProjectOnPlane:Ellipse");

  return myResult->Ellipse();
}

gp_Hypr ProjLib_ProjectOnPlane::Hyperbola() const
{
  if (myType != GeomAbs_Hyperbola)
    throw Standard_NoSuchObject("ProjLib_ProjectOnPlane:Hyperbola");

  return myResult->Hyperbola();
}

gp_Parab ProjLib_ProjectOnPlane::Parabola() const
{
  if (myType != GeomAbs_Parabola)
    throw Standard_NoSuchObject("ProjLib_ProjectOnPlane:Parabola");

  return myResult->Parabola();
}

int ProjLib_ProjectOnPlane::Degree() const
{
  if ((GetType() != GeomAbs_BSplineCurve) && (GetType() != GeomAbs_BezierCurve))
    throw Standard_NoSuchObject("ProjLib_ProjectOnPlane:Degree");

  if (myIsApprox)
    return myResult->Degree();
  else
    return myCurve->Degree();
}

bool ProjLib_ProjectOnPlane::IsRational() const
{
  if ((GetType() != GeomAbs_BSplineCurve) && (GetType() != GeomAbs_BezierCurve))
    throw Standard_NoSuchObject("ProjLib_ProjectOnPlane:IsRational");

  if (myIsApprox)
    return myResult->IsRational();
  else
    return myCurve->IsRational();
}

int ProjLib_ProjectOnPlane::NbPoles() const
{
  if ((GetType() != GeomAbs_BSplineCurve) && (GetType() != GeomAbs_BezierCurve))
    throw Standard_NoSuchObject("ProjLib_ProjectOnPlane:NbPoles");

  if (myIsApprox)
    return myResult->NbPoles();
  else
    return myCurve->NbPoles();
}

int ProjLib_ProjectOnPlane::NbKnots() const
{
  if (GetType() != GeomAbs_BSplineCurve)
    throw Standard_NoSuchObject("ProjLib_ProjectOnPlane:NbKnots");

  if (myIsApprox)
    return myResult->NbKnots();
  else
    return myCurve->NbKnots();
}

occ::handle<Geom_BezierCurve> ProjLib_ProjectOnPlane::Bezier() const
{
  if (myType != GeomAbs_BezierCurve)
    throw Standard_NoSuchObject("ProjLib_ProjectOnPlane:Bezier");

  return myResult->Bezier();
}

occ::handle<Geom_BSplineCurve> ProjLib_ProjectOnPlane::BSpline() const
{
  if (myType != GeomAbs_BSplineCurve)
    throw Standard_NoSuchObject("ProjLib_ProjectOnPlane:BSpline");

  return myResult->BSpline();
}

void ProjLib_ProjectOnPlane::GetTrimmedResult(const occ::handle<Geom_Curve>& theProjCurve)
{
  gp_Lin   aLin;
  gp_Parab aParab;
  gp_Hypr  aHypr;
  if (myType == GeomAbs_Line)
  {
    aLin = occ::down_cast<Geom_Line>(theProjCurve)->Lin();
  }
  else if (myType == GeomAbs_Parabola)
  {
    aParab = occ::down_cast<Geom_Parabola>(theProjCurve)->Parab();
  }
  else if (myType == GeomAbs_Hyperbola)
  {
    aHypr = occ::down_cast<Geom_Hyperbola>(theProjCurve)->Hypr();
  }

  myFirstPar = theProjCurve->FirstParameter();
  myLastPar  = theProjCurve->LastParameter();
  if (!Precision::IsInfinite(myCurve->FirstParameter()))
  {
    gp_Pnt aP = myCurve->Value(myCurve->FirstParameter());
    aP        = ProjectPnt(myPlane, myDirection, aP);
    if (myType == GeomAbs_Line)
    {
      myFirstPar = ElCLib::Parameter(aLin, aP);
    }
    else if (myType == GeomAbs_Parabola)
    {
      myFirstPar = ElCLib::Parameter(aParab, aP);
    }
    else if (myType == GeomAbs_Hyperbola)
    {
      myFirstPar = ElCLib::Parameter(aHypr, aP);
    }
    else
    {
      GeomLib_Tool::Parameter(theProjCurve, aP, Precision::Confusion(), myFirstPar);
    }
  }
  if (!Precision::IsInfinite(myCurve->LastParameter()))
  {
    gp_Pnt aP = myCurve->Value(myCurve->LastParameter());
    aP        = ProjectPnt(myPlane, myDirection, aP);
    if (myType == GeomAbs_Line)
    {
      myLastPar = ElCLib::Parameter(aLin, aP);
    }
    else if (myType == GeomAbs_Parabola)
    {
      myLastPar = ElCLib::Parameter(aParab, aP);
    }
    else if (myType == GeomAbs_Hyperbola)
    {
      myLastPar = ElCLib::Parameter(aHypr, aP);
    }
    else
    {
      GeomLib_Tool::Parameter(theProjCurve, aP, Precision::Confusion(), myLastPar);
    }
  }
  myResult = new GeomAdaptor_Curve(theProjCurve, myFirstPar, myLastPar);
}

bool ProjLib_ProjectOnPlane::BuildParabolaByApex(occ::handle<Geom_Curve>& theGeomParabolaPtr)
{

  double            aF       = myCurve->Parabola().Focal();
  GeomAbs_CurveType aCurType = myType;
  myType                     = GeomAbs_OtherCurve;

  occ::handle<Adaptor3d_Curve> aProjCrv = ShallowCopy();
  myType                                = aCurType;
  LProp3d_CLProps      aProps(aProjCrv, 2, Precision::Confusion());
  ProjLib_MaxCurvature aMaxCur(aProps);
  math_BrentMinimum    aSolver(Precision::PConfusion());
  aSolver.Perform(aMaxCur, -10. * aF, 0., 10. * aF);

  if (!aSolver.IsDone())
  {
    return false;
  }

  double aT;
  aT = aSolver.Location();
  aProps.SetParameter(aT);
  gp_Pnt aP0 = aProps.Value();
  gp_Vec aDY = aProps.D1();
  gp_Dir anYDir(aDY);
  gp_Dir anXDir;
  double aCurv = aProps.Curvature();
  if (Precision::IsInfinite(aCurv) || aCurv < Precision::Confusion())
  {
    return false;
  }
  aProps.Normal(anXDir);

  gp_Lin anXLine(aP0, anXDir);
  gp_Pnt aP1 = Value(aT + 10. * aF);

  double        anX   = ElCLib::LineParameter(anXLine.Position(), aP1);
  double        anY   = anXLine.Distance(aP1);
  double        aNewF = anY * anY / 4. / anX;
  gp_Dir        anN   = anXDir ^ anYDir;
  gp_Ax2        anA2(aP0, anN, anXDir);
  gce_MakeParab aMkParab(anA2, aNewF);
  if (!aMkParab.IsDone())
  {
    return false;
  }

  gp_Parab aProjParab = aMkParab.Value();

  myType             = GeomAbs_Parabola;
  theGeomParabolaPtr = new Geom_Parabola(aProjParab);

  return true;
}

bool ProjLib_ProjectOnPlane::BuildHyperbolaByApex(occ::handle<Geom_Curve>& theGeomHyperbolaPtr)
{

  GeomAbs_CurveType aCurType = myType;
  myType                     = GeomAbs_OtherCurve;

  occ::handle<Adaptor3d_Curve> aProjCrv = ShallowCopy();
  myType                                = aCurType;

  LProp3d_CLProps      aProps(aProjCrv, 2, Precision::Confusion());
  ProjLib_MaxCurvature aMaxCur(aProps);
  math_BrentMinimum    aSolver(Precision::PConfusion());
  aSolver.Perform(aMaxCur, -5., 0., 5.);

  if (aSolver.IsDone())
  {
    double aT;
    aT = aSolver.Location();
    aProps.SetParameter(aT);
    double aCurv = aProps.Curvature();
    if (Precision::IsInfinite(aCurv) || aCurv < Precision::Confusion())
    {
      return false;
    }
    else
    {
      gp_Hypr Hypr   = myCurve->Hyperbola();
      gp_Ax2  AxeRef = Hypr.Position();
      gp_Pnt  P      = ProjectPnt(myPlane, myDirection, AxeRef.Location());
      gp_Dir  Z      = myPlane.Direction();
      gp_Pnt  aP0    = aProps.Value();
      gp_Dir  anXDir = gce_MakeDir(P, aP0);
      gp_Dir  anYDir = gce_MakeDir(aProps.D1());

      double  aMajRad = P.Distance(aP0);
      gp_Pnt  aP1     = Value(aT + 1.);
      gp_Vec  aV(P, aP1);
      double  anX     = aV * anXDir;
      double  anY     = aV * anYDir;
      double  aMinRad = anY / std::sqrt(anX * anX / aMajRad / aMajRad - 1.);
      gp_Ax2  anA2(P, Z, anXDir);
      gp_Hypr anHypr(anA2, aMajRad, aMinRad);
      theGeomHyperbolaPtr = new Geom_Hyperbola(anHypr);
      myType              = GeomAbs_Hyperbola;
    }
  }
  else
  {
    return false;
  }
  return true;
}

void ProjLib_ProjectOnPlane::BuildByApprox(const double theLimitParameter)
{
  myType = GeomAbs_BSplineCurve;
  occ::handle<Geom_BSplineCurve> anApproxCurve;
  if (Precision::IsInfinite(myCurve->FirstParameter())
      || Precision::IsInfinite(myCurve->LastParameter()))
  {

    double                       f = std::max(-theLimitParameter, myCurve->FirstParameter());
    double                       l = std::min(theLimitParameter, myCurve->LastParameter());
    occ::handle<Adaptor3d_Curve> aTrimCurve = myCurve->Trim(f, l, Precision::Confusion());
    PerformApprox(aTrimCurve, myPlane, myDirection, anApproxCurve);
  }
  else
  {
    PerformApprox(myCurve, myPlane, myDirection, anApproxCurve);
  }
  myFirstPar = anApproxCurve->FirstParameter();
  myLastPar  = anApproxCurve->LastParameter();
  GeomAdaptor_Curve aGACurve(anApproxCurve);
  myResult = new GeomAdaptor_Curve(aGACurve);
}
