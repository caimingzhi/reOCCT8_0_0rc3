#include <BRep_Builder.hpp>
#include <BRep_Tool.hpp>
#include <BRepBuilderAPI_MakeEdge.hpp>
#include <BRepBuilderAPI_MakeFace.hpp>
#include <BRepBuilderAPI_MakeWire.hpp>
#include <BRepAdaptor_Curve.hpp>
#include <BRepAdaptor_Curve2d.hpp>
#include <BRepAlgo.hpp>
#include <BRepLib.hpp>
#include <BRepLib_MakeEdge.hpp>
#include <BRepLib_MakeWire.hpp>
#include <BRepTools_WireExplorer.hpp>
#include <ElCLib.hpp>
#include <Geom_Curve.hpp>
#include <Geom_TrimmedCurve.hpp>
#include <Geom2d_TrimmedCurve.hpp>
#include <Geom2dConvert_ApproxArcsSegments.hpp>
#include <GeomAbs_CurveType.hpp>
#include <GeomConvert.hpp>
#include <GeomConvert_CompCurveToBSplineCurve.hpp>
#include <GeomLProp.hpp>
#include <NCollection_Vector.hpp>
#include <gp_Pnt.hpp>
#include <Precision.hpp>
#include <ShapeFix_Shape.hpp>
#include <Geom_BSplineCurve.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <NCollection_Sequence.hpp>
#include <TopExp.hpp>
#include <TopExp_Explorer.hpp>
#include <TopLoc_Location.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDS_Vertex.hpp>
#include <TopoDS_Wire.hpp>

static const double MINIMAL_TOLERANCE = 0.0001;

namespace
{

  struct OrientedCurve
  {
    occ::handle<Geom2d_TrimmedCurve> Curve;
    bool                             IsReverse;

    inline gp_Pnt2d Point(const bool isEnd) const
    {
      if (isEnd == IsReverse)
        return Curve->StartPoint();
      return Curve->EndPoint();
    }
  };

} // namespace

