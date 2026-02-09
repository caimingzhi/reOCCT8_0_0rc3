#include <ShapeProcess.hpp>

#include <NCollection_DataMap.hpp>
#include <Message_Messenger.hpp>
#include <Message_Msg.hpp>
#include <Message_ProgressScope.hpp>
#include <ShapeProcess_Context.hpp>
#include <ShapeProcess_Operator.hpp>
#include <Standard_ErrorHandler.hpp>
#include <Standard_Failure.hpp>
#include <TCollection_AsciiString.hpp>
#include <NCollection_Sequence.hpp>

static NCollection_DataMap<TCollection_AsciiString, occ::handle<ShapeProcess_Operator>>
  aMapOfOperators;

namespace
{

  class ScopeLock
  {
  public:
    ScopeLock(ShapeProcess_Context& theContext, const char* theScopeName)
        : myContext(theContext)
    {
      myContext.SetScope(theScopeName);
    }

    ~ScopeLock() { myContext.UnSetScope(); }

  private:
    ShapeProcess_Context& myContext;
  };
} // namespace

bool ShapeProcess::RegisterOperator(const char* name, const occ::handle<ShapeProcess_Operator>& op)
{
  if (aMapOfOperators.IsBound(name))
  {
#ifdef OCCT_DEBUG
    std::cout << "Warning: operator with name " << name << " is already registered!" << std::endl;
#endif
    return false;
  }
  aMapOfOperators.Bind(name, op);
  return true;
}

bool ShapeProcess::FindOperator(const char* name, occ::handle<ShapeProcess_Operator>& op)
{
  if (!aMapOfOperators.IsBound(name))
  {
#ifdef OCCT_DEBUG
    std::cout << "Error: no operator with name " << name << " registered!" << std::endl;
#endif
    return false;
  }
  op = aMapOfOperators.ChangeFind(name);
  return !op.IsNull();
}

bool ShapeProcess::Perform(const occ::handle<ShapeProcess_Context>& context,
                           const char*                              seq,
                           const Message_ProgressRange&             theProgress)
{
  ScopeLock aSequenceScope(*context, seq);

  TCollection_AsciiString sequence;
  if (!context->GetString("exec.op", sequence))
  {
#ifdef OCCT_DEBUG
    std::cout << "Error: ShapeProcess_Performer::Perform: sequence not defined for " << seq
              << std::endl;
#endif
    if (context->TraceLevel() > 0)
    {
      Message_Msg SMSG3("SP.Sequence.Warn.NoSeq");
      context->Messenger()->Send(SMSG3 << seq, Message_Warning);
    }
    return false;
  }
  NCollection_Sequence<TCollection_AsciiString> sequenceOfOperators;
  TCollection_AsciiString                       oper;
  int                                           i;
  for (i = 1;; i++)
  {
    oper = sequence.Token(" \t,;", i);
    if (oper.Length() <= 0)
      break;
    sequenceOfOperators.Append(oper);
  }

  if (context->TraceLevel() >= 2)
  {
    Message_Msg             SMSG0("SP.Sequence.Info.Seq");
    TCollection_AsciiString Seq;
    for (int i1 = 1; i1 <= sequenceOfOperators.Length(); i1++)
    {
      if (i1 > 1)
        Seq += ",";
      Seq += sequenceOfOperators.Value(i1);
    }
    SMSG0.Arg(Seq.ToCString());
    context->Messenger()->Send(SMSG0, Message_Info);
  }

  bool                  isDone = false;
  Message_ProgressScope aPS(theProgress, nullptr, sequenceOfOperators.Length());
  for (i = 1; i <= sequenceOfOperators.Length() && aPS.More(); i++)
  {
    oper                         = sequenceOfOperators.Value(i);
    Message_ProgressRange aRange = aPS.Next();

    if (context->TraceLevel() >= 2)
    {
      Message_Msg SMSG5("SP.Sequence.Info.Operator");
      SMSG5 << i << sequenceOfOperators.Length() << oper.ToCString();
      context->Messenger()->Send(SMSG5, Message_Alarm);
    }

    occ::handle<ShapeProcess_Operator> op;
    if (!ShapeProcess::FindOperator(oper.ToCString(), op))
    {
      if (context->TraceLevel() > 0)
      {
        Message_Msg SMSG1("SP.Sequence.Error.NoOp");
        context->Messenger()->Send(SMSG1 << oper, Message_Alarm);
      }
      continue;
    }

    ScopeLock anOperationScope(*context, oper.ToCString());
    try
    {
      OCC_CATCH_SIGNALS
      if (op->Perform(context, aRange))
        isDone = true;
    }
    catch (Standard_Failure const& anException)
    {
      Message_Msg SMSG2("SP.Sequence.Error.Except");
      SMSG2 << oper << anException.what();
      context->Messenger()->Send(SMSG2, Message_Alarm);
    }
  }

  return isDone;
}

