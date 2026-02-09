

#include <BRep_Builder.hpp>
#include <BRep_GCurve.hpp>
#include <BRep_TEdge.hpp>
#include <BRep_Tool.hpp>
#include <BRepLib.hpp>
#include <Geom2d_BezierCurve.hpp>
#include <Geom2d_BSplineCurve.hpp>
#include <Geom2d_Curve.hpp>
#include <Geom2d_Line.hpp>
#include <Geom2d_OffsetCurve.hpp>
#include <Geom2d_TrimmedCurve.hpp>
#include <Geom_Curve.hpp>
#include <Geom_Plane.hpp>
#include <Geom_Surface.hpp>
#include <GeomLib.hpp>
#include <Precision.hpp>
#include <ShapeAnalysis_Curve.hpp>
#include <ShapeAnalysis_Edge.hpp>
#include <ShapeAnalysis_Surface.hpp>
#include <ShapeBuild_Edge.hpp>
#include <ShapeConstruct_ProjectCurveOnSurface.hpp>
#include <ShapeExtend.hpp>
#include <ShapeFix_Edge.hpp>
#include <ShapeFix_ShapeTolerance.hpp>
#include <Standard_ErrorHandler.hpp>
#include <Standard_Failure.hpp>
#include <Standard_Type.hpp>
#include <TopLoc_Location.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Vertex.hpp>
#include <ShapeBuild_ReShape.hpp>

IMPLEMENT_STANDARD_RTTIEXT(ShapeFix_Edge, Standard_Transient)

ShapeFix_Edge::ShapeFix_Edge()
{
  myStatus    = ShapeExtend::EncodeStatus(ShapeExtend_OK);
  myProjector = new ShapeConstruct_ProjectCurveOnSurface;
}

occ::handle<ShapeConstruct_ProjectCurveOnSurface> ShapeFix_Edge::Projector()
{
  return myProjector;
}

bool ShapeFix_Edge::FixRemovePCurve(const TopoDS_Edge& edge, const TopoDS_Face& face)
{
  TopLoc_Location                  L;
  const occ::handle<Geom_Surface>& S = BRep_Tool::Surface(face, L);
  return FixRemovePCurve(edge, S, L);
}

bool ShapeFix_Edge::FixRemovePCurve(const TopoDS_Edge&               edge,
                                    const occ::handle<Geom_Surface>& surface,
                                    const TopLoc_Location&           location)
{
  myStatus = ShapeExtend::EncodeStatus(ShapeExtend_OK);
  ShapeAnalysis_Edge EA;
  bool               result = EA.CheckVerticesWithPCurve(edge, surface, location);
  if (result)
    ShapeBuild_Edge().RemovePCurve(edge, surface, location);
  return result;
}

bool ShapeFix_Edge::FixRemoveCurve3d(const TopoDS_Edge& edge)
{
  myStatus = ShapeExtend::EncodeStatus(ShapeExtend_OK);
  ShapeAnalysis_Edge EA;
  bool               result = EA.CheckVerticesWithCurve3d(edge);
  if (result)
    ShapeBuild_Edge().RemoveCurve3d(edge);
  return result;
}

bool ShapeFix_Edge::FixAddPCurve(const TopoDS_Edge& edge,
                                 const TopoDS_Face& face,
                                 const bool         isSeam,
                                 const double       prec)
{
  TopLoc_Location                  L;
  const occ::handle<Geom_Surface>& S = BRep_Tool::Surface(face, L);
  return FixAddPCurve(edge, S, L, isSeam, prec);
}

bool ShapeFix_Edge::FixAddPCurve(const TopoDS_Edge&               edge,
                                 const occ::handle<Geom_Surface>& surface,
                                 const TopLoc_Location&           location,
                                 const bool                       isSeam,
                                 const double                     prec)
{
  occ::handle<Geom_Surface> aTransSurf = surface;
  if (!location.IsIdentity())
  {
    gp_Trsf aTrsf(location);
    aTransSurf = occ::down_cast<Geom_Surface>(surface->Transformed(aTrsf));
  }
  occ::handle<ShapeAnalysis_Surface> sas = new ShapeAnalysis_Surface(aTransSurf);
  return FixAddPCurve(edge, surface, location, isSeam, sas, prec);
}

bool ShapeFix_Edge::FixAddPCurve(const TopoDS_Edge&                        edge,
                                 const TopoDS_Face&                        face,
                                 const bool                                isSeam,
                                 const occ::handle<ShapeAnalysis_Surface>& surfana,
                                 const double                              prec)
{
  TopLoc_Location                  L;
  const occ::handle<Geom_Surface>& S = BRep_Tool::Surface(face, L);
  return FixAddPCurve(edge, S, L, isSeam, surfana, prec);
}

