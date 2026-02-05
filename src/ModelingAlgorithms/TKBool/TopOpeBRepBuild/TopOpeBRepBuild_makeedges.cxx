#include <TopExp.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Shape.hpp>
#include <TopOpeBRepBuild_define.hpp>
#include <TopOpeBRepBuild_EdgeBuilder.hpp>
#include <TopOpeBRepBuild_GTopo.hpp>
#include <TopOpeBRepBuild_PaveSet.hpp>
#include <TopOpeBRepBuild_SolidBuilder.hpp>
#include <TopOpeBRepDS_BuildTool.hpp>
#include <TopOpeBRepDS_HDataStructure.hpp>
#include <TopOpeBRepTool_ShapeExplorer.hpp>
#include <TopOpeBRepTool_TOOL.hpp>

#ifdef OCCT_DEBUG
extern void debfillp(const int i);

extern void debedbu(const int i)
{
  std::cout << "++ debedbu " << i << std::endl;
}
#endif

//=================================================================================================

void TopOpeBRepBuild_Builder::GPVSMakeEdges(const TopoDS_Shape&             EF,
                                            TopOpeBRepBuild_PaveSet&        PVS,
                                            NCollection_List<TopoDS_Shape>& LOE) const
{
#ifdef OCCT_DEBUG
  int  iE;
  bool tSPS = GtraceSPS(EF, iE);
  if (tSPS)
    debfillp(iE);
#endif

  TopOpeBRepBuild_PaveClassifier VCL(EF);
  bool                           equalpar = PVS.HasEqualParameters();
  if (equalpar)
    VCL.SetFirstParameter(PVS.EqualParameters());

  PVS.InitLoop();
  bool novertex = (!PVS.MoreLoop());
#ifdef OCCT_DEBUG
  if (tSPS && novertex)
    std::cout << "#--- GPVSMakeEdges : no vertex from edge " << iE << std::endl;
#endif
  if (novertex)
    return;

  TopOpeBRepBuild_EdgeBuilder EDBU;
  bool                        ForceClass = false;
  EDBU.InitEdgeBuilder(PVS, VCL, ForceClass);
  GEDBUMakeEdges(EF, EDBU, LOE);

} // GPVSMakeEdges

//=================================================================================================

void TopOpeBRepBuild_Builder::GEDBUMakeEdges(const TopoDS_Shape&             EF,
                                             TopOpeBRepBuild_EdgeBuilder&    EDBU,
                                             NCollection_List<TopoDS_Shape>& LOE) const
{
#ifdef OCCT_DEBUG
  int  iE;
  bool tSPS = GtraceSPS(EF, iE);
  if (tSPS)
  {
    std::cout << std::endl;
    GdumpSHA(EF, (char*)"#--- GEDBUMakeEdges ");
    std::cout << std::endl;
  }
  if (tSPS)
  {
    GdumpEDBU(EDBU);
  }
  if (tSPS)
  {
    debedbu(iE);
  }
#endif

  TopoDS_Shape newEdge;
  for (EDBU.InitEdge(); EDBU.MoreEdge(); EDBU.NextEdge())
  {

    int  nloop   = 0;
    bool tosplit = false;
    for (EDBU.InitVertex(); EDBU.MoreVertex(); EDBU.NextVertex())
      nloop++;
    // 0 ou 1 vertex sur edge courante => suppression edge
    if (nloop <= 1)
      continue;

    myBuildTool.CopyEdge(EF, newEdge);

    int nVF = 0, nVR = 0; // nb vertex FORWARD,REVERSED

    TopoDS_Shape VF, VR; // gestion du bit Closed
    VF.Nullify();
    VR.Nullify();

    for (EDBU.InitVertex(); EDBU.MoreVertex(); EDBU.NextVertex())
    {
      TopoDS_Shape       V    = EDBU.Vertex();
      TopAbs_Orientation Vori = V.Orientation();

      bool hassd = myDataStructure->HasSameDomain(V);
      if (hassd)
      { // on prend le vertex reference de V
        int iref = myDataStructure->SameDomainReference(V);
        V        = myDataStructure->Shape(iref);
        V.Orientation(Vori);
      }

      TopAbs_Orientation oriV = V.Orientation();
      if (oriV == TopAbs_EXTERNAL)
        continue;

      bool            equafound = false;
      TopExp_Explorer exE(newEdge, TopAbs_VERTEX);
      for (; exE.More(); exE.Next())
      {
        const TopoDS_Shape& VE    = exE.Current();
        TopAbs_Orientation  oriVE = VE.Orientation();

        if (V.IsEqual(VE))
        {
          equafound = true;
          break;
        }
        else if (oriVE == TopAbs_FORWARD || oriVE == TopAbs_REVERSED)
        {
          if (oriV == oriVE)
          {
            equafound = true;
            break;
          }
        }
        else if (oriVE == TopAbs_INTERNAL || oriVE == TopAbs_EXTERNAL)
        {
          double parV  = EDBU.Parameter();
          double parVE = BRep_Tool::Parameter(TopoDS::Vertex(VE), TopoDS::Edge(newEdge));
          if (parV == parVE)
          {
            equafound = true;
            break;
          }
        }
      }
      if (!equafound)
      {
        if (Vori == TopAbs_FORWARD)
        {
          nVF++;
          if (nVF == 1)
            VF = V;
        }
        if (Vori == TopAbs_REVERSED)
        {
          nVR++;
          if (nVR == 1)
            VR = V;
        }
        if (oriV == TopAbs_INTERNAL)
          tosplit = true;
        double parV = EDBU.Parameter();
        myBuildTool.AddEdgeVertex(newEdge, V);
        myBuildTool.Parameter(newEdge, V, parV);
      } // !equafound

    } // EDBUloop.InitVertex :  on vertices of new edge newEdge

    bool addedge = (nVF == 1 && nVR == 1);
    if (addedge)
    {
      if (tosplit)
      {
        NCollection_List<TopoDS_Shape> loe;
        bool                           ok = TopOpeBRepTool_TOOL::SplitE(TopoDS::Edge(newEdge), loe);
        if (!ok)
          tosplit = false;
        else
          LOE.Append(loe);
      }
      if (!tosplit)
        LOE.Append(newEdge);
    }
  } // EDBU.InitEdge : loop on EDBU edges

} // GEDBUMakeEdges