TopoDS_Wire BRepAlgo::ConvertWire(const TopoDS_Wire& theWire,
                                  const double       theAngleTol,
                                  const TopoDS_Face& theFace)
{
  TopoDS_Wire                       aResult;
  double                            aMaxTol(0.);
  const occ::handle<Geom_Surface>   aSurf = BRep_Tool::Surface(theFace);
  NCollection_Vector<OrientedCurve> vecCurve;

  BRepTools_WireExplorer anExpE(theWire, theFace);

  for (; anExpE.More(); anExpE.Next())
  {
    const TopoDS_Edge&  anEdge = anExpE.Current();
    BRepAdaptor_Curve2d aCurve(anEdge, theFace);
    double              aTol = BRep_Tool::Tolerance(anEdge);
    if (aTol < MINIMAL_TOLERANCE)
      aTol = MINIMAL_TOLERANCE;
    if (aTol > aMaxTol)
      aMaxTol = aTol;
    Geom2dConvert_ApproxArcsSegments                       anAlgo(aCurve, aTol, theAngleTol);
    const NCollection_Sequence<occ::handle<Geom2d_Curve>>& aResultApprox = anAlgo.GetResult();

    if (anEdge.Orientation() == TopAbs_REVERSED)
    {
      for (int iCrv = aResultApprox.Length(); iCrv > 0; iCrv--)
      {
        const occ::handle<Geom2d_Curve>& aCrv = aResultApprox(iCrv);
        if (!aCrv.IsNull())
        {
          OrientedCurve& anOCurve = vecCurve.Append(OrientedCurve());
          anOCurve.Curve          = occ::down_cast<Geom2d_TrimmedCurve>(aCrv);
          anOCurve.IsReverse      = true;
        }
      }
    }
    else
    {
      for (int iCrv = 1; iCrv <= aResultApprox.Length(); iCrv++)
      {
        const occ::handle<Geom2d_Curve>& aCrv = aResultApprox(iCrv);
        if (!aCrv.IsNull())
        {
          OrientedCurve& anOCurve = vecCurve.Append(OrientedCurve());
          anOCurve.Curve          = occ::down_cast<Geom2d_TrimmedCurve>(aCrv);
          anOCurve.IsReverse      = false;
        }
      }
    }
  }

  if (vecCurve.Length() > 0)
  {

    BRep_Builder aVBuilder;
    gp_Pnt2d     aPnt[2] = {vecCurve(0).Point(false), vecCurve(vecCurve.Length() - 1).Point(true)};
    double       aDist   = aPnt[0].Distance(aPnt[1]);
    if (aDist > aMaxTol + Precision::Confusion())
      aDist = Precision::Confusion();
    else
    {
      aDist   = 0.5 * aDist + Precision::Confusion();
      aPnt[0] = 0.5 * (aPnt[0].XY() + aPnt[1].XY());
    }
    gp_Pnt aPnt3d;
    aSurf->D0(aPnt[0].X(), aPnt[0].Y(), aPnt3d);
    TopoDS_Vertex aFirstVertex;
    aVBuilder.MakeVertex(aFirstVertex, aPnt3d, aDist);

    BRepBuilderAPI_MakeWire aMkWire;
    TopoDS_Edge             anEdgeRes;
    TopoDS_Vertex           aVertex = aFirstVertex;
    for (int iCrv = 0; iCrv < vecCurve.Length(); iCrv++)
    {
      const OrientedCurve& anOCurve = vecCurve(iCrv);
      TopoDS_Vertex        aNextVertex;
      aPnt[0] = anOCurve.Point(true);
      if (iCrv == vecCurve.Length() - 1)
      {
        aPnt[1] = vecCurve(0).Point(false);
        aDist   = aPnt[0].Distance(aPnt[1]);
        if (aDist > aMaxTol + Precision::Confusion())
        {
          aSurf->D0(aPnt[0].X(), aPnt[0].Y(), aPnt3d);
          aVBuilder.MakeVertex(aNextVertex, aPnt3d, Precision::Confusion());
        }
        else
        {
          aNextVertex = aFirstVertex;
        }
      }
      else
      {
        aPnt[1] = vecCurve(iCrv + 1).Point(false);
        aDist   = 0.5 * (aPnt[0].Distance(aPnt[1])) + Precision::Confusion();
        aPnt[0] = 0.5 * (aPnt[0].XY() + aPnt[1].XY());
        aSurf->D0(aPnt[0].X(), aPnt[0].Y(), aPnt3d);
        aVBuilder.MakeVertex(aNextVertex, aPnt3d, aDist);
      }
      const double aParam[2] = {anOCurve.Curve->FirstParameter(), anOCurve.Curve->LastParameter()};
      if (anOCurve.IsReverse)
      {
        BRepBuilderAPI_MakeEdge aMkEdge(anOCurve.Curve,
                                        aSurf,
                                        aNextVertex,
                                        aVertex,
                                        aParam[0],
                                        aParam[1]);
        anEdgeRes = aMkEdge.Edge();
        anEdgeRes.Orientation(TopAbs_REVERSED);
      }
      else
      {
        BRepBuilderAPI_MakeEdge aMkEdge(anOCurve.Curve,
                                        aSurf,
                                        aVertex,
                                        aNextVertex,
                                        aParam[0],
                                        aParam[1]);
        anEdgeRes = aMkEdge.Edge();
      }
      aVertex = aNextVertex;
      aMkWire.Add(anEdgeRes);
    }

    if (aMkWire.IsDone())
      aResult = aMkWire.Wire();
  }
  return aResult;
}