static occ::handle<Geom2d_Curve> TranslatePCurve(const occ::handle<Geom_Surface>& aSurf,
                                                 occ::handle<Geom2d_Curve>&       aC2d,
                                                 const double&                    aTol)
{
  double uf, ul, vf, vl;
  aSurf->Bounds(uf, ul, vf, vl);

  occ::handle<Geom2d_Line> theL2d = occ::down_cast<Geom2d_Line>(aC2d);
  if (!theL2d.IsNull())
  {
    gp_Pnt2d theLoc = theL2d->Location();
    gp_Dir2d theDir = theL2d->Direction();

    gp_Pnt2d                 newLoc;
    occ::handle<Geom2d_Line> theNewL2d = theL2d;

    if (std::abs(theDir.X()) <= aTol && std::abs(theDir.Y()) >= aTol)
    {
      if (std::abs(theLoc.X() - uf) < std::abs(theLoc.X() - ul))
        newLoc.SetCoord(theLoc.X() + (ul - uf), theLoc.Y());
      else
        newLoc.SetCoord(theLoc.X() - (ul - uf), theLoc.Y());
      theNewL2d = new Geom2d_Line(newLoc, theDir);
    }

    if (std::abs(theDir.X()) >= aTol && std::abs(theDir.Y()) <= aTol)
    {
      if (std::abs(theLoc.Y() - vf) < std::abs(theLoc.Y() - vl))
        newLoc.SetCoord(theLoc.X(), theLoc.Y() + (vl - vf));
      else
        newLoc.SetCoord(theLoc.X(), theLoc.Y() - (vl - vf));
      theNewL2d = new Geom2d_Line(newLoc, theDir);
    }

#ifdef OCCT_DEBUG
    std::cout << "TranslatePCurve not performed" << std::endl;
#endif
    return theNewL2d;
  }
  else
  {

    occ::handle<Geom2d_BSplineCurve> aBC = occ::down_cast<Geom2d_BSplineCurve>(aC2d);
    if (aBC.IsNull())
    {
#ifdef OCCT_DEBUG
      std::cout << "Untreated curve type in TranslatePCurve" << std::endl;
#endif
      return aC2d;
    }
    occ::handle<Geom2d_BSplineCurve> newC       = occ::down_cast<Geom2d_BSplineCurve>(aBC->Copy());
    gp_Pnt2d                         FirstPoint = aBC->StartPoint();
    gp_Pnt2d                         LastPoint  = aBC->EndPoint();
    gp_Vec2d                         theVector(FirstPoint, LastPoint);
    gp_Pnt2d                         p00(uf, vf), p01(uf, vl), p10(ul, vf);
    gp_Vec2d                         VectIsoUF(p00, p01);
    gp_Vec2d                         VectIsoVF(p00, p10);

    gp_Trsf2d T;
    if (theVector.IsParallel(VectIsoUF, aTol))
    {
      if (std::abs(FirstPoint.X() - uf) < std::abs(FirstPoint.X() - ul))
        T.SetTranslation(p00, p10);
      else
        T.SetTranslation(p10, p00);
      newC->Transform(T);
      return newC;
    }

    else if (theVector.IsParallel(VectIsoVF, aTol))
    {
      if (std::abs(FirstPoint.Y() - vf) < std::abs(FirstPoint.Y() - vl))
        T.SetTranslation(p00, p01);
      else
        T.SetTranslation(p01, p00);
      newC->Transform(T);
      return newC;
    }
  }

  return aC2d;
}

