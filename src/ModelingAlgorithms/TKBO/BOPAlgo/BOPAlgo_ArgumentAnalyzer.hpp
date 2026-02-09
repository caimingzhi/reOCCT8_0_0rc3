#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDS_Shape.hpp>
#include <BOPAlgo_Algo.hpp>
#include <BOPAlgo_Operation.hpp>
#include <BOPAlgo_CheckResult.hpp>
#include <TopAbs_ShapeEnum.hpp>

class BOPAlgo_ArgumentAnalyzer : public BOPAlgo_Algo
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BOPAlgo_ArgumentAnalyzer();
  Standard_EXPORT ~BOPAlgo_ArgumentAnalyzer() override;

  Standard_EXPORT void SetShape1(const TopoDS_Shape& TheShape);

  Standard_EXPORT void SetShape2(const TopoDS_Shape& TheShape);

  Standard_EXPORT const TopoDS_Shape& GetShape1() const;

  Standard_EXPORT const TopoDS_Shape& GetShape2() const;

  Standard_EXPORT BOPAlgo_Operation& OperationType();

  Standard_EXPORT bool& StopOnFirstFaulty();

  bool& ArgumentTypeMode();

  bool& SelfInterMode();

  bool& SmallEdgeMode();

  bool& RebuildFaceMode();

  bool& TangentMode();

  bool& MergeVertexMode();

  bool& MergeEdgeMode();

  bool& ContinuityMode();

  bool& CurveOnSurfaceMode();

  Standard_EXPORT void Perform(
    const Message_ProgressRange& theRange = Message_ProgressRange()) override;

  Standard_EXPORT bool HasFaulty() const;

  Standard_EXPORT const NCollection_List<BOPAlgo_CheckResult>& GetCheckResult() const;

protected:
  Standard_EXPORT void Prepare();

  Standard_EXPORT void TestTypes();

  Standard_EXPORT void TestSelfInterferences(const Message_ProgressRange& theRange);

  Standard_EXPORT void TestSmallEdge();

  Standard_EXPORT void TestRebuildFace();

  Standard_EXPORT void TestTangent();

  Standard_EXPORT void TestMergeSubShapes(const TopAbs_ShapeEnum theType);

  Standard_EXPORT void TestMergeVertex();

  Standard_EXPORT void TestMergeEdge();

  Standard_EXPORT void TestContinuity();

  Standard_EXPORT void TestCurveOnSurface();

private:
  TopoDS_Shape                          myShape1;
  TopoDS_Shape                          myShape2;
  bool                                  myStopOnFirst;
  BOPAlgo_Operation                     myOperation;
  bool                                  myArgumentTypeMode;
  bool                                  mySelfInterMode;
  bool                                  mySmallEdgeMode;
  bool                                  myRebuildFaceMode;
  bool                                  myTangentMode;
  bool                                  myMergeVertexMode;
  bool                                  myMergeEdgeMode;
  bool                                  myContinuityMode;
  bool                                  myCurveOnSurfaceMode;
  bool                                  myEmpty1;
  bool                                  myEmpty2;
  NCollection_List<BOPAlgo_CheckResult> myResult;
};

inline bool& BOPAlgo_ArgumentAnalyzer::ArgumentTypeMode()
{
  return myArgumentTypeMode;
}

inline bool& BOPAlgo_ArgumentAnalyzer::SelfInterMode()
{
  return mySelfInterMode;
}

inline bool& BOPAlgo_ArgumentAnalyzer::SmallEdgeMode()
{
  return mySmallEdgeMode;
}

inline bool& BOPAlgo_ArgumentAnalyzer::RebuildFaceMode()
{
  return myRebuildFaceMode;
}

inline bool& BOPAlgo_ArgumentAnalyzer::TangentMode()
{
  return myTangentMode;
}

inline bool& BOPAlgo_ArgumentAnalyzer::MergeVertexMode()
{
  return myMergeVertexMode;
}

inline bool& BOPAlgo_ArgumentAnalyzer::MergeEdgeMode()
{
  return myMergeEdgeMode;
}

inline bool& BOPAlgo_ArgumentAnalyzer::ContinuityMode()
{
  return myContinuityMode;
}

inline bool& BOPAlgo_ArgumentAnalyzer::CurveOnSurfaceMode()
{
  return myCurveOnSurfaceMode;
}
