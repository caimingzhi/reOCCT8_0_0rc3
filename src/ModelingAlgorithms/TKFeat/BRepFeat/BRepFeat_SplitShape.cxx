#include <BRepFeat_SplitShape.hpp>
#include <LocOpe_WiresOnShape.hpp>
#include <TopoDS_Shape.hpp>
#include <TopExp_Explorer.hpp>

void BRepFeat_SplitShape::Build(const Message_ProgressRange&)
{
  mySShape.Perform(myWOnShape);
  if (mySShape.IsDone())
  {
    Done();
    myShape = mySShape.ResultingShape();
    myRight.Clear();
  }
}

const NCollection_List<TopoDS_Shape>& BRepFeat_SplitShape::DirectLeft() const
{
  return mySShape.DirectLeft();
}

const NCollection_List<TopoDS_Shape>& BRepFeat_SplitShape::Left() const
{
  return mySShape.Left();
}

const NCollection_List<TopoDS_Shape>& BRepFeat_SplitShape::Right() const
{
  if (myRight.IsEmpty())
  {
    NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> aMapOfLeft;
    NCollection_List<TopoDS_Shape>::Iterator               anIterator;
    for (anIterator.Initialize(mySShape.Left()); anIterator.More(); anIterator.Next())
    {
      aMapOfLeft.Add(anIterator.Value());
    }
    TopExp_Explorer anExplorer;
    for (anExplorer.Init(myShape, TopAbs_FACE); anExplorer.More(); anExplorer.Next())
    {
      const TopoDS_Shape& aFace = anExplorer.Current();
      if (!aMapOfLeft.Contains(aFace))
        myRight.Append(aFace);
    }
  }
  return myRight;
}

bool BRepFeat_SplitShape::IsDeleted(const TopoDS_Shape& F)
{
  NCollection_List<TopoDS_Shape>::Iterator itl(((LocOpe_Spliter*)&mySShape)->DescendantShapes(F));

  return (!itl.More());
}

const NCollection_List<TopoDS_Shape>& BRepFeat_SplitShape::Modified(const TopoDS_Shape& F)
{
  return mySShape.DescendantShapes(F);
}
