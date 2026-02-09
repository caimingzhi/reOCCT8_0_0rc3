#ifndef No_Exception
  #define No_Exception
#endif

#include <Bnd_Box.hpp>
#include <ElCLib.hpp>
#include <gp_Lin.hpp>
#include <HLRBRep_CurveTool.hpp>
#include <HLRBRep_EdgeData.hpp>
#include <HLRBRep_Intersector.hpp>
#include <HLRBRep_Surface.hpp>
#include <HLRBRep_SurfaceTool.hpp>
#include <HLRBRep_ThePolygonOfInterCSurf.hpp>
#include <HLRBRep_ThePolyhedronOfInterCSurf.hpp>
#include <IntCurveSurface_IntersectionPoint.hpp>
#include <IntCurveSurface_IntersectionSegment.hpp>
#include <IntImpParGen.hpp>
#include <IntRes2d_IntersectionPoint.hpp>
#include <IntRes2d_IntersectionSegment.hpp>
#include <IntRes2d_Position.hpp>
#include <IntRes2d_Transition.hpp>
#include <StdFail_UndefinedDerivative.hpp>

#ifdef PERF
static int NbIntersCS             = 0;
static int NbIntersCSVides        = 0;
static int NbIntersAuto           = 0;
static int NbIntersSimulate       = 0;
static int NbInters               = 0;
static int NbIntersVides          = 0;
static int NbInters1Segment       = 0;
static int NbInters1Point         = 0;
static int NbIntersNPoints        = 0;
static int NbIntersNSegments      = 0;
static int NbIntersPointEtSegment = 0;
#endif

HLRBRep_Intersector::HLRBRep_Intersector()
    : myTypePerform(0),
      mySurface(nullptr),
      myPolyhedron(nullptr)
{
#ifdef PERF
  if (NbInters)
  {
    printf("\n--------------------------------------");
    printf("\nNbIntersSimulate  : %6d", NbIntersSimulate);
    printf("\nNbIntersCrvSurf   : %6d", NbIntersCS);
    printf("\n      -> vide     : %6d", NbIntersCSVides);
    printf("\nNbAutoInters      : %6d\n", NbIntersAuto);
    printf("\nNbInters          : %6d", NbInters);
    printf("\n        Vides     : %6d", NbIntersVides);
    printf("\n        1 Segment : %6d", NbInters1Segment);
    printf("\n        1 Point   : %6d", NbInters1Point);
    printf("\n       >1 Point   : %6d", NbIntersNPoints);
    printf("\n       >1 Segment : %6d", NbIntersNSegments);
    printf("\n     >1 Pt et Seg : %6d", NbIntersPointEtSegment);
    printf("\n--------------------------------------\n");
  }
  NbIntersSimulate = NbIntersAuto = NbIntersCS = NbInters = NbIntersVides = NbInters1Segment =
    NbInters1Point = NbIntersNPoints = NbIntersNSegments = NbIntersPointEtSegment =
      NbIntersCSVides                                    = 0;
#endif

  const int aMinNbHLRSamples = 4;
  myIntersector.SetMinNbSamples(aMinNbHLRSamples);
}

void HLRBRep_Intersector::Perform(HLRBRep_EdgeData* theEdge1,
                                  const double      theDa1,
                                  const double      theDb1)
{
#ifdef PERF
  NbIntersAuto++;
#endif

  HLRBRep_Curve* myC1 = theEdge1->Curve();

  myTypePerform = 1;

  gp_Pnt2d pa, pb;
  double   a, b, d, tol;
  float    ta, tb;

  theEdge1->Status().Bounds(a, ta, b, tb);
  d = b - a;
  if (theDa1 != 0)
    a = a + d * theDa1;
  if (theDb1 != 0)
    b = b - d * theDb1;
  myC1->D0(a, pa);
  myC1->D0(b, pb);
  a = myC1->Parameter2d(a);
  b = myC1->Parameter2d(b);
  IntRes2d_Domain D1(pa, a, (double)ta, pb, b, (double)tb);

  tol = Precision::Confusion();

  myIntersector.Perform(myC1, D1, tol, tol);
}

