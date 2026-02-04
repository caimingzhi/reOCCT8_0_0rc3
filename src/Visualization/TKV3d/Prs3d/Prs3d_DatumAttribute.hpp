#pragma once


//! Enumeration defining a datum attribute, see Prs3d_Datum.
enum Prs3d_DatumAttribute
{
  Prs3d_DatumAttribute_XAxisLength = 0,
  Prs3d_DatumAttribute_YAxisLength,
  Prs3d_DatumAttribute_ZAxisLength,
  Prs3d_DatumAttribute_ShadingTubeRadiusPercent,
  Prs3d_DatumAttribute_ShadingConeRadiusPercent,
  Prs3d_DatumAttribute_ShadingConeLengthPercent,
  Prs3d_DatumAttribute_ShadingOriginRadiusPercent,
  Prs3d_DatumAttribute_ShadingNumberOfFacettes,

  // old aliases
  Prs3d_DA_XAxisLength                = Prs3d_DatumAttribute_XAxisLength,
  Prs3d_DA_YAxisLength                = Prs3d_DatumAttribute_YAxisLength,
  Prs3d_DA_ZAxisLength                = Prs3d_DatumAttribute_ZAxisLength,
  Prs3d_DP_ShadingTubeRadiusPercent   = Prs3d_DatumAttribute_ShadingTubeRadiusPercent,
  Prs3d_DP_ShadingConeRadiusPercent   = Prs3d_DatumAttribute_ShadingConeRadiusPercent,
  Prs3d_DP_ShadingConeLengthPercent   = Prs3d_DatumAttribute_ShadingConeLengthPercent,
  Prs3d_DP_ShadingOriginRadiusPercent = Prs3d_DatumAttribute_ShadingOriginRadiusPercent,
  Prs3d_DP_ShadingNumberOfFacettes    = Prs3d_DatumAttribute_ShadingNumberOfFacettes
};

enum
{
  Prs3d_DatumAttribute_NB = Prs3d_DatumAttribute_ShadingNumberOfFacettes + 1
};

