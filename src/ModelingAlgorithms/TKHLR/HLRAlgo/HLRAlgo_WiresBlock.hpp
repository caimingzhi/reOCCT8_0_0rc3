#pragma once

#include <HLRAlgo_EdgesBlock.hpp>

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
#include <NCollection_Array1.hpp>
#include <Standard_Integer.hpp>

class HLRAlgo_WiresBlock : public Standard_Transient
{
public:
  HLRAlgo_WiresBlock(const int NbWires)
      : myWires(1, NbWires)
  {
  }

  int NbWires() const { return myWires.Upper(); }

  void Set(const int I, const occ::handle<HLRAlgo_EdgesBlock>& W) { myWires(I) = W; }

  occ::handle<HLRAlgo_EdgesBlock>& Wire(const int I)
  {
    return *((occ::handle<HLRAlgo_EdgesBlock>*)&myWires(I));
  }

  void UpdateMinMax(const HLRAlgo_EdgesBlock::MinMaxIndices& theMinMaxes)
  {
    myMinMax = theMinMaxes;
  }

  HLRAlgo_EdgesBlock::MinMaxIndices& MinMax() { return myMinMax; }

  DEFINE_STANDARD_RTTIEXT(HLRAlgo_WiresBlock, Standard_Transient)

private:
  NCollection_Array1<occ::handle<Standard_Transient>> myWires;
  HLRAlgo_EdgesBlock::MinMaxIndices                   myMinMax;
};
