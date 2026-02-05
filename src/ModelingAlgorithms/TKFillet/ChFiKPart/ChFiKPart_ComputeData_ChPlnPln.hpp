#pragma once

bool ChFiKPart_MakeChamfer(TopOpeBRepDS_DataStructure&         DStr,
                           const occ::handle<ChFiDS_SurfData>& Data,
                           const ChFiDS_ChamfMode              theMode,
                           const gp_Pln&                       Pl1,
                           const gp_Pln&                       Pl2,
                           const TopAbs_Orientation            Or1,
                           const TopAbs_Orientation            Or2,
                           const double                        Dis1,
                           const double                        Dis2,
                           const gp_Lin&                       Spine,
                           const double                        First,
                           const TopAbs_Orientation            Of1);
