

#include <ShapeFix_EdgeProjAux.hpp>

#include <Adaptor3d_CurveOnSurface.hpp>
#include <BRep_Tool.hpp>
#include <ElCLib.hpp>
#include <Extrema_ExtPC.hpp>
#include <Geom2d_BSplineCurve.hpp>
#include <Geom2d_Curve.hpp>
#include <Geom2d_Line.hpp>
#include <Geom2dAdaptor_Curve.hpp>
#include <Geom_Curve.hpp>
#include <Geom_Surface.hpp>
#include <gp_Pnt.hpp>
#include <Precision.hpp>
#include <ShapeAnalysis.hpp>
#include <ShapeAnalysis_Curve.hpp>
#include <ShapeAnalysis_Edge.hpp>
#include <ShapeAnalysis_Surface.hpp>
#include <Standard_ErrorHandler.hpp>
#include <Standard_Failure.hpp>
#include <Standard_Type.hpp>
#include <TopExp.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Vertex.hpp>
#include <Adaptor3d_Curve.hpp>
#include <BSplCLib.hpp>

IMPLEMENT_STANDARD_RTTIEXT(ShapeFix_EdgeProjAux, Standard_Transient)

ShapeFix_EdgeProjAux::ShapeFix_EdgeProjAux()
    : myFirstParam(0.0),
      myLastParam(0.0),
      myFirstDone(false),
      myLastDone(false)
{
}

ShapeFix_EdgeProjAux::ShapeFix_EdgeProjAux(const TopoDS_Face& F, const TopoDS_Edge& E)
{
  Init(F, E);
}

void ShapeFix_EdgeProjAux::Init(const TopoDS_Face& F, const TopoDS_Edge& E)
{
  myFace       = F;
  myEdge       = E;
  myFirstParam = myLastParam = 0.;
  myFirstDone = myLastDone = false;
}

void ShapeFix_EdgeProjAux::Compute(const double preci)
{
  myFirstDone = myLastDone = false;

  myFirstParam = 0.;
  myLastParam  = 0.;
  Init2d(preci);
  if (IsFirstDone() && IsLastDone())
  {
    double U1 = FirstParam();
    double U2 = LastParam();
    if (U1 >= U2)
    {
#ifdef OCCT_DEBUG
      std::cout << "Parametres inverses ... " << std::endl;
#endif
      double tmp = U1;
      U1         = U2;
      U2         = tmp;
    }
    myFirstParam = U1;
    myFirstDone  = true;
    myLastParam  = U2;
    myLastDone   = true;
  }
}

bool ShapeFix_EdgeProjAux::IsFirstDone() const
{
  return myFirstDone;
}

bool ShapeFix_EdgeProjAux::IsLastDone() const
{
  return myLastDone;
}

double ShapeFix_EdgeProjAux::FirstParam() const
{
  return myFirstParam;
}

double ShapeFix_EdgeProjAux::LastParam() const
{
  return myLastParam;
}

bool ShapeFix_EdgeProjAux::IsIso(const occ::handle<Geom2d_Curve>&)
{

  return false;
}

static bool FindParameterWithExt(const gp_Pnt&                   Pt1,
                                 const Adaptor3d_CurveOnSurface& COnS,
                                 const double                    Uinf,
                                 const double                    Usup,
                                 const double                    preci,
                                 double&                         w1)
{
  try
  {
    OCC_CATCH_SIGNALS
    Extrema_ExtPC myExtPC(Pt1, COnS, Uinf, Usup, preci);

    if (myExtPC.IsDone())
    {
      int NbExt1 = myExtPC.NbExt();
      for (int i = 1; i <= NbExt1; i++)
      {
        if (myExtPC.IsMin(i))
        {

          w1 = myExtPC.Point(i).Parameter();
        }
      }
      return true;
    }
    else
      return false;
  }
  catch (Standard_Failure const& anException)
  {
#ifdef OCCT_DEBUG

    std::cout << "Warning: ShapeFix_EdgeProjAux, FindParameterWithExt(): Exception: ";
    anException.Print(std::cout);
    std::cout << std::endl;
#endif
    (void)anException;
    return false;
  }
}

