

#include <BRep_Builder.hpp>
#include <BRep_GCurve.hpp>
#include <BRep_TEdge.hpp>
#include <BRep_Tool.hpp>
#include <BRepTools_ReShape.hpp>
#include <Geom_Surface.hpp>
#include <NCollection_IndexedMap.hpp>
#include <Standard_Type.hpp>
#include <TopLoc_Location.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Iterator.hpp>
#include <TopoDS_Shape.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BRepTools_ReShape, Standard_Transient)

namespace
{

  template <typename TMap>
  void Add(TMap& theMap, const TopoDS_Shape& theShape)
  {
    const TopAbs_ShapeEnum aType = theShape.ShapeType();
    if (aType != TopAbs_WIRE && aType != TopAbs_SHELL && aType != TopAbs_COMPSOLID)
    {
      theMap.Add(theShape);
      return;
    }

    for (TopoDS_Iterator aIt(theShape); aIt.More(); aIt.Next())
    {
      theMap.Add(aIt.Value());
    }
  }

} // namespace

static void CopyRanges(const TopoDS_Shape& toedge,
                       const TopoDS_Shape& fromedge,
                       const double        alpha,
                       const double        beta)
{
  occ::handle<BRep_TEdge> aTEdgeFrom = occ::down_cast<BRep_TEdge>(fromedge.TShape());
  occ::handle<BRep_TEdge> aTEdgeTo   = occ::down_cast<BRep_TEdge>(toedge.TShape());
  NCollection_List<occ::handle<BRep_CurveRepresentation>>& tolist = aTEdgeTo->ChangeCurves();
  NCollection_List<occ::handle<BRep_CurveRepresentation>>::Iterator fromitcr(
    aTEdgeFrom->ChangeCurves());
  for (; fromitcr.More(); fromitcr.Next())
  {
    occ::handle<BRep_GCurve> fromGC = occ::down_cast<BRep_GCurve>(fromitcr.Value());
    if (fromGC.IsNull())
      continue;
    bool isC3d = fromGC->IsCurve3D();
    if (isC3d)
    {
      if (fromGC->Curve3D().IsNull())
        continue;
    }
    else
    {
      if (fromGC->PCurve().IsNull())
        continue;
    }

    if (!isC3d && !fromGC->IsCurveOnSurface())
      continue;

    occ::handle<Geom_Surface> surface;
    TopLoc_Location           L;
    if (!isC3d)
    {
      surface = fromGC->Surface();
      L       = fromGC->Location();
    }

    occ::handle<BRep_GCurve> toGC;
    for (NCollection_List<occ::handle<BRep_CurveRepresentation>>::Iterator toitcr(tolist);
         toitcr.More();
         toitcr.Next())
    {
      toGC = occ::down_cast<BRep_GCurve>(toitcr.Value());
      if (toGC.IsNull())
        continue;
      if (isC3d)
      {
        if (!toGC->IsCurve3D())
          continue;
      }
      else if (!toGC->IsCurveOnSurface() || surface != toGC->Surface() || L != toGC->Location())
        continue;
      double first = fromGC->First();
      double last  = fromGC->Last();
      double len   = last - first;
      toGC->SetRange(first + alpha * len, first + beta * len);
      break;
    }
  }
}

BRepTools_ReShape::BRepTools_ReShape()
    : myStatus(-1)
{
  myConsiderLocation = false;
}

void BRepTools_ReShape::Clear()
{
  myShapeToReplacement.Clear();
  myNewShapes.Clear();
}

void BRepTools_ReShape::Remove(const TopoDS_Shape& shape)
{
  TopoDS_Shape nulshape;
  replace(shape, nulshape, TReplacementKind_Remove);
}

void BRepTools_ReShape::replace(const TopoDS_Shape&    ashape,
                                const TopoDS_Shape&    anewshape,
                                const TReplacementKind theKind)
{
  TopoDS_Shape shape    = ashape;
  TopoDS_Shape newshape = anewshape;
  if (shape.IsNull() || shape == newshape)
    return;

  if (shape.Orientation() == TopAbs_REVERSED)
  {
    shape.Reverse();
    newshape.Reverse();
  }

  else if (shape.Orientation() == TopAbs_INTERNAL || shape.Orientation() == TopAbs_EXTERNAL)
  {
    newshape.Orientation((newshape.Orientation() == shape.Orientation()) ? TopAbs_FORWARD
                                                                         : TopAbs_REVERSED);
    shape.Orientation(TopAbs_FORWARD);
  }

  if (myConsiderLocation)
  {

    newshape.Location(newshape.Location().Multiplied(shape.Location().Inverted()), false);
    TopLoc_Location nullLoc;
    shape.Location(nullLoc);
  }

#ifdef OCCT_DEBUG
  if (IsRecorded(shape)
      && ((myConsiderLocation && !Value(shape).IsPartner(newshape))
          || (!myConsiderLocation && !Value(shape).IsSame(newshape))))
    std::cout << "Warning: BRepTools_ReShape::Replace: shape already recorded" << std::endl;
#endif

  myShapeToReplacement.Bind(shape, TReplacement(newshape, theKind));
  myNewShapes.Add(newshape);
}

