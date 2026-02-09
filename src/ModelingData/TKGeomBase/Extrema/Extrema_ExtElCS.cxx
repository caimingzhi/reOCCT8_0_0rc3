

#include <ElCLib.hpp>
#include <ElSLib.hpp>
#include <Extrema_ExtElC.hpp>
#include <Extrema_ExtElCS.hpp>
#include <Extrema_ExtPElC.hpp>
#include <Extrema_ExtPElS.hpp>
#include <Extrema_POnCurv.hpp>
#include <Extrema_POnSurf.hpp>
#include <gp_Circ.hpp>
#include <gp_Cone.hpp>
#include <gp_Cylinder.hpp>
#include <gp_Hypr.hpp>
#include <gp_Lin.hpp>
#include <gp_Pln.hpp>
#include <gp_Sphere.hpp>
#include <gp_Torus.hpp>
#include <gp_Vec.hpp>
#include <IntAna_IntConicQuad.hpp>
#include <IntAna_Quadric.hpp>
#include <IntAna_QuadQuadGeo.hpp>
#include <Precision.hpp>
#include <Standard_NotImplemented.hpp>
#include <Standard_OutOfRange.hpp>
#include <StdFail_NotDone.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_List.hpp>

Extrema_ExtElCS::Extrema_ExtElCS()
{
  myDone  = false;
  myIsPar = false;
  myNbExt = 0;
}

Extrema_ExtElCS::Extrema_ExtElCS(const gp_Lin& C, const gp_Pln& S)
{
  Perform(C, S);
}

void Extrema_ExtElCS::Perform(const gp_Lin& C, const gp_Pln& S)
{
  myDone  = true;
  myIsPar = false;
  myNbExt = 0;

  if (C.Direction().IsNormal(S.Axis().Direction(), Precision::Angular()))
  {
    mySqDist = new NCollection_HArray1<double>(1, 1);
    mySqDist->SetValue(1, S.SquareDistance(C));
    myIsPar = true;
    myNbExt = 1;
  }
}

Extrema_ExtElCS::Extrema_ExtElCS(const gp_Lin& C, const gp_Cylinder& S)
{
  Perform(C, S);
}

void Extrema_ExtElCS::Perform(const gp_Lin& C, const gp_Cylinder& S)
{
  myDone  = false;
  myNbExt = 0;
  myIsPar = false;

  gp_Ax3 Pos = S.Position();

  bool isParallel = false;

  double         radius = S.Radius();
  Extrema_ExtElC Extrem(gp_Lin(Pos.Axis()), C, Precision::Angular());
  if (Extrem.IsParallel())
  {
    isParallel = true;
  }
  else
  {
    int i;

    Extrema_POnCurv myPOnC1, myPOnC2;
    Extrem.Points(1, myPOnC1, myPOnC2);
    gp_Pnt PonAxis = myPOnC1.Value();
    gp_Pnt PC      = myPOnC2.Value();

    if (radius - PonAxis.Distance(PC) > Precision::PConfusion())
    {
      IntAna_Quadric      theQuadric(S);
      IntAna_IntConicQuad Inters(C, theQuadric);
      if (Inters.IsDone() && Inters.IsInQuadric())
      {
        isParallel = true;
      }
      else if (Inters.IsDone())
      {
        myNbExt = Inters.NbPoints();
        if (myNbExt > 0)
        {

          mySqDist = new NCollection_HArray1<double>(1, myNbExt + 2);
          myPoint1 = new NCollection_HArray1<Extrema_POnCurv>(1, myNbExt + 2);
          myPoint2 = new NCollection_HArray1<Extrema_POnSurf>(1, myNbExt + 2);
          double u, v, w;
          for (i = 1; i <= myNbExt; i++)
          {
            mySqDist->SetValue(i, 0.);
            gp_Pnt P_int = Inters.Point(i);
            w            = Inters.ParamOnConic(i);
            Extrema_POnCurv PonC(w, P_int);
            myPoint1->SetValue(i, PonC);
            ElSLib::CylinderParameters(Pos, radius, P_int, u, v);
            Extrema_POnSurf PonS(u, v, P_int);
            myPoint2->SetValue(i, PonS);
          }
        }
      }
    }
    else
    {

      Extrema_ExtPElS ExPS(PC, S, Precision::Confusion());
      if (ExPS.IsDone())
      {
        myNbExt  = ExPS.NbExt();
        mySqDist = new NCollection_HArray1<double>(1, myNbExt);
        myPoint1 = new NCollection_HArray1<Extrema_POnCurv>(1, myNbExt);
        myPoint2 = new NCollection_HArray1<Extrema_POnSurf>(1, myNbExt);

        for (i = 1; i <= myNbExt; i++)
        {
          myPoint1->SetValue(i, myPOnC2);
          myPoint2->SetValue(i, ExPS.Point(i));
          mySqDist->SetValue(i, (myPOnC2.Value()).SquareDistance(ExPS.Point(i).Value()));
        }
      }
    }

    myDone = true;
  }

  if (isParallel)
  {

    mySqDist         = new NCollection_HArray1<double>(1, 1);
    double    aDist  = Extrem.SquareDistance(1);
    const int aNbExt = Extrem.NbExt();
    for (int i = 2; i <= aNbExt; i++)
    {
      const double aD = Extrem.SquareDistance(i);
      if (aD < aDist)
      {
        aDist = aD;
      }
    }

    aDist = sqrt(aDist) - radius;
    mySqDist->SetValue(1, aDist * aDist);
    myDone  = true;
    myIsPar = true;
    myNbExt = 1;
  }
}

