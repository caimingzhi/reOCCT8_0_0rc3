#ifndef No_Exception
  #define No_Exception
#endif

#include <HLRBRep_FaceData.hpp>
#include <HLRBRep_FaceIterator.hpp>

HLRBRep_FaceIterator::HLRBRep_FaceIterator() = default;

void HLRBRep_FaceIterator::InitEdge(HLRBRep_FaceData& fd)
{
  iWire   = 0;
  myWires = fd.Wires();
  nbWires = myWires->NbWires();

  iEdge   = 0;
  nbEdges = 0;
  NextEdge();
}

void HLRBRep_FaceIterator::NextEdge()
{
  iEdge++;
  if (iEdge > nbEdges)
  {
    iWire++;
    if (iWire <= nbWires)
    {
      iEdge   = 1;
      myEdges = myWires->Wire(iWire);
      nbEdges = myEdges->NbEdges();
    }
  }
}