bool ShapeProcess::Perform(const occ::handle<ShapeProcess_Context>& theContext,
                           const ShapeProcess::OperationsFlags&     theOperations,
                           const Message_ProgressRange&             theProgress)
{
  if (!theContext)
  {
    return false;
  }

  std::vector<std::pair<const char*, occ::handle<ShapeProcess_Operator>>> anOperators =
    getOperators(theOperations);
  if (anOperators.empty())
  {
    return false;
  }

  bool                  anIsAnySuccess = false;
  Message_ProgressScope aProgressScope(theProgress,
                                       nullptr,
                                       static_cast<double>(anOperators.size()));
  for (const auto& anOperator : anOperators)
  {
    const char*                               anOperationName = anOperator.first;
    const occ::handle<ShapeProcess_Operator>& anOperation     = anOperator.second;
    Message_ProgressRange                     aProgressRange  = aProgressScope.Next();
    ScopeLock                                 anOperationScope(*theContext, anOperationName);
    try
    {
      OCC_CATCH_SIGNALS;
      anIsAnySuccess |= anOperation->Perform(theContext, aProgressRange);
    }
    catch (const Standard_Failure& anException)
    {
      Message_Msg aMessage("SP.Sequence.Error.Except");
      aMessage << anOperationName << anException.what();
      theContext->Messenger()->Send(aMessage, Message_Alarm);
    }
  }
  return anIsAnySuccess;
}

std::pair<ShapeProcess::Operation, bool> ShapeProcess::ToOperationFlag(const char* theName)
{
  if (!theName)
  {
    return {Operation::First, false};
  }

  for (std::underlying_type<Operation>::type anOperation = Operation::First;
       anOperation <= Operation::Last;
       ++anOperation)
  {
    const char* anOperationName = toOperationName(static_cast<Operation>(anOperation));
    if (anOperationName && !strcmp(theName, anOperationName))
    {
      return {static_cast<Operation>(anOperation), true};
    }
  }
  return {Operation::First, false};
}

std::vector<std::pair<const char*, occ::handle<ShapeProcess_Operator>>> ShapeProcess::getOperators(
  const ShapeProcess::OperationsFlags& theFlags)
{
  std::vector<std::pair<const char*, occ::handle<ShapeProcess_Operator>>> aResult;
  for (std::underlying_type<Operation>::type anOperation = Operation::First;
       anOperation <= Operation::Last;
       ++anOperation)
  {
    if (theFlags.test(anOperation))
    {
      const char* anOperationName = toOperationName(static_cast<Operation>(anOperation));
      if (!anOperationName)
      {
        continue;
      }
      occ::handle<ShapeProcess_Operator> anOperator;
      if (FindOperator(anOperationName, anOperator))
      {
        aResult.emplace_back(anOperationName, anOperator);
      }
    }
  }
  return aResult;
}

const char* ShapeProcess::toOperationName(const Operation theOperation)
{
  switch (theOperation)
  {
    case Operation::DirectFaces:
      return "DirectFaces";

    case Operation::SameParameter:
      return "SameParameter";

    case Operation::SetTolerance:
      return "SetTolerance";

    case Operation::SplitAngle:
      return "SplitAngle";

    case Operation::BSplineRestriction:
      return "BSplineRestriction";

    case Operation::ElementaryToRevolution:
      return "ElementaryToRevolution";

    case Operation::SweptToElementary:
      return "SweptToElementary";

    case Operation::SurfaceToBSpline:
      return "SurfaceToBSpline";

    case Operation::ToBezier:
      return "ToBezier";

    case Operation::SplitContinuity:
      return "SplitContinuity";

    case Operation::SplitClosedFaces:
      return "SplitClosedFaces";

    case Operation::FixWireGaps:
      return "FixWireGaps";

    case Operation::FixFaceSize:
      return "FixFaceSize";

    case Operation::DropSmallSolids:
      return "DropSmallSolids";

    case Operation::DropSmallEdges:
      return "DropSmallEdges";

    case Operation::FixShape:
      return "FixShape";

    case Operation::SplitClosedEdges:
      return "SplitClosedEdges";

    case Operation::SplitCommonVertex:
      return "SplitCommonVertex";
  }
  return nullptr;
}
