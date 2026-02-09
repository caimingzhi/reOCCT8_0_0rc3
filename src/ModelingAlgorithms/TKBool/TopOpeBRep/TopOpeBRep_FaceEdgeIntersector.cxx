#include <BRep_Tool.hpp>
#include <BRepIntCurveSurface_Inter.hpp>
#include <Geom_Curve.hpp>
#include <gp_Pnt.hpp>
#include <gp_Pnt2d.hpp>
#include <IntCurveSurface_IntersectionPoint.hpp>
#include <IntCurveSurface_TransitionOnCurve.hpp>
#include <Precision.hpp>
#include <Standard_ProgramError.hpp>
#include <TopLoc_Location.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Shape.hpp>
#include <TopOpeBRep_FaceEdgeIntersector.hpp>
#include <TopOpeBRepDS_Transition.hpp>
#include <TopOpeBRepTool_ShapeTool.hpp>

#ifdef OCCT_DEBUG
  #include <TopAbs.hpp>
extern bool TopOpeBRep_GettraceFITOL();
extern bool TopOpeBRep_GettraceSAVFF();
  #include <TCollection_AsciiString.hpp>
  #include <Standard_CString.hpp>
  #include <BRepTools.hpp>

static void SAVFE(const TopoDS_Face& F1, const TopoDS_Edge& E)
{
  TCollection_AsciiString aname_1("FE_face"), aname_2("FE_edge");
  const char *            name_1 = aname_1.ToCString(), name_2 = aname_2.ToCString();
  std::cout << "FaceEdgeIntersector : " << name_1 << "," << name_2 << std::endl;
  BRepTools::Write(F1, name_1);
  BRepTools::Write(E, name_2);
}

extern bool TopOpeBRepTool_GettraceKRO();
  #include <TopOpeBRepTool_KRO.hpp>
Standard_EXPORT TOPKRO KRO_DSFILLER_INTFE("intersection face/edge");
#endif

TopOpeBRep_FaceEdgeIntersector::TopOpeBRep_FaceEdgeIntersector()
{
  ResetIntersection();
}

void TopOpeBRep_FaceEdgeIntersector::ResetIntersection()
{
  mySequenceOfPnt.Clear();
  mySequenceOfState.Clear();
  myNbPoints         = 0;
  myIntersectionDone = false;
}

void TopOpeBRep_FaceEdgeIntersector::Perform(const TopoDS_Shape& SF, const TopoDS_Shape& SE)
{
  ResetIntersection();
  if (!myForceTolerance)
    ShapeTolerances(SF, SE);
  myTol = BRep_Tool::Tolerance(TopoDS::Edge(SE));
#ifdef OCCT_DEBUG
  if (TopOpeBRep_GettraceFITOL())
    std::cout << "Perform : myTol = " << myTol << std::endl;
#endif

  myFace = TopoDS::Face(SF);
  myFace.Orientation(TopAbs_FORWARD);
  myEdge = TopoDS::Edge(SE);
  myEdge.Orientation(TopAbs_FORWARD);

#ifdef OCCT_DEBUG
  if (TopOpeBRep_GettraceSAVFF())
    SAVFE(myFace, myEdge);
#endif

  double                        f, l;
  TopLoc_Location               loc;
  const occ::handle<Geom_Curve> C = BRep_Tool::Curve(myEdge, loc, f, l);

  occ::handle<Geom_Geometry> GGao1  = C->Transformed(loc.Transformation());
  occ::handle<Geom_Curve>*   PGCao1 = (occ::handle<Geom_Curve>*)&GGao1;
  myCurve.Load(*PGCao1, f, l);

#ifdef OCCT_DEBUG
  if (TopOpeBRepTool_GettraceKRO())
    KRO_DSFILLER_INTFE.Start();
#endif

  BRepIntCurveSurface_Inter FEINT;
  FEINT.Init(myFace, myCurve, myTol);

#ifdef OCCT_DEBUG
  if (TopOpeBRepTool_GettraceKRO())
    KRO_DSFILLER_INTFE.Stop();
#endif

  for (FEINT.Init(myFace, myCurve, myTol); FEINT.More(); FEINT.Next())
  {
    mySequenceOfPnt.Append(FEINT.Point());
    int i = (FEINT.State() == TopAbs_IN) ? 0 : 1;
    mySequenceOfState.Append(i);
  }

  myNbPoints         = mySequenceOfPnt.Length();
  myIntersectionDone = true;
}