static void TempSameRange(const TopoDS_Edge& AnEdge, const double Tolerance)
{
  NCollection_List<occ::handle<BRep_CurveRepresentation>>::Iterator an_Iterator(
    (*((occ::handle<BRep_TEdge>*)&AnEdge.TShape()))->ChangeCurves());

  occ::handle<Geom2d_Curve> Curve2dPtr, NewCurve2dPtr;
  occ::handle<Geom2d_Curve> Curve2dPtr2, NewCurve2dPtr2;
  TopLoc_Location           LocalLoc;

  bool                     first_time_in = true, has_curve, has_closed_curve;
  occ::handle<BRep_GCurve> geometric_representation_ptr;
  double                   first, current_first, last, current_last;

  const occ::handle<Geom_Curve> C = BRep_Tool::Curve(AnEdge, LocalLoc, current_first, current_last);
  if (!C.IsNull())
    first_time_in = false;

  while (an_Iterator.More())
  {
    geometric_representation_ptr = occ::down_cast<BRep_GCurve>(an_Iterator.Value());
    if (!geometric_representation_ptr.IsNull())
    {
      has_closed_curve = has_curve = false;
      first                        = geometric_representation_ptr->First();
      last                         = geometric_representation_ptr->Last();
      if (geometric_representation_ptr->IsCurveOnSurface())
      {
        Curve2dPtr = geometric_representation_ptr->PCurve();
        has_curve  = true;
      }
      if (geometric_representation_ptr->IsCurveOnClosedSurface())
      {
        Curve2dPtr2      = geometric_representation_ptr->PCurve2();
        has_closed_curve = true;
      }
      if (has_curve || has_closed_curve)
      {
        if (first_time_in)
        {
          current_first = first;
          current_last  = last;
          first_time_in = false;
        }

        if (std::abs(first - current_first) > Precision::PConfusion()
            || std::abs(last - current_last) > Precision::PConfusion())
        {
          double oldFirst = 0., oldLast = 0.;
          if (has_curve)
          {

            oldFirst = geometric_representation_ptr->First();
            oldLast  = geometric_representation_ptr->Last();

            if (ShapeAnalysis_Curve::IsPeriodic(Curve2dPtr))
            {
              occ::handle<Geom2d_TrimmedCurve> tc =
                new Geom2d_TrimmedCurve(Curve2dPtr, oldFirst, oldLast);
              double shift = tc->FirstParameter() - oldFirst;
              oldFirst += shift;
              oldLast += shift;
            }

            double oldFirstCurve1 = oldFirst, oldLastCurve1 = oldLast;
            if (Curve2dPtr->IsKind(STANDARD_TYPE(Geom2d_BezierCurve)))
            {

              constexpr double preci = Precision::PConfusion();
              if (std::abs(oldFirst) > preci || std::abs(oldLast - 1) > preci)
              {
                occ::handle<Geom2d_BezierCurve> bezier =
                  occ::down_cast<Geom2d_BezierCurve>(Curve2dPtr->Copy());
                bezier->Segment(oldFirst, oldLast);
                Curve2dPtr = bezier;
              }
              oldFirstCurve1 = 0;
              oldLastCurve1  = 1;
            }

            GeomLib::SameRange(Tolerance,
                               Curve2dPtr,
                               oldFirstCurve1,
                               oldLastCurve1,
                               current_first,
                               current_last,
                               NewCurve2dPtr);
            geometric_representation_ptr->PCurve(NewCurve2dPtr);
          }
          if (has_closed_curve)
          {

            double oldFirstCurve2 = oldFirst, oldLastCurve2 = oldLast;

            if (Curve2dPtr2->IsKind(STANDARD_TYPE(Geom2d_BezierCurve)))
            {

              constexpr double preci = Precision::PConfusion();
              if (std::abs(oldFirst) > preci || std::abs(oldLast - 1) > preci)
              {
                occ::handle<Geom2d_BezierCurve> bezier =
                  occ::down_cast<Geom2d_BezierCurve>(Curve2dPtr2->Copy());
                bezier->Segment(oldFirst, oldLast);
                Curve2dPtr2 = bezier;
              }
              oldFirstCurve2 = 0;
              oldLastCurve2  = 1;
            }

            GeomLib::SameRange(Tolerance,
                               Curve2dPtr2,
                               oldFirstCurve2,
                               oldLastCurve2,
                               current_first,
                               current_last,
                               NewCurve2dPtr2);
            geometric_representation_ptr->PCurve2(NewCurve2dPtr2);
          }
        }
      }
    }
    an_Iterator.Next();
  }
  BRep_Builder B;
  B.Range(TopoDS::Edge(AnEdge), current_first, current_last);
  B.SameRange(AnEdge, true);
}

