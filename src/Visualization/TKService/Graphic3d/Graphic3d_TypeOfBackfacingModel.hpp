#pragma once

enum Graphic3d_TypeOfBackfacingModel
{
  Graphic3d_TypeOfBackfacingModel_Auto,

  Graphic3d_TypeOfBackfacingModel_DoubleSided,
  Graphic3d_TypeOfBackfacingModel_BackCulled,
  Graphic3d_TypeOfBackfacingModel_FrontCulled,

  Graphic3d_TOBM_AUTOMATIC  = Graphic3d_TypeOfBackfacingModel_Auto,
  Graphic3d_TOBM_FORCE      = Graphic3d_TypeOfBackfacingModel_DoubleSided,
  Graphic3d_TOBM_DISABLE    = Graphic3d_TypeOfBackfacingModel_BackCulled,
  V3d_TOBM_AUTOMATIC        = Graphic3d_TypeOfBackfacingModel_Auto,
  V3d_TOBM_ALWAYS_DISPLAYED = Graphic3d_TypeOfBackfacingModel_DoubleSided,
  V3d_TOBM_NEVER_DISPLAYED  = Graphic3d_TypeOfBackfacingModel_BackCulled
};
