#include <BRep_CurveRepresentation.hpp>
#include <BRep_GCurve.hpp>
#include <BRep_TEdge.hpp>
#include <BRep_TFace.hpp>
#include <BRep_Tool.hpp>
#include <BRep_TVertex.hpp>
#include <BRepCheck.hpp>
#include <BRepCheck_Status.hpp>
#include <NCollection_List.hpp>
#include <NCollection_Shared.hpp>
#include <BRepCheck_Vertex.hpp>
#include <Geom2d_Curve.hpp>
#include <Geom_Curve.hpp>
#include <Geom_Surface.hpp>
#include <gp_Pnt2d.hpp>
#include <Standard_Type.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Iterator.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDS_Vertex.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BRepCheck_Vertex, BRepCheck_Result)

//=================================================================================================

BRepCheck_Vertex::BRepCheck_Vertex(const TopoDS_Vertex& V)
{
  Init(V);
}

//=================================================================================================

void BRepCheck_Vertex::Minimum()
{
  if (!myMin)
  {
    // checks the existence of a point 3D
    occ::handle<NCollection_Shared<NCollection_List<BRepCheck_Status>>> aNewList =
      new NCollection_Shared<NCollection_List<BRepCheck_Status>>();
    NCollection_List<BRepCheck_Status>& lst = **myMap.Bound(myShape, aNewList);
    lst.Append(BRepCheck_NoError);
    myMin = true;
  }
}

//=================================================================================================

