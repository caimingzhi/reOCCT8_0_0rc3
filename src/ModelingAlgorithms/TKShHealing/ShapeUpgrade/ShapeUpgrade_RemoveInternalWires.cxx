

#include <Precision.hpp>
#include <ShapeAnalysis.hpp>
#include <ShapeBuild_ReShape.hpp>
#include <ShapeExtend_WireData.hpp>
#include <ShapeUpgrade_RemoveInternalWires.hpp>
#include <Standard_Type.hpp>
#include <TopExp.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Iterator.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDS_Wire.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <NCollection_IndexedMap.hpp>
#include <NCollection_Sequence.hpp>

IMPLEMENT_STANDARD_RTTIEXT(ShapeUpgrade_RemoveInternalWires, ShapeUpgrade_Tool)

ShapeUpgrade_RemoveInternalWires::ShapeUpgrade_RemoveInternalWires()
{
  myMinArea                                = 0.;
  myRemoveFacesMode                        = true;
  myStatus                                 = ShapeExtend::EncodeStatus(ShapeExtend_OK);
  occ::handle<ShapeBuild_ReShape> aContext = new ShapeBuild_ReShape;
  SetContext(aContext);
}

ShapeUpgrade_RemoveInternalWires::ShapeUpgrade_RemoveInternalWires(const TopoDS_Shape& theShape)
{
  occ::handle<ShapeBuild_ReShape> aContext = new ShapeBuild_ReShape;
  SetContext(aContext);
  Init(theShape);
}

void ShapeUpgrade_RemoveInternalWires::Init(const TopoDS_Shape& theShape)
{
  myShape = theShape;
  Context()->Apply(theShape);
  TopExp::MapShapesAndAncestors(myShape, TopAbs_EDGE, TopAbs_FACE, myEdgeFaces);
  myStatus          = ShapeExtend::EncodeStatus(ShapeExtend_OK);
  myMinArea         = 0.;
  myRemoveFacesMode = true;
}

bool ShapeUpgrade_RemoveInternalWires::Perform()
{
  Clear();
  if (myShape.IsNull())
  {
    myStatus |= ShapeExtend::EncodeStatus(ShapeExtend_FAIL1);
    return false;
  }
  TopExp_Explorer aExpF(myShape, TopAbs_FACE);
  for (; aExpF.More(); aExpF.Next())
  {
    TopoDS_Face aF = TopoDS::Face(aExpF.Current());
    removeSmallWire(aF, TopoDS_Wire());
  }
  if (myRemoveFacesMode)
    removeSmallFaces();

  myResult = Context()->Apply(myShape);
  return Status(ShapeExtend_DONE);
}

bool ShapeUpgrade_RemoveInternalWires::Perform(
  const NCollection_Sequence<TopoDS_Shape>& theSeqShapes)
{
  if (myShape.IsNull())
  {
    myStatus |= ShapeExtend::EncodeStatus(ShapeExtend_FAIL1);
    return false;
  }
  Clear();
  NCollection_IndexedDataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
      aWireFaces;
  int i = 1, nb = theSeqShapes.Length();
  for (; i <= nb; i++)
  {
    const TopoDS_Shape& aS = theSeqShapes.Value(i);
    if (aS.ShapeType() == TopAbs_FACE)
      removeSmallWire(aS, TopoDS_Wire());
    else if (aS.ShapeType() == TopAbs_WIRE)
    {
      if (!aWireFaces.Extent())
        TopExp::MapShapesAndAncestors(myShape, TopAbs_WIRE, TopAbs_FACE, aWireFaces);
      if (aWireFaces.Contains(aS))
      {
        const NCollection_List<TopoDS_Shape>&    alfaces = aWireFaces.FindFromKey(aS);
        NCollection_List<TopoDS_Shape>::Iterator liter(alfaces);
        for (; liter.More(); liter.Next())
          removeSmallWire(liter.Value(), aS);
      }
    }
  }
  if (myRemoveFacesMode)
    removeSmallFaces();
  myResult = Context()->Apply(myShape);
  return Status(ShapeExtend_DONE);
}

