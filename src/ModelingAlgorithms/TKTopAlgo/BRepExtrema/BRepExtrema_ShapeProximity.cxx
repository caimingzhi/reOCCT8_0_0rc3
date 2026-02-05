#include <BRepExtrema_ShapeProximity.hpp>

#include <Precision.hpp>
#include <TopExp_Explorer.hpp>

// Assign a map of sub-shapes (edges/faces) of a given shape
static bool initSubShapes(const TopoDS_Shape&                   theShape,
                          NCollection_Vector<TopoDS_Shape>&     theSubshapesList,
                          occ::handle<BRepExtrema_TriangleSet>& theTriangleSet)
{
  theSubshapesList.Clear();

  for (TopExp_Explorer anIter(theShape, TopAbs_FACE); anIter.More(); anIter.Next())
  {
    theSubshapesList.Append(anIter.Current());
  }

  for (TopExp_Explorer anIter(theShape, TopAbs_EDGE); anIter.More(); anIter.Next())
  {
    theSubshapesList.Append(anIter.Current());
  }

  if (theTriangleSet.IsNull())
    theTriangleSet = new BRepExtrema_TriangleSet;
  return theTriangleSet->Init(theSubshapesList);
}

//=======================================================================
// function : BRepExtrema_ShapeProximity
// purpose  : Creates uninitialized proximity tool
//=======================================================================
BRepExtrema_ShapeProximity::BRepExtrema_ShapeProximity(const double theTolerance)
    : myTolerance(theTolerance),
      myElementSet1(new BRepExtrema_TriangleSet),
      myElementSet2(new BRepExtrema_TriangleSet),
      myNbSamples1(0),
      myNbSamples2(0)
{
  // Should be initialized later
  myIsInitS1 = myIsInitS2 = false;
}

//=======================================================================
// function : BRepExtrema_ShapeProximity
// purpose  : Creates proximity tool for the given two shapes
//=======================================================================
BRepExtrema_ShapeProximity::BRepExtrema_ShapeProximity(const TopoDS_Shape& theShape1,
                                                       const TopoDS_Shape& theShape2,
                                                       const double        theTolerance)
    : myTolerance(theTolerance),
      myElementSet1(new BRepExtrema_TriangleSet),
      myElementSet2(new BRepExtrema_TriangleSet),
      myNbSamples1(0),
      myNbSamples2(0)
{
  LoadShape1(theShape1);
  LoadShape2(theShape2);
}

//=======================================================================
// function : LoadShape1
// purpose  : Loads 1st shape into proximity tool
//=======================================================================
bool BRepExtrema_ShapeProximity::LoadShape1(const TopoDS_Shape& theShape1)
{
  myIsInitS1 = initSubShapes(theShape1, myShapeList1, myElementSet1);

  if (myTolerance == Precision::Infinite())
  {
    myProxValTool.MarkDirty();
  }
  else
  {
    myOverlapTool.MarkDirty();
  }

  return myIsInitS1;
}

//=======================================================================
// function : LoadShape2
// purpose  : Loads 2nd shape into proximity tool
//=======================================================================
bool BRepExtrema_ShapeProximity::LoadShape2(const TopoDS_Shape& theShape2)
{
  myIsInitS2 = initSubShapes(theShape2, myShapeList2, myElementSet2);

  if (myTolerance == Precision::Infinite())
  {
    myProxValTool.MarkDirty();
  }
  else
  {
    myOverlapTool.MarkDirty();
  }

  return myIsInitS2;
}

//=======================================================================
// function : Perform
// purpose  : Performs search of overlapped faces
//=======================================================================
void BRepExtrema_ShapeProximity::Perform()
{
  if (myTolerance == Precision::Infinite())
  {
    if (!myIsInitS1 || !myIsInitS2 || myProxValTool.IsDone())
    {
      return;
    }

    myProxValTool.LoadTriangleSets(myElementSet1, myElementSet2);
    myProxValTool.LoadShapeLists(myShapeList1, myShapeList2);
    myProxValTool.SetNbSamplePoints(myNbSamples1, myNbSamples2);

    myProxValTool.Perform(myTolerance);
    myProxValTool.ProximityPoints(myProxPoint1, myProxPoint2);
    myProxValTool.ProximityPointsStatus(myProxPntStatus1, myProxPntStatus2);
  }
  else
  {
    if (!myIsInitS1 || !myIsInitS2 || myOverlapTool.IsDone())
    {
      return;
    }

    myOverlapTool.LoadTriangleSets(myElementSet1, myElementSet2);

    myOverlapTool.Perform(myTolerance);
  }
}
