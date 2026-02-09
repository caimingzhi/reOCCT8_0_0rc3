#pragma once

#include <HLRAlgo_WiresBlock.hpp>

class HLRAlgo
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void UpdateMinMax(const double x,
                                           const double y,
                                           const double z,
                                           double       Min[16],
                                           double       Max[16]);

  Standard_EXPORT static void EnlargeMinMax(const double tol, double Min[16], double Max[16]);

  Standard_EXPORT static void InitMinMax(const double Big, double Min[16], double Max[16]);

  Standard_EXPORT static void EncodeMinMax(HLRAlgo_EdgesBlock::MinMaxIndices& Min,
                                           HLRAlgo_EdgesBlock::MinMaxIndices& Max,
                                           HLRAlgo_EdgesBlock::MinMaxIndices& MinMax);

  Standard_EXPORT static double SizeBox(HLRAlgo_EdgesBlock::MinMaxIndices& Min,
                                        HLRAlgo_EdgesBlock::MinMaxIndices& Max);

  Standard_EXPORT static void DecodeMinMax(const HLRAlgo_EdgesBlock::MinMaxIndices& MinMax,
                                           HLRAlgo_EdgesBlock::MinMaxIndices&       Min,
                                           HLRAlgo_EdgesBlock::MinMaxIndices&       Max);

  static void CopyMinMax(HLRAlgo_EdgesBlock::MinMaxIndices& IMin,
                         HLRAlgo_EdgesBlock::MinMaxIndices& IMax,
                         HLRAlgo_EdgesBlock::MinMaxIndices& OMin,
                         HLRAlgo_EdgesBlock::MinMaxIndices& OMax)
  {
    OMin = IMin;
    OMax = IMax;
  }

  Standard_EXPORT static void AddMinMax(HLRAlgo_EdgesBlock::MinMaxIndices& IMin,
                                        HLRAlgo_EdgesBlock::MinMaxIndices& IMax,
                                        HLRAlgo_EdgesBlock::MinMaxIndices& OMin,
                                        HLRAlgo_EdgesBlock::MinMaxIndices& OMax);
};
