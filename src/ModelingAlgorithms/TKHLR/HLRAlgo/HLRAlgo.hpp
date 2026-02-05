#pragma once

#include <HLRAlgo_WiresBlock.hpp>

//! In order to have the precision required in
//! industrial design, drawings need to offer the
//! possibility of removing lines, which are hidden
//! in a given projection. To do this, the Hidden
//! Line Removal component provides two
//! algorithms: HLRBRep_Algo and HLRBRep_PolyAlgo.
//! These algorithms remove or indicate lines
//! hidden by surfaces. For a given projection, they
//! calculate a set of lines characteristic of the
//! object being represented. They are also used
//! in conjunction with extraction utilities, which
//! reconstruct a new, simplified shape from a
//! selection of calculation results. This new shape
//! is made up of edges, which represent the lines
//! of the visualized shape in a plane. This plane is the projection plane.
//! HLRBRep_Algo takes into account the shape
//! itself. HLRBRep_PolyAlgo works with a
//! polyhedral simplification of the shape. When
//! you use HLRBRep_Algo, you obtain an exact
//! result, whereas, when you use
//! HLRBRep_PolyAlgo, you reduce computation
//! time but obtain polygonal segments.
class HLRAlgo
{
public:
  DEFINE_STANDARD_ALLOC

  //! Iterator on the visible or hidden parts of an
  //! EdgeStatus.
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
