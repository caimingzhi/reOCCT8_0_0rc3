#include <TopOpeBRepDS_Filter.hpp>
#include <TopOpeBRepDS_HDataStructure.hpp>

TopOpeBRepDS_Filter::TopOpeBRepDS_Filter(const occ::handle<TopOpeBRepDS_HDataStructure>& HDS,
                                         const TopOpeBRepTool_PShapeClassifier&          pClassif)
    : myHDS(HDS),
      myPShapeClassif(pClassif)
{
}

void TopOpeBRepDS_Filter::ProcessInterferences()
{
  ProcessEdgeInterferences();
  ProcessCurveInterferences();
}

void TopOpeBRepDS_Filter::ProcessEdgeInterferences()
{
  TopOpeBRepDS_DataStructure& BDS = myHDS->ChangeDS();
  int                         i, nshape = BDS.NbShapes();

  for (i = 1; i <= nshape; i++)
  {
    const TopoDS_Shape& S = BDS.Shape(i);
    if (S.IsNull())
      continue;
    if (S.ShapeType() == TopAbs_EDGE)
    {
      ProcessEdgeInterferences(i);
    }
  }
}

void TopOpeBRepDS_Filter::ProcessFaceInterferences(
  const NCollection_DataMap<TopoDS_Shape,
                            TopOpeBRepDS_ListOfShapeOn1State,
                            TopTools_ShapeMapHasher>& MEsp)
{
  TopOpeBRepDS_DataStructure& BDS = myHDS->ChangeDS();
  int                         i, nshape = BDS.NbShapes();

  for (i = 1; i <= nshape; i++)
  {
    const TopoDS_Shape& S = BDS.Shape(i);
    if (S.IsNull())
      continue;
    if (S.ShapeType() == TopAbs_FACE)
    {
      ProcessFaceInterferences(i, MEsp);
    }
  }
}

void TopOpeBRepDS_Filter::ProcessCurveInterferences()
{
  TopOpeBRepDS_DataStructure& BDS = myHDS->ChangeDS();
  int                         i, ncurve = BDS.NbCurves();
  for (i = 1; i <= ncurve; i++)
  {
    ProcessCurveInterferences(i);
  }
}
