#include <BRep_Builder.hpp>
#include <BRep_Tool.hpp>
#include <TopoDS_Shape.hpp>
#include <TopOpeBRepBuild_define.hpp>
#include <TopOpeBRepBuild_FaceBuilder.hpp>
#include <TopOpeBRepBuild_GTopo.hpp>
#include <TopOpeBRepBuild_HBuilder.hpp>
#include <TopOpeBRepBuild_WireEdgeSet.hpp>
#include <TopOpeBRepDS_BuildTool.hpp>
#include <TopOpeBRepDS_CurveIterator.hpp>
#include <TopOpeBRepDS_HDataStructure.hpp>

#ifdef OCCT_DEBUG
extern bool TopOpeBRepBuild_GettraceCU();
extern bool TopOpeBRepBuild_GettraceCUV();
extern bool TopOpeBRepBuild_GettraceSPF();
extern bool TopOpeBRepBuild_GettraceSPS();
extern bool TopOpeBRepBuild_GetcontextSF2();
extern bool TopOpeBRepBuild_GettraceSHEX();
#endif

//=================================================================================================

void TopOpeBRepBuild_Builder::BuildFaces(const int                                       iS,
                                         const occ::handle<TopOpeBRepDS_HDataStructure>& HDS)
{
  double       aTBSTol, aTBCTol;
  BRep_Builder aBB;
  TopoDS_Shape aFace;
  //
  // modified by NIZNHY-PKV Mon Dec 13 10:00:23 2010f
  const TopOpeBRepDS_Surface& aTBS = HDS->Surface(iS);
  aTBSTol                          = aTBS.Tolerance();
  //
  myBuildTool.MakeFace(aFace, aTBS);
  //
  // myBuildTool.MakeFace(aFace,HDS->Surface(iS));
  // modified by NIZNHY-PKV Mon Dec 13 10:01:03 2010t
  //
  TopOpeBRepBuild_WireEdgeSet WES(aFace, this);
  //
#ifdef OCCT_DEBUG
  bool tSE = TopOpeBRepBuild_GettraceSPF();
#endif
  //
  TopOpeBRepDS_CurveIterator SCurves(HDS->SurfaceCurves(iS));
  for (; SCurves.More(); SCurves.Next())
  {
    int                       iC  = SCurves.Current();
    const TopOpeBRepDS_Curve& CDS = HDS->Curve(iC);
#ifdef OCCT_DEBUG
    if (tSE)
      std::cout << std::endl << "BuildFaces : C " << iC << " on S " << iS << std::endl;
#endif
    TopoDS_Shape                             anEdge;
    NCollection_List<TopoDS_Shape>::Iterator Iti(NewEdges(iC));
    for (; Iti.More(); Iti.Next())
    {
      anEdge = Iti.Value();
      // modified by NIZNHY-PKV Mon Dec 13 10:09:38 2010f
      TopoDS_Edge& aE = *((TopoDS_Edge*)&anEdge);
      aTBCTol         = BRep_Tool::Tolerance(aE);
      if (aTBCTol < aTBSTol)
      {
        aBB.UpdateEdge(aE, aTBSTol);
      }
      // modified by NIZNHY-PKV Mon Dec 13 10:09:43 2010f
      TopAbs_Orientation ori = SCurves.Orientation(TopAbs_IN);
      myBuildTool.Orientation(anEdge, ori);
      const occ::handle<Geom2d_Curve>& PC = SCurves.PCurve();
      myBuildTool.PCurve(aFace, anEdge, CDS, PC);
      WES.AddStartElement(anEdge);
    }
  }
  //
  TopOpeBRepBuild_FaceBuilder     FABU(WES, aFace);
  NCollection_List<TopoDS_Shape>& FaceList = ChangeNewFaces(iS);
  MakeFaces(aFace, FABU, FaceList);
}

//=================================================================================================

void TopOpeBRepBuild_Builder::BuildFaces(const occ::handle<TopOpeBRepDS_HDataStructure>& HDS)
{
  int iS, n = HDS->NbSurfaces();
  myNewFaces = new NCollection_HArray1<NCollection_List<TopoDS_Shape>>(0, n);
  for (iS = 1; iS <= n; iS++)
    BuildFaces(iS, HDS);
}
