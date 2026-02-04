#pragma once


bool ChFiKPart_MakeChAsym(TopOpeBRepDS_DataStructure&         DStr,
                          const occ::handle<ChFiDS_SurfData>& Data,
                          const gp_Pln&                       Pln,
                          const gp_Cone&                      Con,
                          const double                        fu,
                          const double                        lu,
                          const TopAbs_Orientation            Or1,
                          const TopAbs_Orientation            Or2,
                          const double                        Dis,
                          const double                        Angle,
                          const gp_Circ&                      Spine,
                          const double                        First,
                          const TopAbs_Orientation            Ofpl,
                          const bool                          plandab,
                          const bool                          DisOnP);

