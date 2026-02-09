#pragma once

#include <BRepTools_History.hpp>

#include <TopoDS_Shape.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <NCollection_Map.hpp>
#include <Standard_Integer.hpp>
#include <Standard_Transient.hpp>
#include <TopAbs_ShapeEnum.hpp>

class TopoDS_Vertex;

#ifdef Status
  #undef Status
#endif

class BRepTools_ReShape : public Standard_Transient
{
public:
  Standard_EXPORT BRepTools_ReShape();

  Standard_EXPORT virtual void Clear();

  Standard_EXPORT virtual void Remove(const TopoDS_Shape& shape);

  virtual void Replace(const TopoDS_Shape& shape, const TopoDS_Shape& newshape)
  {
    replace(shape, newshape, TReplacementKind_Modify);
  }

  template <typename TCollection>
  void Merge(const TCollection& theParts, const TopoDS_Shape& theProduct)
  {
    typename TCollection::Iterator aPIt(theParts);

    if (aPIt.More())
    {
      replace(aPIt.Value(), theProduct, TReplacementKind_Merge_Main);

      aPIt.Next();
    }

    const TReplacementKind aKind = TReplacementKind_Merge_Ordinary;
    for (; aPIt.More(); aPIt.Next())
    {
      replace(aPIt.Value(), theProduct, aKind);
    }
  }

  Standard_EXPORT virtual bool IsRecorded(const TopoDS_Shape& shape) const;

  Standard_EXPORT virtual TopoDS_Shape Value(const TopoDS_Shape& shape) const;

  Standard_EXPORT virtual int Status(const TopoDS_Shape& shape,
                                     TopoDS_Shape&       newsh,
                                     const bool          last = false);

  Standard_EXPORT virtual TopoDS_Shape Apply(const TopoDS_Shape&    theShape,
                                             const TopAbs_ShapeEnum theUntil = TopAbs_SHAPE);

  virtual bool& ModeConsiderLocation() { return myConsiderLocation; }

  Standard_EXPORT TopoDS_Vertex CopyVertex(const TopoDS_Vertex& theV, const double theTol = -1.0);

  Standard_EXPORT TopoDS_Vertex CopyVertex(const TopoDS_Vertex& theV,
                                           const gp_Pnt&        theNewPos,
                                           const double         aTol);

  Standard_EXPORT bool IsNewShape(const TopoDS_Shape& theShape) const;

  Standard_EXPORT occ::handle<BRepTools_History> History() const;

  DEFINE_STANDARD_RTTIEXT(BRepTools_ReShape, Standard_Transient)

protected:
  enum TReplacementKind
  {
    TReplacementKind_Remove         = 1,
    TReplacementKind_Modify         = 2,
    TReplacementKind_Merge_Main     = 4,
    TReplacementKind_Merge_Ordinary = 8
  };

  Standard_EXPORT virtual void replace(const TopoDS_Shape&    shape,
                                       const TopoDS_Shape&    newshape,
                                       const TReplacementKind theKind);

private:
  static bool isOrdinaryMerged(const TReplacementKind theKind)
  {
    return (theKind == TReplacementKind_Merge_Ordinary);
  }

  struct TReplacement
  {
  public:
    TReplacement()
        : myKind(TReplacementKind_Remove)
    {
    }

    TReplacement(const TopoDS_Shape& theResult, const TReplacementKind theKind)
        : myResult(theResult),
          myKind(theKind)
    {
    }

    TopoDS_Shape Result() const
    {
      return (myKind != TReplacementKind_Merge_Ordinary) ? myResult : TopoDS_Shape();
    }

    const TopoDS_Shape& RelationResult() const { return myResult; }

    BRepTools_History::TRelationType RelationKind() const
    {
      return (myKind == TReplacementKind_Remove) ? BRepTools_History::TRelationType_Removed
                                                 : BRepTools_History::TRelationType_Modified;
    }

  private:
    TopoDS_Shape     myResult;
    TReplacementKind myKind;
  };

  typedef NCollection_DataMap<TopoDS_Shape, TReplacement, TopTools_ShapeMapHasher>
    TShapeToReplacement;

private:
  TShapeToReplacement myShapeToReplacement;

protected:
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> myNewShapes;
  int                                                    myStatus;

private:
  bool myConsiderLocation;
};
