#pragma once


#include <TopOpeBRepDS_define.hpp>
Standard_EXPORT void FDS_repvg(const TopOpeBRepDS_DataStructure&                         BDS,
                               const int                                                 EIX,
                               const TopOpeBRepDS_Kind                                   GT,
                               NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& LI,
                               NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& reducedLI);
Standard_EXPORT void FDS_repvg2(
  const TopOpeBRepDS_DataStructure&                         BDS,
  const int                                                 EIX,
  const TopOpeBRepDS_Kind                                   GT,
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& LI,
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& reducedLI);