void HLRBRep_Intersector::Perform(const int,
                                  HLRBRep_EdgeData* theEdge1,
                                  const double      theDa1,
                                  const double      theDb1,
                                  const int,
                                  HLRBRep_EdgeData* theEdge2,
                                  const double      theDa2,
                                  const double      theDb2,
                                  const bool        theEnBout)
{

  HLRBRep_Curve* myC1 = theEdge1->Curve();
  HLRBRep_Curve* myC2 = theEdge2->Curve();

  myTypePerform = 1;

  gp_Pnt2d pa1, pb1, pa2, pb2;
  gp_Vec2d va1, vb1, va2, vb2;
  double   a1, b1, a2, b2, d, dd, tol, tol1, tol2;
  float    ta, tb;

  tol1 = Precision::Confusion();
  tol2 = Precision::Confusion();

  if (tol1 > tol2)
    tol = tol1;
  else
    tol = tol2;

  bool   aPasBon;
  double aDecalagea1 = 100.0;
  double aDecalagea2 = 100.0;
  double aDecalageb1 = 100.0;
  double aDecalageb2 = 100.0;
  do
  {
    aPasBon = false;
    theEdge1->Status().Bounds(a1, ta, b1, tb);
    double mtol = tol;
    if (mtol < ta)
      mtol = ta;
    if (mtol < tb)
      mtol = tb;
    d = b1 - a1;

    double pdist = tol;
    if (pdist < 0.0000001)
      pdist = 0.0000001;

    if (theDa1 != 0)
    {

      myC1->D1(a1, pa1, va1);
      double qwe = va1.Magnitude();
      if (qwe > 1e-12)
      {
        dd = pdist * aDecalagea1 / qwe;
        if (dd < d * 0.4)
        {
          a1 += dd;
        }
        else
        {
          a1 += d * theDa1;
          aDecalagea1 = -1;
        }
      }
      else
      {
        a1 += d * theDa1;
        aDecalagea1 = -1;
      }
    }

    if (theDb1 != 0)
    {

      myC1->D1(b1, pb1, vb1);
      double qwe = vb1.Magnitude();
      if (qwe > 1e-12)
      {
        dd = pdist * aDecalageb1 / qwe;
        if (dd < d * 0.4)
        {
          b1 -= dd;
        }
        else
        {
          b1 -= d * theDb1;
          aDecalageb1 = -1;
        }
      }
      else
      {
        b1 -= d * theDb1;
        aDecalageb1 = -1;
      }
    }

    myC1->D0(a1, pa1);
    myC1->D0(b1, pb1);

    a1 = myC1->Parameter2d(a1);
    b1 = myC1->Parameter2d(b1);

    if (theEnBout)
    {
      ta = tb = -1.;
    }

    if (ta > tol)
      ta = (float)tol;
    if (tb > tol)
      tb = (float)tol;

    IntRes2d_Domain D1(pa1, a1, (double)ta, pb1, b1, (double)tb);

    theEdge2->Status().Bounds(a2, ta, b2, tb);
    mtol = tol;
    if (mtol < ta)
      mtol = ta;
    if (mtol < tb)
      mtol = tb;

    d = b2 - a2;

    if (theDa2 != 0)
    {

      myC2->D1(a2, pa2, va2);
      double qwe = va2.Magnitude();
      if (qwe > 1e-12)
      {
        dd = pdist * aDecalagea2 / qwe;
        if (dd < d * 0.4)
        {
          a2 += dd;
        }
        else
        {
          a2 += d * theDa2;
          aDecalagea2 = -1;
        }
      }
      else
      {
        a2 += d * theDa2;
        aDecalagea2 = -1;
      }
    }

    if (theDb2 != 0)
    {

      myC2->D1(b2, pb2, vb2);
      double qwe = vb2.Magnitude();
      if (qwe > 1e-12)
      {
        dd = pdist * aDecalageb2 / qwe;
        if (dd < d * 0.4)
        {
          b2 -= dd;
        }
        else
        {
          b2 -= d * theDb2;
          aDecalageb2 = -1;
        }
      }
      else
      {
        b2 -= d * theDb2;
        aDecalageb2 = -1;
      }
    }

    myC2->D0(a2, pa2);
    myC2->D0(b2, pb2);

    a2 = myC2->Parameter2d(a2);
    b2 = myC2->Parameter2d(b2);

    if (theEnBout)
    {
      ta = tb = -1.;
    }

    if (ta > tol)
      ta = (float)tol;
    if (tb > tol)
      tb = (float)tol;

    IntRes2d_Domain D2(pa2, a2, (double)ta, pb2, b2, (double)tb);

    if (theEnBout)
    {
      double a1a2 = (theDa1 || theDa2) ? pa1.Distance(pa2) : RealLast();
      double a1b2 = (theDa1 || theDb2) ? pa1.Distance(pb2) : RealLast();
      double b1a2 = (theDb1 || theDa2) ? pb1.Distance(pa2) : RealLast();
      double b1b2 = (theDb1 || theDb2) ? pb1.Distance(pb2) : RealLast();

      int    cote    = 1;
      double mindist = a1a2;
      if (mindist > a1b2)
      {
        mindist = a1b2;
        cote    = 2;
      }
      if (mindist > b1a2)
      {
        mindist = b1a2;
        cote    = 3;
      }
      if (mindist > b1b2)
      {
        mindist = b1b2;
        cote    = 4;
      }

      if (mindist < tol * 1000)
      {
        aPasBon = true;
        switch (cote)
        {
          case 1:
          {
            aDecalagea1 *= 2;
            aDecalagea2 *= 2;
            break;
          }
          case 2:
          {
            aDecalagea1 *= 2;
            aDecalageb2 *= 2;
            break;
          }
          case 3:
          {
            aDecalageb1 *= 2;
            aDecalagea2 *= 2;
            break;
          }
          default:
          {
            aDecalageb1 *= 2;
            aDecalageb2 *= 2;
            break;
          }
        }
        if (aDecalagea1 < 0.0 || aDecalagea2 < 0.0 || aDecalageb1 < 0.0 || aDecalageb2 <= 0.0)
        {
          aPasBon = false;
        }
      }
    }
    if (!aPasBon)
    {
      myIntersector.Perform(myC1, D1, myC2, D2, tol, tol);
    }
  } while (aPasBon);

#ifdef PERF
  NbInters++;
  if (myIntersector.NbPoints() == 1)
  {
    if (myIntersector.NbSegments() == 0)
    {
      NbInters1Point++;
    }
    else
    {
      NbIntersPointEtSegment++;
    }
  }
  else if (myIntersector.NbPoints() == 0)
  {
    if (myIntersector.NbSegments() == 0)
    {
      NbIntersVides++;
    }
    else if (myIntersector.NbSegments() == 1)
    {
      NbInters1Segment++;
    }
    else
    {
      NbIntersNSegments++;
    }
  }
  else
  {
    if (myIntersector.NbSegments() == 0)
    {
      NbIntersNPoints++;
    }
    else
    {
      NbIntersPointEtSegment++;
    }
  }
#endif
}

