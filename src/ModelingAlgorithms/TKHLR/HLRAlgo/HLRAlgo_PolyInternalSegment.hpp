#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Standard_Integer.hpp>

//! to Update OutLines.
struct HLRAlgo_PolyInternalSegment
{
  DEFINE_STANDARD_ALLOC

  int LstSg1, LstSg2, NxtSg1, NxtSg2, Conex1, Conex2;
};
