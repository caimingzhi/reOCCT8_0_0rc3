#pragma once

#include <Graphic3d_ShaderManager.hpp>
#include <OpenGl_Aspects.hpp>
#include <OpenGl_Context.hpp>

#include <OpenGl_ShaderStates.hpp>
#include <OpenGl_Material.hpp>

class OpenGl_MaterialState : public OpenGl_StateInterface
{
public:
  OpenGl_MaterialState()
      : myAlphaCutoff(0.5f),
        myToDistinguish(false),
        myToMapTexture(false)
  {
  }

  void Set(const OpenGl_Material& theMat,
           const float            theAlphaCutoff,
           const bool             theToDistinguish,
           const bool             theToMapTexture)
  {
    myMaterial      = theMat;
    myAlphaCutoff   = theAlphaCutoff;
    myToDistinguish = theToDistinguish;
    myToMapTexture  = theToMapTexture;
  }

  const OpenGl_Material& Material() const { return myMaterial; }

  float AlphaCutoff() const { return myAlphaCutoff; }

  bool HasAlphaCutoff() const { return myAlphaCutoff <= 1.0f; }

  bool ToDistinguish() const { return myToDistinguish; }

  bool ToMapTexture() const { return myToMapTexture; }

private:
  OpenGl_Material myMaterial;
  float           myAlphaCutoff;
  bool            myToDistinguish;
  bool            myToMapTexture;
};

#include <OpenGl_PBREnvironment.hpp>

#include <Graphic3d_ShaderFlags.hpp>
#include <Graphic3d_TypeOfShadingModel.hpp>
#include <NCollection_DataMap.hpp>

class OpenGl_ShaderProgram;

class OpenGl_SetOfPrograms : public Standard_Transient
{
  DEFINE_STANDARD_RTTI_INLINE(OpenGl_SetOfPrograms, Standard_Transient)
public:
  OpenGl_SetOfPrograms() = default;

  occ::handle<OpenGl_ShaderProgram>& ChangeValue(int theProgramBits)
  {
    return myPrograms[theProgramBits];
  }

protected:
  occ::handle<OpenGl_ShaderProgram> myPrograms[Graphic3d_ShaderFlags_NB];
};

class OpenGl_SetOfShaderPrograms : public Standard_Transient
{
  DEFINE_STANDARD_RTTI_INLINE(OpenGl_SetOfShaderPrograms, Standard_Transient)
public:
  OpenGl_SetOfShaderPrograms() = default;

  OpenGl_SetOfShaderPrograms(const occ::handle<OpenGl_SetOfPrograms>& thePrograms)
  {
    for (int aSetIter = 0; aSetIter < Graphic3d_TypeOfShadingModel_NB - 1; ++aSetIter)
    {
      myPrograms[aSetIter] = thePrograms;
    }
  }

  occ::handle<OpenGl_ShaderProgram>& ChangeValue(Graphic3d_TypeOfShadingModel theShadingModel,
                                                 int                          theProgramBits)
  {
    occ::handle<OpenGl_SetOfPrograms>& aSet = myPrograms[theShadingModel - 1];
    if (aSet.IsNull())
    {
      aSet = new OpenGl_SetOfPrograms();
    }
    return aSet->ChangeValue(theProgramBits);
  }

protected:
  occ::handle<OpenGl_SetOfPrograms> myPrograms[Graphic3d_TypeOfShadingModel_NB - 1];
};

#include <OpenGl_ShaderProgram.hpp>
#include <OpenGl_ShaderStates.hpp>
#include <OpenGl_Texture.hpp>
#include <OpenGl_TextureSet.hpp>

class OpenGl_VertexBuffer;

class OpenGl_ShaderManager : public Graphic3d_ShaderManager
{
  DEFINE_STANDARD_RTTIEXT(OpenGl_ShaderManager, Graphic3d_ShaderManager)
  friend class OpenGl_ShaderProgram;

public:
  Standard_EXPORT OpenGl_ShaderManager(OpenGl_Context* theContext);

  Standard_EXPORT ~OpenGl_ShaderManager() override;

  Standard_EXPORT void clear();