void ShapeFix_EdgeProjAux::Init2d(const double preci)
{
  double cl = 0., cf = 0.;

  myFirstDone = myLastDone             = false;
  occ::handle<Geom_Surface> theSurface = BRep_Tool::Surface(myFace);
  occ::handle<Geom2d_Curve> theCurve2d = BRep_Tool::CurveOnSurface(myEdge, myFace, cf, cl);
  if (theCurve2d.IsNull())
    return;
  myFirstParam = 0.;
  myLastParam  = 0.;
  TopoDS_Vertex V1, V2;
  TopExp::Vertices(myEdge, V1, V2);
  gp_Pnt Pt1, Pt2;

  ShapeAnalysis_Edge      sae;
  double                  a, b;
  occ::handle<Geom_Curve> C3d;
  if (sae.Curve3d(myEdge, C3d, a, b, false))
  {
    Pt1 = C3d->Value(a);
    Pt2 = C3d->Value(b);
  }
  else
  {
    Pt1 = BRep_Tool::Pnt(V1);
    Pt2 = BRep_Tool::Pnt(V2);
  }

  if (V1.IsSame(V2))
  {
    occ::handle<ShapeAnalysis_Surface> stsu = new ShapeAnalysis_Surface(theSurface);
    gp_Pnt2d                           aPt1, aPt2;
    double                             firstpar, lastpar;
    if (stsu->DegeneratedValues(Pt1, preci, aPt1, aPt2, firstpar, lastpar))
    {

      if (theCurve2d->IsKind(STANDARD_TYPE(Geom2d_Line)))
      {
        if (aPt1.IsEqual(theCurve2d->Value(firstpar), preci)
            && aPt2.IsEqual(theCurve2d->Value(lastpar), preci))
        {
          myFirstParam = firstpar;
          myLastParam  = lastpar;
          myFirstDone = myLastDone = true;
          return;
        }
      }
#ifdef OCCT_DEBUG
      else
        std::cout << "Other type of deg curve" << std::endl;
#endif
    }
  }

  bool                             parU = false, parV = false;
  GeomAdaptor_Surface              SA     = GeomAdaptor_Surface(theSurface);
  occ::handle<GeomAdaptor_Surface> myHSur = new GeomAdaptor_Surface(SA);

  cf = theCurve2d->FirstParameter();
  cl = theCurve2d->LastParameter();

  if (Precision::IsInfinite(cf) || Precision::IsInfinite(cl))
  {
    if (theCurve2d->IsKind(STANDARD_TYPE(Geom2d_Line)))
    {
      double uf, ul, vf, vl;
      theSurface->Bounds(uf, ul, vf, vl);

      if (SA.GetType() == GeomAbs_SurfaceOfExtrusion)
      {
        if (SA.BasisCurve()->GetType() == GeomAbs_Hyperbola)
        {
          uf = std::max(uf, -23.);
          ul = std::min(ul, 23.);
        }
      }
      if (SA.GetType() == GeomAbs_SurfaceOfRevolution)
      {
        if (SA.BasisCurve()->GetType() == GeomAbs_Hyperbola)
        {
          vf = std::max(vf, -23.);
          vl = std::min(vl, 23.);
        }
      }
      if (!Precision::IsInfinite(uf) && !Precision::IsInfinite(ul) && !Precision::IsInfinite(vf)
          && !Precision::IsInfinite(vl))
      {
        double                   cfi, cli;
        occ::handle<Geom2d_Line> lin = occ::down_cast<Geom2d_Line>(theCurve2d);
        gp_Pnt2d                 pnt = lin->Location();
        gp_Dir2d                 dir = lin->Direction();
        if (dir.Y() == 0)
        {
          parU = true;
          cfi  = (uf - pnt.X()) / dir.X();
          cli  = (ul - pnt.X()) / dir.X();
        }
        else if (dir.X() == 0)
        {
          parV = true;
          cfi  = (vf - pnt.Y()) / dir.Y();
          cli  = (vl - pnt.Y()) / dir.Y();
        }
        else
        {
          double xfi, xli, yfi, yli;
          xfi = (uf - pnt.X()) / dir.X();
          xli = (ul - pnt.X()) / dir.X();
          yfi = (vf - pnt.Y()) / dir.Y();
          yli = (vl - pnt.Y()) / dir.Y();
          if (dir.X() * dir.Y() > 0)
          {
            cfi = (std::abs(xli - xfi) < std::abs(xli - yfi) ? xfi : yfi);
            cli = (std::abs(xfi - xli) < std::abs(xfi - yli) ? xli : yli);
          }
          else
          {
            cfi = (std::abs(xli - xfi) < std::abs(xli - yli) ? xfi : yli);
            cli = (std::abs(yli - xli) < std::abs(yli - yfi) ? xli : yfi);
          }
        }
        if (cfi < cli)
        {
          cf = cfi;
          cl = cli;
        }
        else
        {
          cf = cli;
          cl = cfi;
        }
      }
      else if (!Precision::IsInfinite(uf) && !Precision::IsInfinite(ul))
      {
        occ::handle<Geom2d_Line> lin = occ::down_cast<Geom2d_Line>(theCurve2d);
        gp_Dir2d                 dir = lin->Direction();
        if (dir.X() != 0)
        {
          if (dir.Y() == 0)
            parU = true;
          gp_Pnt2d pnt = lin->Location();
          double   cfi = (uf - pnt.X()) / dir.X();
          double   cli = (ul - pnt.X()) / dir.X();
          if (cfi < cli)
          {
            cf = cfi;
            cl = cli;
          }
          else
          {
            cf = cli;
            cl = cfi;
          }
        }
        else
        {
          cf = -10000;
          cl = 10000;
        }
      }
      else
      {
        cf = -10000;
        cl = 10000;

#ifdef OCCT_DEBUG
        std::cout << "Infinite Surface" << std::endl;
#endif
      }
    }
    else
    {

      cf = -10000;
      cl = 10000;
      if (theCurve2d->IsKind(STANDARD_TYPE(Geom2d_BSplineCurve)))
      {

        occ::handle<Geom2d_BSplineCurve> aBspl =
          occ::down_cast<Geom2d_BSplineCurve>(theCurve2d->Copy());
        NCollection_Array1<double> aNewKnots(1, aBspl->NbKnots());
        aBspl->Knots(aNewKnots);
        BSplCLib::Reparametrize(cf, cl, aNewKnots);
        aBspl->SetKnots(aNewKnots);
        theCurve2d = aBspl;
      }

#ifdef OCCT_DEBUG
      std::cout << "Some infinite curve" << std::endl;
#endif
    }
  }

  Geom2dAdaptor_Curve              CA     = Geom2dAdaptor_Curve(theCurve2d, cf, cl);
  occ::handle<Geom2dAdaptor_Curve> myHCur = new Geom2dAdaptor_Curve(CA);

  Adaptor3d_CurveOnSurface COnS = Adaptor3d_CurveOnSurface(myHCur, myHSur);

  double Uinf = COnS.FirstParameter();
  double Usup = COnS.LastParameter();

  double              w1 = 0., w2 = 0.;
  ShapeAnalysis_Curve sac;
  gp_Pnt              pnt;
  double              dist = sac.Project(COnS, Pt1, preci, pnt, w1, false);

  if (Precision::IsInfinite(dist))
    return;

  myFirstDone  = true;
  myFirstParam = w1;

  dist = sac.Project(COnS, Pt2, preci, pnt, w2, false);

  if (Precision::IsInfinite(dist))
    return;

  myLastDone  = true;
  myLastParam = w2;

  if (fabs(w1 - w2) < Precision::PConfusion())
  {
    if (!theSurface->IsUPeriodic() && !theSurface->IsVPeriodic())
      return;
  }

  if (myFirstParam == Uinf && myLastParam == Usup)
    return;
  if (myFirstParam == Usup && myLastParam == Uinf)
  {
    myFirstParam = theCurve2d->ReversedParameter(Usup);
    myLastParam  = theCurve2d->ReversedParameter(Uinf);
    theCurve2d->Reverse();
#ifdef OCCT_DEBUG
    std::cout << "Warning: ShapeFix_EdgeProjAux: pcurve reversed" << std::endl;
#endif
    return;
  }

  if (COnS.Value(Uinf).Distance(COnS.Value(Usup)) < Precision::Confusion())
  {

    if (std::abs(myFirstParam - Uinf) < ::Precision::PConfusion()
        && std::abs(myLastParam - Uinf) < ::Precision::PConfusion())
      myLastParam = w2 = Usup;

    else if (std::abs(myFirstParam - Usup) < ::Precision::PConfusion()
             && std::abs(myLastParam - Usup) < ::Precision::PConfusion())
      myFirstParam = w1 = Uinf;
  }

  if (parU || parV)
  {
    double uf, ul, vf, vl;
    theSurface->Bounds(uf, ul, vf, vl);
    double period = (parU ? ul - uf : vl - vf);
    w1 += ShapeAnalysis::AdjustToPeriod(w1, 0, period);
    myFirstParam = w1;
    w2 += ShapeAnalysis::AdjustToPeriod(w2, 0, period);
    myLastParam = w2;
    occ::handle<Geom_Curve> C3d1;
    if (!sae.Curve3d(myEdge, C3d1, cf, cl, false))
    {
      UpdateParam2d(theCurve2d);
      return;
    }
    gp_Pnt mid = C3d1->Value((cf + cl) / 2);
    double wmid;
    sac.Project(COnS, mid, preci, pnt, wmid, false);
    wmid += ShapeAnalysis::AdjustToPeriod(wmid, 0, period);
    if (w1 >= w2)
    {
      if (w2 > wmid)
        myFirstParam -= period;
      else if (w1 > wmid)
        UpdateParam2d(theCurve2d);
      else
      {
        myLastParam += period;
#ifdef OCCT_DEBUG
        std::cout << " Added" << std::endl;
#endif
      }
    }
    else
    {
      if (w1 > wmid)
      {
        myLastParam -= period;
        UpdateParam2d(theCurve2d);
#ifdef OCCT_DEBUG
        std::cout << " Added & Inverted" << std::endl;
#endif
      }
      else if (w2 < wmid)
      {
        myFirstParam += period;
        UpdateParam2d(theCurve2d);
      }
    }
  }
  UpdateParam2d(theCurve2d);
  return;
}