bool TopOpeBRep_FaceEdgeIntersector::IsEmpty()
{
  bool b = myNbPoints == 0;
  return b;
}

const TopoDS_Shape& TopOpeBRep_FaceEdgeIntersector::Shape(const int Index) const
{
  if (Index == 1)
    return myFace;
  else if (Index == 2)
    return myEdge;
  else
    throw Standard_ProgramError("TopOpeBRep_FaceEdgeIntersector::Shape");
}

void TopOpeBRep_FaceEdgeIntersector::ForceTolerance(const double Tol)
{
  myTol            = Tol;
  myForceTolerance = true;

#ifdef OCCT_DEBUG
  if (TopOpeBRep_GettraceFITOL())
    std::cout << "ForceTolerance : myTol = " << myTol << std::endl;
#endif
}

double TopOpeBRep_FaceEdgeIntersector::Tolerance() const
{
  return myTol;
}

int TopOpeBRep_FaceEdgeIntersector::NbPoints() const
{
  int n = myNbPoints;
  return n;
}

void TopOpeBRep_FaceEdgeIntersector::InitPoint()
{
  myPointIndex = 1;
}

bool TopOpeBRep_FaceEdgeIntersector::MorePoint() const
{
  bool b = myPointIndex <= myNbPoints;
  return b;
}

void TopOpeBRep_FaceEdgeIntersector::NextPoint()
{
  myPointIndex++;
}

gp_Pnt TopOpeBRep_FaceEdgeIntersector::Value() const
{
  const IntCurveSurface_IntersectionPoint& IP = mySequenceOfPnt(myPointIndex);
  const gp_Pnt&                            P  = IP.Pnt();
  return P;
}

double TopOpeBRep_FaceEdgeIntersector::Parameter() const
{
  const IntCurveSurface_IntersectionPoint& IP = mySequenceOfPnt(myPointIndex);
  double                                   p  = IP.W();
  return p;
}

void TopOpeBRep_FaceEdgeIntersector::UVPoint(gp_Pnt2d& P2d) const
{
  const IntCurveSurface_IntersectionPoint& IP = mySequenceOfPnt(myPointIndex);
  double                                   u  = IP.U();
  double                                   v  = IP.V();
  P2d.SetCoord(u, v);
}

TopAbs_State TopOpeBRep_FaceEdgeIntersector::State() const
{
  int          i = mySequenceOfState(myPointIndex);
  TopAbs_State s = (i == 0) ? TopAbs_IN : TopAbs_ON;
  return s;
}