Extrema_ExtElCS::Extrema_ExtElCS(const gp_Lin& C, const gp_Cone& S)
{
  Perform(C, S);
}

void Extrema_ExtElCS::Perform(const gp_Lin&, const gp_Cone&)
{
  throw Standard_NotImplemented();
}

Extrema_ExtElCS::Extrema_ExtElCS(const gp_Lin& C, const gp_Sphere& S)
{
  Perform(C, S);
}

void Extrema_ExtElCS::Perform(const gp_Lin& C, const gp_Sphere& S)
{

  myDone        = false;
  myNbExt       = 0;
  myIsPar       = false;
  int aStartIdx = 0;

  gp_Pnt aCenter = S.Location();

  Extrema_ExtPElC Extrem(aCenter, C, Precision::Angular(), RealFirst(), RealLast());

  int i;
  if (Extrem.IsDone() && Extrem.NbExt() > 0)
  {
    Extrema_POnCurv myPOnC1 = Extrem.Point(1);
    if (myPOnC1.Value().Distance(aCenter) <= S.Radius())
    {
      IntAna_IntConicQuad aLinSphere(C, S);
      if (aLinSphere.IsDone())
      {
        myNbExt   = aLinSphere.NbPoints();
        aStartIdx = myNbExt;

        mySqDist = new NCollection_HArray1<double>(1, myNbExt + 2);
        myPoint1 = new NCollection_HArray1<Extrema_POnCurv>(1, myNbExt + 2);
        myPoint2 = new NCollection_HArray1<Extrema_POnSurf>(1, myNbExt + 2);

        for (i = 1; i <= myNbExt; i++)
        {
          Extrema_POnCurv aCPnt(aLinSphere.ParamOnConic(i), aLinSphere.Point(i));

          double u, v;
          ElSLib::Parameters(S, aLinSphere.Point(i), u, v);
          Extrema_POnSurf aSPnt(u, v, aLinSphere.Point(i));

          myPoint1->SetValue(i, aCPnt);
          myPoint2->SetValue(i, aSPnt);
          mySqDist->SetValue(i, (aCPnt.Value()).SquareDistance(aSPnt.Value()));
        }
      }
    }

    Extrema_ExtPElS ExPS(myPOnC1.Value(), S, Precision::Confusion());
    if (ExPS.IsDone())
    {
      if (aStartIdx == 0)
      {
        myNbExt  = ExPS.NbExt();
        mySqDist = new NCollection_HArray1<double>(1, myNbExt);
        myPoint1 = new NCollection_HArray1<Extrema_POnCurv>(1, myNbExt);
        myPoint2 = new NCollection_HArray1<Extrema_POnSurf>(1, myNbExt);
      }
      else
        myNbExt += ExPS.NbExt();

      for (i = aStartIdx + 1; i <= myNbExt; i++)
      {
        myPoint1->SetValue(i, myPOnC1);
        myPoint2->SetValue(i, ExPS.Point(i - aStartIdx));
        mySqDist->SetValue(i, (myPOnC1.Value()).SquareDistance(ExPS.Point(i - aStartIdx).Value()));
      }
    }
  }
  myDone = true;
}