bool ShapeFix_Edge::FixAddPCurve(const TopoDS_Edge&                        edge,
                                 const occ::handle<Geom_Surface>&          surf,
                                 const TopLoc_Location&                    location,
                                 const bool                                isSeam,
                                 const occ::handle<ShapeAnalysis_Surface>& sas,
                                 const double                              prec)
{
  ShapeAnalysis_Edge sae;
  myStatus = ShapeExtend::EncodeStatus(ShapeExtend_OK);
  if ((!isSeam && sae.HasPCurve(edge, surf, location))
      || (isSeam && sae.IsSeam(edge, surf, location)))
    return false;

  if (surf->IsKind(STANDARD_TYPE(Geom_Plane)))
    return false;

  try
  {
    OCC_CATCH_SIGNALS
    double First, Last;

    BRep_Builder B;

    double                  preci = (prec > 0. ? prec : BRep_Tool::Tolerance(edge));
    occ::handle<Geom_Curve> c3d   = BRep_Tool::Curve(edge, First, Last);

    if (c3d.IsNull())
    {
      myStatus |= ShapeExtend::EncodeStatus(ShapeExtend_FAIL1);
      return false;
    }

    occ::handle<Geom2d_Curve> c2d;
    double                    a1, b1;
    if (!sae.HasPCurve(edge, surf, location))
    {
      double        TolFirst = -1, TolLast = -1;
      TopoDS_Vertex V1, V2;
      TopExp::Vertices(edge, V1, V2);
      if (!V1.IsNull())
        TolFirst = BRep_Tool::Tolerance(V1);
      if (!V2.IsNull())
        TolLast = BRep_Tool::Tolerance(V2);

      myProjector->Init(sas, preci);
      myProjector->Perform(c3d, First, Last, c2d, TolFirst, TolLast);

      if (myProjector->Status(ShapeExtend_DONE4))
        myStatus |= ShapeExtend::EncodeStatus(ShapeExtend_DONE2);
      a1 = First;
      b1 = Last;
    }
    else
    {
      sae.PCurve(edge, surf, location, c2d, a1, b1, false);
    }

    if (isSeam)
    {

      occ::handle<Geom2d_Curve> c2d2 = occ::down_cast<Geom2d_Curve>(c2d->Copy());

      double uf, ul, vf, vl;
      surf->Bounds(uf, ul, vf, vl);

      if (sas->IsUClosed(prec) && !sas->IsVClosed(prec))
      {
        gp_Vec2d tranvec(ul - uf, 0);
        c2d2->Translate(tranvec);
      }
      else if (sas->IsVClosed(prec) && !sas->IsUClosed(prec))
      {
        gp_Vec2d tranvec(0, vl - vf);
        c2d2->Translate(tranvec);
      }
      else if (sas->IsUClosed() && sas->IsVClosed())
      {

        c2d2 = TranslatePCurve(sas->Surface(), c2d2, prec);
      }
      B.UpdateEdge(edge, c2d, c2d2, surf, location, 0.);

      B.Range(edge, surf, location, a1, b1);
    }
    else
    {
      B.UpdateEdge(edge, c2d, surf, location, 0.);
    }

    if (myProjector->Status(ShapeExtend_DONE3))
    {
      double G3dCFirst = c3d->FirstParameter();
      double G3dCLast  = c3d->LastParameter();
      B.UpdateEdge(edge, c3d, 0.);
      B.Range(edge, G3dCFirst, G3dCLast, true);
    }
  }
  catch (Standard_Failure const& anException)
  {
#ifdef OCCT_DEBUG

    std::cout << "Warning: ShapeFix_Edge::FixAddPCurve(): Exception: ";
    anException.Print(std::cout);
    std::cout << std::endl;
#endif
    (void)anException;
    myStatus |= ShapeExtend::EncodeStatus(ShapeExtend_FAIL2);
  }
  myStatus |= ShapeExtend::EncodeStatus(ShapeExtend_DONE1);
  return true;
}

bool ShapeFix_Edge::FixAddCurve3d(const TopoDS_Edge& edge)
{
  myStatus = ShapeExtend::EncodeStatus(ShapeExtend_OK);
  ShapeAnalysis_Edge EA;
  if (BRep_Tool::Degenerated(edge) || EA.HasCurve3d(edge))
    return false;
  if (!BRep_Tool::SameRange(edge))
    TempSameRange(edge, Precision::PConfusion());

  if (!ShapeBuild_Edge().BuildCurve3d(edge))
  {
    myStatus |= ShapeExtend::EncodeStatus(ShapeExtend_FAIL1);
    return false;
  }
  myStatus |= ShapeExtend::EncodeStatus(ShapeExtend_DONE1);
  return true;
}

