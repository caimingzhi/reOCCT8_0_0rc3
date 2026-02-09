#include <BRep_Tool.hpp>
#include <BRepAdaptor_Surface.hpp>
#include <Standard_Type.hpp>
#include <TopExp.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Shape.hpp>
#include <TopOpeBRep_define.hpp>
#include <TopOpeBRep_Hctxee2d.hpp>
#include <TopOpeBRepTool_2d.hpp>
#include <TopOpeBRepTool_CurveTool.hpp>
#include <TopOpeBRepTool_GEOMETRY.hpp>
#include <TopOpeBRepTool_PROJECT.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TopOpeBRep_Hctxee2d, Standard_Transient)

#ifdef OCCT_DEBUG
  #include <GeomTools_SurfaceSet.hpp>
  #include <GeomTools_CurveSet.hpp>
  #include <GeomTools_Curve2dSet.hpp>
  #include <Geom_Curve.hpp>
Standard_EXPORT bool TopOpeBRep_GettracePROEDG();
#endif

TopOpeBRep_Hctxee2d::TopOpeBRep_Hctxee2d() = default;

void TopOpeBRep_Hctxee2d::SetEdges(const TopoDS_Edge&         E1,
                                   const TopoDS_Edge&         E2,
                                   const BRepAdaptor_Surface& BAS1,
                                   const BRepAdaptor_Surface& BAS2)
{
  const TopoDS_Face&  F1  = BAS1.Face();
  GeomAbs_SurfaceType ST1 = BAS1.GetType();
  const TopoDS_Face&  F2  = BAS2.Face();

  myEdge1 = TopoDS::Edge(E1);
  myEdge2 = TopoDS::Edge(E2);

  double   first, last, tole, tolpc;
  gp_Pnt2d pfirst, plast;

  occ::handle<Geom2d_Curve> PC1;
  PC1 = FC2D_CurveOnSurface(myEdge1, F1, first, last, tolpc);
  if (PC1.IsNull())
    throw Standard_Failure("TopOpeBRep_Hctxee2d::SetEdges : no 2d curve");
  myCurve1.Load(PC1);
  BRep_Tool::UVPoints(myEdge1, F1, pfirst, plast);
  tole = BRep_Tool::Tolerance(myEdge1);
  myDomain1.SetValues(pfirst, first, tole, plast, last, tole);

#ifdef OCCT_DEBUG
  bool trc = false;
  if (trc)
  {
    std::cout << "ed1 on fa1 : {pfirst=(" << pfirst.X() << " " << pfirst.Y() << "),first=" << first
              << "\n";
    std::cout << "              plast =(" << plast.X() << " " << plast.Y() << "),last=" << last
              << "}" << std::endl;
  }
#endif

  bool                            memesfaces  = F1.IsSame(F2);
  bool                            memesupport = false;
  TopLoc_Location                 L1, L2;
  const occ::handle<Geom_Surface> S1 = BRep_Tool::Surface(F1, L1);
  const occ::handle<Geom_Surface> S2 = BRep_Tool::Surface(F2, L2);
  if (S1 == S2 && L1 == L2)
    memesupport = true;

  if (ST1 == GeomAbs_Plane || memesfaces || memesupport)
  {
    occ::handle<Geom2d_Curve> PC2 = FC2D_CurveOnSurface(myEdge2, F1, first, last, tolpc);
    myCurve2.Load(PC2);
    BRep_Tool::UVPoints(myEdge2, F1, pfirst, plast);
    tole = BRep_Tool::Tolerance(myEdge2);
    myDomain2.SetValues(pfirst, first, tole, plast, last, tole);

#ifdef OCCT_DEBUG
    if (trc)
    {
      std::cout << "ed2 on fa1 : {pfirst=(" << pfirst.X() << " " << pfirst.Y()
                << "),first=" << first << "\n";
      std::cout << "              plast =(" << plast.X() << " " << plast.Y() << "),last=" << last
                << "}" << std::endl;
    }
#endif
  }
  else
  {

    occ::handle<Geom2d_Curve> PC2on1;
    occ::handle<Geom_Curve>   NC;
    bool                      dgE2 = BRep_Tool::Degenerated(myEdge2);
    if (dgE2)
    {
      TopExp_Explorer      exv(myEdge2, TopAbs_VERTEX);
      const TopoDS_Vertex& v2  = TopoDS::Vertex(exv.Current());
      gp_Pnt               pt2 = BRep_Tool::Pnt(v2);
      gp_Pnt2d             uv2;
      double               d;
      bool                 ok = FUN_tool_projPonF(pt2, F1, uv2, d);
      if (!ok)
        return;
      occ::handle<Geom_Surface> aS1  = BRep_Tool::Surface(F1);
      bool                      apex = FUN_tool_onapex(uv2, aS1);
      if (apex)
      {
        TopoDS_Vertex vf, vl;
        TopExp::Vertices(myEdge1, vf, vl);
        gp_Pnt        ptf  = BRep_Tool::Pnt(vf);
        double        df   = pt2.Distance(ptf);
        double        tolf = BRep_Tool::Tolerance(vf);
        bool          onf  = (df < tolf);
        TopoDS_Vertex v1   = onf ? vf : vl;
        NCollection_IndexedDataMap<TopoDS_Shape,
                                   NCollection_List<TopoDS_Shape>,
                                   TopTools_ShapeMapHasher>
          mapVE;
        TopExp::MapShapesAndAncestors(F1, TopAbs_VERTEX, TopAbs_EDGE, mapVE);
        const NCollection_List<TopoDS_Shape>&    Edsanc = mapVE.FindFromKey(v1);
        NCollection_List<TopoDS_Shape>::Iterator it(Edsanc);
        for (; it.More(); it.Next())
        {
          const TopoDS_Edge& ee   = TopoDS::Edge(it.Value());
          bool               dgee = BRep_Tool::Degenerated(ee);
          if (!dgee)
            continue;
          PC2on1 = BRep_Tool::CurveOnSurface(ee, F1, first, last);
        }
      }
      else
      {
      }
    }
    else
    {

      TopLoc_Location         loc;
      occ::handle<Geom_Curve> C = BRep_Tool::Curve(myEdge2, loc, first, last);
      NC                        = occ::down_cast<Geom_Curve>(C->Transformed(loc.Transformation()));
      double tolreached2d;
      PC2on1 = TopOpeBRepTool_CurveTool::MakePCurveOnFace(F1, NC, tolreached2d);
    }

    if (!PC2on1.IsNull())
    {
      myCurve2.Load(PC2on1);
      tole = BRep_Tool::Tolerance(myEdge2);
      PC2on1->D0(first, pfirst);
      PC2on1->D0(last, plast);
      myDomain2.SetValues(pfirst, first, tole, plast, last, tole);
#ifdef OCCT_DEBUG
      if (TopOpeBRep_GettracePROEDG())
      {
        std::cout << "------------ projection de curve" << std::endl;
        std::cout << "--- Curve : " << std::endl;
        GeomTools_CurveSet::PrintCurve(NC, std::cout);
        std::cout << "--- nouvelle PCurve : " << std::endl;
        GeomTools_Curve2dSet::PrintCurve2d(PC2on1, std::cout);
        occ::handle<Geom_Surface> aS1 = BRep_Tool::Surface(F1);
        std::cout << "--- sur surface : " << std::endl;
        GeomTools_SurfaceSet::PrintSurface(aS1, std::cout);
        std::cout << std::endl;
      }
#endif
    }
  }
}

const TopoDS_Shape& TopOpeBRep_Hctxee2d::Edge(const int Index) const
{
  if (Index == 1)
    return myEdge1;
  else if (Index == 2)
    return myEdge2;
  else
    throw Standard_Failure("TopOpeBRep_Hctxee2d::Edge");
}

const Geom2dAdaptor_Curve& TopOpeBRep_Hctxee2d::Curve(const int Index) const
{
  if (Index == 1)
    return myCurve1;
  else if (Index == 2)
    return myCurve2;
  else
    throw Standard_Failure("TopOpeBRep_Hctxee2d::Curve");
}

const IntRes2d_Domain& TopOpeBRep_Hctxee2d::Domain(const int Index) const
{
  if (Index == 1)
    return myDomain1;
  else if (Index == 2)
    return myDomain2;
  else
    throw Standard_Failure("TopOpeBRep_Hctxee2d::Domain");
}