  Standard_EXPORT void UpdateSRgbState();

  const gp_XYZ& LocalOrigin() const { return myLocalOrigin; }

  void SetLocalOrigin(const gp_XYZ& theOrigin)
  {
    myLocalOrigin    = theOrigin;
    myHasLocalOrigin = !theOrigin.IsEqual(gp_XYZ(0.0, 0.0, 0.0), gp::Resolution());
  }

  double LocalClippingPlaneW(const Graphic3d_ClipPlane& thePlane) const
  {
    const NCollection_Vec4<double>& anEq = thePlane.GetEquation();
    if (myHasLocalOrigin)
    {
      const gp_XYZ aPos = thePlane.ToPlane().Position().Location().XYZ() - myLocalOrigin;
      return -(anEq.x() * aPos.X() + anEq.y() * aPos.Y() + anEq.z() * aPos.Z());
    }
    return anEq.w();
  }

  Standard_EXPORT bool Create(const occ::handle<Graphic3d_ShaderProgram>& theProxy,
                              TCollection_AsciiString&                    theShareKey,
                              occ::handle<OpenGl_ShaderProgram>&          theProgram);

  Standard_EXPORT void Unregister(TCollection_AsciiString&           theShareKey,
                                  occ::handle<OpenGl_ShaderProgram>& theProgram);

  const NCollection_Sequence<occ::handle<OpenGl_ShaderProgram>>& ShaderPrograms() const
  {
    return myProgramList;
  }

  bool IsEmpty() const { return myProgramList.IsEmpty(); }

  bool BindFaceProgram(const occ::handle<OpenGl_TextureSet>&    theTextures,
                       Graphic3d_TypeOfShadingModel             theShadingModel,
                       Graphic3d_AlphaMode                      theAlphaMode,
                       bool                                     theHasVertColor,
                       bool                                     theEnableEnvMap,
                       const occ::handle<OpenGl_ShaderProgram>& theCustomProgram)
  {
    return BindFaceProgram(theTextures,
                           theShadingModel,
                           theAlphaMode,
                           Aspect_IS_SOLID,
                           theHasVertColor,
                           theEnableEnvMap,
                           false,
                           theCustomProgram);
  }

  bool BindFaceProgram(const occ::handle<OpenGl_TextureSet>&    theTextures,
                       Graphic3d_TypeOfShadingModel             theShadingModel,
                       Graphic3d_AlphaMode                      theAlphaMode,
                       Aspect_InteriorStyle                     theInteriorStyle,
                       bool                                     theHasVertColor,
                       bool                                     theEnableEnvMap,
                       bool                                     theEnableMeshEdges,
                       const occ::handle<OpenGl_ShaderProgram>& theCustomProgram)
  {
    const Graphic3d_TypeOfShadingModel aShadeModelOnFace =
      theShadingModel != Graphic3d_TypeOfShadingModel_Unlit
          && (theTextures.IsNull() || theTextures->IsModulate())
        ? theShadingModel
        : Graphic3d_TypeOfShadingModel_Unlit;
    if (!theCustomProgram.IsNull() || myContext->caps->ffpEnable)
    {
      return bindProgramWithState(theCustomProgram, aShadeModelOnFace);
    }

    const int                          aBits    = getProgramBits(theTextures,
                                     theAlphaMode,
                                     theInteriorStyle,
                                     theHasVertColor,
                                     theEnableEnvMap,
                                     theEnableMeshEdges);
    occ::handle<OpenGl_ShaderProgram>& aProgram = getStdProgram(aShadeModelOnFace, aBits);
    return bindProgramWithState(aProgram, aShadeModelOnFace);
  }