Extrema_ExtElCS::Extrema_ExtElCS(const gp_Lin& C, const gp_Torus& S)
{
  Perform(C, S);
}

void Extrema_ExtElCS::Perform(const gp_Lin&, const gp_Torus&)
{
  throw Standard_NotImplemented();
}

Extrema_ExtElCS::Extrema_ExtElCS(const gp_Circ& C, const gp_Pln& S)
{
  Perform(C, S);
}

void Extrema_ExtElCS::Perform(const gp_Circ& C, const gp_Pln& S)
{
  myDone  = true;
  myIsPar = false;
  myNbExt = 0;

  gp_Ax2 Pos   = C.Position();
  gp_Dir NCirc = Pos.Direction();
  gp_Dir NPln  = S.Axis().Direction();

  bool isParallel = false;

  if (NCirc.IsParallel(NPln, Precision::Angular()))
  {
    isParallel = true;
  }
  else
  {

    gp_Dir ExtLine = NCirc ^ NPln;
    ExtLine        = ExtLine ^ NCirc;

    gp_Dir XDir = Pos.XDirection();
    double T[2];
    T[0] = XDir.AngleWithRef(ExtLine, NCirc);
    if (T[0] < 0.)
    {

      T[0] += M_PI;
    }
    T[1] = T[0] + M_PI;

    myNbExt = 2;

    IntAna_IntConicQuad anInter(C, S, Precision::Angular(), Precision::Confusion());

    if (anInter.IsDone() && anInter.IsInQuadric())
    {
      isParallel = true;
    }
    else if (anInter.IsDone())
    {
      if (anInter.NbPoints() > 1)
      {
        myNbExt += anInter.NbPoints();
      }
    }

    if (!isParallel)
    {
      myPoint1 = new NCollection_HArray1<Extrema_POnCurv>(1, myNbExt);
      mySqDist = new NCollection_HArray1<double>(1, myNbExt);
      myPoint2 = new NCollection_HArray1<Extrema_POnSurf>(1, myNbExt);

      int             i;
      gp_Pnt          PC, PP;
      double          U, V;
      Extrema_POnCurv POnC;
      Extrema_POnSurf POnS;
      for (i = 0; i < 2; ++i)
      {
        PC = ElCLib::CircleValue(T[i], C.Position(), C.Radius());
        POnC.SetValues(T[i], PC);
        myPoint1->SetValue(i + 1, POnC);
        ElSLib::PlaneParameters(S.Position(), PC, U, V);
        PP = ElSLib::PlaneValue(U, V, S.Position());
        POnS.SetParameters(U, V, PP);
        myPoint2->SetValue(i + 1, POnS);
        mySqDist->SetValue(i + 1, PC.SquareDistance(PP));
      }

      if (myNbExt > 2)
      {

        for (i = 1; i <= anInter.NbPoints(); ++i)
        {
          double t = anInter.ParamOnConic(i);
          PC       = ElCLib::CircleValue(t, C.Position(), C.Radius());
          POnC.SetValues(t, PC);
          myPoint1->SetValue(i + 2, POnC);
          ElSLib::PlaneParameters(S.Position(), PC, U, V);
          PP = ElSLib::PlaneValue(U, V, S.Position());
          POnS.SetParameters(U, V, PP);
          myPoint2->SetValue(i + 2, POnS);
          mySqDist->SetValue(i + 2, PC.SquareDistance(PP));
        }
      }
    }
  }

  if (isParallel)
  {
    mySqDist = new NCollection_HArray1<double>(1, 1);
    mySqDist->SetValue(1, S.SquareDistance(C.Location()));
    myIsPar = true;
    myNbExt = 1;
  }
}

