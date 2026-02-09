#pragma once

enum OpenGl_RenderFilter
{
  OpenGl_RenderFilter_Empty = 0x000,

  OpenGl_RenderFilter_OpaqueOnly = 0x001,

  OpenGl_RenderFilter_TransparentOnly = 0x002,

  OpenGl_RenderFilter_NonRaytraceableOnly = 0x004,
  OpenGl_RenderFilter_FillModeOnly        = 0x008,

  OpenGl_RenderFilter_SkipTrsfPersistence = 0x010,
};
