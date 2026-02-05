#include <BRep_Builder.hpp>
#include <ElSLib.hpp>
#include <Geom2d_Line.hpp>
#include <Geom_CartesianPoint.hpp>
#include <Geom_Line.hpp>
#include <Geom_Plane.hpp>
#include <Geom_Surface.hpp>
#include <gp_Vec2d.hpp>
#include <Precision.hpp>
#include <ShapeAnalysis_Surface.hpp>
#include <StdFail_NotDone.hpp>
#include <StepData_Factors.hpp>
#include <StepShape_PolyLoop.hpp>
#include <StepToGeom.hpp>
#include <StepToTopoDS_Tool.hpp>
#include <StepToTopoDS_TranslatePolyLoop.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDS_Vertex.hpp>
#include <TopoDS_Wire.hpp>
#include <Transfer_TransientProcess.hpp>

// #include <BRepAPI.hxx>
//=================================================================================================

StepToTopoDS_TranslatePolyLoop::StepToTopoDS_TranslatePolyLoop()
    : myError(StepToTopoDS_TranslatePolyLoopOther)
{
  done = false;
}

//=================================================================================================

StepToTopoDS_TranslatePolyLoop::StepToTopoDS_TranslatePolyLoop(
  const occ::handle<StepShape_PolyLoop>& PL,
  StepToTopoDS_Tool&                     T,
  const occ::handle<Geom_Surface>&       S,
  const TopoDS_Face&                     F,
  const StepData_Factors&                theLocalFactors)
{
  Init(PL, T, S, F, theLocalFactors);
}

//=================================================================================================

void StepToTopoDS_TranslatePolyLoop::Init(const occ::handle<StepShape_PolyLoop>& PL,
                                          StepToTopoDS_Tool&                     aTool,
                                          const occ::handle<Geom_Surface>&       GeomSurf,
                                          const TopoDS_Face&                     TopoFace,
                                          const StepData_Factors&                theLocalFactors)
{
  if (!aTool.IsBound(PL))
  {
    BRep_Builder                           B;
    occ::handle<Transfer_TransientProcess> TP = aTool.TransientProcess();

    //: S4136    double preci = BRepAPI::Precision();
    int                                  i;
    occ::handle<StepGeom_CartesianPoint> P1, P2;
    occ::handle<Geom_CartesianPoint>     GP1, GP2;
    TopoDS_Vertex                        V1, V2;
    TopoDS_Edge                          E;
    TopoDS_Wire                          W;
    occ::handle<Geom_Line>               L;
    occ::handle<Geom2d_Line>             L2d;
    gp_Vec                               V;
    gp_Vec2d                             V2d;
    double                               Magn;
    occ::handle<Geom_Plane>              SP = occ::down_cast<Geom_Plane>(GeomSurf);
    if (SP.IsNull())
      TP->AddFail(PL, "Surface not planar in a FacetedBRep !");
    occ::handle<ShapeAnalysis_Surface> STSU = new ShapeAnalysis_Surface(GeomSurf);
    int                                Nb   = PL->NbPolygon();
    occ::handle<NCollection_HArray1<occ::handle<StepGeom_CartesianPoint>>> Poly =
      new NCollection_HArray1<occ::handle<StepGeom_CartesianPoint>>(1, Nb + 1);

    for (i = 1; i <= Nb; i++)
      Poly->SetValue(i, PL->PolygonValue(i));

    Nb++;
    Poly->SetValue(Nb, PL->PolygonValue(1));
    P1  = Poly->Value(1);
    GP1 = StepToGeom::MakeCartesianPoint(P1, theLocalFactors);
    if (aTool.IsVertexBound(P1))
    {
      V1 = aTool.FindVertex(P1);
    }
    else
    {
      B.MakeVertex(V1, GP1->Pnt(), Precision::Confusion()); //: S4136: preci
      aTool.BindVertex(P1, V1);
    }
    B.MakeWire(W);
    for (i = 2; i <= Nb; i++)
    {
      P2 = Poly->Value(i);
      if (P1 == P2)
        continue; // peut arriver (KK)  CKY 9-DEC-1997
      StepToTopoDS_PointPair PP(P1, P2);
      GP2 = StepToGeom::MakeCartesianPoint(P2, theLocalFactors);
      TopoDS_Shape aBoundEdge;
      bool         isbound = aTool.IsEdgeBound(PP);
      if (!isbound)
      {
        if (aTool.IsVertexBound(P2))
        {
          V2 = aTool.FindVertex(P2);
        }
        else
        {
          B.MakeVertex(V2, GP2->Pnt(), Precision::Confusion()); //: S4136: preci
          aTool.BindVertex(P2, V2);
        }
        V = gp_Vec(GP1->Pnt(), GP2->Pnt());
        L = new Geom_Line(GP1->Pnt(), gp_Dir(V));
        B.MakeEdge(E, L, Precision::Confusion()); //: S4136: preci
        V1.Orientation(TopAbs_FORWARD);
        V2.Orientation(TopAbs_REVERSED);
        B.Add(E, V1);
        B.Add(E, V2);
        Magn = V.Magnitude();
        B.UpdateVertex(V1, 0., E, 0.);   //: S4136: preci
        B.UpdateVertex(V2, Magn, E, 0.); //: S4136: preci
      }
      else
      {
        aBoundEdge = aTool.FindEdge(PP);
        E          = TopoDS::Edge(aBoundEdge);
        //  Il faut qu en finale l edge soit vue
        //  - via sa premiere face, orientation combinee = celle de cette premiere face
        //  - via sa deuxieme face, orientation combinee INVERSE de la precedente
        if (TopoFace.Orientation() == TopAbs_FORWARD)
          E.Reverse();
        V2 = aTool.FindVertex(P2);
      }
      gp_Pnt2d V2p1 = STSU->ValueOfUV(GP1->Pnt(), Precision());
      gp_Pnt2d V2p2 = STSU->ValueOfUV(GP2->Pnt(), Precision());
      if (E.Orientation() == TopAbs_FORWARD)
      {
        V2d = gp_Vec2d(V2p1, V2p2);
        L2d = new Geom2d_Line(V2p1, gp_Dir2d(V2d));
      }
      else
      {
        V2d = gp_Vec2d(V2p2, V2p1);
        L2d = new Geom2d_Line(V2p2, gp_Dir2d(V2d));
      }
      B.UpdateEdge(E, L2d, TopoFace, 0.);
      TopoDS_Edge EB = E; // pour le binding : cumul des orientations !
      EB.Orientation(TopoFace.Orientation());
      if (!isbound)
        aTool.BindEdge(PP, EB);
      if (!E.IsNull())
      {
        B.Add(W, E);
      }
      P1  = P2;
      GP1 = GP2;
      V1  = V2;
    }
    W.Closed(BRep_Tool::IsClosed(W));
    aTool.Bind(PL, W);
    myResult = W;
    myError  = StepToTopoDS_TranslatePolyLoopDone;
    done     = true;
  }
  else
  {
    myResult = TopoDS::Wire(aTool.Find(PL));
    myError  = StepToTopoDS_TranslatePolyLoopDone;
    done     = true;
  }
}

//=================================================================================================

const TopoDS_Shape& StepToTopoDS_TranslatePolyLoop::Value() const
{
  StdFail_NotDone_Raise_if(!done, "StepToTopoDS_TranslatePolyLoop::Value() - no result");
  return myResult;
}

//=================================================================================================

StepToTopoDS_TranslatePolyLoopError StepToTopoDS_TranslatePolyLoop::Error() const
{
  return myError;
}
