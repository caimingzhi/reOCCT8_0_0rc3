#include <BRep_Tool.hpp>
#include <HLRAlgo_WiresBlock.hpp>
#include <HLRBRep_FaceData.hpp>
#include <HLRBRep_Surface.hpp>
#include <TopoDS_Face.hpp>

//=================================================================================================

HLRBRep_FaceData::HLRBRep_FaceData()
    : myFlags(0),
      mySize(0)
{
  Selected(true);
}

//=================================================================================================

void HLRBRep_FaceData::Set(const TopoDS_Face&       FG,
                           const TopAbs_Orientation Or,
                           const bool               Cl,
                           const int                NW)
{
  Closed(Cl);
  Geometry().Surface(FG);
  myTolerance = (float)(BRep_Tool::Tolerance(FG));
  Orientation(Or);
  Wires() = new HLRAlgo_WiresBlock(NW);
}

//=================================================================================================

void HLRBRep_FaceData::SetWire(const int WI, const int NE)
{
  Wires()->Set(WI, new HLRAlgo_EdgesBlock(NE));
}

//=================================================================================================

void HLRBRep_FaceData::SetWEdge(const int                WI,
                                const int                EWI,
                                const int                EI,
                                const TopAbs_Orientation Or,
                                const bool               OutL,
                                const bool               Inte,
                                const bool               Dble,
                                const bool               IsoL)
{
  Wires()->Wire(WI)->Edge(EWI, EI);
  Wires()->Wire(WI)->Orientation(EWI, Or);
  Wires()->Wire(WI)->OutLine(EWI, OutL);
  Wires()->Wire(WI)->Internal(EWI, Inte);
  Wires()->Wire(WI)->Double(EWI, Dble);
  Wires()->Wire(WI)->IsoLine(EWI, IsoL);
}
