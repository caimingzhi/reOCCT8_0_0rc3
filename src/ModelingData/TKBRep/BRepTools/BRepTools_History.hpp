#pragma once

#include <NCollection_Handle.hpp>
#include <TopExp.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <NCollection_Map.hpp>

class BRepTools_History : public Standard_Transient
{
public:
  BRepTools_History() = default;

  template <class TheAlgo>
  BRepTools_History(const NCollection_List<TopoDS_Shape>& theArguments, TheAlgo& theAlgo)
  {

    NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> anArgsMap;
    NCollection_List<TopoDS_Shape>::Iterator                      aIt(theArguments);
    for (; aIt.More(); aIt.Next())
    {
      if (!aIt.Value().IsNull())
        TopExp::MapShapes(aIt.Value(), anArgsMap);
    }

    int i, aNb = anArgsMap.Extent();
    for (i = 1; i <= aNb; ++i)
    {
      const TopoDS_Shape& aS = anArgsMap(i);
      if (!IsSupportedType(aS))
        continue;

      if (theAlgo.IsDeleted(aS))
        Remove(aS);

      const NCollection_List<TopoDS_Shape>& aModified = theAlgo.Modified(aS);
      for (aIt.Initialize(aModified); aIt.More(); aIt.Next())
        AddModified(aS, aIt.Value());

      const NCollection_List<TopoDS_Shape>& aGenerated = theAlgo.Generated(aS);
      for (aIt.Initialize(aGenerated); aIt.More(); aIt.Next())
        AddGenerated(aS, aIt.Value());
    }
  }

public:
  enum TRelationType
  {
    TRelationType_Removed,
    TRelationType_Generated,
    TRelationType_Modified
  };

public:
  static bool IsSupportedType(const TopoDS_Shape& theShape)
  {
    const TopAbs_ShapeEnum aType = theShape.ShapeType();
    return aType == TopAbs_VERTEX || aType == TopAbs_EDGE || aType == TopAbs_FACE
           || aType == TopAbs_SOLID;
  }

public:
  Standard_EXPORT void AddGenerated(const TopoDS_Shape& theInitial,
                                    const TopoDS_Shape& theGenerated);

  Standard_EXPORT void AddModified(const TopoDS_Shape& theInitial, const TopoDS_Shape& theModified);

  Standard_EXPORT void Remove(const TopoDS_Shape& theRemoved);

  Standard_EXPORT void ReplaceGenerated(const TopoDS_Shape& theInitial,
                                        const TopoDS_Shape& theGenerated);

  Standard_EXPORT void ReplaceModified(const TopoDS_Shape& theInitial,
                                       const TopoDS_Shape& theModified);

  void Clear()
  {
    myShapeToModified.Clear();
    myShapeToGenerated.Clear();
    myRemoved.Clear();
  }

public:
  Standard_EXPORT const NCollection_List<TopoDS_Shape>& Generated(
    const TopoDS_Shape& theInitial) const;

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& Modified(
    const TopoDS_Shape& theInitial) const;

  Standard_EXPORT bool IsRemoved(const TopoDS_Shape& theInitial) const;

  bool HasGenerated() const { return !myShapeToGenerated.IsEmpty(); }

  bool HasModified() const { return !myShapeToModified.IsEmpty(); }

  bool HasRemoved() const { return !myRemoved.IsEmpty(); }

public:
  Standard_EXPORT void Merge(const occ::handle<BRepTools_History>& theHistory23);

  Standard_EXPORT void Merge(const BRepTools_History& theHistory23);

  template <class TheAlgo>
  void Merge(const NCollection_List<TopoDS_Shape>& theArguments, TheAlgo& theAlgo)
  {

    Merge(BRepTools_History(theArguments, theAlgo));
  }

public:
  void Dump(Standard_OStream& theS)
  {
    theS << "History contains:\n";
    theS << " - " << myRemoved.Extent() << " Deleted shapes;\n";
    theS << " - " << myShapeToModified.Extent() << " Modified shapes;\n";
    theS << " - " << myShapeToGenerated.Extent() << " Generated shapes.\n";
  }

public:
  DEFINE_STANDARD_RTTIEXT(BRepTools_History, Standard_Transient)

private:
  bool prepareGenerated(const TopoDS_Shape& theInitial, const TopoDS_Shape& theGenerated);

  bool prepareModified(const TopoDS_Shape& theInitial, const TopoDS_Shape& theModified);

private:
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
    myShapeToModified;

  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
    myShapeToGenerated;

  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> myRemoved;

private:
  static const NCollection_List<TopoDS_Shape> myEmptyList;

  Standard_EXPORT static const NCollection_List<TopoDS_Shape>& emptyList();

private:
  static const char* myMsgUnsupportedType;
  static const char* myMsgGeneratedAndRemoved;
  static const char* myMsgModifiedAndRemoved;
  static const char* myMsgGeneratedAndModified;
};