  bool BindLineProgram(const occ::handle<OpenGl_TextureSet>&    theTextures,
                       const Aspect_TypeOfLine                  theLineType,
                       const Graphic3d_TypeOfShadingModel       theShadingModel,
                       const Graphic3d_AlphaMode                theAlphaMode,
                       const bool                               theHasVertColor,
                       const occ::handle<OpenGl_ShaderProgram>& theCustomProgram)
  {
    if (!theCustomProgram.IsNull() || myContext->caps->ffpEnable)
    {
      return bindProgramWithState(theCustomProgram, theShadingModel);
    }

    int aBits =
      getProgramBits(theTextures, theAlphaMode, Aspect_IS_SOLID, theHasVertColor, false, false);
    if (theLineType != Aspect_TOL_SOLID)
    {
      aBits |= Graphic3d_ShaderFlags_StippleLine;
    }

    occ::handle<OpenGl_ShaderProgram>& aProgram = getStdProgram(theShadingModel, aBits);
    return bindProgramWithState(aProgram, theShadingModel);
  }

  Standard_EXPORT bool BindMarkerProgram(const occ::handle<OpenGl_TextureSet>&    theTextures,
                                         Graphic3d_TypeOfShadingModel             theShadingModel,
                                         Graphic3d_AlphaMode                      theAlphaMode,
                                         bool                                     theHasVertColor,
                                         const occ::handle<OpenGl_ShaderProgram>& theCustomProgram);

  bool BindFontProgram(const occ::handle<OpenGl_ShaderProgram>& theCustomProgram);

  bool BindOutlineProgram()
  {
    if (myContext->caps->ffpEnable)
    {
      return false;
    }

    const int aBits = getProgramBits(occ::handle<OpenGl_TextureSet>(),
                                     Graphic3d_AlphaMode_Opaque,
                                     Aspect_IS_SOLID,
                                     false,
                                     false,
                                     false);
    if (myOutlinePrograms.IsNull())
    {
      myOutlinePrograms = new OpenGl_SetOfPrograms();
    }
    occ::handle<OpenGl_ShaderProgram>& aProgram = myOutlinePrograms->ChangeValue(aBits);
    if (aProgram.IsNull())
    {
      prepareStdProgramUnlit(aProgram, aBits, true);
    }
    return bindProgramWithState(aProgram, Graphic3d_TypeOfShadingModel_Unlit);
  }

  Standard_EXPORT bool BindFboBlitProgram(int theNbSamples, bool theIsFallback_sRGB);

  Standard_EXPORT bool BindOitCompositingProgram(bool theIsMSAAEnabled);

  Standard_EXPORT bool BindOitDepthPeelingBlendProgram(bool theIsMSAAEnabled);

  Standard_EXPORT bool BindOitDepthPeelingFlushProgram(bool theIsMSAAEnabled);

  Standard_EXPORT bool BindStereoProgram(Graphic3d_StereoMode theStereoMode);

  bool BindBoundBoxProgram()
  {
    if (myBoundBoxProgram.IsNull())
    {
      prepareStdProgramBoundBox();
    }
    return bindProgramWithState(myBoundBoxProgram, Graphic3d_TypeOfShadingModel_Unlit);
  }

  const occ::handle<OpenGl_VertexBuffer>& BoundBoxVertBuffer() const
  {
    return myBoundBoxVertBuffer;
  }

  bool BindPBREnvBakingProgram(int theIndex)
  {
    if (myPBREnvBakingProgram[theIndex].IsNull())
    {
      preparePBREnvBakingProgram(theIndex);
    }
    return myContext->BindProgram(myPBREnvBakingProgram[theIndex]);
  }

  Standard_EXPORT const occ::handle<Graphic3d_ShaderProgram>& GetBgCubeMapProgram();

  Standard_EXPORT const occ::handle<Graphic3d_ShaderProgram>& GetBgSkydomeProgram();

  Standard_EXPORT const occ::handle<Graphic3d_ShaderProgram>& GetColoredQuadProgram();

  static Graphic3d_TypeOfShadingModel PBRShadingModelFallback(
    Graphic3d_TypeOfShadingModel theShadingModel,
    bool                         theIsPbrAllowed = false)
  {
    if (theIsPbrAllowed)
    {
      return theShadingModel;
    }

    switch (theShadingModel)
    {
      case Graphic3d_TypeOfShadingModel_Pbr:
        return Graphic3d_TypeOfShadingModel_Phong;
      case Graphic3d_TypeOfShadingModel_PbrFacet:
        return Graphic3d_TypeOfShadingModel_PhongFacet;
      default:
        return theShadingModel;
    }
  }

public:
  const OpenGl_LightSourceState& LightSourceState() const { return myLightSourceState; }