void BRepCheck_Vertex::InContext(const TopoDS_Shape& S)
{
  occ::handle<NCollection_Shared<NCollection_List<BRepCheck_Status>>> aHList;
  {
    std::unique_lock<std::mutex> aLock =
      myMutex ? std::unique_lock<std::mutex>(*myMutex) : std::unique_lock<std::mutex>();
    if (myMap.IsBound(S))
    {
      return;
    }

    occ::handle<NCollection_Shared<NCollection_List<BRepCheck_Status>>> aNewList =
      new NCollection_Shared<NCollection_List<BRepCheck_Status>>();
    aHList = *myMap.Bound(S, aNewList);
  }
  NCollection_List<BRepCheck_Status>& lst = *aHList;

  TopExp_Explorer exp(S, TopAbs_VERTEX);
  for (; exp.More(); exp.Next())
  {
    if (exp.Current().IsSame(myShape))
    {
      break;
    }
  }
  if (!exp.More())
  {
    BRepCheck::Add(lst, BRepCheck_SubshapeNotInShape);
    return; // leaves
  }

  occ::handle<BRep_TVertex>& TV   = *((occ::handle<BRep_TVertex>*)&myShape.TShape());
  const gp_Pnt&              prep = TV->Pnt();
  gp_Pnt                     Controlp;

  TopAbs_ShapeEnum styp = S.ShapeType();
  switch (styp)
  {
    case TopAbs_EDGE:
    {
      // Try to find the vertex on the edge
      const TopoDS_Edge& E = TopoDS::Edge(S);
      TopoDS_Iterator    itv(E.Oriented(TopAbs_FORWARD));
      TopoDS_Vertex      VFind;
      bool               multiple = false;
      while (itv.More())
      {
        const TopoDS_Vertex& VF = TopoDS::Vertex(itv.Value());
        if (itv.Value().IsSame(myShape))
        {
          if (VFind.IsNull())
          {
            VFind = VF;
          }
          else
          {
            if ((VFind.Orientation() == TopAbs_FORWARD && VF.Orientation() == TopAbs_REVERSED)
                || (VFind.Orientation() == TopAbs_REVERSED && VF.Orientation() == TopAbs_FORWARD))
            {
              // the vertex on the edge is at once F and R
              multiple = true;
            }
            if (VFind.Orientation() != TopAbs_FORWARD && VFind.Orientation() != TopAbs_REVERSED)
            {
              if (VF.Orientation() == TopAbs_FORWARD || VF.Orientation() == TopAbs_REVERSED)
              {
                VFind = VF;
              }
            }
          }
        }
        itv.Next();
      }

      // VFind is not null for sure
      TopAbs_Orientation orv = VFind.Orientation();

      double Tol = BRep_Tool::Tolerance(TopoDS::Vertex(myShape));
      Tol        = std::max(Tol, BRep_Tool::Tolerance(E)); // to check
      Tol *= Tol;

      occ::handle<BRep_TEdge>& TE = *((occ::handle<BRep_TEdge>*)&E.TShape());
      NCollection_List<occ::handle<BRep_CurveRepresentation>>::Iterator itcr(TE->Curves());
      const TopLoc_Location&                                            Eloc = E.Location();

      NCollection_List<occ::handle<BRep_PointRepresentation>>::Iterator itpr;
      while (itcr.More())
      {
        // For each CurveRepresentation, the provided parameter is checked
        const occ::handle<BRep_CurveRepresentation>& cr  = itcr.Value();
        const TopLoc_Location&                       loc = cr->Location();
        TopLoc_Location L = (Eloc * loc).Predivided(myShape.Location());

        if (cr->IsCurve3D())
        {
          const occ::handle<Geom_Curve>& C = cr->Curve3D();
          if (!C.IsNull()) // edge non degenerated
          {
            itpr.Initialize(TV->Points());
            while (itpr.More())
            {
              const occ::handle<BRep_PointRepresentation>& pr = itpr.Value();
              if (pr->IsPointOnCurve(C, L))
              {
                Controlp = C->Value(pr->Parameter());
                Controlp.Transform(L.Transformation());
                if (prep.SquareDistance(Controlp) > Tol)
                {
                  BRepCheck::Add(lst, BRepCheck_InvalidPointOnCurve);
                }
              }
              itpr.Next();
            }
            if (orv == TopAbs_FORWARD || orv == TopAbs_REVERSED)
            {
              occ::handle<BRep_GCurve> GC = occ::down_cast<BRep_GCurve>(cr);
              if (orv == TopAbs_FORWARD || multiple)
              {
                Controlp = C->Value(GC->First());
                Controlp.Transform(L.Transformation());
                if (prep.SquareDistance(Controlp) > Tol)
                {
                  BRepCheck::Add(lst, BRepCheck_InvalidPointOnCurve);
                }
              }
              if (orv == TopAbs_REVERSED || multiple)
              {
                Controlp = C->Value(GC->Last());
                Controlp.Transform(L.Transformation());
                if (prep.SquareDistance(Controlp) > Tol)
                {
                  BRepCheck::Add(lst, BRepCheck_InvalidPointOnCurve);
                }
              }
            }
          }
        }
        else if (cr->IsCurveOnSurface())
        {
          const occ::handle<Geom_Surface>& Su = cr->Surface();
          const occ::handle<Geom2d_Curve>& PC = cr->PCurve();
          occ::handle<Geom2d_Curve>        PC2;
          if (cr->IsCurveOnClosedSurface())
          {
            PC2 = cr->PCurve2();
          }
          itpr.Initialize(TV->Points());
          while (itpr.More())
          {
            const occ::handle<BRep_PointRepresentation>& pr = itpr.Value();
            if (pr->IsPointOnCurveOnSurface(PC, Su, L))
            {
              gp_Pnt2d p2d = PC->Value(pr->Parameter());
              Controlp     = Su->Value(p2d.X(), p2d.Y());
              Controlp.Transform(L.Transformation());
              if (prep.SquareDistance(Controlp) > Tol)
              {
                BRepCheck::Add(lst, BRepCheck_InvalidPointOnCurveOnSurface);
              }
            }
            if (!PC2.IsNull() && pr->IsPointOnCurveOnSurface(PC2, Su, L))
            {
              gp_Pnt2d p2d = PC2->Value(pr->Parameter());
              Controlp     = Su->Value(p2d.X(), p2d.Y());
              Controlp.Transform(L.Transformation());
              if (prep.SquareDistance(Controlp) > Tol)
              {
                BRepCheck::Add(lst, BRepCheck_InvalidPointOnCurveOnSurface);
              }
            }
            itpr.Next();
          }
        }
        itcr.Next();
      }
      if (lst.IsEmpty())
      {
        lst.Append(BRepCheck_NoError);
      }
      break;
    }
    case TopAbs_FACE:
    {
      occ::handle<BRep_TFace>&         TF    = *((occ::handle<BRep_TFace>*)&S.TShape());
      const TopLoc_Location&           Floc  = S.Location();
      const TopLoc_Location&           TFloc = TF->Location();
      const occ::handle<Geom_Surface>& Su    = TF->Surface();
      TopLoc_Location                  L     = (Floc * TFloc).Predivided(myShape.Location());

      double Tol = BRep_Tool::Tolerance(TopoDS::Vertex(myShape));
      Tol        = std::max(Tol, BRep_Tool::Tolerance(TopoDS::Face(S))); // to check
      Tol *= Tol;

      NCollection_List<occ::handle<BRep_PointRepresentation>>::Iterator itpr(TV->Points());
      while (itpr.More())
      {
        const occ::handle<BRep_PointRepresentation>& pr = itpr.Value();
        if (pr->IsPointOnSurface(Su, L))
        {
          Controlp = Su->Value(pr->Parameter(), pr->Parameter2());
          Controlp.Transform(L.Transformation());
          if (prep.SquareDistance(Controlp) > Tol)
          {
            BRepCheck::Add(lst, BRepCheck_InvalidPointOnSurface);
          }
        }
        itpr.Next();
      }
      if (lst.IsEmpty())
      {
        lst.Append(BRepCheck_NoError);
      }
      break;
    }
    default:
    {
      break;
    }
  }
}

