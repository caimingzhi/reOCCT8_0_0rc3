#ifndef No_Exception
  #define No_Exception
#endif

#include <HLRAlgo_EdgesBlock.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(HLRAlgo_EdgesBlock, Standard_Transient)

HLRAlgo_EdgesBlock::HLRAlgo_EdgesBlock(const int NbEdges)
    : myEdges(1, NbEdges),
      myFlags(1, NbEdges)
{
}