bool BRepTools_ReShape::IsRecorded(const TopoDS_Shape& ashape) const
{
  TopoDS_Shape shape = ashape;
  if (myConsiderLocation)
  {
    TopLoc_Location nullLoc;
    shape.Location(nullLoc);
  }
  if (shape.IsNull())
    return false;
  return myShapeToReplacement.IsBound(shape);
}

TopoDS_Shape BRepTools_ReShape::Value(const TopoDS_Shape& ashape) const
{
  TopoDS_Shape res;
  if (ashape.IsNull())
    return res;
  TopoDS_Shape shape = ashape;
  if (myConsiderLocation)
  {
    TopLoc_Location nullLoc;
    shape.Location(nullLoc);
  }

  bool fromMap = false;
  if (!myShapeToReplacement.IsBound(shape))
  {
    res = shape;
  }
  else
  {
    res = myShapeToReplacement(shape).Result();
    if (shape.Orientation() == TopAbs_REVERSED)
    {
      res.Reverse();
    }
    fromMap = true;
  }

  if (shape.Orientation() == TopAbs_INTERNAL || shape.Orientation() == TopAbs_EXTERNAL)
    res.Orientation(shape.Orientation());

  if (myConsiderLocation)
  {

    if (fromMap)
      res.Location(ashape.Location() * res.Location(), false);
    else
      res.Location(ashape.Location(), false);
  }

  return res;
}

int BRepTools_ReShape::Status(const TopoDS_Shape& ashape, TopoDS_Shape& newsh, const bool last)
{
  int res = 0;
  if (ashape.IsNull())
  {
    newsh.Nullify();
    return res;
  }

  TopoDS_Shape    shape  = ashape;
  TopLoc_Location aLocSh = shape.Location();
  if (myConsiderLocation)
  {
    TopLoc_Location nullLoc;
    shape.Location(nullLoc);
  }

  if (!myShapeToReplacement.IsBound(shape))
  {
    newsh = shape;
    res   = 0;
  }
  else
  {
    newsh = myShapeToReplacement(shape).Result();
    res   = 1;
  }
  if (res > 0)
  {
    if (newsh.IsNull())
      res = -1;
    else if (newsh.IsEqual(shape))
      res = 0;
    else if (last
             && ((myConsiderLocation && !newsh.IsPartner(shape))
                 || (!myConsiderLocation && !newsh.IsSame(shape))))
    {

      newsh = Apply(shape, TopAbs_SHAPE);
      if (newsh.IsNull())
        res = -1;
      if (newsh.IsEqual(shape))
        res = 0;
    }
  }
  if (myConsiderLocation && !newsh.IsNull())
  {
    TopLoc_Location aResLoc =
      (res > 0 && !newsh.Location().IsIdentity() ? aLocSh * newsh.Location() : aLocSh);
    newsh.Location(aResLoc, false);
  }
  return res;
}

static int EncodeStatus(const int status)
{
  switch (status)
  {
    case 0:
      return 0x0000;
    case 1:
      return 0x0001;
    case 2:
      return 0x0002;
    case 3:
      return 0x0004;
    case 4:
      return 0x0008;
    case 5:
      return 0x0010;
    case 6:
      return 0x0020;
    case 7:
      return 0x0040;
    case 8:
      return 0x0080;
    case 9:
      return 0x00ff;
    case 10:
      return 0x0100;
    case 11:
      return 0x0200;
    case 12:
      return 0x0400;
    case 13:
      return 0x0800;
    case 14:
      return 0x1000;
    case 15:
      return 0x2000;
    case 16:
      return 0x4000;
    case 17:
      return 0x8000;
    case 18:
      return 0xff00;
  }
  return 0;
}

