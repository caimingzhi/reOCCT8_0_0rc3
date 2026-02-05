#include <TopOpeBRepDS_Filter.hpp>
#include <TopOpeBRepDS_Interference.hpp>
#include <NCollection_List.hpp>
#include <TopOpeBRepDS_ProcessInterferencesTool.hpp>

Standard_EXPORT int FUN_unkeepFdoubleGBoundinterferences(
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& LI,
  const TopOpeBRepDS_DataStructure&                         BDS,
  const int                                                 SIX);
Standard_EXPORT void FUN_resolveFUNKNOWN(
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& LI,
  TopOpeBRepDS_DataStructure&                               BDS,
  const int                                                 SIX,
  const NCollection_DataMap<TopoDS_Shape,
                            TopOpeBRepDS_ListOfShapeOn1State,
                            TopTools_ShapeMapHasher>&       MEsp,
  TopOpeBRepTool_PShapeClassifier                           pClassif);

//=================================================================================================

void TopOpeBRepDS_Filter::ProcessFaceInterferences(
  const int                                           SIX,
  const NCollection_DataMap<TopoDS_Shape,
                            TopOpeBRepDS_ListOfShapeOn1State,
                            TopTools_ShapeMapHasher>& MEsp)
{
  TopOpeBRepDS_DataStructure& BDS = myHDS->ChangeDS();

  //                 BDS.Shape(SIX);
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& LI = BDS.ChangeShapeInterferences(SIX);
  ::FUN_reducedoublons(LI, BDS, SIX);

  NCollection_List<occ::handle<TopOpeBRepDS_Interference>> lw, lE, lFE, lFEF, lF, lUU, lall;
  lall.Assign(LI);

  ::FUN_selectTRAUNKinterference(lall, lUU);
  FUN_resolveFUNKNOWN(lUU, BDS, SIX, MEsp, myPShapeClassif);
  lw.Append(lall);
  lw.Append(lUU);

  ::FUN_selectTRASHAinterference(lw, TopAbs_FACE, lF);
  ::FUN_selectGKinterference(lF, TopOpeBRepDS_EDGE, lFE);
  ::FUN_selectSKinterference(lFE, TopOpeBRepDS_FACE, lFEF);
  ::FUN_selectTRASHAinterference(lw, TopAbs_EDGE, lE);

  LI.Clear();
  LI.Append(lF);
  LI.Append(lFE);
  LI.Append(lFEF);
  LI.Append(lE);

} // ProcessFaceInterferences