TopoDS_Face BRepAlgo::ConvertFace(const TopoDS_Face& theFace, const double theAngleTolerance)
{
  TopoDS_Face                     aResult;
  const occ::handle<Geom_Surface> aSurf = BRep_Tool::Surface(theFace);
  BRepBuilderAPI_MakeFace         aMkFace(aSurf, Precision::Confusion());

  TopExp_Explorer anExp(theFace, TopAbs_WIRE);
  for (; anExp.More(); anExp.Next())
  {
    const TopoDS_Wire& aWire    = TopoDS::Wire(anExp.Current());
    const TopoDS_Wire  aNewWire = ConvertWire(aWire, theAngleTolerance, theFace);
    aMkFace.Add(aNewWire);
  }
  if (aMkFace.IsDone())
  {
    aResult = aMkFace.Face();
  }
  return aResult;
}

TopoDS_Wire BRepAlgo::ConcatenateWire(const TopoDS_Wire&  W,
                                      const GeomAbs_Shape Option,
                                      const double        TolAngular)
{

  int                    nb_curve, index;
  BRepTools_WireExplorer WExp(W);
  TopoDS_Edge            edge;
  TopLoc_Location        L;
  double                 First = 0., Last = 0., First0 = 0., toler = 0., tolleft, tolright;
  TopoDS_Vertex          Vfirst, Vlast;
  gp_Pnt                 Pfirst, Plast;

  BRepLib_MakeWire MakeResult;
  double           closed_tolerance = 0.0;
  bool             closed_flag      = false;

  nb_curve = 0;

  while (WExp.More())
  {
    nb_curve++;
    WExp.Next();
  }

  if (nb_curve > 1)
  {
    NCollection_Array1<occ::handle<Geom_BSplineCurve>> tab(0, nb_curve - 1);
    NCollection_Array1<double>                         tabtolvertex(0, nb_curve - 2);

    WExp.Init(W);

    for (index = 0; index < nb_curve; index++)
    {
      edge                                    = WExp.Current();
      const occ::handle<Geom_Curve>& aCurve   = BRep_Tool::Curve(edge, L, First, Last);
      occ::handle<Geom_TrimmedCurve> aTrCurve = new Geom_TrimmedCurve(aCurve, First, Last);
      tab(index)                              = GeomConvert::CurveToBSplineCurve(aTrCurve);
      tab(index)->Transform(L.Transformation());
      GeomConvert::C0BSplineToC1BSplineCurve(tab(index), Precision::Confusion());

      if (index >= 1)
      {
        if (edge.Orientation() == TopAbs_REVERSED)
          tab(index)->Reverse();
        tolleft                 = BRep_Tool::Tolerance(TopExp::LastVertex(edge));
        tolright                = BRep_Tool::Tolerance(TopExp::FirstVertex(edge));
        tabtolvertex(index - 1) = std::max(tolleft, tolright);
      }

      if (index == 0)
      {
        First0 = First;
        if (edge.Orientation() == TopAbs_REVERSED)
        {
          Vfirst = TopExp::LastVertex(edge);
          tab(index)->Reverse();
        }
        else
          Vfirst = TopExp::FirstVertex(edge);
      }

      if (index == nb_curve - 1)
      {
        if (edge.Orientation() == TopAbs_REVERSED)
          Vlast = TopExp::FirstVertex(edge);
        else
          Vlast = TopExp::LastVertex(edge);
      }
      WExp.Next();
    }

    if (BRep_Tool::Tolerance(Vfirst) > BRep_Tool::Tolerance(Vlast))
      toler = BRep_Tool::Tolerance(Vfirst);
    else
      toler = BRep_Tool::Tolerance(Vlast);

    Pfirst = BRep_Tool::Pnt(Vfirst);
    Plast  = BRep_Tool::Pnt(Vlast);

    if ((Pfirst.Distance(Plast) <= toler)
        && (GeomLProp::
              Continuity(tab(nb_curve - 1), tab(0), Last, First0, true, true, toler, TolAngular)
            >= GeomAbs_G1))
    {

      closed_tolerance = toler;

      closed_flag = true;
    }
    occ::handle<NCollection_HArray1<occ::handle<Geom_BSplineCurve>>> concatcurve;
    occ::handle<NCollection_HArray1<int>>                            ArrayOfIndices;
    if (Option == GeomAbs_G1)
      GeomConvert::ConcatG1(tab, tabtolvertex, concatcurve, closed_flag, closed_tolerance);
    else
      GeomConvert::ConcatC1(tab,
                            tabtolvertex,
                            ArrayOfIndices,
                            concatcurve,
                            closed_flag,
                            closed_tolerance);

    for (index = 0; index <= (concatcurve->Length() - 1); index++)
    {
      BRepLib_MakeEdge EdgeBuilder(concatcurve->Value(index));
      edge = EdgeBuilder.Edge();
      MakeResult.Add(edge);
    }
  }
  else
  {

    WExp.Init(W);

    edge                              = WExp.Current();
    const occ::handle<Geom_Curve>& aC = BRep_Tool::Curve(edge, L, First, Last);
    occ::handle<Geom_BSplineCurve> aBS =
      GeomConvert::CurveToBSplineCurve(new Geom_TrimmedCurve(aC, First, Last));
    aBS->Transform(L.Transformation());
    GeomConvert::C0BSplineToC1BSplineCurve(aBS, Precision::Confusion());
    if (edge.Orientation() == TopAbs_REVERSED)
    {
      aBS->Reverse();
    }

    BRepLib_MakeEdge EdgeBuilder(aBS);
    edge = EdgeBuilder.Edge();
    MakeResult.Add(edge);
  }
  return MakeResult.Wire();
}