//=================================================================================================

void BRepCheck_Vertex::Blind()
{
  if (myBlind)
  {
    return;
  }
  //   modified by NIZHNY-MKK  Fri May  7 16:43:38 2004.BEGIN
  //   The body of this function is removed because of its useless
  //   (see specification "Substitution existing set of evaluation DRAW commands to one").

  //   Check all the representations  of the vertex. (i-e checks the TVertex
  //   NCollection_List<BRepCheck_Status>& lst = myMap(myShape);
  //   lst.Clear(); // there was NoError...

  //   occ::handle<BRep_TVertex>& TV = *((occ::handle<BRep_TVertex>*) &myShape.TShape());
  //   const gp_Pnt& prep = TV->Pnt();
  //   double Tol  = BRep_Tool::Tolerance(TopoDS::Vertex(myShape));
  //   Tol *= Tol;

  //   gp_Pnt Controlp;
  //   NCollection_List<occ::handle<BRep_PointRepresentation>>::Iterator itpr(TV->Points());
  //   BRepCheck_Status stat=BRepCheck_NoError;
  //   while (itpr.More()) {
  //     const occ::handle<BRep_PointRepresentation>& pr = itpr.Value();
  //     const TopLoc_Location& loc = pr->Location();
  //     if (pr->IsPointOnCurve()) {
  //       Controlp = pr->Curve()->Value(pr->Parameter());
  //       stat = BRepCheck_InvalidPointOnCurve;
  //     }
  //     else if (pr->IsPointOnCurveOnSurface()) {
  //       gp_Pnt2d Puv = pr->PCurve()->Value(pr->Parameter());
  //       Controlp = pr->Surface()->Value(Puv.X(),Puv.Y());
  //       stat = BRepCheck_InvalidPointOnCurveOnSurface;
  //     }
  //     else if (pr->IsPointOnSurface()) {
  //       Controlp = pr->Surface()->Value(pr->Parameter(),pr->Parameter2());
  //       stat = BRepCheck_InvalidPointOnSurface;
  //     }
  //     Controlp.Transform(loc.Transformation());
  //     if (prep.SquareDistance(Controlp) > Tol) {
  //       BRepCheck::Add(lst,stat);
  //     }
  //     itpr.Next();
  //   }

  //   if (lst.IsEmpty()) {
  //     lst.Append(BRepCheck_NoError);
  //   }
  // modified by NIZHNY-MKK  Fri May  7 16:43:45 2004.END
  myBlind = true;
}

//=================================================================================================

double BRepCheck_Vertex::Tolerance()
{

  // Check all the representations  of the vertex. (i-e checks the TVertex
  occ::handle<BRep_TVertex>& TV   = *((occ::handle<BRep_TVertex>*)&myShape.TShape());
  const gp_Pnt&              prep = TV->Pnt();
  double                     Tol  = BRep_Tool::Tolerance(TopoDS::Vertex(myShape));
  Tol *= Tol;

  gp_Pnt Controlp;
  Controlp = prep;
  NCollection_List<occ::handle<BRep_PointRepresentation>>::Iterator itpr(TV->Points());
  while (itpr.More())
  {
    const occ::handle<BRep_PointRepresentation>& pr  = itpr.Value();
    const TopLoc_Location&                       loc = pr->Location();
    if (pr->IsPointOnCurve())
    {
      if (!pr->Curve().IsNull())
        Controlp = pr->Curve()->Value(pr->Parameter());
    }
    else if (pr->IsPointOnCurveOnSurface())
    {
      gp_Pnt2d Puv = pr->PCurve()->Value(pr->Parameter());
      Controlp     = pr->Surface()->Value(Puv.X(), Puv.Y());
    }
    else if (pr->IsPointOnSurface())
    {
      Controlp = pr->Surface()->Value(pr->Parameter(), pr->Parameter2());
    }
    Controlp.Transform(loc.Transformation());
    if (prep.SquareDistance(Controlp) > Tol)
    {
      Tol = prep.SquareDistance(Controlp);
    }
    itpr.Next();
  }
  return sqrt(Tol * 1.05);
}
