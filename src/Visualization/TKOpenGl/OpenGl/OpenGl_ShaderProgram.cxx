#include <OSD_File.hpp>
#include <OSD_Environment.hpp>

#include <OpenGl_Context.hpp>
#include <OpenGl_ShaderProgram.hpp>
#include <OpenGl_ShaderManager.hpp>
#include <OpenGl_ArbTexBindless.hpp>

#include <OpenGl_GlCore32.hpp>

#include "../../TKService/Shaders/Shaders_DeclarationsImpl_glsl.hpp"
#include "../../TKService/Shaders/Shaders_Declarations_glsl.hpp"

#ifdef _WIN32
  #include <malloc.h>
#endif

IMPLEMENT_STANDARD_RTTIEXT(OpenGl_ShaderProgram, OpenGl_NamedResource)

OpenGl_VariableSetterSelector OpenGl_ShaderProgram::mySetterSelector =
  OpenGl_VariableSetterSelector();

const char* OpenGl_ShaderProgram::PredefinedKeywords[] = {"occModelWorldMatrix",
                                                          "occWorldViewMatrix",
                                                          "occProjectionMatrix",
                                                          "occModelWorldMatrixInverse",
                                                          "occWorldViewMatrixInverse",
                                                          "occProjectionMatrixInverse",
                                                          "occModelWorldMatrixTranspose",
                                                          "occWorldViewMatrixTranspose",
                                                          "occProjectionMatrixTranspose",
                                                          "occModelWorldMatrixInverseTranspose",
                                                          "occWorldViewMatrixInverseTranspose",
                                                          "occProjectionMatrixInverseTranspose",

                                                          "occClipPlaneEquations",
                                                          "occClipPlaneChains",
                                                          "occClipPlaneCount",

                                                          "occLightSourcesCount",
                                                          "occLightSourcesTypes",
                                                          "occLightSources",
                                                          "occLightAmbient",
                                                          "occShadowMapSizeBias",
                                                          "occShadowMapSamplers",
                                                          "occShadowMapMatrices",

                                                          "occTextureEnable",
                                                          "occDistinguishingMode",
                                                          "occPbrMaterial",
                                                          "occCommonMaterial",
                                                          "occAlphaCutoff",
                                                          "occColor",

                                                          "occOitOutput",
                                                          "occOitDepthFactor",

                                                          "occTexTrsf2d",
                                                          "occPointSize",

                                                          "occViewport",
                                                          "occLineWidth",
                                                          "occLineFeather",
                                                          "occStipplePattern",
                                                          "occStippleFactor",
                                                          "occWireframeColor",
                                                          "occIsQuadMode",

                                                          "occOrthoScale",
                                                          "occSilhouetteThickness",

                                                          "occNbSpecIBLLevels"};

namespace
{

  static GLenum shaderTypeToGl(Graphic3d_TypeOfShaderObject theType)
  {
    switch (theType)
    {
      case Graphic3d_TOS_VERTEX:
        return GL_VERTEX_SHADER;
      case Graphic3d_TOS_FRAGMENT:
        return GL_FRAGMENT_SHADER;
      case Graphic3d_TOS_GEOMETRY:
        return GL_GEOMETRY_SHADER;
      case Graphic3d_TOS_TESS_CONTROL:
        return GL_TESS_CONTROL_SHADER;
      case Graphic3d_TOS_TESS_EVALUATION:
        return GL_TESS_EVALUATION_SHADER;
      case Graphic3d_TOS_COMPUTE:
        return GL_COMPUTE_SHADER;
    }
    return 0;
  }
} // namespace

OpenGl_VariableSetterSelector::OpenGl_VariableSetterSelector()
{

  mySetterList = OpenGl_HashMapInitializer::CreateListOf<size_t, OpenGl_SetterInterface*>(
    Graphic3d_UniformValueTypeID<int>::ID,
    new OpenGl_VariableSetter<int>())(Graphic3d_UniformValueTypeID<float>::ID,
                                      new OpenGl_VariableSetter<float>())(
    Graphic3d_UniformValueTypeID<NCollection_Vec2<float>>::ID,
    new OpenGl_VariableSetter<NCollection_Vec2<float>>())(
    Graphic3d_UniformValueTypeID<NCollection_Vec3<float>>::ID,
    new OpenGl_VariableSetter<NCollection_Vec3<float>>())(
    Graphic3d_UniformValueTypeID<NCollection_Vec4<float>>::ID,
    new OpenGl_VariableSetter<NCollection_Vec4<float>>())(
    Graphic3d_UniformValueTypeID<NCollection_Vec2<int>>::ID,
    new OpenGl_VariableSetter<NCollection_Vec2<int>>())(
    Graphic3d_UniformValueTypeID<NCollection_Vec3<int>>::ID,
    new OpenGl_VariableSetter<NCollection_Vec3<int>>())(
    Graphic3d_UniformValueTypeID<NCollection_Vec4<int>>::ID,
    new OpenGl_VariableSetter<NCollection_Vec4<int>>());
}

OpenGl_VariableSetterSelector::~OpenGl_VariableSetterSelector()
{
  for (NCollection_DataMap<size_t, OpenGl_SetterInterface*>::Iterator anIt(mySetterList);
       anIt.More();
       anIt.Next())
  {
    delete anIt.Value();
  }

  mySetterList.Clear();
}

void OpenGl_VariableSetterSelector::Set(const occ::handle<OpenGl_Context>&           theCtx,
                                        const occ::handle<Graphic3d_ShaderVariable>& theVariable,
                                        OpenGl_ShaderProgram* theProgram) const
{
  Standard_ASSERT_RETURN(mySetterList.IsBound(theVariable->Value()->TypeID()),
                         "The type of user-defined uniform variable is not supported...",
                         Standard_VOID_RETURN);

  mySetterList.Find(theVariable->Value()->TypeID())->Set(theCtx, theVariable, theProgram);
}

OpenGl_ShaderProgram::OpenGl_ShaderProgram(const occ::handle<Graphic3d_ShaderProgram>& theProxy,
                                           const TCollection_AsciiString&              theId)
    : OpenGl_NamedResource(!theProxy.IsNull() ? theProxy->GetId() : theId),
      myProgramID(NO_PROGRAM),
      myProxy(theProxy),
      myShareCount(1),
      myNbLightsMax(0),
      myNbShadowMaps(0),
      myNbClipPlanesMax(0),
      myNbFragOutputs(1),
      myTextureSetBits(Graphic3d_TextureSetBits_NONE),
      myOitOutput(Graphic3d_RTM_BLEND_UNORDERED),
      myHasAlphaTest(false),
      myHasTessShader(false)
{
  memset(myCurrentState, 0, sizeof(myCurrentState));
}

