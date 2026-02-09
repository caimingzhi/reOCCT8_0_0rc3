#pragma once

#include <Aspect_GraphicsLibrary.hpp>
#include <Graphic3d_ShaderFlags.hpp>
#include <Graphic3d_StereoMode.hpp>
#include <NCollection_Vec2.hpp>
#include <Standard_TypeDef.hpp>
#include <Standard_Transient.hpp>
#include <TCollection_AsciiString.hpp>

class Graphic3d_LightSet;
class Graphic3d_ShaderProgram;

enum Graphic3d_GlslExtension
{
  Graphic3d_GlslExtension_GL_OES_standard_derivatives,

  Graphic3d_GlslExtension_GL_EXT_shader_texture_lod,

  Graphic3d_GlslExtension_GL_EXT_frag_depth,
  Graphic3d_GlslExtension_GL_EXT_gpu_shader4,
};

enum
{
  Graphic3d_GlslExtension_NB = Graphic3d_GlslExtension_GL_EXT_gpu_shader4 + 1
};

class Graphic3d_ShaderManager : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(Graphic3d_ShaderManager, Standard_Transient)
public:
  Standard_EXPORT Graphic3d_ShaderManager(Aspect_GraphicsLibrary theGapi);

  Standard_EXPORT ~Graphic3d_ShaderManager() override;

  bool IsGapiGreaterEqual(int theVerMajor, int theVerMinor) const
  {
    return (myGapiVersion[0] > theVerMajor)
           || (myGapiVersion[0] == theVerMajor && myGapiVersion[1] >= theVerMinor);
  }

  int GapiVersionMajor() const { return myGapiVersion[0]; }

  int GapiVersionMinor() const { return myGapiVersion[1]; }

  void SetGapiVersion(int theVerMajor, int theVerMinor)
  {
    myGapiVersion.SetValues(theVerMajor, theVerMinor);
  }

  bool UseRedAlpha() const { return myUseRedAlpha; }

  void SetUseRedAlpha(bool theUseRedAlpha) { myUseRedAlpha = theUseRedAlpha; }

  bool HasFlatShading() const { return myHasFlatShading; }

  bool ToReverseDFdxSign() const { return myToReverseDFdxSign; }

  void SetFlatShading(bool theToUse, bool theToReverseSign)
  {
    myHasFlatShading    = theToUse;
    myToReverseDFdxSign = theToReverseSign;
  }

  bool ToEmulateDepthClamp() const { return myToEmulateDepthClamp; }

  void SetEmulateDepthClamp(bool theToEmulate) { myToEmulateDepthClamp = theToEmulate; }

  bool HasGlslExtension(Graphic3d_GlslExtension theExt) const { return myGlslExtensions[theExt]; }

  void EnableGlslExtension(Graphic3d_GlslExtension theExt, bool theToEnable = true)
  {
    myGlslExtensions[theExt] = theToEnable;
  }

protected:
  Standard_EXPORT TCollection_AsciiString
    genLightKey(const occ::handle<Graphic3d_LightSet>& theLights, const bool theHasShadowMap) const;

  Standard_EXPORT occ::handle<Graphic3d_ShaderProgram> getStdProgramFont() const;

  Standard_EXPORT occ::handle<Graphic3d_ShaderProgram> getStdProgramUnlit(
    int  theBits,
    bool theIsOutline = false) const;

  Standard_EXPORT occ::handle<Graphic3d_ShaderProgram> getStdProgramGouraud(
    const occ::handle<Graphic3d_LightSet>& theLights,
    int                                    theBits) const;

  Standard_EXPORT occ::handle<Graphic3d_ShaderProgram> getStdProgramPhong(
    const occ::handle<Graphic3d_LightSet>& theLights,
    const int                              theBits,
    const bool                             theIsFlatNormal,
    const bool                             theIsPBR,
    const int                              theNbShadowMaps) const;

  Standard_EXPORT occ::handle<Graphic3d_ShaderProgram> getStdProgramBoundBox() const;

  Standard_EXPORT occ::handle<Graphic3d_ShaderProgram> getBgCubeMapProgram() const;

  Standard_EXPORT occ::handle<Graphic3d_ShaderProgram> getBgSkydomeProgram() const;

  Standard_EXPORT occ::handle<Graphic3d_ShaderProgram> getColoredQuadProgram() const;

  Standard_EXPORT occ::handle<Graphic3d_ShaderProgram> getPBREnvBakingProgram(int theIndex) const;

  Standard_EXPORT occ::handle<Graphic3d_ShaderProgram> getStdProgramFboBlit(
    int  theNbSamples,
    bool theIsFallback_sRGB) const;

  Standard_EXPORT occ::handle<Graphic3d_ShaderProgram> getStdProgramStereo(
    Graphic3d_StereoMode theStereoMode) const;

  Standard_EXPORT occ::handle<Graphic3d_ShaderProgram> getStdProgramOitCompositing(
    bool theMsaa) const;

  Standard_EXPORT occ::handle<Graphic3d_ShaderProgram> getStdProgramOitDepthPeelingBlend(
    bool theMsaa) const;

  Standard_EXPORT occ::handle<Graphic3d_ShaderProgram> getStdProgramOitDepthPeelingFlush(
    bool theMsaa) const;

protected:
  Standard_EXPORT bool hasGlslBitwiseOps() const;

  Standard_EXPORT int defaultGlslVersion(const occ::handle<Graphic3d_ShaderProgram>& theProgram,
                                         const TCollection_AsciiString&              theName,
                                         int                                         theBits,
                                         bool theUsesDerivates = false) const;

  Standard_EXPORT void defaultOitGlslVersion(const occ::handle<Graphic3d_ShaderProgram>& theProgram,
                                             const TCollection_AsciiString&              theName,
                                             bool theMsaa) const;

  Standard_EXPORT TCollection_AsciiString pointSpriteAlphaSrc(int theBits) const;

  Standard_EXPORT TCollection_AsciiString
    pointSpriteShadingSrc(const TCollection_AsciiString& theBaseColorSrc, int theBits) const;

  Standard_EXPORT TCollection_AsciiString
    stdComputeLighting(int&                                   theNbLights,
                       const occ::handle<Graphic3d_LightSet>& theLights,
                       bool                                   theHasVertColor,
                       bool                                   theIsPBR,
                       bool                                   theHasTexColor,
                       int                                    theNbShadowMaps) const;

protected:
  Aspect_GraphicsLibrary myGapi;
  NCollection_Vec2<int>  myGapiVersion;
  bool                   myGlslExtensions[Graphic3d_GlslExtension_NB];
  bool                   myHasFlatShading;
  bool                   myToReverseDFdxSign;
  bool                   mySetPointSize;

  bool myUseRedAlpha;

  bool myToEmulateDepthClamp;
  bool mySRgbState;
};