Extrema_ExtElCS::Extrema_ExtElCS(const gp_Circ& C, const gp_Cylinder& S)
{
  Perform(C, S);
}

void Extrema_ExtElCS::Perform(const gp_Circ& C, const gp_Cylinder& S)
{
  myDone  = false;
  myIsPar = false;
  myNbExt = 0;

  gp_Lin anAxis(S.Axis());

  Extrema_ExtElC anExtC(anAxis, C, 0.);

  if (!anExtC.IsDone())
    return;

  bool isParallel = false;

  if (anExtC.IsParallel())
  {
    isParallel = true;
  }
  else
  {
    int              aNbExt = anExtC.NbExt();
    int              i;
    int              aCurI    = 1;
    constexpr double aTolConf = Precision::Confusion();
    double           aCylRad  = S.Radius();

    IntAna_Quadric      aCylQuad(S);
    IntAna_IntConicQuad aCircCylInter(C, aCylQuad);
    int                 aNbInter = 0;
    if (aCircCylInter.IsDone() && aCircCylInter.IsInQuadric())
    {
      isParallel = true;
    }
    else if (aCircCylInter.IsDone())
    {
      aNbInter = aCircCylInter.NbPoints();
    }

    if (!isParallel)
    {

      myNbExt  = 2 * aNbExt + aNbInter;
      mySqDist = new NCollection_HArray1<double>(1, myNbExt);
      myPoint1 = new NCollection_HArray1<Extrema_POnCurv>(1, myNbExt);
      myPoint2 = new NCollection_HArray1<Extrema_POnSurf>(1, myNbExt);

      for (i = 1; i <= aNbExt; i++)
      {
        Extrema_POnCurv aPOnAxis;
        Extrema_POnCurv aPOnCirc;
        double          aSqDist = anExtC.SquareDistance(i);
        double          aDist   = sqrt(aSqDist);

        anExtC.Points(i, aPOnAxis, aPOnCirc);

        if (aSqDist <= (aTolConf * aTolConf))
        {
          myNbExt -= 2;
          continue;
        }

        gp_Dir aDir(aPOnAxis.Value().XYZ().Subtracted(aPOnCirc.Value().XYZ()));
        double aShift[2] = {aDist + aCylRad, aDist - aCylRad};
        int    j;

        for (j = 0; j < 2; j++)
        {
          gp_Vec aVec(aDir);
          gp_Pnt aPntOnCyl;

          aVec.Multiply(aShift[j]);
          aPntOnCyl = aPOnCirc.Value().Translated(aVec);

          double aU;
          double aV;

          ElSLib::Parameters(S, aPntOnCyl, aU, aV);

          Extrema_POnSurf aPOnSurf(aU, aV, aPntOnCyl);

          myPoint1->SetValue(aCurI, aPOnCirc);
          myPoint2->SetValue(aCurI, aPOnSurf);
          mySqDist->SetValue(aCurI++, aShift[j] * aShift[j]);
        }
      }

      for (i = 1; i <= aNbInter; i++)
      {
        double aU;
        double aV;

        gp_Pnt aInterPnt = aCircCylInter.Point(i);

        aU = ElCLib::Parameter(C, aInterPnt);
        Extrema_POnCurv aPOnCirc(aU, aInterPnt);

        ElSLib::Parameters(S, aInterPnt, aU, aV);
        Extrema_POnSurf aPOnCyl(aU, aV, aInterPnt);
        myPoint1->SetValue(aCurI, aPOnCirc);
        myPoint2->SetValue(aCurI, aPOnCyl);
        mySqDist->SetValue(aCurI++, 0.0);
      }
    }
  }

  myDone = true;

  if (isParallel)
  {

    myIsPar      = true;
    myNbExt      = 1;
    mySqDist     = new NCollection_HArray1<double>(1, 1);
    double aDist = anExtC.SquareDistance(1);

    const int aNbExt = anExtC.NbExt();
    for (int i = 2; i <= aNbExt; i++)
    {
      const double aD = anExtC.SquareDistance(i);
      if (aD < aDist)
      {
        aDist = aD;
      }
    }

    aDist = sqrt(aDist) - S.Radius();
    mySqDist->SetValue(1, aDist * aDist);
  }
}