void ShapeFix_EdgeProjAux::Init3d(const double preci)
{
  double cl, cf;

  occ::handle<Geom_Surface> theSurface = BRep_Tool::Surface(myFace);
  occ::handle<Geom2d_Curve> theCurve2d = BRep_Tool::CurveOnSurface(myEdge, myFace, cf, cl);
  if (theCurve2d.IsNull())
    return;
  TopoDS_Vertex V1, V2;

  V1         = TopExp::FirstVertex(myEdge);
  V2         = TopExp::LastVertex(myEdge);
  gp_Pnt Pt1 = BRep_Tool::Pnt(V1);
  gp_Pnt Pt2 = BRep_Tool::Pnt(V2);

  GeomAdaptor_Surface              SA     = GeomAdaptor_Surface(theSurface);
  occ::handle<GeomAdaptor_Surface> myHSur = new GeomAdaptor_Surface(SA);

  Geom2dAdaptor_Curve              CA     = Geom2dAdaptor_Curve(theCurve2d);
  occ::handle<Geom2dAdaptor_Curve> myHCur = new Geom2dAdaptor_Curve(CA);

  Adaptor3d_CurveOnSurface COnS = Adaptor3d_CurveOnSurface(myHCur, myHSur);

  double Uinf = theCurve2d->FirstParameter();
  double Usup = theCurve2d->LastParameter();

  if (theCurve2d->IsKind(STANDARD_TYPE(Geom2d_BoundedCurve)))
  {

    gp_Pnt Pdeb = COnS.Value(Uinf);
    gp_Pnt Pfin = COnS.Value(Usup);

    if (Pdeb.IsEqual(Pt1, preci) && Pfin.IsEqual(Pt2, preci))
    {
      myFirstParam = Uinf;
      myLastParam  = Usup;
      myFirstDone = myLastDone = true;
      return;
    }
  }

  double w1 = COnS.FirstParameter();
  double w2 = COnS.LastParameter();

  if ((!Precision::IsInfinite(w1) && !Precision::IsInfinite(w2)
       && theCurve2d->Continuity() != GeomAbs_C0)
      || IsIso(theCurve2d))
  {

    if (FindParameterWithExt(Pt1, COnS, Uinf, Usup, preci, w1)
        && FindParameterWithExt(Pt2, COnS, Uinf, Usup, preci, w2))
    {
      myFirstParam = w1;
      myLastParam  = w2;
      UpdateParam2d(theCurve2d);
      myFirstDone = myLastDone = true;
      return;
    }
  }
  myFirstDone = myLastDone = true;
}