bool OpenGl_ShaderProgram::Initialize(
  const occ::handle<OpenGl_Context>&                               theCtx,
  const NCollection_Sequence<occ::handle<Graphic3d_ShaderObject>>& theShaders)
{
  myHasTessShader = false;
  if (theCtx.IsNull() || !Create(theCtx))
  {
    return false;
  }

  TCollection_AsciiString aHeaderVer =
    !myProxy.IsNull() ? myProxy->Header() : TCollection_AsciiString();
  int aShaderMask = 0;
  for (NCollection_Sequence<occ::handle<Graphic3d_ShaderObject>>::Iterator anIter(theShaders);
       anIter.More();
       anIter.Next())
  {
    aShaderMask |= anIter.Value()->Type();
  }
  myHasTessShader =
    (aShaderMask & (Graphic3d_TOS_TESS_CONTROL | Graphic3d_TOS_TESS_EVALUATION)) != 0;
  myNbFragOutputs  = !myProxy.IsNull() ? myProxy->NbFragmentOutputs() : 1;
  myTextureSetBits = Graphic3d_TextureSetBits_NONE;
  myHasAlphaTest   = !myProxy.IsNull() && myProxy->HasAlphaTest();
  myOitOutput      = !myProxy.IsNull() ? myProxy->OitOutput() : Graphic3d_RTM_BLEND_UNORDERED;
  if (myOitOutput == Graphic3d_RTM_BLEND_OIT && myNbFragOutputs < 2)
  {
    myOitOutput = Graphic3d_RTM_BLEND_UNORDERED;
  }
  else if (myOitOutput == Graphic3d_RTM_DEPTH_PEELING_OIT && myNbFragOutputs < 3)
  {
    myOitOutput = Graphic3d_RTM_BLEND_UNORDERED;
  }

  if (theCtx->GraphicsLibrary() == Aspect_GraphicsLibrary_OpenGLES)
  {
    if (myHasTessShader)
    {
      if (!theCtx->IsGlGreaterEqual(3, 2))
      {
        theCtx->PushMessage(GL_DEBUG_SOURCE_APPLICATION,
                            GL_DEBUG_TYPE_ERROR,
                            0,
                            GL_DEBUG_SEVERITY_HIGH,
                            "Error! Tessellation shader requires OpenGL ES 3.2+");
        return false;
      }
      else if (aHeaderVer.IsEmpty())
      {
        aHeaderVer = "#version 320 es";
      }
    }
    else if ((aShaderMask & Graphic3d_TOS_GEOMETRY) != 0)
    {
      switch (theCtx->hasGeometryStage)
      {
        case OpenGl_FeatureNotAvailable:
        {
          theCtx->PushMessage(
            GL_DEBUG_SOURCE_APPLICATION,
            GL_DEBUG_TYPE_ERROR,
            0,
            GL_DEBUG_SEVERITY_HIGH,
            "Error! Geometry shader requires OpenGL ES 3.2+ or GL_EXT_geometry_shader");
          return false;
        }
        case OpenGl_FeatureInExtensions:
        {
          if (aHeaderVer.IsEmpty())
          {
            aHeaderVer = "#version 310 es";
          }
          break;
        }
        case OpenGl_FeatureInCore:
        {
          if (aHeaderVer.IsEmpty())
          {
            aHeaderVer = "#version 320 es";
          }
          break;
        }
      }
    }
    else if ((aShaderMask & Graphic3d_TOS_COMPUTE) != 0)
    {
      if (!theCtx->IsGlGreaterEqual(3, 1))
      {
        theCtx->PushMessage(GL_DEBUG_SOURCE_APPLICATION,
                            GL_DEBUG_TYPE_ERROR,
                            0,
                            GL_DEBUG_SEVERITY_HIGH,
                            "Error! Compute shaders require OpenGL ES 3.1+");
        return false;
      }
      else if (aHeaderVer.IsEmpty())
      {
        aHeaderVer = "#version 310 es";
      }
    }
  }
  else
  {
    if ((aShaderMask & Graphic3d_TOS_COMPUTE) != 0)
    {
      if (!theCtx->IsGlGreaterEqual(4, 3))
      {
        theCtx->PushMessage(GL_DEBUG_SOURCE_APPLICATION,
                            GL_DEBUG_TYPE_ERROR,
                            0,
                            GL_DEBUG_SEVERITY_HIGH,
                            "Error! Compute shaders require OpenGL 4.3+");
        return false;
      }
      else if (aHeaderVer.IsEmpty())
      {
        aHeaderVer = "#version 430";
      }
    }
    else if (myHasTessShader)
    {
      if (!theCtx->IsGlGreaterEqual(4, 0))
      {
        theCtx->PushMessage(GL_DEBUG_SOURCE_APPLICATION,
                            GL_DEBUG_TYPE_ERROR,
                            0,
                            GL_DEBUG_SEVERITY_HIGH,
                            "Error! Tessellation shaders require OpenGL 4.0+");
        return false;
      }
      else if (aHeaderVer.IsEmpty())
      {
        aHeaderVer = "#version 400";
      }
    }
    else if ((aShaderMask & Graphic3d_TOS_GEOMETRY) != 0)
    {
      if (!theCtx->IsGlGreaterEqual(3, 2))
      {
        theCtx->PushMessage(GL_DEBUG_SOURCE_APPLICATION,
                            GL_DEBUG_TYPE_ERROR,
                            0,
                            GL_DEBUG_SEVERITY_HIGH,
                            "Error! Geometry shaders require OpenGL 3.2+");
        return false;
      }
      else if (aHeaderVer.IsEmpty())
      {
        aHeaderVer = "#version 150";
      }
    }
  }

  for (NCollection_Sequence<occ::handle<Graphic3d_ShaderObject>>::Iterator anIter(theShaders);
       anIter.More();
       anIter.Next())
  {
    if (!anIter.Value()->IsDone())
    {
      const TCollection_ExtendedString aMsg = "Error! Failed to get shader source";
      theCtx->PushMessage(GL_DEBUG_SOURCE_APPLICATION,
                          GL_DEBUG_TYPE_ERROR,
                          0,
                          GL_DEBUG_SEVERITY_HIGH,
                          aMsg);
      return false;
    }

    const GLenum aShaderType = shaderTypeToGl(anIter.Value()->Type());
    if (aShaderType == 0)
    {
      return false;
    }

    occ::handle<OpenGl_ShaderObject> aShader = new OpenGl_ShaderObject(aShaderType);
    if (!aShader->Create(theCtx))
    {
      aShader->Release(theCtx.operator->());
      return false;
    }

    TCollection_AsciiString anExtensions = "// Enable extensions used in OCCT GLSL programs\n";
    if (myNbFragOutputs > 1)
    {
      if (theCtx->hasDrawBuffers)
      {
        anExtensions += "#define OCC_ENABLE_draw_buffers\n";
        switch (myOitOutput)
        {
          case Graphic3d_RTM_BLEND_UNORDERED:
            break;
          case Graphic3d_RTM_BLEND_OIT:
            anExtensions += "#define OCC_WRITE_WEIGHT_OIT_COVERAGE\n";
            break;
          case Graphic3d_RTM_DEPTH_PEELING_OIT:
            anExtensions += "#define OCC_DEPTH_PEEL_OIT\n";
            break;
        }
      }
      else
      {
        theCtx->PushMessage(
          GL_DEBUG_SOURCE_APPLICATION,
          GL_DEBUG_TYPE_ERROR,
          0,
          GL_DEBUG_SEVERITY_HIGH,
          "Error! Multiple draw buffers required by the program, but aren't supported by OpenGL");
        return false;
      }

      if (theCtx->hasDrawBuffers == OpenGl_FeatureInExtensions)
      {
        if (theCtx->arbDrawBuffers)
        {
          anExtensions += "#extension GL_ARB_draw_buffers : enable\n";
        }
        else if (theCtx->extDrawBuffers)
        {
          anExtensions += "#extension GL_EXT_draw_buffers : enable\n";
        }
      }
    }
    if (myHasAlphaTest)
    {
      anExtensions += "#define OCC_ALPHA_TEST\n";
    }

    if (theCtx->hasSampleVariables == OpenGl_FeatureInExtensions)
    {
      if (theCtx->GraphicsLibrary() == Aspect_GraphicsLibrary_OpenGLES
          && theCtx->oesSampleVariables)
      {
        anExtensions += "#extension GL_OES_sample_variables : enable\n";
      }
      else if (theCtx->GraphicsLibrary() == Aspect_GraphicsLibrary_OpenGL
               && theCtx->arbSampleShading)
      {
        anExtensions += "#extension GL_ARB_sample_shading : enable\n";
      }
    }

    if (theCtx->GraphicsLibrary() == Aspect_GraphicsLibrary_OpenGLES
        && theCtx->hasGeometryStage == OpenGl_FeatureInExtensions)
    {
      anExtensions += "#extension GL_EXT_geometry_shader : enable\n"
                      "#extension GL_EXT_shader_io_blocks : enable\n";
    }

    TCollection_AsciiString aPrecisionHeader;
    if (anIter.Value()->Type() == Graphic3d_TOS_FRAGMENT
        && theCtx->GraphicsLibrary() == Aspect_GraphicsLibrary_OpenGLES)
    {
      aPrecisionHeader = theCtx->hasHighp ? "precision highp float;\n"
                                            "precision highp int;\n"
                                          : "precision mediump float;\n"
                                            "precision mediump int;\n";
    }

    TCollection_AsciiString aHeaderType;
    switch (anIter.Value()->Type())
    {
      case Graphic3d_TOS_COMPUTE:
      {
        aHeaderType = "#define COMPUTE_SHADER\n";
        break;
      }
      case Graphic3d_TOS_VERTEX:
      {
        aHeaderType = "#define VERTEX_SHADER\n";
        break;
      }
      case Graphic3d_TOS_TESS_CONTROL:
      {
        aHeaderType = "#define TESS_CONTROL_SHADER\n";
        break;
      }
      case Graphic3d_TOS_TESS_EVALUATION:
      {
        aHeaderType = "#define TESS_EVALUATION_SHADER\n";
        break;
      }
      case Graphic3d_TOS_GEOMETRY:
      {
        aHeaderType = "#define GEOMETRY_SHADER\n";
        break;
      }
      case Graphic3d_TOS_FRAGMENT:
      {
        aHeaderType = "#define FRAGMENT_SHADER\n";
        break;
      }
    }

    TCollection_AsciiString aHeaderConstants;
    myNbLightsMax     = !myProxy.IsNull() ? myProxy->NbLightsMax() : 0;
    myNbShadowMaps    = !myProxy.IsNull() ? myProxy->NbShadowMaps() : 0;
    myNbClipPlanesMax = !myProxy.IsNull() ? myProxy->NbClipPlanesMax() : 0;
    aHeaderConstants += TCollection_AsciiString("#define THE_MAX_LIGHTS ") + myNbLightsMax + "\n";
    aHeaderConstants +=
      TCollection_AsciiString("#define THE_MAX_CLIP_PLANES ") + myNbClipPlanesMax + "\n";
    aHeaderConstants +=
      TCollection_AsciiString("#define THE_NB_FRAG_OUTPUTS ") + myNbFragOutputs + "\n";
    if (myNbShadowMaps > 0)
    {
      aHeaderConstants +=
        TCollection_AsciiString("#define THE_NB_SHADOWMAPS ") + myNbShadowMaps + "\n";
    }
    if (theCtx->caps->useZeroToOneDepth && theCtx->arbClipControl)
    {
      aHeaderConstants += "#define THE_ZERO_TO_ONE_DEPTH\n";
    }
    if (!myProxy.IsNull() && myProxy->HasDefaultSampler())
    {
      aHeaderConstants += "#define THE_HAS_DEFAULT_SAMPLER\n";
    }
    if (!myProxy.IsNull())
    {
      if (myProxy->IsPBR())
      {
        aHeaderConstants += "#define THE_IS_PBR\n";
      }
      if ((myProxy->TextureSetBits() & Graphic3d_TextureSetBits_BaseColor) != 0)
      {
        aHeaderConstants += "#define THE_HAS_TEXTURE_COLOR\n";
      }
      if ((myProxy->TextureSetBits() & Graphic3d_TextureSetBits_Emissive) != 0)
      {
        aHeaderConstants += "#define THE_HAS_TEXTURE_EMISSIVE\n";
      }
      if ((myProxy->TextureSetBits() & Graphic3d_TextureSetBits_Normal) != 0)
      {
        aHeaderConstants += "#define THE_HAS_TEXTURE_NORMAL\n";
      }
      if ((myProxy->TextureSetBits() & Graphic3d_TextureSetBits_Occlusion) != 0)
      {
        aHeaderConstants += "#define THE_HAS_TEXTURE_OCCLUSION\n";
      }
      if ((myProxy->TextureSetBits() & Graphic3d_TextureSetBits_MetallicRoughness) != 0)
      {
        aHeaderConstants += "#define THE_HAS_TEXTURE_METALROUGHNESS\n";
      }
    }

    const TCollection_AsciiString aSource =
      aHeaderVer + (!aHeaderVer.IsEmpty() ? "\n" : "") + anExtensions + aPrecisionHeader
      + aHeaderType + aHeaderConstants + Shaders_Declarations_glsl + Shaders_DeclarationsImpl_glsl

      + anIter.Value()->Source();

    if (!aShader->LoadAndCompile(theCtx, myResourceId, aSource))
    {
      aShader->Release(theCtx.operator->());
      return false;
    }

    if (theCtx->caps->glslDumpLevel)
    {
      TCollection_AsciiString anOutputSource = aSource;
      if (theCtx->caps->glslDumpLevel == OpenGl_ShaderProgramDumpLevel_Short)
      {
        anOutputSource = aHeaderVer + (!aHeaderVer.IsEmpty() ? "\n" : "") + anExtensions
                         + aPrecisionHeader + aHeaderType + aHeaderConstants
                         + anIter.Value()->Source();
      }
      aShader->DumpSourceCode(theCtx, myResourceId, anOutputSource);
    }

    if (!AttachShader(theCtx, aShader))
    {
      aShader->Release(theCtx.operator->());
      return false;
    }
  }

  SetAttributeName(theCtx, Graphic3d_TOA_POS, "occVertex");
  SetAttributeName(theCtx, Graphic3d_TOA_NORM, "occNormal");
  SetAttributeName(theCtx, Graphic3d_TOA_UV, "occTexCoord");
  SetAttributeName(theCtx, Graphic3d_TOA_COLOR, "occVertColor");

  if (!myProxy.IsNull())
  {
    for (NCollection_Sequence<occ::handle<Graphic3d_ShaderAttribute>>::Iterator anAttribIter(
           myProxy->VertexAttributes());
         anAttribIter.More();
         anAttribIter.Next())
    {
      SetAttributeName(theCtx,
                       anAttribIter.Value()->Location(),
                       anAttribIter.Value()->Name().ToCString());
    }
  }

  if (!Link(theCtx))
  {
    return false;
  }

  const occ::handle<OpenGl_ShaderProgram>& anOldProgram = theCtx->ActiveProgram();
  theCtx->core20fwd->glUseProgram(myProgramID);
  if (const OpenGl_ShaderUniformLocation aLocTexEnable =
        GetStateLocation(OpenGl_OCCT_TEXTURE_ENABLE))
  {
    SetUniform(theCtx, aLocTexEnable, 0);
  }
  if (const OpenGl_ShaderUniformLocation aLocSampler =
        GetUniformLocation(theCtx, "occActiveSampler"))
  {
    SetUniform(theCtx, aLocSampler, GLint(Graphic3d_TextureUnit_0));
  }
  if (const OpenGl_ShaderUniformLocation aLocSampler =
        GetUniformLocation(theCtx, "occSamplerBaseColor"))
  {
    myTextureSetBits |= Graphic3d_TextureSetBits_BaseColor;
    SetUniform(theCtx, aLocSampler, GLint(Graphic3d_TextureUnit_BaseColor));
  }
  if (const OpenGl_ShaderUniformLocation aLocSampler =
        GetUniformLocation(theCtx, "occSamplerPointSprite"))
  {

    SetUniform(theCtx, aLocSampler, GLint(theCtx->SpriteTextureUnit()));
  }
  if (const OpenGl_ShaderUniformLocation aLocSampler =
        GetUniformLocation(theCtx, "occSamplerMetallicRoughness"))
  {
    myTextureSetBits |= Graphic3d_TextureSetBits_MetallicRoughness;
    SetUniform(theCtx, aLocSampler, GLint(Graphic3d_TextureUnit_MetallicRoughness));
  }
  if (const OpenGl_ShaderUniformLocation aLocSampler =
        GetUniformLocation(theCtx, "occSamplerEmissive"))
  {
    myTextureSetBits |= Graphic3d_TextureSetBits_Emissive;
    SetUniform(theCtx, aLocSampler, GLint(Graphic3d_TextureUnit_Emissive));
  }
  if (const OpenGl_ShaderUniformLocation aLocSampler =
        GetUniformLocation(theCtx, "occSamplerOcclusion"))
  {
    myTextureSetBits |= Graphic3d_TextureSetBits_Occlusion;
    SetUniform(theCtx, aLocSampler, GLint(Graphic3d_TextureUnit_Occlusion));
  }
  if (const OpenGl_ShaderUniformLocation aLocSampler =
        GetUniformLocation(theCtx, "occSamplerNormal"))
  {
    myTextureSetBits |= Graphic3d_TextureSetBits_Normal;
    SetUniform(theCtx, aLocSampler, GLint(Graphic3d_TextureUnit_Normal));
  }
  if (const OpenGl_ShaderUniformLocation aLocSampler =
        GetUniformLocation(theCtx, "occDiffIBLMapSHCoeffs"))
  {
    SetUniform(theCtx, aLocSampler, GLint(theCtx->PBRDiffIBLMapSHTexUnit()));
  }
  if (const OpenGl_ShaderUniformLocation aLocSampler = GetUniformLocation(theCtx, "occSpecIBLMap"))
  {
    SetUniform(theCtx, aLocSampler, GLint(theCtx->PBRSpecIBLMapTexUnit()));
  }
  if (const OpenGl_ShaderUniformLocation aLocSampler = GetUniformLocation(theCtx, "occEnvLUT"))
  {
    SetUniform(theCtx, aLocSampler, GLint(theCtx->PBREnvLUTTexUnit()));
  }
  if (const OpenGl_ShaderUniformLocation aLocSampler =
        GetUniformLocation(theCtx, "occShadowMapSamplers"))
  {
    std::vector<GLint> aShadowSamplers(myNbShadowMaps);
    const GLint        aSamplFrom = GLint(theCtx->ShadowMapTexUnit()) - myNbShadowMaps + 1;
    for (int aSamplerIter = 0; aSamplerIter < myNbShadowMaps; ++aSamplerIter)
    {
      aShadowSamplers[aSamplerIter] = aSamplFrom + aSamplerIter;
    }
    SetUniform(theCtx, aLocSampler, myNbShadowMaps, &aShadowSamplers.front());
  }

  if (const OpenGl_ShaderUniformLocation aLocSampler =
        GetUniformLocation(theCtx, "occDepthPeelingDepth"))
  {
    SetUniform(theCtx, aLocSampler, GLint(theCtx->DepthPeelingDepthTexUnit()));
  }
  if (const OpenGl_ShaderUniformLocation aLocSampler =
        GetUniformLocation(theCtx, "occDepthPeelingFrontColor"))
  {
    SetUniform(theCtx, aLocSampler, GLint(theCtx->DepthPeelingFrontColorTexUnit()));
  }

  const TCollection_AsciiString aSamplerNamePrefix("occSampler");
  const int                     aNbUnitsMax =
    std::max(theCtx->MaxCombinedTextureUnits(), static_cast<int>(Graphic3d_TextureUnit_NB));
  for (GLint aUnitIter = 0; aUnitIter < aNbUnitsMax; ++aUnitIter)
  {
    const TCollection_AsciiString aName = aSamplerNamePrefix + aUnitIter;
    if (const OpenGl_ShaderUniformLocation aLocSampler =
          GetUniformLocation(theCtx, aName.ToCString()))
    {
      SetUniform(theCtx, aLocSampler, aUnitIter);
    }
  }

  theCtx->core20fwd->glUseProgram(!anOldProgram.IsNull() ? anOldProgram->ProgramId()
                                                         : OpenGl_ShaderProgram::NO_PROGRAM);
  return true;
}