Extrema_ExtElCS::Extrema_ExtElCS(const gp_Circ& C, const gp_Cone& S)
{
  Perform(C, S);
}

void Extrema_ExtElCS::Perform(const gp_Circ&, const gp_Cone&)
{
  throw Standard_NotImplemented();
}

Extrema_ExtElCS::Extrema_ExtElCS(const gp_Circ& C, const gp_Sphere& S)
{
  Perform(C, S);
}

void Extrema_ExtElCS::Perform(const gp_Circ& C, const gp_Sphere& S)
{
  myDone  = false;
  myIsPar = false;
  myNbExt = 0;

  if (gp_Lin(C.Axis()).SquareDistance(S.Location()) < Precision::SquareConfusion())
  {

    myIsPar = true;
    myDone  = true;
    myNbExt = 1;

    double aSqDistLoc = C.Location().SquareDistance(S.Location());
    double aSqDist    = aSqDistLoc + C.Radius() * C.Radius();
    double aDist      = sqrt(aSqDist) - S.Radius();
    mySqDist          = new NCollection_HArray1<double>(1, 1);
    mySqDist->SetValue(1, aDist * aDist);
    return;
  }

  gp_Pln             CPln(C.Location(), C.Axis().Direction());
  IntAna_QuadQuadGeo anInter(CPln, S);
  if (!anInter.IsDone())

    return;

  if (anInter.TypeInter() != IntAna_Circle)
  {

    myNbExt = 1;
    myDone  = true;

    mySqDist = new NCollection_HArray1<double>(1, 1);
    myPoint1 = new NCollection_HArray1<Extrema_POnCurv>(1, 1);
    myPoint2 = new NCollection_HArray1<Extrema_POnSurf>(1, 1);

    const double aT = ElCLib::Parameter(C, S.Location());

    gp_Pnt aPOnC = ElCLib::Value(aT, C);

    double aU, aV;
    ElSLib::Parameters(S, aPOnC, aU, aV);

    gp_Pnt aPOnS = ElSLib::Value(aU, aV, S);

    myPoint1->SetValue(1, Extrema_POnCurv(aT, aPOnC));
    myPoint2->SetValue(1, Extrema_POnSurf(aU, aV, aPOnS));
    mySqDist->SetValue(1, aPOnC.SquareDistance(aPOnS));
    return;
  }

  gp_Circ aCInt = anInter.Circle(1);

  Extrema_ExtElC anExtC(C, aCInt);
  bool           isExtremaCircCircValid = anExtC.IsDone() && !anExtC.IsParallel()

                                && anExtC.NbExt() > 0;

  if (!isExtremaCircCircValid)

    return;

  myDone = true;

  double aNbExt = anExtC.NbExt();

  double aMinSqDist = ::RealLast();
  for (int i = 1; i <= aNbExt; ++i)
  {
    double aSqDist = anExtC.SquareDistance(i);
    if (aSqDist < aMinSqDist)
      aMinSqDist = aSqDist;
  }

  NCollection_List<int> aSols;
  for (int i = 1; i <= aNbExt; ++i)
  {
    double aDiff = anExtC.SquareDistance(i) - aMinSqDist;
    if (aDiff < Precision::SquareConfusion())
      aSols.Append(i);
  }

  myNbExt = aSols.Extent();

  mySqDist = new NCollection_HArray1<double>(1, myNbExt);
  myPoint1 = new NCollection_HArray1<Extrema_POnCurv>(1, myNbExt);
  myPoint2 = new NCollection_HArray1<Extrema_POnSurf>(1, myNbExt);

  NCollection_List<int>::Iterator it(aSols);
  for (int iSol = 1; it.More(); it.Next(), ++iSol)
  {
    Extrema_POnCurv P1, P2;
    anExtC.Points(it.Value(), P1, P2);

    double aU, aV;
    ElSLib::Parameters(S, P1.Value(), aU, aV);

    gp_Pnt aPOnS = ElSLib::Value(aU, aV, S);

    myPoint1->SetValue(iSol, P1);
    myPoint2->SetValue(iSol, Extrema_POnSurf(aU, aV, aPOnS));
    mySqDist->SetValue(iSol, P1.Value().SquareDistance(aPOnS));
  }
}

