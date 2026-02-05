#pragma once

bool ChFiKPart_MakeRotule(TopOpeBRepDS_DataStructure&         DStr,
                          const occ::handle<ChFiDS_SurfData>& Data,
                          const gp_Pln&                       pl,
                          const gp_Pln&                       pl1,
                          const gp_Pln&                       pl2,
                          const TopAbs_Orientation            opl,
                          const TopAbs_Orientation            opl1,
                          const TopAbs_Orientation            opl2,
                          const double                        r,
                          const TopAbs_Orientation            ofpl);
