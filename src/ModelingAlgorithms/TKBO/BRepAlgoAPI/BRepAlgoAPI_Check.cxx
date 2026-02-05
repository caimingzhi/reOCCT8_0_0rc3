#include <BRepAlgoAPI_Check.hpp>

#include <BOPAlgo_ArgumentAnalyzer.hpp>
#include <BRepCheck_Analyzer.hpp>

//=================================================================================================

BRepAlgoAPI_Check::BRepAlgoAPI_Check()
    : myTestSE(true),
      myTestSI(true),
      myOperation(BOPAlgo_UNKNOWN)
{
}

//=================================================================================================

BRepAlgoAPI_Check::BRepAlgoAPI_Check(const TopoDS_Shape&          theS,
                                     const bool                   bTestSE,
                                     const bool                   bTestSI,
                                     const Message_ProgressRange& theRange)
    : myS1(theS),
      myTestSE(bTestSE),
      myTestSI(bTestSI),
      myOperation(BOPAlgo_UNKNOWN)
{
  Perform(theRange);
}

//=================================================================================================

BRepAlgoAPI_Check::BRepAlgoAPI_Check(const TopoDS_Shape&          theS1,
                                     const TopoDS_Shape&          theS2,
                                     const BOPAlgo_Operation      theOp,
                                     const bool                   bTestSE,
                                     const bool                   bTestSI,
                                     const Message_ProgressRange& theRange)
    : myS1(theS1),
      myS2(theS2),
      myTestSE(bTestSE),
      myTestSI(bTestSI),
      myOperation(theOp)
{
  Perform(theRange);
}

//=================================================================================================

BRepAlgoAPI_Check::~BRepAlgoAPI_Check() = default;

//=================================================================================================

void BRepAlgoAPI_Check::Perform(const Message_ProgressRange& theRange)
{
  // Check the incompatibility of shapes types, small edges and self-interference
  BOPAlgo_ArgumentAnalyzer anAnalyzer;
  // Set the shapes and options for the check
  anAnalyzer.SetShape1(myS1);
  anAnalyzer.SetShape2(myS2);
  anAnalyzer.OperationType()    = myOperation;
  anAnalyzer.ArgumentTypeMode() = true;
  anAnalyzer.SmallEdgeMode()    = myTestSE;
  anAnalyzer.SelfInterMode()    = myTestSI;
  // Set options from BOPAlgo_Options
  anAnalyzer.SetRunParallel(myRunParallel);
  anAnalyzer.SetFuzzyValue(myFuzzyValue);
  // Perform the check
  Message_ProgressScope aPS(theRange, "Checking shapes", 1);
  anAnalyzer.Perform(aPS.Next());
  if (UserBreak(aPS))
  {
    return;
  }
  // Get the results
  myFaultyShapes = anAnalyzer.GetCheckResult();

  // Check the topological validity of the shapes
  bool isValidS1 = !myS1.IsNull() ? BRepCheck_Analyzer(myS1).IsValid() : true;

  bool isValidS2 = !myS2.IsNull() ? BRepCheck_Analyzer(myS2).IsValid() : true;

  if (!isValidS1 || !isValidS2)
  {
    BOPAlgo_CheckResult aRes;
    aRes.SetCheckStatus(BOPAlgo_NotValid);
    if (!isValidS1)
    {
      aRes.SetShape1(myS1);
    }
    if (!isValidS2)
    {
      aRes.SetShape2(myS2);
    }
    myFaultyShapes.Append(aRes);
  }
}