Extrema_ExtElCS::Extrema_ExtElCS(const gp_Circ& C, const gp_Torus& S)
{
  Perform(C, S);
}

void Extrema_ExtElCS::Perform(const gp_Circ&, const gp_Torus&)
{
  throw Standard_NotImplemented();
}

Extrema_ExtElCS::Extrema_ExtElCS(const gp_Hypr& C, const gp_Pln& S)
{
  Perform(C, S);
}

void Extrema_ExtElCS::Perform(const gp_Hypr& C, const gp_Pln& S)
{
  myDone  = true;
  myIsPar = false;
  myNbExt = 0;

  gp_Ax2 Pos   = C.Position();
  gp_Dir NHypr = Pos.Direction();
  gp_Dir NPln  = S.Axis().Direction();

  if (NHypr.IsParallel(NPln, Precision::Angular()))
  {

    mySqDist = new NCollection_HArray1<double>(1, 1);
    mySqDist->SetValue(1, S.SquareDistance(C.Location()));
    myIsPar = true;
    myNbExt = 1;
  }
  else
  {

    gp_Dir XDir = Pos.XDirection();
    gp_Dir YDir = Pos.YDirection();

    double A = C.MinorRadius() * (NPln.Dot(YDir));
    double B = C.MajorRadius() * (NPln.Dot(XDir));

    if (std::abs(B) > std::abs(A))
    {
      double          T  = -0.5 * std::log((A + B) / (B - A));
      gp_Pnt          Ph = ElCLib::HyperbolaValue(T, Pos, C.MajorRadius(), C.MinorRadius());
      Extrema_POnCurv PC(T, Ph);
      myPoint1 = new NCollection_HArray1<Extrema_POnCurv>(1, 1);
      myPoint1->SetValue(1, PC);

      mySqDist = new NCollection_HArray1<double>(1, 1);
      mySqDist->SetValue(1, S.SquareDistance(Ph));

      double U, V;
      ElSLib::PlaneParameters(S.Position(), Ph, U, V);
      gp_Pnt          Pp = ElSLib::PlaneValue(U, V, S.Position());
      Extrema_POnSurf PS(U, V, Pp);
      myPoint2 = new NCollection_HArray1<Extrema_POnSurf>(1, 1);
      myPoint2->SetValue(1, PS);

      myNbExt = 1;
    }
  }
}

bool Extrema_ExtElCS::IsDone() const
{
  return myDone;
}

int Extrema_ExtElCS::NbExt() const
{
  if (!IsDone())
    throw StdFail_NotDone();
  return myNbExt;
}

double Extrema_ExtElCS::SquareDistance(const int N) const
{
  if (N < 1 || N > NbExt())
  {
    throw Standard_OutOfRange();
  }

  return mySqDist->Value(N);
}

void Extrema_ExtElCS::Points(const int N, Extrema_POnCurv& P1, Extrema_POnSurf& P2) const
{
  if (N < 1 || N > NbExt())
  {
    throw Standard_OutOfRange();
  }

  P1 = myPoint1->Value(N);
  P2 = myPoint2->Value(N);
}

bool Extrema_ExtElCS::IsParallel() const
{
  if (!IsDone())
  {
    throw StdFail_NotDone();
  }
  return myIsPar;
}
