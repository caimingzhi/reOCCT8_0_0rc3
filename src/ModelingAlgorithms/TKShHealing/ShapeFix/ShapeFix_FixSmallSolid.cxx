

#include <BRep_Builder.hpp>
#include <BRepGProp.hpp>
#include <GProp_GProps.hpp>
#include <Message_Msg.hpp>
#include <ShapeBuild_ReShape.hpp>
#include <ShapeFix_FixSmallSolid.hpp>
#include <Standard_Type.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS_Builder.hpp>
#include <TopoDS_Compound.hpp>
#include <TopoDS_Iterator.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <NCollection_Map.hpp>

IMPLEMENT_STANDARD_RTTIEXT(ShapeFix_FixSmallSolid, ShapeFix_Root)

ShapeFix_FixSmallSolid::ShapeFix_FixSmallSolid()
    : myFixMode(0),
      myVolumeThreshold(Precision::Infinite()),
      myWidthFactorThreshold(Precision::Infinite())
{
}

void ShapeFix_FixSmallSolid::SetFixMode(const int theMode)
{
  myFixMode = (theMode < 0 || theMode > 2) ? 0 : theMode;
}

void ShapeFix_FixSmallSolid::SetVolumeThreshold(const double theThreshold)
{
  myVolumeThreshold = theThreshold >= 0.0 ? theThreshold : Precision::Infinite();
}

void ShapeFix_FixSmallSolid::SetWidthFactorThreshold(const double theThreshold)
{
  myWidthFactorThreshold = theThreshold >= 0.0 ? theThreshold : Precision::Infinite();
}

static bool IsValidInput(const TopoDS_Shape& theShape)
{
  if (theShape.IsNull())
    return false;

  switch (theShape.ShapeType())
  {
    case TopAbs_COMPOUND:
    case TopAbs_COMPSOLID:
    case TopAbs_SOLID:
      return true;
    default:
      return false;
  }
}

TopoDS_Shape ShapeFix_FixSmallSolid::Remove(const TopoDS_Shape&                    theShape,
                                            const occ::handle<ShapeBuild_ReShape>& theContext) const
{

  if (!IsThresholdsSet() || !IsValidInput(theShape))
    return theShape;

  TopExp_Explorer aSolidIter(theShape, TopAbs_SOLID);
  for (; aSolidIter.More(); aSolidIter.Next())
  {
    const TopoDS_Shape& aSolid = aSolidIter.Current();
    if (IsSmall(aSolid))
    {
      theContext->Remove(aSolid);
      SendWarning(aSolid, Message_Msg("ShapeFix.FixSmallSolid.MSG0"));
    }
  }

  return theContext->Apply(theShape);
}

static double ShapeArea(const TopoDS_Shape& theShape)
{
  GProp_GProps aProps;
  BRepGProp::SurfaceProperties(theShape, aProps);
  return aProps.Mass();
}

static double ShapeVolume(const TopoDS_Shape& theShape)
{
  GProp_GProps aProps;
  BRepGProp::VolumeProperties(theShape, aProps);
  return aProps.Mass();
}

static void AddToMap(
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>&
                      theMap,
  const TopoDS_Shape& theKey,
  const TopoDS_Shape& theItem)
{
  NCollection_List<TopoDS_Shape>* aListPtr = theMap.ChangeSeek(theKey);
  if (aListPtr == nullptr)
  {
    NCollection_List<TopoDS_Shape> aList;
    aList.Append(theItem);
    theMap.Bind(theKey, aList);
  }
  else
    aListPtr->Append(theItem);
}

static void AddToMap(
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>&
                                  theMap,
  const TopoDS_Shape&             theKey,
  NCollection_List<TopoDS_Shape>& theItems)
{
  if (theItems.IsEmpty())
    return;

  NCollection_List<TopoDS_Shape>* aListPtr = theMap.ChangeSeek(theKey);
  if (aListPtr == nullptr)
    theMap.Bind(theKey, theItems);
  else
    aListPtr->Append(theItems);
}

static void MapFacesToShells(
  const TopoDS_Shape&                                                       theSolid,
  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>& theMap)
{
  TopoDS_Iterator aShellIter(theSolid);
  for (; aShellIter.More(); aShellIter.Next())
  {
    const TopoDS_Shape& aShell = aShellIter.Value();
    if (aShell.ShapeType() != TopAbs_SHELL)
      continue;

    TopoDS_Iterator aFaceIter(aShell);
    for (; aFaceIter.More(); aFaceIter.Next())
    {
      const TopoDS_Shape& aFace = aFaceIter.Value();
      if (aFace.ShapeType() != TopAbs_FACE)
        continue;

      if (!theMap.Bind(aFace, aShell))
        theMap.UnBind(aFace);
    }
  }
}