bool ShapeFix_Edge::FixVertexTolerance(const TopoDS_Edge& edge, const TopoDS_Face& face)
{
  myStatus                      = ShapeExtend::EncodeStatus(ShapeExtend_OK);
  TopoDS_Edge        anEdgeCopy = edge;
  ShapeAnalysis_Edge sae;
  if (!Context().IsNull())
  {
    anEdgeCopy = TopoDS::Edge(Context()->Apply(edge));
  }

  double toler1, toler2;
  if (!sae.CheckVertexTolerance(anEdgeCopy, face, toler1, toler2))
    return false;
  if (sae.Status(ShapeExtend_DONE1))
    myStatus = ShapeExtend::EncodeStatus(ShapeExtend_DONE1);
  if (sae.Status(ShapeExtend_DONE2))
    myStatus = ShapeExtend::EncodeStatus(ShapeExtend_DONE2);
  BRep_Builder  B;
  TopoDS_Vertex V1 = sae.FirstVertex(anEdgeCopy);
  TopoDS_Vertex V2 = sae.LastVertex(anEdgeCopy);
  if (!Context().IsNull())
  {
    Context()->CopyVertex(V1, toler1);
    Context()->CopyVertex(V2, toler2);
  }
  else
  {
    B.UpdateVertex(V1, toler1);
    B.UpdateVertex(V2, toler2);
  }
  return true;
}

bool ShapeFix_Edge::FixVertexTolerance(const TopoDS_Edge& edge)
{
  myStatus                      = ShapeExtend::EncodeStatus(ShapeExtend_OK);
  TopoDS_Edge        anEdgeCopy = edge;
  ShapeAnalysis_Edge sae;
  if (!Context().IsNull())
  {
    anEdgeCopy = TopoDS::Edge(Context()->Apply(edge));
  }
  double toler1, toler2;
  if (!sae.CheckVertexTolerance(anEdgeCopy, toler1, toler2))
    return false;
  if (sae.Status(ShapeExtend_DONE1))
    myStatus = ShapeExtend::EncodeStatus(ShapeExtend_DONE1);
  if (sae.Status(ShapeExtend_DONE2))
    myStatus = ShapeExtend::EncodeStatus(ShapeExtend_DONE2);
  BRep_Builder  B;
  TopoDS_Vertex V1 = sae.FirstVertex(anEdgeCopy);
  TopoDS_Vertex V2 = sae.LastVertex(anEdgeCopy);
  if (!Context().IsNull())
  {
    Context()->CopyVertex(V1, toler1);
    Context()->CopyVertex(V2, toler2);
  }
  else
  {
    B.UpdateVertex(V1, toler1);
    B.UpdateVertex(V2, toler2);
  }
  return true;
}

bool ShapeFix_Edge::FixReversed2d(const TopoDS_Edge& edge, const TopoDS_Face& face)
{
  TopLoc_Location                  L;
  const occ::handle<Geom_Surface>& S = BRep_Tool::Surface(face, L);
  return FixReversed2d(edge, S, L);
}

bool ShapeFix_Edge::FixReversed2d(const TopoDS_Edge&               edge,
                                  const occ::handle<Geom_Surface>& surface,
                                  const TopLoc_Location&           location)
{
  myStatus = ShapeExtend::EncodeStatus(ShapeExtend_OK);

  ShapeAnalysis_Edge EA;
  EA.CheckCurve3dWithPCurve(edge, surface, location);
  if (EA.Status(ShapeExtend_FAIL1))
    myStatus |= ShapeExtend::EncodeStatus(ShapeExtend_FAIL1);
  if (EA.Status(ShapeExtend_FAIL2))
    myStatus |= ShapeExtend::EncodeStatus(ShapeExtend_FAIL2);
  if (!EA.Status(ShapeExtend_DONE))
    return false;

  occ::handle<Geom2d_Curve> c2d;
  double                    f, l;
  EA.PCurve(edge, surface, location, c2d, f, l, false);

  double newf = c2d->ReversedParameter(l), newl = c2d->ReversedParameter(f);
  c2d->Reverse();
  BRep_Builder B;

  B.Range(edge, surface, location, newf, newl);

  double first, last;
  BRep_Tool::Range(edge, first, last);
  if (first != newf || last != newl)
  {
    B.SameRange(edge, false);
    B.SameParameter(edge, false);
  }
  myStatus |= ShapeExtend::EncodeStatus(ShapeExtend_DONE1);
  return true;
}

bool ShapeFix_Edge::FixSameParameter(const TopoDS_Edge& edge, const double tolerance)
{
  TopoDS_Face anEmptyFace;
  return FixSameParameter(edge, anEmptyFace, tolerance);
}

