#pragma once

bool ChFiKPart_MakeChAsym(TopOpeBRepDS_DataStructure&         DStr,
                          const occ::handle<ChFiDS_SurfData>& Data,
                          const gp_Pln&                       Pl1,
                          const gp_Pln&                       Pl2,
                          const TopAbs_Orientation            Or1,
                          const TopAbs_Orientation            Or2,
                          const double                        Dis,
                          const double                        Angle,
                          const gp_Lin&                       Spine,
                          const double                        First,
                          const TopAbs_Orientation            Of1,
                          const bool                          DisOnP1);
