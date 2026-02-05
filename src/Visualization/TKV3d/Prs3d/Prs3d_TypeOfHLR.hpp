#pragma once

//! Declares types of hidden line removal algorithm.
//! TOH_Algo enables using of exact HLR algorithm.
//! TOH_PolyAlgo enables using of polygonal HLR algorithm.
//! TOH_NotSet is used by Prs3d_Drawer class, it means that the drawer should return the global
//! value. For more details see Prs3d_Drawer class, AIS_Shape::Compute() method and HLRAlgo package
//! from TKHLR toolkit.
enum Prs3d_TypeOfHLR
{
  Prs3d_TOH_NotSet,
  Prs3d_TOH_PolyAlgo,
  Prs3d_TOH_Algo
};
