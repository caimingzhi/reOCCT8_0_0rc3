#pragma once

enum Prs3d_DatumParts
{
  Prs3d_DatumParts_Origin = 0,
  Prs3d_DatumParts_XAxis,
  Prs3d_DatumParts_YAxis,
  Prs3d_DatumParts_ZAxis,
  Prs3d_DatumParts_XArrow,
  Prs3d_DatumParts_YArrow,
  Prs3d_DatumParts_ZArrow,
  Prs3d_DatumParts_XOYAxis,
  Prs3d_DatumParts_YOZAxis,
  Prs3d_DatumParts_XOZAxis,
  Prs3d_DatumParts_None,

  Prs3d_DP_Origin  = Prs3d_DatumParts_Origin,
  Prs3d_DP_XAxis   = Prs3d_DatumParts_XAxis,
  Prs3d_DP_YAxis   = Prs3d_DatumParts_YAxis,
  Prs3d_DP_ZAxis   = Prs3d_DatumParts_ZAxis,
  Prs3d_DP_XArrow  = Prs3d_DatumParts_XArrow,
  Prs3d_DP_YArrow  = Prs3d_DatumParts_YArrow,
  Prs3d_DP_ZArrow  = Prs3d_DatumParts_ZArrow,
  Prs3d_DP_XOYAxis = Prs3d_DatumParts_XOYAxis,
  Prs3d_DP_YOZAxis = Prs3d_DatumParts_YOZAxis,
  Prs3d_DP_XOZAxis = Prs3d_DatumParts_XOZAxis,
  Prs3d_DP_None    = Prs3d_DatumParts_None
};

enum
{
  Prs3d_DatumParts_NB = Prs3d_DatumParts_None + 1
};
