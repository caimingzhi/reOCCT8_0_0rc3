#pragma once

#include <Standard_Type.hpp>
#include <Standard_Transient.hpp>

#ifndef _OpenGl_ShaderProgramDumpLevel_H__
  #define _OpenGl_ShaderProgramDumpLevel_H__

enum OpenGl_ShaderProgramDumpLevel
{
  OpenGl_ShaderProgramDumpLevel_Off,
  OpenGl_ShaderProgramDumpLevel_Short,

  OpenGl_ShaderProgramDumpLevel_Full
};

#endif

class OpenGl_Caps : public Standard_Transient
{

public:
  bool sRGBDisable;

  bool compressedTexturesDisable;
  bool vboDisable;
  bool pntSpritesDisable;
  bool keepArrayData;
  bool ffpEnable;
  bool usePolygonMode;
  bool useSystemBuffer;
  int  swapInterval;
  bool useZeroToOneDepth;

public:
  bool buffersNoSwap;

  bool buffersOpaqueAlpha;

  bool buffersDeepColor;

  bool contextStereo;

  bool contextDebug;

  bool contextSyncDebug;

  bool contextNoAccel;

  bool contextCompatible;

  bool contextNoExtensions;

  int contextMajorVersionUpper;
  int contextMinorVersionUpper;

  bool isTopDownTextureUV;

public:
  bool glslWarnings;

  bool suppressExtraMsg;

  OpenGl_ShaderProgramDumpLevel glslDumpLevel;

public:
  Standard_EXPORT OpenGl_Caps();

  Standard_EXPORT ~OpenGl_Caps() override;

  Standard_EXPORT OpenGl_Caps& operator=(const OpenGl_Caps& theCopy);

private:
  OpenGl_Caps(const OpenGl_Caps&) = delete;

public:
  DEFINE_STANDARD_RTTIEXT(OpenGl_Caps, Standard_Transient)
};
