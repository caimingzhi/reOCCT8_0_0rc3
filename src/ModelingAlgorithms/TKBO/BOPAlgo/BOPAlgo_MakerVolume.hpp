#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <BOPAlgo_Builder.hpp>
#include <Bnd_Box.hpp>
#include <NCollection_BaseAllocator.hpp>
#include <TopoDS_Solid.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_Map.hpp>
class BOPAlgo_PaveFiller;

class BOPAlgo_MakerVolume : public BOPAlgo_Builder
{
public:
  DEFINE_STANDARD_ALLOC

  BOPAlgo_MakerVolume();
  ~BOPAlgo_MakerVolume() override;

  BOPAlgo_MakerVolume(const occ::handle<NCollection_BaseAllocator>& theAllocator);

  void Clear() override;

  void SetIntersect(const bool bIntersect);

  bool IsIntersect() const;

  const TopoDS_Solid& Box() const;

  const NCollection_List<TopoDS_Shape>& Faces() const;

  void SetAvoidInternalShapes(const bool theAvoidInternal)
  {
    myAvoidInternalShapes = theAvoidInternal;
  }

  bool IsAvoidInternalShapes() const { return myAvoidInternalShapes; }

  Standard_EXPORT void Perform(
    const Message_ProgressRange& theRange = Message_ProgressRange()) override;

protected:
  Standard_EXPORT void CheckData() override;

  Standard_EXPORT void PerformInternal1(
    const BOPAlgo_PaveFiller&    thePF,
    const Message_ProgressRange& theRange = Message_ProgressRange()) override;

  Standard_EXPORT void CollectFaces();

  Standard_EXPORT void MakeBox(NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>& theBoxFaces);

  Standard_EXPORT void BuildSolids(NCollection_List<TopoDS_Shape>& theLSR,
                                   const Message_ProgressRange&    theRange);

  Standard_EXPORT void RemoveBox(
    NCollection_List<TopoDS_Shape>&                               theLSR,
    const NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>& theBoxFaces);

  Standard_EXPORT void FillInternalShapes(const NCollection_List<TopoDS_Shape>& theLSR);

  Standard_EXPORT void BuildShape(const NCollection_List<TopoDS_Shape>& theLSR);

protected:
  enum BOPAlgo_PIOperation
  {
    PIOperation_BuildSolids = BOPAlgo_Builder::PIOperation_Last,
    PIOperation_Last
  };

  Standard_EXPORT void fillPISteps(BOPAlgo_PISteps& theSteps) const override;

protected:
  bool                           myIntersect;
  Bnd_Box                        myBBox;
  TopoDS_Solid                   mySBox;
  NCollection_List<TopoDS_Shape> myFaces;
  bool                           myAvoidInternalShapes;
};

inline BOPAlgo_MakerVolume::BOPAlgo_MakerVolume()
    : myIntersect(true),
      myAvoidInternalShapes(false)
{
}

inline BOPAlgo_MakerVolume::BOPAlgo_MakerVolume(
  const occ::handle<NCollection_BaseAllocator>& theAllocator)
    : BOPAlgo_Builder(theAllocator),
      myIntersect(true),
      myAvoidInternalShapes(false)
{
}

inline BOPAlgo_MakerVolume::~BOPAlgo_MakerVolume()
{
  Clear();
}

inline void BOPAlgo_MakerVolume::Clear()
{
  BOPAlgo_Builder::Clear();
  myIntersect = true;
  myBBox      = Bnd_Box();
  mySBox.Nullify();
  myFaces.Clear();
  myAvoidInternalShapes = false;
}

inline void BOPAlgo_MakerVolume::SetIntersect(const bool bIntersect)
{
  myIntersect = bIntersect;
}

inline bool BOPAlgo_MakerVolume::IsIntersect() const
{
  return myIntersect;
}

inline const TopoDS_Solid& BOPAlgo_MakerVolume::Box() const
{
  return mySBox;
}

inline const NCollection_List<TopoDS_Shape>& BOPAlgo_MakerVolume::Faces() const
{
  return myFaces;
}