static bool FindMostSharedShell(
  const TopoDS_Shape& theSolid,
  const NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>&
                                  theMapFacesToOuterShells,
  TopoDS_Shape&                   theMostSharedOuterShell,
  TopoDS_Shape&                   theMostSharedSolidShell,
  NCollection_List<TopoDS_Shape>& theOtherSolidShells)
{
  NCollection_DataMap<TopoDS_Shape, double, TopTools_ShapeMapHasher> aSharedAreas;
  double                                                             aMaxSharedArea = 0.0;
  const TopoDS_Shape* aMostSharedOuterShellPtr                                      = nullptr;
  const TopoDS_Shape* aMostSharedSolidShellPtr                                      = nullptr;

  TopoDS_Iterator aShellIter(theSolid);
  for (; aShellIter.More(); aShellIter.Next())
  {
    const TopoDS_Shape& aSolidShell = aShellIter.Value();
    if (aSolidShell.ShapeType() != TopAbs_SHELL)
      continue;

    theOtherSolidShells.Append(aSolidShell);

    TopoDS_Iterator aFaceIter(aSolidShell);
    for (; aFaceIter.More(); aFaceIter.Next())
    {
      const TopoDS_Shape& aFace = aFaceIter.Value();
      if (aFace.ShapeType() != TopAbs_FACE)
        continue;

      const TopoDS_Shape* anOuterShellPtr = theMapFacesToOuterShells.Seek(aFace);
      if (anOuterShellPtr == nullptr)
        continue;
      const TopoDS_Shape& anOuterShell = *anOuterShellPtr;

      double  anArea         = ShapeArea(aFace);
      double* aSharedAreaPtr = aSharedAreas.ChangeSeek(anOuterShell);
      if (aSharedAreaPtr == nullptr)
        aSharedAreas.Bind(anOuterShell, anArea);
      else
        anArea = (*aSharedAreaPtr) += anArea;

      if (aMaxSharedArea < anArea)
      {
        aMaxSharedArea           = anArea;
        aMostSharedOuterShellPtr = &anOuterShell;
        aMostSharedSolidShellPtr = &aSolidShell;
      }
    }
  }

  if (aMostSharedSolidShellPtr == nullptr)
    return false;

  theMostSharedOuterShell = *aMostSharedOuterShellPtr;
  theMostSharedSolidShell = *aMostSharedSolidShellPtr;

  NCollection_List<TopoDS_Shape>::Iterator anOtherShellIter(theOtherSolidShells);
  while (!anOtherShellIter.Value().IsSame(theMostSharedSolidShell))
    anOtherShellIter.Next();
  theOtherSolidShells.Remove(anOtherShellIter);

  return true;
}

static TopoDS_Shape MergeShells(
  const TopoDS_Shape&             theBaseShell,
  NCollection_List<TopoDS_Shape>& theShellsToMerge,
  const NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>&
    theMapFacesToOuterShells,
  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>&
    theMapNewFreeFacesToShells)
{

  BRep_Builder aBuilder;
  TopoDS_Shape aNewShell = theBaseShell.EmptyCopied();

  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> aRemoveFaces;
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> aNewFreeFaces;

  NCollection_List<TopoDS_Shape>::Iterator aShellIter(theShellsToMerge);
  for (; aShellIter.More(); aShellIter.Next())
  {
    TopoDS_Iterator aFaceIter(aShellIter.Value());
    for (; aFaceIter.More(); aFaceIter.Next())
    {
      const TopoDS_Shape& aFace = aFaceIter.Value();

      if (aFace.ShapeType() != TopAbs_FACE)
      {
        aBuilder.Add(aNewShell, aFace);
        continue;
      }

      const TopoDS_Shape* anOuterShellPtr = theMapFacesToOuterShells.Seek(aFace);
      if (anOuterShellPtr != nullptr)
      {
        if (anOuterShellPtr->IsSame(theBaseShell))
          aRemoveFaces.Add(aFace);
        else
          aBuilder.Add(aNewShell, aFace);
      }
      else
      {
        if (aNewFreeFaces.Contains(aFace))
          aNewFreeFaces.Remove(aFace);
        else
          aNewFreeFaces.Add(aFace);
      }
    }
  }
  theShellsToMerge.Clear();

  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>::Iterator aNewFaceIter(aNewFreeFaces);
  for (; aNewFaceIter.More(); aNewFaceIter.Next())
  {
    const TopoDS_Shape& aFace = aNewFaceIter.Key();
    aBuilder.Add(aNewShell, aFace);
    theMapNewFreeFacesToShells.Bind(aFace, aNewShell);
  }
  aNewFreeFaces.Clear();

  TopoDS_Iterator aBaseFaceIter(theBaseShell);
  for (; aBaseFaceIter.More(); aBaseFaceIter.Next())
  {
    const TopoDS_Shape& aFace = aBaseFaceIter.Value();
    if (!aRemoveFaces.Contains(aFace))
      aBuilder.Add(aNewShell, aFace);
  }

  if (aNewShell.NbChildren() == 0)
    return TopoDS_Shape();

  return aNewShell;
}