void ShapeFix_EdgeProjAux::UpdateParam2d(const occ::handle<Geom2d_Curve>& theCurve2d)
{
  if (myFirstParam < myLastParam)
    return;

  double cf = theCurve2d->FirstParameter();
  double cl = theCurve2d->LastParameter();

  constexpr double preci2d = Precision::PConfusion();

  if (ShapeAnalysis_Curve::IsPeriodic(theCurve2d))
  {
    ElCLib::AdjustPeriodic(cf, cl, preci2d, myFirstParam, myLastParam);
  }
  else if (theCurve2d->IsClosed())
  {

    if (std::abs(myFirstParam - cl) <= preci2d)
      myFirstParam = cf;
    else if (std::abs(myLastParam - cf) <= preci2d)
      myLastParam = cl;
    else
    {
#ifdef OCCT_DEBUG
      std::cout << "Error : curve 2d range crossing non periodic curve origin";
      std::cout << std::endl;
#endif

      return;
    }
  }

  else if (theCurve2d->IsKind(STANDARD_TYPE(Geom2d_BSplineCurve)))
  {
    occ::handle<Geom2d_BSplineCurve> aBSpline2d = occ::down_cast<Geom2d_BSplineCurve>(theCurve2d);
    if (aBSpline2d->StartPoint().Distance(aBSpline2d->EndPoint()) <= preci2d)
    {
      if (std::abs(myFirstParam - cl) <= preci2d)
        myFirstParam = cf;
      else if (std::abs(myLastParam - cf) <= preci2d)
        myLastParam = cl;
    }
  }
  else
  {
#ifdef OCCT_DEBUG
    std::cout << "Warning : non increasing parameters for 2d curve." << std::endl;
    std::cout << "          update parameter 2d uncertain." << std::endl;
#endif
    double tmp1 = myFirstParam, tmp2 = myLastParam;
    myFirstParam = theCurve2d->ReversedParameter(tmp1);
    myLastParam  = theCurve2d->ReversedParameter(tmp2);
    theCurve2d->Reverse();
  }
}