OpenGl_ShaderProgram::~OpenGl_ShaderProgram()
{
  Release(nullptr);
}

bool OpenGl_ShaderProgram::AttachShader(const occ::handle<OpenGl_Context>&      theCtx,
                                        const occ::handle<OpenGl_ShaderObject>& theShader)
{
  if (myProgramID == NO_PROGRAM || theShader.IsNull())
  {
    return false;
  }

  for (NCollection_Sequence<occ::handle<OpenGl_ShaderObject>>::Iterator anIter(myShaderObjects);
       anIter.More();
       anIter.Next())
  {
    if (theShader == anIter.Value())
    {
      return false;
    }
  }

  myShaderObjects.Append(theShader);
  theCtx->core20fwd->glAttachShader(myProgramID, theShader->myShaderID);
  return true;
}

bool OpenGl_ShaderProgram::DetachShader(const occ::handle<OpenGl_Context>&      theCtx,
                                        const occ::handle<OpenGl_ShaderObject>& theShader)
{
  if (myProgramID == NO_PROGRAM || theShader.IsNull())
  {
    return false;
  }

  NCollection_Sequence<occ::handle<OpenGl_ShaderObject>>::Iterator anIter(myShaderObjects);
  while (anIter.More())
  {
    if (theShader == anIter.Value())
    {
      myShaderObjects.Remove(anIter);
      break;
    }

    anIter.Next();
  }

  if (!anIter.More())
  {
    return false;
  }

  theCtx->core20fwd->glDetachShader(myProgramID, theShader->myShaderID);
  return true;
}

