#include <BRep_Tool.hpp>
#include <IntPatch_GLine.hpp>
#include <Standard_Type.hpp>
#include <TopoDS.hpp>
#include <TopOpeBRep.hpp>
#include <TopOpeBRep_FacesFiller.hpp>
#include <TopOpeBRep_FacesIntersector.hpp>
#include <TopOpeBRep_FFDumper.hpp>
#include <TopOpeBRep_FFTransitionTool.hpp>
#include <TopOpeBRep_LineInter.hpp>
#include <TopOpeBRep_VPointInter.hpp>
#include <TopOpeBRep_VPointInterIterator.hpp>
#include <TopOpeBRepDS_DataStructure.hpp>
#include <TopOpeBRepDS_HDataStructure.hpp>
#include <TopOpeBRepTool_ShapeTool.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TopOpeBRep_FFDumper, Standard_Transient)

#ifdef OCCT_DEBUG
static TCollection_AsciiString PRODINP("dinp ");
#endif

#ifndef OCCT_DEBUG
TopOpeBRep_FFDumper::TopOpeBRep_FFDumper(const TopOpeBRep_PFacesFiller&)
{
#else
TopOpeBRep_FFDumper::TopOpeBRep_FFDumper(const TopOpeBRep_PFacesFiller& PFF)
{
  Init(PFF);
#endif
}

#ifndef OCCT_DEBUG
void TopOpeBRep_FFDumper::Init(const TopOpeBRep_PFacesFiller&)
{

  (void)myEn1;
  (void)myEn2;
  (void)myLineIndex;
}
#else
void TopOpeBRep_FFDumper::Init(const TopOpeBRep_PFacesFiller& PFF)
{
  myPFF                     = PFF;
  const TopoDS_Face& fpff1  = myPFF->Face(1);
  const TopoDS_Face& fpff2  = myPFF->Face(2);
  bool               f1diff = (!myF1.IsEqual(fpff1));
  bool               f2diff = (!myF2.IsEqual(fpff2));
  bool               init   = f1diff || f2diff;
  if (init)
  {
    myF1 = myPFF->Face(1);
    myF2 = myPFF->Face(2);
    myEM1.Clear();
    myEn1 = 0;
    myEM2.Clear();
    myEn2 = 0;
    TopExp_Explorer x;
    for (x.Init(myF1, TopAbs_EDGE); x.More(); x.Next())
      myEM1.Bind(x.Current(), ++myEn1);
    for (x.Init(myF2, TopAbs_EDGE); x.More(); x.Next())
      myEM2.Bind(x.Current(), ++myEn2);
    myLineIndex = 0;
  }
}
#endif

#ifndef OCCT_DEBUG
void TopOpeBRep_FFDumper::DumpLine(const int)
{
#else
void TopOpeBRep_FFDumper::DumpLine(const int I)
{
  const TopOpeBRep_LineInter& L = myPFF->ChangeFacesIntersector().ChangeLine(I);
  DumpLine(L);
#endif
}

#ifndef OCCT_DEBUG
void TopOpeBRep_FFDumper::DumpLine(const TopOpeBRep_LineInter&)
{
#else
void TopOpeBRep_FFDumper::DumpLine(const TopOpeBRep_LineInter& LI)
{
  int il          = LI.Index();
  myLineIndex     = il;
  int  nl         = myPFF->ChangeFacesIntersector().NbLines();
  bool HasVPonR   = LI.HasVPonR();
  bool IsVClosed  = LI.IsVClosed();
  bool IsPeriodic = LI.IsPeriodic();
  bool isrest     = (LI.TypeLineCurve() == TopOpeBRep_RESTRICTION);

  std::cout << std::endl << "--------------------------------------------------" << std::endl;
  std::cout << "line " << il << "/" << nl << " is a ";
  LI.DumpType();
  if (isrest)
  {
    bool isedge1 = LI.ArcIsEdge(1);
    bool isedge2 = LI.ArcIsEdge(2);
    if (isedge1)
      std::cout << " of 1";
    else if (isedge2)
      std::cout << " of 2";
    else
      std::cout << "of 0(BUG)";
  }
  std::cout << std::endl;
  if (isrest)
  {
    const TopoDS_Shape& Erest    = LI.Arc();
    bool                FIisrest = myPFF->ChangeFacesIntersector().IsRestriction(Erest);
    std::cout << "++++ line restriction";
    if (FIisrest)
    {
      std::cout << " edge restriction";
      int iErest = 0;
      if (myPFF->ChangeDataStructure().HasShape(Erest))
        iErest = myPFF->ChangeDataStructure().Shape(Erest);
      std::cout << " " << iErest;
    }
    std::cout << std::endl;
  }
  if (HasVPonR)
    std::cout << "has vertex on restriction" << std::endl;
  else
    std::cout << "has no vertex on restriction" << std::endl;
  if (IsVClosed)
    std::cout << "is closed by vertices" << std::endl;
  else
    std::cout << "is not closed by vertices" << std::endl;
  if (IsPeriodic)
    std::cout << "is periodic" << std::endl;
  else
    std::cout << "is not periodic" << std::endl;

  TopOpeBRep_VPointInterIterator VPI;

  VPI.Init(LI);
  if (VPI.More())
    std::cout << std::endl;
  for (; VPI.More(); VPI.Next())
  {
    TCollection_AsciiString stol("; #draw ");
    stol = stol + VPI.CurrentVP().Tolerance() + "\n";
    LI.DumpVPoint(VPI.CurrentVPIndex(), PRODINP, stol);
  }

  VPI.Init(LI);
  if (VPI.More())
    std::cout << std::endl;
  for (; VPI.More(); VPI.Next())
  {
    const TopOpeBRep_VPointInter& VP   = VPI.CurrentVP();
    bool                          dump = VP.Keep();
    if (dump)
    {
      DumpVP(VP);
      std::cout << std::endl;
    }
  }

  if (LI.TypeLineCurve() == TopOpeBRep_LINE)
  {
    gp_Dir D = LI.LineG()->Line().Direction();
    TopOpeBRep::Print(LI.TypeLineCurve(), std::cout);
    double x, y, z;
    D.Coord(x, y, z);
    std::cout << " dir : " << x << " " << y << " " << z << std::endl;
  }

  LI.DumpLineTransitions(std::cout);

  std::cout << std::endl << "--------------------------------------------------" << std::endl;
#endif
}

#ifndef OCCT_DEBUG
void TopOpeBRep_FFDumper::DumpVP(const TopOpeBRep_VPointInter&)
{
#else
void TopOpeBRep_FFDumper::DumpVP(const TopOpeBRep_VPointInter& VP)
{
  int il = myLineIndex;
  std::cout << "VP " << VP.Index() << " on " << VP.ShapeIndex() << " :";
  double Cpar = VP.ParameterOnLine();
  std::cout << " on curve : " << Cpar;
  if (!VP.Keep())
    std::cout << " NOT kept";
  std::cout << std::endl;
  bool          k = VP.Keep();
  const gp_Pnt& P = VP.Value();
  std::cout << PRODINP << "L" << il << "P" << VP.Index();
  if (k)
    std::cout << "K";
  std::cout << " " << P.X() << " " << P.Y() << " " << P.Z();
  std::cout << "; #draw" << std::endl;

  if (VP.ShapeIndex() == 1)
    DumpVP(VP, 1);
  else if (VP.ShapeIndex() == 2)
    DumpVP(VP, 2);
  else if (VP.ShapeIndex() == 3)
  {
    DumpVP(VP, 1);
    DumpVP(VP, 2);
  }
#endif
}

#ifndef OCCT_DEBUG
void TopOpeBRep_FFDumper::DumpVP(const TopOpeBRep_VPointInter&, const int)
{
#else
void TopOpeBRep_FFDumper::DumpVP(const TopOpeBRep_VPointInter& VP, const int ISI)
{
  const occ::handle<TopOpeBRepDS_HDataStructure>& HDS  = myPFF->HDataStructure();
  const TopoDS_Edge&                              E    = TopoDS::Edge(VP.Edge(ISI));
  double                                          Epar = VP.EdgeParameter(ISI);
  TopAbs_Orientation                              O    = E.Orientation();
  TopOpeBRep_FFTransitionTool::ProcessLineTransition(VP, ISI, O);
  const TopoDS_Face F      = myPFF->Face(ISI);
  bool              Closed = TopOpeBRepTool_ShapeTool::Closed(E, F);
  bool              Degen  = BRep_Tool::Degenerated(E);
  int               exi    = ExploreIndex(E, ISI);
  int               dsi    = (HDS->HasShape(E)) ? HDS->Shape(E) : 0;
  bool              isv    = VP.IsVertex(ISI);
  if (isv)
    std::cout << "is vertex of " << ISI << std::endl;
  if (Closed)
    std::cout << "on closing edge ";
  else
    std::cout << "on edge ";
  if (Degen)
    std::cout << " on degenerated edge ";
  TopAbs::Print(O, std::cout);
  std::cout << " (ds" << dsi << ") (ex" << exi << ") of face of " << ISI;
  std::cout << " : par : " << Epar << std::endl;
  if (Closed)
    std::cout << "on closing edge ";
  else
    std::cout << "on edge ";
  if (Degen)
    std::cout << " on degenerated edge ";
  TopAbs::Print(O, std::cout);
  std::cout << " (ds" << dsi << ") (ex" << exi << ") of face of " << ISI;
#endif
}

#ifndef OCCT_DEBUG
int TopOpeBRep_FFDumper::ExploreIndex(const TopoDS_Shape&, const int) const
{
  return 0;
}
#else
int TopOpeBRep_FFDumper::ExploreIndex(const TopoDS_Shape& S, const int ISI) const
{
  int r = 0;
  if (ISI == 1)
    r = myEM1.Find(S);
  if (ISI == 2)
    r = myEM2.Find(S);
  return r;
}
#endif

#ifndef OCCT_DEBUG
void TopOpeBRep_FFDumper::DumpDSP(const TopOpeBRep_VPointInter&,
                                  const TopOpeBRepDS_Kind,
                                  const int,
                                  const bool) const
{
#else
void TopOpeBRep_FFDumper::DumpDSP(const TopOpeBRep_VPointInter& VP,
                                  const TopOpeBRepDS_Kind       GK,
                                  const int                     G,
                                  const bool                    newinDS) const
{
  std::cout << "VP " << VP.Index() << " on " << VP.ShapeIndex();
  if (newinDS)
  {
    if (GK == TopOpeBRepDS_VERTEX)
      std::cout << " gives new DSV";
    else if (GK == TopOpeBRepDS_POINT)
      std::cout << " gives new DSP";
    else
      std::cout << " gives new DS???";
  }
  else
  {
    if (GK == TopOpeBRepDS_VERTEX)
      std::cout << " equals new DSV";
    else if (GK == TopOpeBRepDS_POINT)
      std::cout << " equals new DSP";
    else
      std::cout << " equals new DS???";
  }
  std::cout << " " << G;

  const occ::handle<TopOpeBRepDS_HDataStructure>& HDS = myPFF->HDataStructure();
  double                                          tol = Precision::Confusion();
  if (GK == TopOpeBRepDS_VERTEX)
    tol = BRep_Tool::Tolerance(TopoDS::Vertex(HDS->Shape(G)));
  else if (GK == TopOpeBRepDS_POINT)
    tol = HDS->Point(G).Tolerance();
  std::cout << " tol = " << tol;
  std::cout << std::endl;
#endif
}

TopOpeBRep_PFacesFiller TopOpeBRep_FFDumper::PFacesFillerDummy() const
{
  return myPFF;
}
