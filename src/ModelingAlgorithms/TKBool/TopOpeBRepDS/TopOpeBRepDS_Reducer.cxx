

#include <TopOpeBRepDS_EIR.hpp>
#include <TopOpeBRepDS_EXPORT.hpp>
#include <TopOpeBRepDS_FIR.hpp>
#include <TopOpeBRepDS_HDataStructure.hpp>
#include <TopOpeBRepDS_Reducer.hpp>

TopOpeBRepDS_Reducer::TopOpeBRepDS_Reducer(const occ::handle<TopOpeBRepDS_HDataStructure>& HDS)
    : myHDS(HDS)
{
}

void TopOpeBRepDS_Reducer::ProcessEdgeInterferences()
{
  TopOpeBRepDS_EIR eir(myHDS);
  eir.ProcessEdgeInterferences();
}

void TopOpeBRepDS_Reducer::ProcessFaceInterferences(
  const NCollection_DataMap<TopoDS_Shape,
                            TopOpeBRepDS_ListOfShapeOn1State,
                            TopTools_ShapeMapHasher>& M)
{

  TopOpeBRepDS_FIR fir(myHDS);
  fir.ProcessFaceInterferences(M);
}