void ShapeUpgrade_RemoveInternalWires::removeSmallWire(const TopoDS_Shape& theFace,
                                                       const TopoDS_Shape& theWire)
{
  TopoDS_Face     aF     = TopoDS::Face(theFace);
  TopoDS_Wire     anOutW = ShapeAnalysis::OuterWire(aF);
  TopoDS_Iterator aIt(aF);
  for (; aIt.More(); aIt.Next())
  {
    if (aIt.Value().ShapeType() != TopAbs_WIRE || aIt.Value().IsSame(anOutW))
      continue;

    TopoDS_Wire aW = TopoDS::Wire(aIt.Value());
    if (!theWire.IsNull() && !theWire.IsSame(aW))
      continue;
    double anArea = ShapeAnalysis::ContourArea(aW);
    if (anArea < myMinArea - Precision::Confusion())
    {
      Context()->Remove(aW);
      myRemoveWires.Append(aW);
      myStatus |= ShapeExtend::EncodeStatus(ShapeExtend_DONE1);
      if (!myRemoveFacesMode)
        continue;

      TopoDS_Iterator aIte(aW, false);
      for (; aIte.More(); aIte.Next())
      {
        const TopoDS_Shape& aE = aIte.Value();
        if (myRemoveEdges.IsBound(aE))
          myRemoveEdges.ChangeFind(aE).Append(aF);
        else
        {
          NCollection_List<TopoDS_Shape> alfaces;
          alfaces.Append(aF);
          myRemoveEdges.Bind(aE, alfaces);
        }
      }
    }
  }
}

void ShapeUpgrade_RemoveInternalWires::removeSmallFaces()
{

  int i = 1;
  for (; i <= myRemoveWires.Length(); i++)
  {
    TopoDS_Shape                                                  aWire = myRemoveWires.Value(i);
    TopoDS_Iterator                                               aIte(aWire, false);
    NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> aFaceCandidates;

    for (; aIte.More(); aIte.Next())
    {

      const TopoDS_Shape& aEdge = aIte.Value();
      if (!myEdgeFaces.Contains(aEdge))
      {
        myStatus |= ShapeExtend::EncodeStatus(ShapeExtend_FAIL2);
        continue;
      }
      const NCollection_List<TopoDS_Shape>&    aLface1 = myEdgeFaces.FindFromKey(aEdge);
      const NCollection_List<TopoDS_Shape>&    aLface2 = myRemoveEdges.Find(aEdge);
      NCollection_List<TopoDS_Shape>::Iterator aliter(aLface1);
      NCollection_List<TopoDS_Shape>::Iterator aliter2(aLface2);
      for (; aliter.More(); aliter.Next())
      {
        TopoDS_Shape aF = Context()->Apply(aliter.Value());
        if (aF.IsNull())
          continue;
        bool isFind = false;
        for (; aliter2.More() && !isFind; aliter2.Next())
        {
          TopoDS_Shape aF2 = Context()->Apply(aliter2.Value());
          isFind           = aF.IsSame(aF2);
        }

        if (!isFind)
        {
          TopoDS_Wire     aWout   = ShapeAnalysis::OuterWire(TopoDS::Face(aF));
          bool            isOuter = false;
          TopoDS_Iterator aIter(aWout, false);
          for (; aIter.More() && !isOuter; aIter.Next())
            isOuter = aEdge.IsSame(aIter.Value());
          if (isOuter)
            aFaceCandidates.Add(aF);
        }
      }
    }

    int k = 1;
    for (; k <= aFaceCandidates.Extent(); k++)
    {
      TopoDS_Shape                      aF     = aFaceCandidates.FindKey(k);
      TopoDS_Wire                       anOutW = ShapeAnalysis::OuterWire(TopoDS::Face(aF));
      occ::handle<ShapeExtend_WireData> asewd  = new ShapeExtend_WireData(anOutW);
      int                               n = 1, nbE = asewd->NbEdges();
      int                               nbNotRemoved = 0;
      for (; n <= nbE; n++)
      {
        if (asewd->IsSeam(n))
          continue;
        TopoDS_Edge aE = asewd->Edge(n);
        if (!myRemoveEdges.IsBound(aE))
        {
          const NCollection_List<TopoDS_Shape>&    aLface3 = myEdgeFaces.FindFromKey(aE);
          NCollection_List<TopoDS_Shape>::Iterator aliter3(aLface3);
          for (; aliter3.More(); aliter3.Next())
          {
            TopoDS_Shape aF2 = Context()->Apply(aliter3.Value());
            if (aF2.IsNull())
              continue;
            if (!aF.IsSame(aF2) && !aFaceCandidates.Contains(aF2))
              nbNotRemoved++;
          }
        }
      }

      if (!nbNotRemoved)
      {
        Context()->Remove(aF);
        myRemovedFaces.Append(aF);
      }
    }
  }

  if (myRemovedFaces.Length())
    myStatus |= ShapeExtend::EncodeStatus(ShapeExtend_DONE2);
}

void ShapeUpgrade_RemoveInternalWires::Clear()
{
  myRemoveEdges.Clear();
  myRemovedFaces.Clear();
  myRemoveWires.Clear();
  myStatus = ShapeExtend::EncodeStatus(ShapeExtend_OK);
}