bool OpenGl_ShaderProgram::link(const occ::handle<OpenGl_Context>& theCtx)
{
  if (myProgramID == NO_PROGRAM)
  {
    return false;
  }

  GLint aStatus = GL_FALSE;
  theCtx->core20fwd->glLinkProgram(myProgramID);
  theCtx->core20fwd->glGetProgramiv(myProgramID, GL_LINK_STATUS, &aStatus);
  if (aStatus == GL_FALSE)
  {
    return false;
  }

  memset(myCurrentState, 0, sizeof(myCurrentState));
  for (GLint aVar = 0; aVar < OpenGl_OCCT_NUMBER_OF_STATE_VARIABLES; ++aVar)
  {
    myStateLocations[aVar] = GetUniformLocation(theCtx, PredefinedKeywords[aVar]);
  }
  return true;
}

bool OpenGl_ShaderProgram::Link(const occ::handle<OpenGl_Context>& theCtx, bool theIsVerbose)
{
  if (!theIsVerbose)
  {
    return link(theCtx);
  }

  if (!link(theCtx))
  {
    TCollection_AsciiString aLog;
    FetchInfoLog(theCtx, aLog);
    if (aLog.IsEmpty())
    {
      aLog = "Linker log is empty.";
    }
    theCtx->PushMessage(GL_DEBUG_SOURCE_APPLICATION,
                        GL_DEBUG_TYPE_ERROR,
                        0,
                        GL_DEBUG_SEVERITY_HIGH,
                        TCollection_AsciiString("Failed to link program object [") + myResourceId
                          + "]! Linker log:\n" + aLog);
    return false;
  }
  else if (theCtx->caps->glslWarnings)
  {
    TCollection_AsciiString aLog;
    FetchInfoLog(theCtx, aLog);
    if (!aLog.IsEmpty() && !aLog.IsEqual("No errors.\n"))
    {
      theCtx->PushMessage(GL_DEBUG_SOURCE_APPLICATION,
                          GL_DEBUG_TYPE_PORTABILITY,
                          0,
                          GL_DEBUG_SEVERITY_LOW,
                          TCollection_AsciiString("GLSL linker log [") + myResourceId + "]:\n"
                            + aLog);
    }
  }
  return true;
}