  Standard_EXPORT void UpdateLightSourceStateTo(
    const occ::handle<Graphic3d_LightSet>&    theLights,
    int                                       theSpecIBLMapLevels,
    const occ::handle<OpenGl_ShadowMapArray>& theShadowMaps);

  bool SetCastShadows(const bool theToCast)
  {
    if (myLightSourceState.ShadowMaps().IsNull() || myLightSourceState.ToCastShadows() == theToCast)
    {
      return myLightSourceState.ToCastShadows();
    }

    myLightSourceState.SetCastShadows(theToCast);
    switchLightPrograms();
    return !theToCast;
  }

  Standard_EXPORT void UpdateLightSourceState();

  void PushLightSourceState(const occ::handle<OpenGl_ShaderProgram>& theProgram) const
  {
    if (myLightSourceState.Index() != theProgram->ActiveState(OpenGl_LIGHT_SOURCES_STATE)
        || myWorldViewState.Index() != theProgram->ActiveState(OpenGl_WORLD_VIEW_STATE))
    {
      pushLightSourceState(theProgram);
    }
  }

  Standard_EXPORT void pushLightSourceState(
    const occ::handle<OpenGl_ShaderProgram>& theProgram) const;

public:
  const OpenGl_ProjectionState& ProjectionState() const { return myProjectionState; }

  Standard_EXPORT void UpdateProjectionStateTo(const NCollection_Mat4<float>& theProjectionMatrix);

  void PushProjectionState(const occ::handle<OpenGl_ShaderProgram>& theProgram) const
  {
    if (myProjectionState.Index() != theProgram->ActiveState(OpenGl_PROJECTION_STATE))
    {
      pushProjectionState(theProgram);
    }
  }

  Standard_EXPORT void pushProjectionState(
    const occ::handle<OpenGl_ShaderProgram>& theProgram) const;

public:
  const OpenGl_ModelWorldState& ModelWorldState() const { return myModelWorldState; }

  Standard_EXPORT void UpdateModelWorldStateTo(const NCollection_Mat4<float>& theModelWorldMatrix);

  void PushModelWorldState(const occ::handle<OpenGl_ShaderProgram>& theProgram) const
  {
    if (myModelWorldState.Index() != theProgram->ActiveState(OpenGl_MODEL_WORLD_STATE))
    {
      pushModelWorldState(theProgram);
    }
  }

  Standard_EXPORT void pushModelWorldState(
    const occ::handle<OpenGl_ShaderProgram>& theProgram) const;

public:
  const OpenGl_WorldViewState& WorldViewState() const { return myWorldViewState; }

  Standard_EXPORT void UpdateWorldViewStateTo(const NCollection_Mat4<float>& theWorldViewMatrix);

  void PushWorldViewState(const occ::handle<OpenGl_ShaderProgram>& theProgram) const
  {
    if (myWorldViewState.Index() != theProgram->ActiveState(OpenGl_WORLD_VIEW_STATE))
    {
      pushWorldViewState(theProgram);
    }
  }

  Standard_EXPORT void pushWorldViewState(
    const occ::handle<OpenGl_ShaderProgram>& theProgram) const;

public:
  Standard_EXPORT void UpdateClippingState();

  Standard_EXPORT void RevertClippingState();

  void PushClippingState(const occ::handle<OpenGl_ShaderProgram>& theProgram) const
  {
    if (myClippingState.Index() != theProgram->ActiveState(OpenGl_CLIP_PLANES_STATE))
    {
      pushClippingState(theProgram);
    }
  }

  Standard_EXPORT void pushClippingState(const occ::handle<OpenGl_ShaderProgram>& theProgram) const;

public:
  const OpenGl_MaterialState& MaterialState() const { return myMaterialState; }

  void UpdateMaterialStateTo(const OpenGl_Material& theMat,
                             const float            theAlphaCutoff,
                             const bool             theToDistinguish,
                             const bool             theToMapTexture)
  {
    myMaterialState.Set(theMat, theAlphaCutoff, theToDistinguish, theToMapTexture);
    myMaterialState.Update();
  }

