#include <HLRBRep_ShapeBounds.hpp>
#include <HLRTopoBRep_OutLiner.hpp>
#include <Standard_Transient.hpp>

HLRBRep_ShapeBounds::HLRBRep_ShapeBounds(const occ::handle<HLRTopoBRep_OutLiner>& S,
                                         const occ::handle<Standard_Transient>&   SData,
                                         const int                                nbIso,
                                         const int                                V1,
                                         const int                                V2,
                                         const int                                E1,
                                         const int                                E2,
                                         const int                                F1,
                                         const int                                F2)
    : myShape(S),
      myShapeData(SData),
      myNbIso(nbIso),
      myVertStart(V1),
      myVertEnd(V2),
      myEdgeStart(E1),
      myEdgeEnd(E2),
      myFaceStart(F1),
      myFaceEnd(F2)
{
}

HLRBRep_ShapeBounds::HLRBRep_ShapeBounds(const occ::handle<HLRTopoBRep_OutLiner>& S,
                                         const int                                nbIso,
                                         const int                                V1,
                                         const int                                V2,
                                         const int                                E1,
                                         const int                                E2,
                                         const int                                F1,
                                         const int                                F2)
    : myShape(S),
      myNbIso(nbIso),
      myVertStart(V1),
      myVertEnd(V2),
      myEdgeStart(E1),
      myEdgeEnd(E2),
      myFaceStart(F1),
      myFaceEnd(F2)
{
}

void HLRBRep_ShapeBounds::Translate(const int NV, const int NE, const int NF)
{
  myVertStart += NV;
  myVertEnd += NV;
  myEdgeStart += NE;
  myEdgeEnd += NE;
  myFaceStart += NF;
  myFaceEnd += NF;
}

void HLRBRep_ShapeBounds::Sizes(int& NV, int& NE, int& NF) const
{
  NV = myVertEnd + 1 - myVertStart;
  NE = myEdgeEnd + 1 - myEdgeStart;
  NF = myFaceEnd + 1 - myFaceStart;
}

void HLRBRep_ShapeBounds::Bounds(int& V1, int& V2, int& E1, int& E2, int& F1, int& F2) const
{
  V1 = myVertStart;
  V2 = myVertEnd;
  E1 = myEdgeStart;
  E2 = myEdgeEnd;
  F1 = myFaceStart;
  F2 = myFaceEnd;
}