TopoDS_Edge BRepAlgo::ConcatenateWireC0(const TopoDS_Wire& aWire)
{
  double LinTol = Precision::Confusion();
  double AngTol = Precision::Angular();

  TopoDS_Edge ResEdge;

  TopoDS_Wire theWire = aWire;
  BRepLib::BuildCurves3d(theWire);
  occ::handle<ShapeFix_Shape> Fixer = new ShapeFix_Shape(theWire);
  Fixer->SetPrecision(LinTol);
  Fixer->SetMaxTolerance(LinTol);
  Fixer->Perform();
  theWire = TopoDS::Wire(Fixer->Shape());

  NCollection_Sequence<occ::handle<Geom_Curve>> CurveSeq;
  NCollection_Sequence<double>                  FparSeq;
  NCollection_Sequence<double>                  LparSeq;
  NCollection_Sequence<double>                  TolSeq;
  NCollection_Sequence<bool>                    IsFwdSeq;
  GeomAbs_CurveType                             CurType = GeomAbs_OtherCurve;
  TopoDS_Vertex                                 FirstVertex, LastVertex;

  BRepTools_WireExplorer wexp(theWire);

  for (; wexp.More(); wexp.Next())
  {
    const TopoDS_Edge&      anEdge = wexp.Current();
    double                  fpar, lpar;
    occ::handle<Geom_Curve> aCurve = BRep_Tool::Curve(anEdge, fpar, lpar);

    if (aCurve.IsNull())
      continue;

    GeomAdaptor_Curve              aGACurve(aCurve);
    GeomAbs_CurveType              aType       = aGACurve.GetType();
    const occ::handle<Geom_Curve>& aBasisCurve = aGACurve.Curve();
    bool                           isFwd       = (wexp.Orientation() != TopAbs_REVERSED);

    if (aBasisCurve->IsPeriodic())
    {
      ElCLib::AdjustPeriodic(aBasisCurve->FirstParameter(),
                             aBasisCurve->LastParameter(),
                             Precision::PConfusion(),
                             fpar,
                             lpar);
    }

    if (CurveSeq.IsEmpty())
    {
      CurveSeq.Append(aCurve);
      FparSeq.Append(fpar);
      LparSeq.Append(lpar);
      IsFwdSeq.Append(isFwd);
      CurType     = aType;
      FirstVertex = wexp.CurrentVertex();
    }
    else
    {
      bool              isSameCurve = false;
      double            NewFpar = RealFirst(), NewLpar = RealLast();
      GeomAdaptor_Curve GAprevcurve(CurveSeq.Last());

      if (aCurve == CurveSeq.Last())
      {
        NewFpar     = fpar;
        NewLpar     = lpar;
        isSameCurve = true;
      }
      else if (aType == CurType)
      {
        switch (aType)
        {
          case GeomAbs_Line:
          {
            gp_Lin aLine    = aGACurve.Line();
            gp_Lin PrevLine = GAprevcurve.Line();

            if (aLine.Contains(PrevLine.Location(), LinTol)
                && aLine.Direction().IsParallel(PrevLine.Direction(), AngTol))
            {
              gp_Pnt P1 = ElCLib::Value(fpar, aLine);
              gp_Pnt P2 = ElCLib::Value(lpar, aLine);

              NewFpar     = ElCLib::Parameter(PrevLine, P1);
              NewLpar     = ElCLib::Parameter(PrevLine, P2);
              isSameCurve = true;
            }
            break;
          }
          case GeomAbs_Circle:
          {
            gp_Circ aCircle    = aGACurve.Circle();
            gp_Circ PrevCircle = GAprevcurve.Circle();

            if (aCircle.Location().Distance(PrevCircle.Location()) <= LinTol
                && std::abs(aCircle.Radius() - PrevCircle.Radius()) <= LinTol
                && aCircle.Axis().IsParallel(PrevCircle.Axis(), AngTol))
            {
              gp_Pnt P1 = ElCLib::Value(fpar, aCircle);
              gp_Pnt P2 = ElCLib::Value(lpar, aCircle);

              NewFpar     = ElCLib::Parameter(PrevCircle, P1);
              NewLpar     = ElCLib::Parameter(PrevCircle, P2);
              isSameCurve = true;
            }
            break;
          }
          case GeomAbs_Ellipse:
          {
            gp_Elips anEllipse   = aGACurve.Ellipse();
            gp_Elips PrevEllipse = GAprevcurve.Ellipse();

            if (anEllipse.Focus1().Distance(PrevEllipse.Focus1()) <= LinTol
                && anEllipse.Focus2().Distance(PrevEllipse.Focus2()) <= LinTol
                && std::abs(anEllipse.MajorRadius() - PrevEllipse.MajorRadius()) <= LinTol
                && std::abs(anEllipse.MinorRadius() - PrevEllipse.MinorRadius()) <= LinTol
                && anEllipse.Axis().IsParallel(PrevEllipse.Axis(), AngTol))
            {
              gp_Pnt P1 = ElCLib::Value(fpar, anEllipse);
              gp_Pnt P2 = ElCLib::Value(lpar, anEllipse);

              NewFpar     = ElCLib::Parameter(PrevEllipse, P1);
              NewLpar     = ElCLib::Parameter(PrevEllipse, P2);
              isSameCurve = true;
            }
            break;
          }
          case GeomAbs_Hyperbola:
          {
            gp_Hypr aHypr    = aGACurve.Hyperbola();
            gp_Hypr PrevHypr = GAprevcurve.Hyperbola();

            if (aHypr.Focus1().Distance(PrevHypr.Focus1()) <= LinTol
                && aHypr.Focus2().Distance(PrevHypr.Focus2()) <= LinTol
                && std::abs(aHypr.MajorRadius() - PrevHypr.MajorRadius()) <= LinTol
                && std::abs(aHypr.MinorRadius() - PrevHypr.MinorRadius()) <= LinTol
                && aHypr.Axis().IsParallel(PrevHypr.Axis(), AngTol))
            {
              gp_Pnt P1 = ElCLib::Value(fpar, aHypr);
              gp_Pnt P2 = ElCLib::Value(lpar, aHypr);

              NewFpar     = ElCLib::Parameter(PrevHypr, P1);
              NewLpar     = ElCLib::Parameter(PrevHypr, P2);
              isSameCurve = true;
            }
            break;
          }
          case GeomAbs_Parabola:
          {
            gp_Parab aParab    = aGACurve.Parabola();
            gp_Parab PrevParab = GAprevcurve.Parabola();

            if (aParab.Location().Distance(PrevParab.Location()) <= LinTol
                && aParab.Focus().Distance(PrevParab.Focus()) <= LinTol
                && std::abs(aParab.Focal() - PrevParab.Focal()) <= LinTol
                && aParab.Axis().IsParallel(PrevParab.Axis(), AngTol))
            {
              gp_Pnt P1 = ElCLib::Value(fpar, aParab);
              gp_Pnt P2 = ElCLib::Value(lpar, aParab);

              NewFpar     = ElCLib::Parameter(PrevParab, P1);
              NewLpar     = ElCLib::Parameter(PrevParab, P2);
              isSameCurve = true;
            }
            break;
          }
          default:
            break;
        }
      }

      if (isSameCurve)
      {
        const bool isSameDir = (isFwd == IsFwdSeq.Last());

        if (aBasisCurve->IsPeriodic())
        {

          const double aPeriod = aBasisCurve->Period();

          if (isSameDir)
          {

            while (NewFpar > NewLpar)
            {
              NewFpar -= aPeriod;
            }
          }
          else
          {

            while (NewLpar > NewFpar)
            {
              NewLpar -= aPeriod;
            }

            const double aTmpPar = NewLpar;

            NewLpar = NewFpar;
            NewFpar = aTmpPar;
          }

          if (IsFwdSeq.Last())
          {

            ElCLib::AdjustPeriodic(LparSeq.Last(),
                                   LparSeq.Last() + aPeriod,
                                   Precision::PConfusion(),
                                   NewFpar,
                                   NewLpar);
          }
          else
          {

            ElCLib::AdjustPeriodic(FparSeq.Last() - aPeriod,
                                   FparSeq.Last(),
                                   Precision::PConfusion(),
                                   NewFpar,
                                   NewLpar);
          }
        }
        else if (!isSameDir)
        {

          const double aTmpPar = NewLpar;

          NewLpar = NewFpar;
          NewFpar = aTmpPar;
        }

        if (IsFwdSeq.Last())
        {

          LparSeq(LparSeq.Length()) = NewLpar;
        }
        else
        {

          FparSeq(FparSeq.Length()) = NewFpar;
        }
      }
      else
      {

        CurveSeq.Append(aCurve);
        FparSeq.Append(fpar);
        LparSeq.Append(lpar);
        IsFwdSeq.Append(isFwd);
        TolSeq.Append(BRep_Tool::Tolerance(wexp.CurrentVertex()));
        CurType = aType;
      }
    }
  }

  LastVertex = wexp.CurrentVertex();
  TolSeq.Append(BRep_Tool::Tolerance(LastVertex));

  bool isReverse = false;

  if (!IsFwdSeq.IsEmpty())
  {
    isReverse = !IsFwdSeq(1);
  }

  TopoDS_Vertex FirstVtx_final, LastVtx_final;
  if (isReverse)
  {
    FirstVtx_final = LastVertex;
    LastVtx_final  = FirstVertex;
  }
  else
  {
    FirstVtx_final = FirstVertex;
    LastVtx_final  = LastVertex;
  }
  FirstVtx_final.Orientation(TopAbs_FORWARD);
  LastVtx_final.Orientation(TopAbs_REVERSED);

  if (CurveSeq.IsEmpty())
    return ResEdge;

  int                                                nb_curve = CurveSeq.Length();
  NCollection_Array1<occ::handle<Geom_BSplineCurve>> tab(0, nb_curve - 1);
  NCollection_Array1<double>                         tabtolvertex(0, nb_curve - 1);

  int i;

  if (nb_curve > 1)
  {
    for (i = 1; i <= nb_curve; i++)
    {
      if (CurveSeq(i)->IsInstance(STANDARD_TYPE(Geom_TrimmedCurve)))
        CurveSeq(i) = (*((occ::handle<Geom_TrimmedCurve>*)&(CurveSeq(i))))->BasisCurve();

      occ::handle<Geom_TrimmedCurve> aTrCurve =
        new Geom_TrimmedCurve(CurveSeq(i), FparSeq(i), LparSeq(i));
      tab(i - 1) = GeomConvert::CurveToBSplineCurve(aTrCurve);
      GeomConvert::C0BSplineToC1BSplineCurve(tab(i - 1), Precision::Confusion());

      if (!IsFwdSeq(i))
      {
        tab(i - 1)->Reverse();
      }

      if (i > 1)
        tabtolvertex(i - 2) = TolSeq(i - 1) * 5.;
    }
    tabtolvertex(nb_curve - 1) = TolSeq(TolSeq.Length()) * 5.;

    bool   closed_flag      = false;
    double closed_tolerance = 0.;
    if (FirstVertex.IsSame(LastVertex)
        && GeomLProp::Continuity(tab(0),
                                 tab(nb_curve - 1),
                                 tab(0)->FirstParameter(),
                                 tab(nb_curve - 1)->LastParameter(),
                                 false,
                                 false,
                                 LinTol,
                                 AngTol)
             >= GeomAbs_G1)
    {
      closed_flag      = true;
      closed_tolerance = BRep_Tool::Tolerance(FirstVertex);
    }

    occ::handle<NCollection_HArray1<occ::handle<Geom_BSplineCurve>>> concatcurve;
    occ::handle<NCollection_HArray1<int>>                            ArrayOfIndices;
    GeomConvert::ConcatC1(tab,
                          tabtolvertex,
                          ArrayOfIndices,
                          concatcurve,
                          closed_flag,
                          closed_tolerance);

    if (concatcurve->Length() > 1)
    {
      double MaxTolVer = LinTol;
      for (i = 1; i <= TolSeq.Length(); i++)
        if (TolSeq(i) > MaxTolVer)
          MaxTolVer = TolSeq(i);
      MaxTolVer *= 5.;

      GeomConvert_CompCurveToBSplineCurve Concat(concatcurve->Value(concatcurve->Lower()));

      for (i = concatcurve->Lower() + 1; i <= concatcurve->Upper(); i++)
        Concat.Add(concatcurve->Value(i), MaxTolVer, true);

      concatcurve->SetValue(concatcurve->Lower(), Concat.BSplineCurve());
    }

    if (isReverse)
    {
      concatcurve->ChangeValue(concatcurve->Lower())->Reverse();
    }
    ResEdge = BRepLib_MakeEdge(concatcurve->Value(concatcurve->Lower()),
                               FirstVtx_final,
                               LastVtx_final,
                               concatcurve->Value(concatcurve->Lower())->FirstParameter(),
                               concatcurve->Value(concatcurve->Lower())->LastParameter());
  }
  else
  {
    if (CurveSeq(1)->IsInstance(STANDARD_TYPE(Geom_TrimmedCurve)))
      CurveSeq(1) = (*((occ::handle<Geom_TrimmedCurve>*)&(CurveSeq(1))))->BasisCurve();

    occ::handle<Geom_Curve> aCopyCurve = occ::down_cast<Geom_Curve>(CurveSeq(1)->Copy());

    ResEdge = BRepLib_MakeEdge(aCopyCurve, FirstVtx_final, LastVtx_final, FparSeq(1), LparSeq(1));
  }

  if (isReverse)
    ResEdge.Reverse();

  return ResEdge;
}