  void UpdateMaterialState() { myMaterialState.Update(); }

  void PushMaterialState(const occ::handle<OpenGl_ShaderProgram>& theProgram) const
  {
    if (myMaterialState.Index() != theProgram->ActiveState(OpenGl_MATERIAL_STATE))
    {
      pushMaterialState(theProgram);
    }
  }

  Standard_EXPORT void pushMaterialState(const occ::handle<OpenGl_ShaderProgram>& theProgram) const;

public:
  Standard_EXPORT void PushInteriorState(const occ::handle<OpenGl_ShaderProgram>& theProgram,
                                         const occ::handle<Graphic3d_Aspects>&    theAspect) const;

public:
  const OpenGl_OitState& OitState() const { return myOitState; }

  void ResetOitState()
  {
    myOitState.Set(Graphic3d_RTM_BLEND_UNORDERED, 0.0f);
    myOitState.Update();
  }

  void SetOitState(Graphic3d_RenderTransparentMethod theMode)
  {
    myOitState.Set(theMode, 0.0f);
    myOitState.Update();
  }

  void SetWeighedOitState(float theDepthFactor)
  {
    myOitState.Set(Graphic3d_RTM_BLEND_OIT, theDepthFactor);
    myOitState.Update();
  }

  void PushOitState(const occ::handle<OpenGl_ShaderProgram>& theProgram) const
  {
    if (theProgram->IsValid() && myOitState.Index() != theProgram->ActiveState(OpenGL_OIT_STATE))
    {
      pushOitState(theProgram);
    }
  }

  Standard_EXPORT void pushOitState(const occ::handle<OpenGl_ShaderProgram>& theProgram) const;

public:
  Standard_EXPORT void PushState(
    const occ::handle<OpenGl_ShaderProgram>& theProgram,
    Graphic3d_TypeOfShadingModel theShadingModel = Graphic3d_TypeOfShadingModel_Unlit) const;

public:
  void SetContext(OpenGl_Context* theCtx) { myContext = theCtx; }

  bool IsSameContext(OpenGl_Context* theCtx) const { return myContext == theCtx; }

  Graphic3d_TypeOfShadingModel ChooseFaceShadingModel(Graphic3d_TypeOfShadingModel theCustomModel,
                                                      bool theHasNodalNormals) const
  {
    if (!myContext->ColorMask())
    {
      return Graphic3d_TypeOfShadingModel_Unlit;
    }
    Graphic3d_TypeOfShadingModel aModel =
      theCustomModel != Graphic3d_TypeOfShadingModel_DEFAULT ? theCustomModel : myShadingModel;
    switch (aModel)
    {
      case Graphic3d_TypeOfShadingModel_DEFAULT:
      case Graphic3d_TypeOfShadingModel_Unlit:
      case Graphic3d_TypeOfShadingModel_PhongFacet:
        return aModel;
      case Graphic3d_TypeOfShadingModel_Gouraud:
      case Graphic3d_TypeOfShadingModel_Phong:
        return theHasNodalNormals ? aModel : Graphic3d_TypeOfShadingModel_PhongFacet;
      case Graphic3d_TypeOfShadingModel_Pbr:
        return PBRShadingModelFallback(theHasNodalNormals ? aModel
                                                          : Graphic3d_TypeOfShadingModel_PbrFacet,
                                       IsPbrAllowed());
      case Graphic3d_TypeOfShadingModel_PbrFacet:
        return PBRShadingModelFallback(aModel, IsPbrAllowed());
    }
    return Graphic3d_TypeOfShadingModel_Unlit;
  }