bool OpenGl_ShaderProgram::FetchInfoLog(const occ::handle<OpenGl_Context>& theCtx,
                                        TCollection_AsciiString&           theOutput)
{
  if (myProgramID == NO_PROGRAM)
  {
    return false;
  }

  GLint aLength = 0;
  theCtx->core20fwd->glGetProgramiv(myProgramID, GL_INFO_LOG_LENGTH, &aLength);
  if (aLength > 0)
  {
    GLchar* aLog = (GLchar*)alloca(aLength);
    memset(aLog, 0, aLength);
    theCtx->core20fwd->glGetProgramInfoLog(myProgramID, aLength, nullptr, aLog);
    theOutput = aLog;
  }
  return true;
}

bool OpenGl_ShaderProgram::ApplyVariables(const occ::handle<OpenGl_Context>& theCtx)
{
  if (myProxy.IsNull() || myProxy->Variables().IsEmpty())
  {
    return false;
  }

  for (NCollection_Sequence<occ::handle<Graphic3d_ShaderVariable>>::Iterator anIter(
         myProxy->Variables());
       anIter.More();
       anIter.Next())
  {
    mySetterSelector.Set(theCtx, anIter.Value(), this);
  }

  myProxy->ClearVariables();
  return true;
}

OpenGl_ShaderUniformLocation OpenGl_ShaderProgram::GetUniformLocation(
  const occ::handle<OpenGl_Context>& theCtx,
  const GLchar*                      theName) const
{
  return OpenGl_ShaderUniformLocation(
    myProgramID != NO_PROGRAM ? theCtx->core20fwd->glGetUniformLocation(myProgramID, theName)
                              : INVALID_LOCATION);
}

