#pragma once

//! Identifies the type of resulting edge of HLRBRep_Algo
enum HLRBRep_TypeOfResultingEdge
{
  HLRBRep_Undefined,

  //! isoparametric line
  HLRBRep_IsoLine,

  //! outline ("silhouette")
  HLRBRep_OutLine,

  //! smooth edge of G1-continuity between two surfaces
  HLRBRep_Rg1Line,

  //! sewn edge of CN-continuity on one surface
  HLRBRep_RgNLine,

  //! sharp edge (of C0-continuity)
  HLRBRep_Sharp
};