  Graphic3d_TypeOfShadingModel ChooseLineShadingModel(Graphic3d_TypeOfShadingModel theCustomModel,
                                                      bool theHasNodalNormals) const
  {
    if (!myContext->ColorMask())
    {
      return Graphic3d_TypeOfShadingModel_Unlit;
    }
    Graphic3d_TypeOfShadingModel aModel =
      theCustomModel != Graphic3d_TypeOfShadingModel_DEFAULT ? theCustomModel : myShadingModel;
    switch (aModel)
    {
      case Graphic3d_TypeOfShadingModel_DEFAULT:
      case Graphic3d_TypeOfShadingModel_Unlit:
      case Graphic3d_TypeOfShadingModel_PhongFacet:
        return Graphic3d_TypeOfShadingModel_Unlit;
      case Graphic3d_TypeOfShadingModel_Gouraud:
      case Graphic3d_TypeOfShadingModel_Phong:
        return theHasNodalNormals ? aModel : Graphic3d_TypeOfShadingModel_Unlit;
      case Graphic3d_TypeOfShadingModel_Pbr:
        return PBRShadingModelFallback(theHasNodalNormals ? aModel
                                                          : Graphic3d_TypeOfShadingModel_Unlit,
                                       IsPbrAllowed());
      case Graphic3d_TypeOfShadingModel_PbrFacet:
        return Graphic3d_TypeOfShadingModel_Unlit;
    }
    return Graphic3d_TypeOfShadingModel_Unlit;
  }

  Graphic3d_TypeOfShadingModel ChooseMarkerShadingModel(Graphic3d_TypeOfShadingModel theCustomModel,
                                                        bool theHasNodalNormals) const
  {
    return ChooseLineShadingModel(theCustomModel, theHasNodalNormals);
  }

  Graphic3d_TypeOfShadingModel ShadingModel() const { return myShadingModel; }

  Standard_EXPORT void SetShadingModel(const Graphic3d_TypeOfShadingModel theModel);

protected:
  int getClipPlaneBits() const
  {
    const int aNbPlanes = myContext->Clipping().NbClippingOrCappingOn();
    if (aNbPlanes <= 0)
    {
      return 0;
    }

    int aBits = 0;
    if (myContext->Clipping().HasClippingChains())
    {
      aBits |= Graphic3d_ShaderFlags_ClipChains;
    }

    if (aNbPlanes == 1)
    {
      aBits |= Graphic3d_ShaderFlags_ClipPlanes1;
    }
    else if (aNbPlanes == 2)
    {
      aBits |= Graphic3d_ShaderFlags_ClipPlanes2;
    }
    else
    {
      aBits |= Graphic3d_ShaderFlags_ClipPlanesN;
    }
    return aBits;
  }

  int getProgramBits(const occ::handle<OpenGl_TextureSet>& theTextures,
                     Graphic3d_AlphaMode                   theAlphaMode,
                     Aspect_InteriorStyle                  theInteriorStyle,
                     bool                                  theHasVertColor,
                     bool                                  theEnableEnvMap,
                     bool                                  theEnableMeshEdges) const
  {
    int aBits = 0;
    if (theAlphaMode == Graphic3d_AlphaMode_Mask || theAlphaMode == Graphic3d_AlphaMode_MaskBlend)
    {
      aBits |= Graphic3d_ShaderFlags_AlphaTest;
    }

    aBits |= getClipPlaneBits();
    if (theEnableMeshEdges && myContext->hasGeometryStage != OpenGl_FeatureNotAvailable)
    {
      aBits |= Graphic3d_ShaderFlags_MeshEdges;
      if (theInteriorStyle == Aspect_IS_HOLLOW)
      {
        aBits |= Graphic3d_ShaderFlags_AlphaTest;
      }
    }

    if (theEnableEnvMap)
    {

      aBits |= Graphic3d_ShaderFlags_TextureEnv;
    }
    else if (!theTextures.IsNull() && theTextures->HasNonPointSprite())
    {
      aBits |= Graphic3d_ShaderFlags_TextureRGB;
      if ((theTextures->TextureSetBits() & Graphic3d_TextureSetBits_Normal) != 0)
      {
        aBits |= Graphic3d_ShaderFlags_TextureNormal;
      }
    }
    if (theHasVertColor && theInteriorStyle != Aspect_IS_HIDDENLINE)
    {
      aBits |= Graphic3d_ShaderFlags_VertColor;
    }

    if (myOitState.ActiveMode() == Graphic3d_RTM_BLEND_OIT)
    {
      aBits |= Graphic3d_ShaderFlags_WriteOit;
    }
    else if (myOitState.ActiveMode() == Graphic3d_RTM_DEPTH_PEELING_OIT)
    {
      aBits |= Graphic3d_ShaderFlags_OitDepthPeeling;
    }
    return aBits;
  }

