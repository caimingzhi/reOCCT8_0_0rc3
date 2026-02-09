#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <BOPAlgo_GlueEnum.hpp>
#include <BOPAlgo_PPaveFiller.hpp>
#include <BOPAlgo_PBuilder.hpp>
#include <BRepAlgoAPI_Algo.hpp>
#include <BRepTools_History.hpp>
#include <Precision.hpp>
#include <Standard_Real.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>

class BRepAlgoAPI_BuilderAlgo : public BRepAlgoAPI_Algo
{
public:
  DEFINE_STANDARD_ALLOC

public:
  Standard_EXPORT BRepAlgoAPI_BuilderAlgo();
  Standard_EXPORT ~BRepAlgoAPI_BuilderAlgo() override;

  Standard_EXPORT BRepAlgoAPI_BuilderAlgo(const BOPAlgo_PaveFiller& thePF);

  BRepAlgoAPI_BuilderAlgo(const BRepAlgoAPI_BuilderAlgo&) = delete;

  BRepAlgoAPI_BuilderAlgo(BRepAlgoAPI_BuilderAlgo&&) = delete;

  BRepAlgoAPI_BuilderAlgo& operator=(const BRepAlgoAPI_BuilderAlgo&) = delete;

  BRepAlgoAPI_BuilderAlgo& operator=(BRepAlgoAPI_BuilderAlgo&&) = delete;

public:
  void SetArguments(const NCollection_List<TopoDS_Shape>& theLS) { myArguments = theLS; }

  const NCollection_List<TopoDS_Shape>& Arguments() const { return myArguments; }

public:
  void SetNonDestructive(const bool theFlag) { myNonDestructive = theFlag; }

  bool NonDestructive() const { return myNonDestructive; }

  void SetGlue(const BOPAlgo_GlueEnum theGlue) { myGlue = theGlue; }

  BOPAlgo_GlueEnum Glue() const { return myGlue; }

  void SetCheckInverted(const bool theCheck) { myCheckInverted = theCheck; }

  bool CheckInverted() const { return myCheckInverted; }

public:
  Standard_EXPORT void Build(
    const Message_ProgressRange& theRange = Message_ProgressRange()) override;

public:
  Standard_EXPORT void SimplifyResult(const bool   theUnifyEdges = true,
                                      const bool   theUnifyFaces = true,
                                      const double theAngularTol = Precision::Angular());

public:
  Standard_EXPORT const NCollection_List<TopoDS_Shape>& Modified(const TopoDS_Shape& theS) override;

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& Generated(
    const TopoDS_Shape& theS) override;

  Standard_EXPORT bool IsDeleted(const TopoDS_Shape& aS) override;

  Standard_EXPORT virtual bool HasModified() const;

  Standard_EXPORT virtual bool HasGenerated() const;

  Standard_EXPORT virtual bool HasDeleted() const;

public:
  void SetToFillHistory(const bool theHistFlag) { myFillHistory = theHistFlag; }

  bool HasHistory() const { return myFillHistory; }

public:
  Standard_EXPORT const NCollection_List<TopoDS_Shape>& SectionEdges();

public:
  const BOPAlgo_PPaveFiller& DSFiller() const { return myDSFiller; }

  const BOPAlgo_PBuilder& Builder() const { return myBuilder; }

  occ::handle<BRepTools_History> History() const { return myFillHistory ? myHistory : nullptr; }

protected:
  virtual void SetAttributes() {}

protected:
  Standard_EXPORT void IntersectShapes(const NCollection_List<TopoDS_Shape>& theArgs,
                                       const Message_ProgressRange&          theRange);

  Standard_EXPORT void BuildResult(const Message_ProgressRange& theRange = Message_ProgressRange());

protected:
  Standard_EXPORT void Clear() override;

protected:
  NCollection_List<TopoDS_Shape> myArguments;

  bool             myNonDestructive;
  BOPAlgo_GlueEnum myGlue;
  bool             myCheckInverted;
  bool             myFillHistory;

  bool myIsIntersectionNeeded;

  BOPAlgo_PPaveFiller myDSFiller;

  BOPAlgo_PBuilder myBuilder;

  occ::handle<BRepTools_History> myHistory;

  occ::handle<BRepTools_History> mySimplifierHistory;
};
