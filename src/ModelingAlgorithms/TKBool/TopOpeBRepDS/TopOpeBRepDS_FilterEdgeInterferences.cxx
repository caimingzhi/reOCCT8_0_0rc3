#include <TopOpeBRepDS_Filter.hpp>
#include <TopOpeBRepDS_Interference.hpp>
#include <NCollection_List.hpp>
#include <TopOpeBRepDS_ProcessInterferencesTool.hpp>

Standard_EXPORT int FUN_unkeepEinterferences(
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& LI,
  const TopOpeBRepDS_DataStructure&                         BDS,
  const int                                                 SIX);
Standard_EXPORT void FUN_unkeepEsymetrictransitions(
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& LI,
  const TopOpeBRepDS_DataStructure&                         BDS,
  const int                                                 SIX);
Standard_EXPORT void FUN_orderFFsamedomain(
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& LI,
  const occ::handle<TopOpeBRepDS_HDataStructure>&           BDS,
  const int                                                 SIX);
Standard_EXPORT void FUN_orderSTATETRANS(
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& LI,
  const occ::handle<TopOpeBRepDS_HDataStructure>&           BDS,
  const int                                                 SIX);
Standard_EXPORT void FUN_resolveEUNKNOWN(
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& LI,
  TopOpeBRepDS_DataStructure&                               BDS,
  const int                                                 SIX);
Standard_EXPORT void FUN_purgeDSonSE(const occ::handle<TopOpeBRepDS_HDataStructure>&           HDS,
                                     const int                                                 EIX,
                                     NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& LI);

//------------------------------------------------------
static void FUN_FilterEdge
  //------------------------------------------------------
  (NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& LI,
   const occ::handle<TopOpeBRepDS_HDataStructure>&           HDS,
   const int                                                 SIX)
{
  TopOpeBRepDS_DataStructure& BDS = HDS->ChangeDS();

  FUN_orderFFsamedomain(LI, HDS, SIX);
  FUN_orderSTATETRANS(LI, HDS, SIX);
  FUN_unkeepEinterferences(LI, BDS, SIX);
  FUN_reducedoublons(LI, BDS, SIX);
}

//=================================================================================================

void TopOpeBRepDS_Filter::ProcessEdgeInterferences(const int SIX)
{
  TopOpeBRepDS_DataStructure& BDS = myHDS->ChangeDS();
  //                 BDS.Shape(SIX);
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& LI = BDS.ChangeShapeInterferences(SIX);
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>  lw, lE, lF, lUU, lall;
  lall.Assign(LI);

  // xpu : 270398 :
  // deleting faulty interferences attached to section edge EIX
  // I = (T(Ftrasha),G,Ftrasha), Ftrasha sdm with FancestorofEIX
  FUN_purgeDSonSE(myHDS, SIX, lall);
  // xpu : 270398 (pro1260, edge 49,ftrasha 93)
  ::FUN_selectTRAUNKinterference(lall, lUU);
  FUN_resolveEUNKNOWN(lUU, BDS, SIX);
  lw.Append(lall);
  lw.Append(lUU);
  ::FUN_selectTRASHAinterference(lw, TopAbs_FACE, lF);
  ::FUN_selectTRASHAinterference(lw, TopAbs_EDGE, lE);
  ::FUN_FilterEdge(lF, myHDS, SIX);
  //  ::FUN_unkeepEsymetrictransitions(lF,BDS,SIX);
  ::FUN_FilterEdge(lE, myHDS, SIX);

  LI.Clear();
  LI.Append(lF);
  LI.Append(lE);
} // ProcessEdgeInterferences