  occ::handle<OpenGl_ShaderProgram>& getStdProgram(Graphic3d_TypeOfShadingModel theShadingModel,
                                                   int                          theBits)
  {
    if (theShadingModel == Graphic3d_TypeOfShadingModel_Unlit
        || (theBits & Graphic3d_ShaderFlags_HasTextures) == Graphic3d_ShaderFlags_TextureEnv)
    {

      occ::handle<OpenGl_ShaderProgram>& aProgram = myUnlitPrograms->ChangeValue(theBits);
      if (aProgram.IsNull())
      {
        prepareStdProgramUnlit(aProgram, theBits, false);
      }
      return aProgram;
    }

    occ::handle<OpenGl_ShaderProgram>& aProgram =
      myLightPrograms->ChangeValue(theShadingModel, theBits);
    if (aProgram.IsNull())
    {
      prepareStdProgramLight(aProgram, theShadingModel, theBits);
    }
    return aProgram;
  }

  Standard_EXPORT bool prepareStdProgramUnlit(occ::handle<OpenGl_ShaderProgram>& theProgram,
                                              int                                theBits,
                                              bool theIsOutline = false);

  bool prepareStdProgramLight(occ::handle<OpenGl_ShaderProgram>& theProgram,
                              Graphic3d_TypeOfShadingModel       theShadingModel,
                              int                                theBits)
  {
    switch (theShadingModel)
    {
      case Graphic3d_TypeOfShadingModel_Unlit:
        return prepareStdProgramUnlit(theProgram, theBits, false);
      case Graphic3d_TypeOfShadingModel_PhongFacet:
        return prepareStdProgramPhong(theProgram, theBits, true);
      case Graphic3d_TypeOfShadingModel_Gouraud:
        return prepareStdProgramGouraud(theProgram, theBits);
      case Graphic3d_TypeOfShadingModel_DEFAULT:
      case Graphic3d_TypeOfShadingModel_Phong:
        return prepareStdProgramPhong(theProgram, theBits, false);
      case Graphic3d_TypeOfShadingModel_Pbr:
        return prepareStdProgramPhong(theProgram, theBits, false, true);
      case Graphic3d_TypeOfShadingModel_PbrFacet:
        return prepareStdProgramPhong(theProgram, theBits, true, true);
    }
    return false;
  }

  Standard_EXPORT bool prepareStdProgramGouraud(occ::handle<OpenGl_ShaderProgram>& theProgram,
                                                const int                          theBits);

  Standard_EXPORT bool prepareStdProgramPhong(occ::handle<OpenGl_ShaderProgram>& theProgram,
                                              const int                          theBits,
                                              const bool theIsFlatNormal = false,
                                              const bool theIsPBR        = false);

  Standard_EXPORT bool bindProgramWithState(const occ::handle<OpenGl_ShaderProgram>& theProgram,
                                            Graphic3d_TypeOfShadingModel theShadingModel);

  Standard_EXPORT void switchLightPrograms();

  Standard_EXPORT bool prepareStdProgramBoundBox();

  Standard_EXPORT bool preparePBREnvBakingProgram(int theIndex);

  bool IsPbrAllowed() const
  {
    return myShadingModel == Graphic3d_TypeOfShadingModel_Pbr
           || myShadingModel == Graphic3d_TypeOfShadingModel_PbrFacet;
  }

protected:
  struct OpenGl_ShaderLightParameters
  {
    NCollection_Vec4<float> Color;
    NCollection_Vec4<float> Position;
    NCollection_Vec4<float> Direction;
    NCollection_Vec4<float> Parameters;

    const NCollection_Vec4<float>* Packed() const
    {
      return reinterpret_cast<const NCollection_Vec4<float>*>(this);
    }

    static int NbOfVec4() { return 4; }
  };