static TopoDS_Compound AddShells(const TopoDS_Shape&             theBaseShell,
                                 NCollection_List<TopoDS_Shape>& theShellsToAdd)
{

  BRep_Builder    aBuilder;
  TopoDS_Compound aCompound;
  aBuilder.MakeCompound(aCompound);

  if (!theBaseShell.IsNull())
    aBuilder.Add(aCompound, theBaseShell);

  NCollection_List<TopoDS_Shape>::Iterator aShellIter(theShellsToAdd);
  for (; aShellIter.More(); aShellIter.Next())
    aBuilder.Add(aCompound, aShellIter.Value());

  theShellsToAdd.Clear();

  return aCompound;
}

TopoDS_Shape ShapeFix_FixSmallSolid::Merge(const TopoDS_Shape&                    theShape,
                                           const occ::handle<ShapeBuild_ReShape>& theContext) const
{

  if (!IsThresholdsSet() || !IsValidInput(theShape))
    return theShape;

  NCollection_List<TopoDS_Shape>                                           aSmallSolids;
  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher> aMapFacesToShells;

  TopExp_Explorer aSolidIter(theShape, TopAbs_SOLID);
  for (; aSolidIter.More(); aSolidIter.Next())
  {
    const TopoDS_Shape& aSolid = aSolidIter.Current();
    if (IsSmall(aSolid))
      aSmallSolids.Append(aSolid);
    else
      MapFacesToShells(aSolid, aMapFacesToShells);
  }

  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>  aNewMapFacesToShells;
  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>* aMapFacesToShellsPtr =
    &aMapFacesToShells;
  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>*
    aNewMapFacesToShellsPtr = &aNewMapFacesToShells;
  while (!aSmallSolids.IsEmpty())
  {

    NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
                                             aShellsToMerge, aShellsToAdd;
    NCollection_List<TopoDS_Shape>::Iterator aSmallIter(aSmallSolids);
    while (aSmallIter.More())
    {
      const TopoDS_Shape& aSmallSolid = aSmallIter.Value();

      TopoDS_Shape                   aNonSmallSolidShell;
      TopoDS_Shape                   anAdjacentShell;
      NCollection_List<TopoDS_Shape> aNotAdjacentShells;
      if (FindMostSharedShell(aSmallSolid,
                              *aMapFacesToShellsPtr,
                              aNonSmallSolidShell,
                              anAdjacentShell,
                              aNotAdjacentShells))
      {

        AddToMap(aShellsToMerge, aNonSmallSolidShell, anAdjacentShell);
        AddToMap(aShellsToAdd, aNonSmallSolidShell, aNotAdjacentShells);

        theContext->Remove(aSmallSolid);
        SendWarning(aSmallSolid, Message_Msg("ShapeFix.FixSmallSolid.MSG1"));

        aSmallSolids.Remove(aSmallIter);
      }
      else
        aSmallIter.Next();
    }

    if (aShellsToMerge.IsEmpty())
      break;

    NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>::
      Iterator aShellIter(aShellsToMerge);
    for (; aShellIter.More(); aShellIter.Next())
    {

      const TopoDS_Shape&             aBaseShell = aShellIter.Key();
      NCollection_List<TopoDS_Shape>& aShellsToBeMerged =
        (NCollection_List<TopoDS_Shape>&)aShellIter.Value();
      NCollection_List<TopoDS_Shape>* aShellsToBeAddedPtr = aShellsToAdd.ChangeSeek(aBaseShell);

      TopoDS_Shape aNewShell =
        MergeShells(aBaseShell, aShellsToBeMerged, *aMapFacesToShellsPtr, *aNewMapFacesToShellsPtr);

      if (aShellsToBeAddedPtr != nullptr)
        aNewShell = AddShells(aNewShell, *aShellsToBeAddedPtr);

      theContext->Replace(aBaseShell, aNewShell);
    }

    aMapFacesToShellsPtr->Clear();
    std::swap(aMapFacesToShellsPtr, aNewMapFacesToShellsPtr);
  }

  return theContext->Apply(theShape);
}

bool ShapeFix_FixSmallSolid::IsThresholdsSet() const
{
  return (IsUsedVolumeThreshold() && myVolumeThreshold < Precision::Infinite())
         || (IsUsedWidthFactorThreshold() && myWidthFactorThreshold < Precision::Infinite());
}

bool ShapeFix_FixSmallSolid::IsSmall(const TopoDS_Shape& theSolid) const
{

  double aVolume = ShapeVolume(theSolid);
  if (IsUsedVolumeThreshold() && aVolume > myVolumeThreshold)
    return false;

  if (IsUsedWidthFactorThreshold() && myWidthFactorThreshold < Precision::Infinite())
  {
    double anArea = ShapeArea(theSolid);
    if (aVolume > myWidthFactorThreshold * anArea * 0.5)
      return false;
  }

  return true;
}

bool ShapeFix_FixSmallSolid::IsUsedWidthFactorThreshold() const
{
  return myFixMode == 0 || myFixMode == 1;
}

bool ShapeFix_FixSmallSolid::IsUsedVolumeThreshold() const
{
  return myFixMode == 0 || myFixMode == 2;
}