bool ShapeFix_Edge::FixSameParameter(const TopoDS_Edge& edge,
                                     const TopoDS_Face& face,
                                     const double       tolerance)
{
  myStatus = ShapeExtend::EncodeStatus(ShapeExtend_OK);

  if (BRep_Tool::Degenerated(edge))
  {
    BRep_Builder B;
    if (!BRep_Tool::SameRange(edge))
      TempSameRange(edge, Precision::PConfusion());
    B.SameParameter(edge, true);
    return false;
  }

  ShapeFix_ShapeTolerance SFST;
  ShapeAnalysis_Edge      sae;
  BRep_Builder            B;

  TopoDS_Edge   copyedge;
  TopoDS_Vertex V1    = sae.FirstVertex(edge);
  TopoDS_Vertex V2    = sae.LastVertex(edge);
  double        TolFV = (V1.IsNull() ? 0.0 : BRep_Tool::Tolerance(V1));
  double        TolLV = (V2.IsNull() ? 0.0 : BRep_Tool::Tolerance(V2));
  double        tol   = BRep_Tool::Tolerance(edge);

  bool wasSP = BRep_Tool::SameParameter(edge), SP = false;
  {
    try
    {
      OCC_CATCH_SIGNALS
      if (!BRep_Tool::SameRange(edge))
        TempSameRange(edge, Precision::PConfusion());

      if (!wasSP)
      {

        copyedge = ShapeBuild_Edge().Copy(edge, false);
        B.SameParameter(copyedge, false);

        double aF, aL;
        BRep_Tool::Range(edge, aF, aL);
        B.Range(copyedge, aF, aL, true);
        BRepLib::SameParameter(copyedge, (tolerance >= Precision::Confusion() ? tolerance : tol));
        SP = BRep_Tool::SameParameter(copyedge);
        if (!SP)
          myStatus |= ShapeExtend::EncodeStatus(ShapeExtend_FAIL2);
      }
    }
    catch (Standard_Failure const& anException)
    {
#ifdef OCCT_DEBUG
      std::cout << "\nWarning: ShapeFix_Edge: Exception in SameParameter: ";
      anException.Print(std::cout);
      std::cout << std::endl;
#endif
      (void)anException;
      myStatus |= ShapeExtend::EncodeStatus(ShapeExtend_FAIL2);
    }
  }

  double maxdev;
  B.SameParameter(edge, true);

  TopoDS_Face aFace = face;
  if (!wasSP)
  {
    TopoDS_Face anEmptyFace;
    aFace = anEmptyFace;
  }

  sae.CheckSameParameter(edge, aFace, maxdev);
  if (sae.Status(ShapeExtend_FAIL2))
    myStatus |= ShapeExtend::EncodeStatus(ShapeExtend_FAIL1);

  if (SP)
  {
    double BRLTol = BRep_Tool::Tolerance(copyedge), BRLDev;
    sae.CheckSameParameter(copyedge, BRLDev);
    myStatus |= ShapeExtend::EncodeStatus(ShapeExtend_DONE3);
    if (BRLTol < BRLDev)
      BRLTol = BRLDev;

    if (BRLTol < maxdev)
    {
      if (sae.Status(ShapeExtend_FAIL2))
        myStatus |= ShapeExtend::EncodeStatus(ShapeExtend_FAIL1);

      ShapeBuild_Edge().CopyPCurves(edge, copyedge);
      maxdev = BRLTol;
      SFST.SetTolerance(edge, BRLTol, TopAbs_EDGE);
      myStatus |= ShapeExtend::EncodeStatus(ShapeExtend_DONE5);
    }
  }

  if (!V1.IsNull())
    SFST.SetTolerance(V1, std::max(maxdev, TolFV), TopAbs_VERTEX);
  if (!V2.IsNull())
    SFST.SetTolerance(V2, std::max(maxdev, TolLV), TopAbs_VERTEX);

  if (maxdev > tol)
  {
    myStatus |= ShapeExtend::EncodeStatus(ShapeExtend_DONE1);
    B.UpdateEdge(edge, maxdev);
    FixVertexTolerance(edge);
  }

  if (!wasSP && !SP)
    myStatus |= ShapeExtend::EncodeStatus(ShapeExtend_DONE2);
  return Status(ShapeExtend_DONE);
}

bool ShapeFix_Edge::Status(const ShapeExtend_Status status) const
{
  return ShapeExtend::DecodeStatus(myStatus, status);
}

occ::handle<ShapeBuild_ReShape> ShapeFix_Edge::Context() const
{
  return myContext;
}

void ShapeFix_Edge::SetContext(const occ::handle<ShapeBuild_ReShape>& context)
{
  myContext = context;
}