TopOpeBRepDS_Transition TopOpeBRep_FaceEdgeIntersector::Transition(
  const int                Index,
  const TopAbs_Orientation FaceOrientation) const
{

  TopAbs_State stB, stA;

  const IntCurveSurface_IntersectionPoint& IP = mySequenceOfPnt(myPointIndex);

  if (Index == 2)
  {
    switch (IP.Transition())
    {
      case IntCurveSurface_In:
        stB = TopAbs_OUT;
        stA = TopAbs_IN;
        break;
      case IntCurveSurface_Out:
        stB = TopAbs_IN;
        stA = TopAbs_OUT;
        break;
      default:
        stB = TopAbs_IN;
        stA = TopAbs_IN;
        break;
    }

    TopOpeBRepDS_Transition TR;
    TopAbs_ShapeEnum        onB = TopAbs_FACE, onA = TopAbs_FACE;
    if (FaceOrientation == TopAbs_FORWARD)
      TR.Set(stB, stA, onB, onA);
    else if (FaceOrientation == TopAbs_REVERSED)
      TR.Set(stA, stB, onA, onB);
    else if (FaceOrientation == TopAbs_EXTERNAL)
      TR.Set(TopAbs_OUT, TopAbs_OUT, onA, onB);
    else if (FaceOrientation == TopAbs_INTERNAL)
      TR.Set(TopAbs_IN, TopAbs_IN, onA, onB);
    return TR;
  }

  else if (Index == 1)
  {
    switch (IP.Transition())
    {
      case IntCurveSurface_In:
        stB = stA = TopAbs_IN;
        break;
      case IntCurveSurface_Out:
        stB = stA = TopAbs_IN;
        break;
      default:
        stB = stA = TopAbs_IN;
        break;
    }
    TopAbs_ShapeEnum        onB = TopAbs_FACE, onA = TopAbs_FACE;
    TopOpeBRepDS_Transition TR;
    TR.Set(stB, stA, onB, onA);
    return TR;
  }

  else
    throw Standard_ProgramError("FEINT Transition Index");
}

bool TopOpeBRep_FaceEdgeIntersector::IsVertex(const TopoDS_Shape& S,
                                              const gp_Pnt&       P,
                                              const double        Tol,
                                              TopoDS_Vertex&      VR)
{
  bool isv = false;
  VR       = myNullVertex;

  double Tol2 = Tol * Tol;
  for (myVertexExplorer.Init(S, TopAbs_VERTEX); myVertexExplorer.More(); myVertexExplorer.Next())
  {
    const TopoDS_Shape&  SS = myVertexExplorer.Current();
    const TopoDS_Vertex& VV = TopoDS::Vertex(SS);
    gp_Pnt               PV = BRep_Tool::Pnt(VV);
    isv                     = P.SquareDistance(PV) < Tol2;
    if (isv)
    {
      VR = VV;
    }
  }

  return isv;
}

bool TopOpeBRep_FaceEdgeIntersector::IsVertex(const int I, TopoDS_Vertex& VR)
{
  bool   isv = false;
  gp_Pnt P   = Value();
  if (I == 1)
    isv = IsVertex(myFace, P, myTol, VR);
  else if (I == 2)
    isv = IsVertex(myEdge, P, myTol, VR);
  return isv;
}

int TopOpeBRep_FaceEdgeIntersector::Index() const
{
#ifdef OCCT_DEBUG
  return myPointIndex;
#else
  return 0;
#endif
}

void TopOpeBRep_FaceEdgeIntersector::ShapeTolerances(const TopoDS_Shape& S1, const TopoDS_Shape& S2)
{
  myTol            = std::max(ToleranceMax(S1, TopAbs_EDGE), ToleranceMax(S2, TopAbs_EDGE));
  myForceTolerance = false;

#ifdef OCCT_DEBUG
  if (TopOpeBRep_GettraceFITOL())
  {
    std::cout << "ShapeTolerances on S1 = ";
    TopAbs::Print(S1.ShapeType(), std::cout);
    std::cout << " S2 = ";
    TopAbs::Print(S2.ShapeType(), std::cout);
    std::cout << " : myTol = " << myTol << std::endl;
  }
#endif
}

double TopOpeBRep_FaceEdgeIntersector::ToleranceMax(const TopoDS_Shape&    S,
                                                    const TopAbs_ShapeEnum T) const
{
  TopExp_Explorer e(S, T);
  if (!e.More())
    return Precision::Intersection();
  else
  {
    double tol = RealFirst();
    for (; e.More(); e.Next())
      tol = std::max(tol, TopOpeBRepTool_ShapeTool::Tolerance(e.Current()));
    return tol;
  }
}
