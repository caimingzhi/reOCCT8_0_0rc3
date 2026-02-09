#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <BOPAlgo_RemoveFeatures.hpp>
#include <BRepAlgoAPI_Algo.hpp>

class BRepAlgoAPI_Defeaturing : public BRepAlgoAPI_Algo
{
public:
  DEFINE_STANDARD_ALLOC

public:
  BRepAlgoAPI_Defeaturing()
      : myFillHistory(true)
  {
  }

public:
  void SetShape(const TopoDS_Shape& theShape) { myInputShape = theShape; }

  const TopoDS_Shape& InputShape() const { return myInputShape; }

  void AddFaceToRemove(const TopoDS_Shape& theFace) { myFacesToRemove.Append(theFace); }

  void AddFacesToRemove(const NCollection_List<TopoDS_Shape>& theFaces)
  {
    NCollection_List<TopoDS_Shape>::Iterator it(theFaces);
    for (; it.More(); it.Next())
      myFacesToRemove.Append(it.Value());
  }

  const NCollection_List<TopoDS_Shape>& FacesToRemove() const { return myFacesToRemove; }

public:
  Standard_EXPORT void Build(
    const Message_ProgressRange& theRange = Message_ProgressRange()) override;

public:
  void SetToFillHistory(const bool theFlag) { myFillHistory = theFlag; }

  bool HasHistory() const { return myFillHistory; }

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& Modified(const TopoDS_Shape& theS) override;

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& Generated(
    const TopoDS_Shape& theS) override;

  Standard_EXPORT bool IsDeleted(const TopoDS_Shape& theS) override;

  Standard_EXPORT virtual bool HasModified() const;

  Standard_EXPORT virtual bool HasGenerated() const;

  Standard_EXPORT virtual bool HasDeleted() const;

  occ::handle<BRepTools_History> History() { return myFeatureRemovalTool.History(); }

protected:
  void Clear() override
  {
    BRepAlgoAPI_Algo::Clear();
    myFeatureRemovalTool.Clear();
  }

protected:
  TopoDS_Shape                   myInputShape;
  NCollection_List<TopoDS_Shape> myFacesToRemove;
  bool                           myFillHistory;

  BOPAlgo_RemoveFeatures myFeatureRemovalTool;
};
