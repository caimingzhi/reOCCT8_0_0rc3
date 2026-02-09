

#include <BRepTools_PurgeLocations.hpp>
#include <TopoDS_Iterator.hpp>
#include <NCollection_Vector.hpp>
#include <BRepTools.hpp>
#include <BRepTools_TrsfModification.hpp>
#include <BRepTools_Modifier.hpp>
#include <TopLoc_Datum3D.hpp>

BRepTools_PurgeLocations::BRepTools_PurgeLocations()
    : myDone(false)
{
}

bool BRepTools_PurgeLocations::Perform(const TopoDS_Shape& theShape)
{
  myShape = theShape;
  myMapShapes.Clear();
  myLocations.Clear();
  myDone = true;
  AddShape(myShape);

  int                     ind;
  NCollection_Vector<int> aBadTrsfInds;
  for (ind = 1;; ++ind)
  {
    const TopLoc_Location& aLoc = myLocations.Location(ind);

    if (aLoc.IsIdentity())
      break;

    const gp_Trsf& aTrsf = aLoc.Transformation();
    bool           isBadTrsf =
      aTrsf.IsNegative()
      || (std::abs(std::abs(aTrsf.ScaleFactor()) - 1.) > TopLoc_Location::ScalePrec());
    if (isBadTrsf)
    {
      aBadTrsfInds.Append(ind);
    }
  }

  if (aBadTrsfInds.IsEmpty())
  {
    return myDone;
  }

  int aNbShapes = myMapShapes.Extent();
  myMapNewShapes.Clear();
  int inds;
  for (inds = 1; inds <= aNbShapes; ++inds)
  {
    const TopoDS_Shape& anS     = myMapShapes(inds);
    int                 aLocInd = myLocations.Index(anS.Location());
    if (aLocInd == 0)
    {
      continue;
    }
    int il;
    for (il = 0; il < aBadTrsfInds.Size(); ++il)
    {
      if (aBadTrsfInds(il) == aLocInd)
      {
        TopoDS_Shape aTrS;
        bool         isDone = PurgeLocation(anS, aTrS);
        myDone              = myDone && isDone;
        myMapNewShapes.Bind(anS, aTrS);
        break;
      }
    }
  }

  if (myReShape.IsNull())
  {
    myReShape = new BRepTools_ReShape;
  }
  else
  {
    myReShape->Clear();
  }
  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>::Iterator anIter(
    myMapNewShapes);
  for (; anIter.More(); anIter.Next())
  {
    const TopoDS_Shape& anOldS = anIter.Key();
    const TopoDS_Shape& aNewS  = anIter.Value();
    myReShape->Replace(anOldS, aNewS);
  }

  myShape = myReShape->Apply(myShape);

  return myDone;
}

bool BRepTools_PurgeLocations::PurgeLocation(const TopoDS_Shape& theS, TopoDS_Shape& theRes)
{
  bool            isDone  = true;
  TopLoc_Location aRefLoc = theS.Location();
  bool            isEmpty = aRefLoc.IsIdentity();
  if (isEmpty)
  {
    theRes = theS;
    return isDone;
  }

  TopLoc_Location aNullLoc;
  theRes = theS.Located(aNullLoc);

  while (!isEmpty)
  {
    const occ::handle<TopLoc_Datum3D>& aFD   = aRefLoc.FirstDatum();
    gp_Trsf                            aTrsf = aFD->Trsf();
    int                                aFP   = aRefLoc.FirstPower();
    bool                               isBad = aTrsf.IsNegative()
                 || (std::abs(std::abs(aTrsf.ScaleFactor()) - 1.) > TopLoc_Location::ScalePrec());
    TopLoc_Location aLoc(aFD);
    aLoc  = aLoc.Powered(aFP);
    aTrsf = aLoc.Transformation();
    if (isBad)
    {
      occ::handle<BRepTools_TrsfModification> aModification = new BRepTools_TrsfModification(aTrsf);
      BRepTools_Modifier                      aModifier(theRes, aModification);
      if (aModifier.IsDone())
      {
        theRes = aModifier.ModifiedShape(theRes);
      }
      else
      {
        isDone = false;
        theRes = theRes.Moved(aLoc);
      }
    }
    else
    {
      theRes = theRes.Moved(aLoc);
    }

    aRefLoc = aRefLoc.NextLocation();
    isEmpty = aRefLoc.IsIdentity();
  }

  return isDone;
}

void BRepTools_PurgeLocations::AddShape(const TopoDS_Shape& theS)
{
  myMapShapes.Add(theS);
  myLocations.Add(theS.Location());

  TopoDS_Iterator It(theS, false, false);
  while (It.More())
  {
    AddShape(It.Value());
    It.Next();
  }
}

const TopoDS_Shape& BRepTools_PurgeLocations::GetResult() const
{
  return myShape;
}

bool BRepTools_PurgeLocations::IsDone() const
{
  return myDone;
}

TopoDS_Shape BRepTools_PurgeLocations::ModifiedShape(const TopoDS_Shape& theInitShape) const
{
  TopoDS_Shape aShape = theInitShape;
  if (myMapNewShapes.IsBound(theInitShape))
    aShape = myMapNewShapes.Find(theInitShape);
  return aShape;
}
