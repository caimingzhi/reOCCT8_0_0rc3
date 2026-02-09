#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Standard_Integer.hpp>

struct HLRAlgo_TriangleData
{
  DEFINE_STANDARD_ALLOC

  int Node1, Node2, Node3, Flags;
};