void HLRBRep_Intersector::SimulateOnePoint(HLRBRep_EdgeData* theEdge1,
                                           const double      theU,
                                           HLRBRep_EdgeData* theEdge2,
                                           const double      theV)
{
#ifdef PERF
  NbIntersSimulate++;
#endif
  HLRBRep_Curve* myC1 = theEdge1->Curve();
  HLRBRep_Curve* myC2 = theEdge2->Curve();

  double   u3 = myC1->Parameter3d(theU);
  double   v3 = myC2->Parameter3d(theV);
  gp_Pnt2d P13, P23;
  gp_Vec2d T13, T23;
  myC1->D1(u3, P13, T13);
  myC2->D1(v3, P23, T23);

  IntRes2d_Transition Tr1, Tr2;
  IntRes2d_Position   Pos1, Pos2;
  Pos1 = Pos2 = IntRes2d_Middle;

  IntImpParGen::DetermineTransition(Pos1, T13, Tr1, Pos2, T23, Tr2, 0.0);
  myTypePerform = 0;
  mySinglePoint.SetValues(P13, theU, theV, Tr1, Tr2, false);
}

void HLRBRep_Intersector::Load(HLRBRep_Surface* theSurface)
{
  mySurface = theSurface;
  if (myPolyhedron != nullptr)
  {
    delete myPolyhedron;
    myPolyhedron = nullptr;
  }
}