GLint OpenGl_ShaderProgram::GetAttributeLocation(const occ::handle<OpenGl_Context>& theCtx,
                                                 const GLchar*                      theName) const
{
  return myProgramID != NO_PROGRAM ? theCtx->core20fwd->glGetAttribLocation(myProgramID, theName)
                                   : INVALID_LOCATION;
}

bool OpenGl_ShaderProgram::GetUniform(const occ::handle<OpenGl_Context>& theCtx,
                                      GLint                              theLocation,
                                      NCollection_Vec4<int>&             theValue) const
{
  if (myProgramID == NO_PROGRAM || theLocation == INVALID_LOCATION)
  {
    return false;
  }

  theCtx->core20fwd->glGetUniformiv(myProgramID, theLocation, theValue);
  return true;
}

bool OpenGl_ShaderProgram::GetUniform(const occ::handle<OpenGl_Context>& theCtx,
                                      GLint                              theLocation,
                                      NCollection_Vec4<float>&           theValue) const
{
  if (myProgramID == NO_PROGRAM || theLocation == INVALID_LOCATION)
  {
    return false;
  }

  theCtx->core20fwd->glGetUniformfv(myProgramID, theLocation, theValue);
  return true;
}

bool OpenGl_ShaderProgram::GetAttribute(const occ::handle<OpenGl_Context>& theCtx,
                                        GLint                              theIndex,
                                        NCollection_Vec4<int>&             theValue) const
{
  if (myProgramID == NO_PROGRAM || theIndex == INVALID_LOCATION)
  {
    return false;
  }

  theCtx->core20fwd->glGetVertexAttribiv(theIndex, GL_CURRENT_VERTEX_ATTRIB, theValue);
  return true;
}

bool OpenGl_ShaderProgram::GetAttribute(const occ::handle<OpenGl_Context>& theCtx,
                                        GLint                              theIndex,
                                        NCollection_Vec4<float>&           theValue) const
{
  if (myProgramID == NO_PROGRAM || theIndex == INVALID_LOCATION)
  {
    return false;
  }

  theCtx->core20fwd->glGetVertexAttribfv(theIndex, GL_CURRENT_VERTEX_ATTRIB, theValue);
  return true;
}

bool OpenGl_ShaderProgram::SetAttributeName(const occ::handle<OpenGl_Context>& theCtx,
                                            GLint                              theIndex,
                                            const GLchar*                      theName)
{
  theCtx->core20fwd->glBindAttribLocation(myProgramID, theIndex, theName);
  return true;
}

bool OpenGl_ShaderProgram::SetAttribute(const occ::handle<OpenGl_Context>& theCtx,
                                        GLint                              theIndex,
                                        GLfloat                            theValue)
{
  if (myProgramID == NO_PROGRAM || theIndex == INVALID_LOCATION)
  {
    return false;
  }

  theCtx->core20fwd->glVertexAttrib1f(theIndex, theValue);
  return true;
}

bool OpenGl_ShaderProgram::SetAttribute(const occ::handle<OpenGl_Context>& theCtx,
                                        GLint                              theIndex,
                                        const NCollection_Vec2<float>&     theValue)
{
  if (myProgramID == NO_PROGRAM || theIndex == INVALID_LOCATION)
  {
    return false;
  }

  theCtx->core20fwd->glVertexAttrib2fv(theIndex, theValue);
  return true;
}

bool OpenGl_ShaderProgram::SetAttribute(const occ::handle<OpenGl_Context>& theCtx,
                                        GLint                              theIndex,
                                        const NCollection_Vec3<float>&     theValue)
{
  if (myProgramID == NO_PROGRAM || theIndex == INVALID_LOCATION)
  {
    return false;
  }

  theCtx->core20fwd->glVertexAttrib3fv(theIndex, theValue);
  return true;
}

bool OpenGl_ShaderProgram::SetAttribute(const occ::handle<OpenGl_Context>& theCtx,
                                        GLint                              theIndex,
                                        const NCollection_Vec4<float>&     theValue)
{
  if (myProgramID == NO_PROGRAM || theIndex == INVALID_LOCATION)
  {
    return false;
  }

  theCtx->core20fwd->glVertexAttrib4fv(theIndex, theValue);
  return true;
}

bool OpenGl_ShaderProgram::SetUniform(const occ::handle<OpenGl_Context>& theCtx,
                                      GLint                              theLocation,
                                      GLint                              theValue)
{
  if (myProgramID == NO_PROGRAM || theLocation == INVALID_LOCATION)
  {
    return false;
  }

  theCtx->core20fwd->glUniform1i(theLocation, theValue);
  return true;
}

bool OpenGl_ShaderProgram::SetUniform(const occ::handle<OpenGl_Context>&    theCtx,
                                      GLint                                 theLocation,
                                      const NCollection_Vec2<unsigned int>& theValue)
{
  if (myProgramID == NO_PROGRAM || theLocation == INVALID_LOCATION)
  {
    return false;
  }

  if (theCtx->GraphicsLibrary() == Aspect_GraphicsLibrary_OpenGLES)
  {
    if (theCtx->core30 != nullptr)
    {
      theCtx->core30->glUniform2uiv(theLocation, 1, theValue.GetData());
      return true;
    }
  }
  else
  {
    if (theCtx->core32 != nullptr)
    {
      theCtx->core32->glUniform2uiv(theLocation, 1, theValue.GetData());
      return true;
    }
  }

  return false;
}

