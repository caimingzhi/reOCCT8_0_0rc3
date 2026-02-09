#pragma once

#include <Message_ProgressRange.hpp>
#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <bitset>
#include <vector>

class ShapeProcess_Operator;
class ShapeProcess_Context;

class ShapeProcess
{
public:
  DEFINE_STANDARD_ALLOC

  enum Operation : uint8_t
  {
    First       = 0,
    DirectFaces = First,
    SameParameter,
    SetTolerance,
    SplitAngle,
    BSplineRestriction,
    ElementaryToRevolution,
    SweptToElementary,
    SurfaceToBSpline,
    ToBezier,
    SplitContinuity,
    SplitClosedFaces,
    FixWireGaps,
    FixFaceSize,
    DropSmallSolids,
    DropSmallEdges,
    FixShape,
    SplitClosedEdges,
    SplitCommonVertex,
    Last = SplitCommonVertex
  };

  using OperationsFlags = std::bitset<Operation::Last + 1>;

public:
  Standard_EXPORT static bool RegisterOperator(const char*                               name,
                                               const occ::handle<ShapeProcess_Operator>& op);

  Standard_EXPORT static bool FindOperator(const char*                         name,
                                           occ::handle<ShapeProcess_Operator>& op);

  Standard_EXPORT static bool Perform(
    const occ::handle<ShapeProcess_Context>& context,
    const char*                              seq,
    const Message_ProgressRange&             theProgress = Message_ProgressRange());

  Standard_EXPORT static bool Perform(
    const occ::handle<ShapeProcess_Context>& theContext,
    const OperationsFlags&                   theOperations,
    const Message_ProgressRange&             theProgress = Message_ProgressRange());

  Standard_EXPORT static std::pair<Operation, bool> ToOperationFlag(const char* theName);

private:
  static std::vector<std::pair<const char*, occ::handle<ShapeProcess_Operator>>> getOperators(
    const OperationsFlags& theFlags);

  static const char* toOperationName(const Operation theOperation);
};
