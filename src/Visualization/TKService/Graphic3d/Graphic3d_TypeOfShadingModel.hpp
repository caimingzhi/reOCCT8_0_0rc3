#pragma once

enum Graphic3d_TypeOfShadingModel
{

  Graphic3d_TypeOfShadingModel_DEFAULT = -1,

  Graphic3d_TypeOfShadingModel_Unlit = 0,

  Graphic3d_TypeOfShadingModel_PhongFacet,

  Graphic3d_TypeOfShadingModel_Gouraud,

  Graphic3d_TypeOfShadingModel_Phong,

  Graphic3d_TypeOfShadingModel_Pbr,

  Graphic3d_TypeOfShadingModel_PbrFacet,

  Graphic3d_TOSM_DEFAULT   = Graphic3d_TypeOfShadingModel_DEFAULT,
  Graphic3d_TOSM_UNLIT     = Graphic3d_TypeOfShadingModel_Unlit,
  Graphic3d_TOSM_FACET     = Graphic3d_TypeOfShadingModel_PhongFacet,
  Graphic3d_TOSM_VERTEX    = Graphic3d_TypeOfShadingModel_Gouraud,
  Graphic3d_TOSM_FRAGMENT  = Graphic3d_TypeOfShadingModel_Phong,
  Graphic3d_TOSM_PBR       = Graphic3d_TypeOfShadingModel_Pbr,
  Graphic3d_TOSM_PBR_FACET = Graphic3d_TypeOfShadingModel_PbrFacet,

  Graphic3d_TOSM_NONE = Graphic3d_TOSM_UNLIT,
  V3d_COLOR           = Graphic3d_TOSM_NONE,
  V3d_FLAT            = Graphic3d_TOSM_FACET,
  V3d_GOURAUD         = Graphic3d_TOSM_VERTEX,
  V3d_PHONG           = Graphic3d_TOSM_FRAGMENT
};

enum
{

  Graphic3d_TypeOfShadingModel_NB = Graphic3d_TypeOfShadingModel_PbrFacet + 1
};