bool OpenGl_ShaderProgram::SetUniform(const occ::handle<OpenGl_Context>&    theCtx,
                                      const GLchar*                         theName,
                                      const GLsizei                         theCount,
                                      const NCollection_Vec2<unsigned int>* theValue)
{
  return SetUniform(theCtx, GetUniformLocation(theCtx, theName), theCount, theValue);
}

bool OpenGl_ShaderProgram::SetUniform(const occ::handle<OpenGl_Context>&    theCtx,
                                      GLint                                 theLocation,
                                      const GLsizei                         theCount,
                                      const NCollection_Vec2<unsigned int>* theValue)
{
  if (myProgramID == NO_PROGRAM || theLocation == INVALID_LOCATION)
  {
    return false;
  }

  if (theCtx->GraphicsLibrary() == Aspect_GraphicsLibrary_OpenGLES)
  {
    if (theCtx->core30 != nullptr)
    {
      theCtx->core30->glUniform2uiv(theLocation, theCount, theValue->GetData());
      return true;
    }
  }
  else
  {
    if (theCtx->core32 != nullptr)
    {
      theCtx->core32->glUniform2uiv(theLocation, theCount, theValue->GetData());
      return true;
    }
  }
  return false;
}

bool OpenGl_ShaderProgram::SetUniform(const occ::handle<OpenGl_Context>& theCtx,
                                      GLint                              theLocation,
                                      GLfloat                            theValue)
{
  if (myProgramID == NO_PROGRAM || theLocation == INVALID_LOCATION)
  {
    return false;
  }

  theCtx->core20fwd->glUniform1f(theLocation, theValue);
  return true;
}

bool OpenGl_ShaderProgram::SetUniform(const occ::handle<OpenGl_Context>& theCtx,
                                      GLint                              theLocation,
                                      const NCollection_Vec2<int>&       theValue)
{
  if (myProgramID == NO_PROGRAM || theLocation == INVALID_LOCATION)
  {
    return false;
  }

  theCtx->core20fwd->glUniform2iv(theLocation, 1, theValue);
  return true;
}

bool OpenGl_ShaderProgram::SetUniform(const occ::handle<OpenGl_Context>& theCtx,
                                      GLint                              theLocation,
                                      const NCollection_Vec3<int>&       theValue)
{
  if (myProgramID == NO_PROGRAM || theLocation == INVALID_LOCATION)
  {
    return false;
  }

  theCtx->core20fwd->glUniform3iv(theLocation, 1, theValue);
  return true;
}

bool OpenGl_ShaderProgram::SetUniform(const occ::handle<OpenGl_Context>& theCtx,
                                      GLint                              theLocation,
                                      const NCollection_Vec4<int>&       theValue)
{
  if (myProgramID == NO_PROGRAM || theLocation == INVALID_LOCATION)
  {
    return false;
  }

  theCtx->core20fwd->glUniform4iv(theLocation, 1, theValue);
  return true;
}

bool OpenGl_ShaderProgram::SetUniform(const occ::handle<OpenGl_Context>& theCtx,
                                      GLint                              theLocation,
                                      const NCollection_Vec2<float>&     theValue)
{
  if (myProgramID == NO_PROGRAM || theLocation == INVALID_LOCATION)
  {
    return false;
  }

  theCtx->core20fwd->glUniform2fv(theLocation, 1, theValue);
  return true;
}

bool OpenGl_ShaderProgram::SetUniform(const occ::handle<OpenGl_Context>& theCtx,
                                      GLint                              theLocation,
                                      const NCollection_Vec3<float>&     theValue)
{
  if (myProgramID == NO_PROGRAM || theLocation == INVALID_LOCATION)
  {
    return false;
  }

  theCtx->core20fwd->glUniform3fv(theLocation, 1, theValue);
  return true;
}

bool OpenGl_ShaderProgram::SetUniform(const occ::handle<OpenGl_Context>& theCtx,
                                      GLint                              theLocation,
                                      const NCollection_Vec4<float>&     theValue)
{
  if (myProgramID == NO_PROGRAM || theLocation == INVALID_LOCATION)
  {
    return false;
  }

  theCtx->core20fwd->glUniform4fv(theLocation, 1, theValue);
  return true;
}

bool OpenGl_ShaderProgram::SetUniform(const occ::handle<OpenGl_Context>& theCtx,
                                      GLint                              theLocation,
                                      GLuint                             theCount,
                                      const NCollection_Mat3<float>*     theData)
{
  if (myProgramID == NO_PROGRAM || theLocation == INVALID_LOCATION)
  {
    return false;
  }

  theCtx->core20fwd->glUniformMatrix3fv(theLocation, theCount, GL_FALSE, theData->GetData());
  return true;
}

bool OpenGl_ShaderProgram::SetUniform(const occ::handle<OpenGl_Context>& theCtx,
                                      GLint                              theLocation,
                                      const NCollection_Mat4<float>&     theValue,
                                      GLboolean                          theTranspose)
{
  if (myProgramID == NO_PROGRAM || theLocation == INVALID_LOCATION)
  {
    return false;
  }

  theCtx->core20fwd->glUniformMatrix4fv(theLocation,
                                        1,
                                        GL_FALSE,
                                        theTranspose ? theValue.Transposed().GetData()
                                                     : theValue.GetData());
  return true;
}

bool OpenGl_ShaderProgram::SetUniform(const occ::handle<OpenGl_Context>& theCtx,
                                      GLint                              theLocation,
                                      GLuint                             theCount,
                                      const NCollection_Mat4<float>*     theData)
{
  if (myProgramID == NO_PROGRAM || theLocation == INVALID_LOCATION)
  {
    return false;
  }

  theCtx->core20fwd->glUniformMatrix4fv(theLocation, theCount, GL_FALSE, theData->GetData());
  return true;
}

bool OpenGl_ShaderProgram::SetUniform(const occ::handle<OpenGl_Context>& theCtx,
                                      GLint                              theLocation,
                                      GLuint                             theCount,
                                      const float*                       theData)
{
  if (myProgramID == NO_PROGRAM || theLocation == INVALID_LOCATION)
  {
    return false;
  }

  theCtx->core20fwd->glUniform1fv(theLocation, theCount, theData);
  return true;
}