  class OpenGl_ShaderProgramFFP : public OpenGl_ShaderProgram
  {
    DEFINE_STANDARD_RTTI_INLINE(OpenGl_ShaderProgramFFP, OpenGl_ShaderProgram)
    friend class OpenGl_ShaderManager;

  protected:
    OpenGl_ShaderProgramFFP() {}
  };

protected:
  void addClippingPlane(int&                            thePlaneId,
                        const Graphic3d_ClipPlane&      thePlane,
                        const NCollection_Vec4<double>& theEq,
                        const int                       theChainFwd) const
  {
    myClipChainArray.SetValue(thePlaneId, theChainFwd);
    NCollection_Vec4<float>& aPlaneEq = myClipPlaneArray.ChangeValue(thePlaneId);
    aPlaneEq.x()                      = float(theEq.x());
    aPlaneEq.y()                      = float(theEq.y());
    aPlaneEq.z()                      = float(theEq.z());
    aPlaneEq.w()                      = float(theEq.w());
    if (myHasLocalOrigin)
    {
      aPlaneEq.w() = float(LocalClippingPlaneW(thePlane));
    }
    ++thePlaneId;
  }

protected:
  occ::handle<OpenGl_ShaderProgramFFP> myFfpProgram;

  Graphic3d_TypeOfShadingModel                            myShadingModel;
  NCollection_Sequence<occ::handle<OpenGl_ShaderProgram>> myProgramList;

  occ::handle<OpenGl_SetOfShaderPrograms>               myLightPrograms;
  occ::handle<OpenGl_SetOfPrograms>                     myUnlitPrograms;
  occ::handle<OpenGl_SetOfPrograms>                     myOutlinePrograms;
  occ::handle<OpenGl_ShaderProgram>                     myFontProgram;
  NCollection_Array1<occ::handle<OpenGl_ShaderProgram>> myBlitPrograms[2];
  occ::handle<OpenGl_ShaderProgram>                     myBoundBoxProgram;
  occ::handle<OpenGl_ShaderProgram>                     myOitCompositingProgram[2];
  occ::handle<OpenGl_ShaderProgram>                     myOitDepthPeelingBlendProgram[2];
  occ::handle<OpenGl_ShaderProgram>                     myOitDepthPeelingFlushProgram[2];
  NCollection_DataMap<TCollection_AsciiString, occ::handle<OpenGl_SetOfShaderPrograms>>
    myMapOfLightPrograms;

  occ::handle<OpenGl_ShaderProgram>    myPBREnvBakingProgram[3];
  occ::handle<Graphic3d_ShaderProgram> myBgCubeMapProgram;
  occ::handle<Graphic3d_ShaderProgram> myBgSkydomeProgram;
  occ::handle<Graphic3d_ShaderProgram> myColoredQuadProgram;

  occ::handle<OpenGl_ShaderProgram> myStereoPrograms[Graphic3d_StereoMode_NB];

  occ::handle<OpenGl_VertexBuffer> myBoundBoxVertBuffer;

  mutable occ::handle<OpenGl_PBREnvironment> myPBREnvironment;

  OpenGl_Context* myContext;

protected:
  OpenGl_ProjectionState  myProjectionState;
  OpenGl_ModelWorldState  myModelWorldState;
  OpenGl_WorldViewState   myWorldViewState;
  OpenGl_ClippingState    myClippingState;
  OpenGl_LightSourceState myLightSourceState;
  OpenGl_MaterialState    myMaterialState;
  OpenGl_OitState         myOitState;

  gp_XYZ myLocalOrigin;
  bool   myHasLocalOrigin;

  mutable NCollection_Array1<int>                          myLightTypeArray;
  mutable NCollection_Array1<OpenGl_ShaderLightParameters> myLightParamsArray;
  mutable NCollection_Array1<NCollection_Mat4<float>>      myShadowMatArray;
  mutable NCollection_Array1<NCollection_Vec4<float>>      myClipPlaneArray;
  mutable NCollection_Array1<NCollection_Vec4<double>>     myClipPlaneArrayFfp;
  mutable NCollection_Array1<int>                          myClipChainArray;
};