void HLRBRep_Intersector::Perform(const gp_Lin& L, const double P)
{
  myTypePerform                 = 2;
  const GeomAbs_SurfaceType typ = HLRBRep_SurfaceTool::GetType(mySurface);
  switch (typ)
  {
    case GeomAbs_Plane:
    case GeomAbs_Cylinder:
    case GeomAbs_Cone:
    case GeomAbs_Sphere:
    case GeomAbs_Torus:
      myCSIntersector.Perform(L, mySurface);
      break;
    default:
    {
      if (myPolyhedron == nullptr)
      {
        int    nbsu, nbsv;
        double u1, v1, u2, v2;
        u1           = HLRBRep_SurfaceTool::FirstUParameter(mySurface);
        v1           = HLRBRep_SurfaceTool::FirstVParameter(mySurface);
        u2           = HLRBRep_SurfaceTool::LastUParameter(mySurface);
        v2           = HLRBRep_SurfaceTool::LastVParameter(mySurface);
        nbsu         = HLRBRep_SurfaceTool::NbSamplesU(mySurface, u1, u2);
        nbsv         = HLRBRep_SurfaceTool::NbSamplesV(mySurface, v1, v2);
        myPolyhedron = new HLRBRep_ThePolyhedronOfInterCSurf(mySurface, nbsu, nbsv, u1, v1, u2, v2);
      }
      double x0, y0, z0, x1, y1, z1, pmin, pmax;
      myPolyhedron->Bounding().Get(x0, y0, z0, x1, y1, z1);

      double p;
      p    = ElCLib::Parameter(L, gp_Pnt(x0, y0, z0));
      pmin = pmax = p;
      p           = ElCLib::Parameter(L, gp_Pnt(x0, y0, z1));
      if (pmin > p)
        pmin = p;
      if (pmax < p)
        pmax = p;

      p = ElCLib::Parameter(L, gp_Pnt(x1, y0, z0));
      if (pmin > p)
        pmin = p;
      if (pmax < p)
        pmax = p;
      p = ElCLib::Parameter(L, gp_Pnt(x1, y0, z1));
      if (pmin > p)
        pmin = p;
      if (pmax < p)
        pmax = p;

      p = ElCLib::Parameter(L, gp_Pnt(x0, y1, z0));
      if (pmin > p)
        pmin = p;
      if (pmax < p)
        pmax = p;
      p = ElCLib::Parameter(L, gp_Pnt(x0, y1, z1));
      if (pmin > p)
        pmin = p;
      if (pmax < p)
        pmax = p;

      p = ElCLib::Parameter(L, gp_Pnt(x1, y1, z0));
      if (pmin > p)
        pmin = p;
      if (pmax < p)
        pmax = p;
      p = ElCLib::Parameter(L, gp_Pnt(x1, y1, z1));
      if (pmin > p)
        pmin = p;
      if (pmax < p)
        pmax = p;
      pmin -= 0.000001;
      pmax += 0.000001;

      if (pmin > P)
      {
        pmin = pmax + 1;
        pmax = pmax + 2;
      }
      else
      {
        if (pmax > P)
          pmax = P + 0.0000001;
      }
      HLRBRep_ThePolygonOfInterCSurf Polygon(L, pmin, pmax, 3);
      myCSIntersector.Perform(L,
                              Polygon,
                              mySurface,
                              *((HLRBRep_ThePolyhedronOfInterCSurf*)myPolyhedron));

      break;
    }
  }
#ifdef PERF
  NbIntersCS++;
  if (myCSIntersector.NbPoints() == 0)
  {
    NbIntersCSVides++;
  }
#endif
}

bool HLRBRep_Intersector::IsDone() const
{
  if (myTypePerform == 1)
    return myIntersector.IsDone();
  else if (myTypePerform == 2)
    return myCSIntersector.IsDone();
  else
    return (true);
}

int HLRBRep_Intersector::NbPoints() const
{
  if (myTypePerform == 43)
    return (0);

  if (myTypePerform == 1)
    return myIntersector.NbPoints();
  else if (myTypePerform == 2)
    return myCSIntersector.NbPoints();
  else
    return (1);
}

const IntRes2d_IntersectionPoint& HLRBRep_Intersector::Point(const int N) const
{
  if (myTypePerform == 0)
    return (mySinglePoint);
  else
    return myIntersector.Point(N);
}

const IntCurveSurface_IntersectionPoint& HLRBRep_Intersector::CSPoint(const int N) const
{
  return myCSIntersector.Point(N);
}

int HLRBRep_Intersector::NbSegments() const
{
  if (myTypePerform == 1)
    return myIntersector.NbSegments();
  else if (myTypePerform == 2)
    return myCSIntersector.NbSegments();
  else
    return (0);
}

const IntRes2d_IntersectionSegment& HLRBRep_Intersector::Segment(const int N) const
{
  return myIntersector.Segment(N);
}

const IntCurveSurface_IntersectionSegment& HLRBRep_Intersector::CSSegment(const int N) const
{
  return myCSIntersector.Segment(N);
}

void HLRBRep_Intersector::Destroy()
{
  if (myPolyhedron != nullptr)
    delete myPolyhedron;
}
