#pragma once


bool ChFiKPart_MakeChamfer(TopOpeBRepDS_DataStructure&         DStr,
                           const occ::handle<ChFiDS_SurfData>& Data,
                           const ChFiDS_ChamfMode              theMode,
                           const gp_Pln&                       Pln,
                           const gp_Cylinder&                  Cyl,
                           const double                        fu,
                           const double                        lu,
                           const TopAbs_Orientation            Or1,
                           const TopAbs_Orientation            Or2,
                           const double                        Dis1,
                           const double                        Dis2,
                           const gp_Circ&                      Spine,
                           const double                        First,
                           const TopAbs_Orientation            Ofpl,
                           const bool                          plandab);

// File:	ChFiKPart_ComputeData_ChPlnCyl.cxx
// Created:	Fri May 10 09:43:15 1996
// Author:	Stagiaire Xuan Trang PHAMPHU
//		<xpu@phylox>

bool ChFiKPart_MakeChamfer(TopOpeBRepDS_DataStructure&         DStr,
                           const occ::handle<ChFiDS_SurfData>& Data,
                           const ChFiDS_ChamfMode              theMode,
                           const gp_Pln&                       Pln,
                           const gp_Cylinder&                  Cyl,
                           const double                        fu,
                           const double                        lu,
                           const TopAbs_Orientation            Or1,
                           const TopAbs_Orientation            Or2,
                           const double                        Dis1,
                           const double                        Dis2,
                           const gp_Lin&                       Spine,
                           const double                        First,
                           const TopAbs_Orientation            Ofpl,
                           const bool                          plandab);

