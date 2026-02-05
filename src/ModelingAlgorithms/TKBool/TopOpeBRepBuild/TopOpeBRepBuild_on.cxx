#include <TopOpeBRepBuild_BuilderON.hpp>
#include <TopOpeBRepBuild_define.hpp>
#include <TopOpeBRepBuild_GTopo.hpp>
#include <TopOpeBRepBuild_WireEdgeSet.hpp>
#include <TopOpeBRepDS_CurveIterator.hpp>

// Standard_IMPORT extern bool GLOBAL_faces2d;
extern bool GLOBAL_faces2d;

//=================================================================================================

void TopOpeBRepBuild_Builder::GFillONPartsWES(const TopoDS_Shape&                   FOR,
                                              const TopOpeBRepBuild_GTopo&          G,
                                              const NCollection_List<TopoDS_Shape>& LSclass,
                                              TopOpeBRepBuild_WireEdgeSet&          WES)
{
  TopOpeBRepBuild_BuilderON BON;
  if (GLOBAL_faces2d)
    BON.Perform2d(this,
                  FOR,
                  (TopOpeBRepBuild_PGTopo)&G,
                  (TopOpeBRepTool_Plos)&LSclass,
                  (TopOpeBRepBuild_PWireEdgeSet)&WES);
  else
    BON.Perform(this,
                FOR,
                (TopOpeBRepBuild_PGTopo)&G,
                (TopOpeBRepTool_Plos)&LSclass,
                (TopOpeBRepBuild_PWireEdgeSet)&WES);
}