TopoDS_Shape BRepTools_ReShape::Apply(const TopoDS_Shape& shape, const TopAbs_ShapeEnum until)
{
  myStatus = EncodeStatus(0);
  if (shape.IsNull())
    return shape;

  TopoDS_Shape newsh = Value(shape);

  if (newsh.IsNull())
  {
    myStatus = EncodeStatus(2);
    return newsh;
  }

  if ((myConsiderLocation && !newsh.IsPartner(shape))
      || (!myConsiderLocation && !newsh.IsSame(shape)))
  {
    TopoDS_Shape res = Apply(newsh, until);
    myStatus |= EncodeStatus(1);
    return res;
  }

  TopAbs_ShapeEnum st = shape.ShapeType();
  if (st > until || (st == until && until > TopAbs_COMPOUND))
    return newsh;
  if (st == TopAbs_VERTEX || st == TopAbs_SHAPE)
    return shape;

  BRep_Builder B;

  TopoDS_Shape       result = shape.EmptyCopied();
  TopAbs_Orientation orien  = shape.Orientation();
  result.Orientation(TopAbs_FORWARD);
  bool modif     = false;
  int  locStatus = myStatus;

  bool isEmpty = true;
  for (TopoDS_Iterator it(shape, false); it.More(); it.Next())
  {
    const TopoDS_Shape& sh = it.Value();
    newsh                  = Apply(sh, until);
    if (newsh != sh)
    {
      if (myStatus & EncodeStatus(4))
        locStatus |= EncodeStatus(4);
      modif = true;
    }
    if (newsh.IsNull())
    {
      locStatus |= EncodeStatus(4);
      continue;
    }
    if (isEmpty)
      isEmpty = false;
    locStatus |= EncodeStatus(3);
    if (st == TopAbs_COMPOUND || newsh.ShapeType() == sh.ShapeType())
    {
      B.Add(result, newsh);
      continue;
    }
    int nitems = 0;
    for (TopoDS_Iterator subit(newsh); subit.More(); subit.Next(), nitems++)
    {
      const TopoDS_Shape& subsh = subit.Value();

      if (subsh.ShapeType() == sh.ShapeType())
        B.Add(result, subsh);
      else
        locStatus |= EncodeStatus(10);
    }
    if (!nitems)
      locStatus |= EncodeStatus(10);
  }
  if (!modif)
    return shape;

  if (isEmpty && st != TopAbs_VERTEX && st != TopAbs_EDGE && st != TopAbs_FACE)
  {
    result = TopoDS_Shape();
  }
  else
  {

    if (st == TopAbs_EDGE)
    {
      CopyRanges(result, shape, 0, 1);
    }
    else if (st == TopAbs_FACE)
    {
      TopoDS_Face face = TopoDS::Face(shape);
      if (BRep_Tool::NaturalRestriction(face))
      {
        BRep_Builder aB;
        aB.NaturalRestriction(TopoDS::Face(result), true);
      }
    }
    else if (st == TopAbs_WIRE || st == TopAbs_SHELL)
      result.Closed(BRep_Tool::IsClosed(result));

    result.Orientation(orien);
  }

  replace(shape, result, result.IsNull() ? TReplacementKind_Remove : TReplacementKind_Modify);
  myStatus = locStatus;

  return result;
}

TopoDS_Vertex BRepTools_ReShape::CopyVertex(const TopoDS_Vertex& theV, const double theTol)
{
  return CopyVertex(theV, BRep_Tool::Pnt(theV), theTol);
}

TopoDS_Vertex BRepTools_ReShape::CopyVertex(const TopoDS_Vertex& theV,
                                            const gp_Pnt&        theNewPos,
                                            const double         theTol)
{
  TopoDS_Vertex aVertexCopy;
  bool          isRecorded = IsRecorded(theV);
  aVertexCopy = isRecorded ? TopoDS::Vertex(Apply(theV)) : TopoDS::Vertex(theV.EmptyCopied());

  BRep_Builder B;
  double       aNewTol = theTol > 0.0 ? theTol : BRep_Tool::Tolerance(theV);
  B.UpdateVertex(aVertexCopy, theNewPos, aNewTol);

  if (!isRecorded)
    Replace(theV, aVertexCopy);

  return aVertexCopy;
}

bool BRepTools_ReShape::IsNewShape(const TopoDS_Shape& theShape) const
{
  return myNewShapes.Contains(theShape);
}

occ::handle<BRepTools_History> BRepTools_ReShape::History() const
{
  occ::handle<BRepTools_History> aHistory = new BRepTools_History;

  for (TShapeToReplacement::Iterator aRIt(myShapeToReplacement); aRIt.More(); aRIt.Next())
  {
    const TopoDS_Shape& aShape = aRIt.Key();
    if (!BRepTools_History::IsSupportedType(aShape) || myNewShapes.Contains(aShape))
    {
      continue;
    }

    NCollection_IndexedMap<TopoDS_Shape> aIntermediates;
    NCollection_Map<TopoDS_Shape>        aModified;
    aIntermediates.Add(aShape);
    for (int aI = 1; aI <= aIntermediates.Size(); ++aI)
    {
      const TopoDS_Shape& aIntermediate = aIntermediates(aI);
      const TReplacement* aReplacement  = myShapeToReplacement.Seek(aIntermediate);
      if (aReplacement == nullptr)
      {
        Add(aModified, aIntermediate);
      }
      else if (aReplacement->RelationKind() != BRepTools_History::TRelationType_Removed)
      {
        const TopoDS_Shape aResult = aReplacement->RelationResult();
        if (!aResult.IsNull())
        {
          Add(aIntermediates, aResult);
        }
      }
    }

    if (aModified.IsEmpty())
    {
      aHistory->Remove(aShape);
    }
    else
    {
      for (NCollection_Map<TopoDS_Shape>::Iterator aIt(aModified); aIt.More(); aIt.Next())
      {
        aHistory->AddModified(aShape, aIt.Value());
      }
    }
  }

  return aHistory;
}