bool OpenGl_ShaderProgram::SetUniform(const occ::handle<OpenGl_Context>& theCtx,
                                      GLint                              theLocation,
                                      GLuint                             theCount,
                                      const NCollection_Vec2<float>*     theData)
{
  if (myProgramID == NO_PROGRAM || theLocation == INVALID_LOCATION)
  {
    return false;
  }

  theCtx->core20fwd->glUniform2fv(theLocation, theCount, theData[0].GetData());
  return true;
}

bool OpenGl_ShaderProgram::SetUniform(const occ::handle<OpenGl_Context>& theCtx,
                                      GLint                              theLocation,
                                      GLuint                             theCount,
                                      const NCollection_Vec3<float>*     theData)
{
  if (myProgramID == NO_PROGRAM || theLocation == INVALID_LOCATION)
  {
    return false;
  }

  theCtx->core20fwd->glUniform3fv(theLocation, theCount, theData[0].GetData());
  return true;
}

bool OpenGl_ShaderProgram::SetUniform(const occ::handle<OpenGl_Context>& theCtx,
                                      GLint                              theLocation,
                                      GLuint                             theCount,
                                      const NCollection_Vec4<float>*     theData)
{
  if (myProgramID == NO_PROGRAM || theLocation == INVALID_LOCATION)
  {
    return false;
  }

  theCtx->core20fwd->glUniform4fv(theLocation, theCount, theData[0].GetData());
  return true;
}

bool OpenGl_ShaderProgram::SetUniform(const occ::handle<OpenGl_Context>& theCtx,
                                      GLint                              theLocation,
                                      GLuint                             theCount,
                                      const int*                         theData)
{
  if (myProgramID == NO_PROGRAM || theLocation == INVALID_LOCATION)
  {
    return false;
  }

  theCtx->core20fwd->glUniform1iv(theLocation, theCount, theData);
  return true;
}

bool OpenGl_ShaderProgram::SetUniform(const occ::handle<OpenGl_Context>& theCtx,
                                      GLint                              theLocation,
                                      GLuint                             theCount,
                                      const NCollection_Vec2<int>*       theData)
{
  if (myProgramID == NO_PROGRAM || theLocation == INVALID_LOCATION)
  {
    return false;
  }

  theCtx->core20fwd->glUniform2iv(theLocation, theCount, theData[0].GetData());
  return true;
}

bool OpenGl_ShaderProgram::SetUniform(const occ::handle<OpenGl_Context>& theCtx,
                                      GLint                              theLocation,
                                      GLuint                             theCount,
                                      const NCollection_Vec3<int>*       theData)
{
  if (myProgramID == NO_PROGRAM || theLocation == INVALID_LOCATION)
  {
    return false;
  }

  theCtx->core20fwd->glUniform3iv(theLocation, theCount, theData[0].GetData());
  return true;
}

bool OpenGl_ShaderProgram::SetUniform(const occ::handle<OpenGl_Context>& theCtx,
                                      GLint                              theLocation,
                                      GLuint                             theCount,
                                      const NCollection_Vec4<int>*       theData)
{
  if (myProgramID == NO_PROGRAM || theLocation == INVALID_LOCATION)
  {
    return false;
  }

  theCtx->core20fwd->glUniform4iv(theLocation, theCount, theData[0].GetData());
  return true;
}

bool OpenGl_ShaderProgram::SetSampler(const occ::handle<OpenGl_Context>& theCtx,
                                      GLint                              theLocation,
                                      const Graphic3d_TextureUnit        theTextureUnit)
{
  if (myProgramID == NO_PROGRAM || theLocation == INVALID_LOCATION)
  {
    return false;
  }

  theCtx->core20fwd->glUniform1i(theLocation, theTextureUnit);
  return true;
}

bool OpenGl_ShaderProgram::Create(const occ::handle<OpenGl_Context>& theCtx)
{
  if (myProgramID == NO_PROGRAM && theCtx->core20fwd != nullptr)
  {
    myProgramID = theCtx->core20fwd->glCreateProgram();
  }

  return myProgramID != NO_PROGRAM;
}

void OpenGl_ShaderProgram::Release(OpenGl_Context* theCtx)
{
  if (myProgramID == NO_PROGRAM)
  {
    return;
  }

  Standard_ASSERT_RETURN(
    theCtx != nullptr,
    "OpenGl_ShaderProgram destroyed without GL context! Possible GPU memory leakage...",
    Standard_VOID_RETURN);

  for (NCollection_Sequence<occ::handle<OpenGl_ShaderObject>>::Iterator anIter(myShaderObjects);
       anIter.More();
       anIter.Next())
  {
    if (!anIter.Value().IsNull())
    {
      anIter.ChangeValue()->Release(theCtx);
      anIter.ChangeValue().Nullify();
    }
  }

  if (theCtx->core20fwd != nullptr && theCtx->IsValid())
  {
    theCtx->core20fwd->glDeleteProgram(myProgramID);
  }

  myProgramID = NO_PROGRAM;
}

bool OpenGl_ShaderProgram::UpdateDebugDump(const occ::handle<OpenGl_Context>& theCtx,
                                           const TCollection_AsciiString&     theFolder,
                                           bool                               theToBeautify,
                                           bool                               theToReset)
{
  if (myProgramID == NO_PROGRAM)
  {
    return false;
  }

  TCollection_AsciiString aFolder = theFolder;
  if (aFolder.IsEmpty())
  {
    OSD_Environment aShaderVar("CSF_ShadersDirectoryDump");
    aFolder = aShaderVar.Value();
    if (aFolder.IsEmpty())
    {
      aFolder = ".";
    }
  }

  bool hasUpdates = false;
  for (NCollection_Sequence<occ::handle<OpenGl_ShaderObject>>::Iterator anIter(myShaderObjects);
       anIter.More();
       anIter.Next())
  {
    if (!anIter.Value().IsNull())
    {

      hasUpdates = anIter.ChangeValue()->updateDebugDump(theCtx,
                                                         myResourceId,
                                                         aFolder,
                                                         theToBeautify,
                                                         theToReset)
                   || hasUpdates;
    }
  }
  if (hasUpdates)
  {
    return Link(theCtx);
  }
  return false;
}
