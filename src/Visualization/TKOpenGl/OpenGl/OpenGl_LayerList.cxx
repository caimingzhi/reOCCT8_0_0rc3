#include <OpenGl_GlCore15.hpp>

#include <BVH_LinearBuilder.hpp>
#include <OpenGl_DepthPeeling.hpp>
#include <OpenGl_FrameBuffer.hpp>
#include <OpenGl_LayerList.hpp>
#include <OpenGl_RenderFilter.hpp>
#include <OpenGl_ShaderManager.hpp>
#include <OpenGl_ShadowMap.hpp>
#include <OpenGl_VertexBuffer.hpp>
#include <OpenGl_View.hpp>
#include <OpenGl_Workspace.hpp>

namespace
{

  class OpenGl_IndexedLayerIterator
      : public NCollection_List<occ::handle<Graphic3d_Layer>>::Iterator
  {
  public:
    OpenGl_IndexedLayerIterator(const NCollection_List<occ::handle<Graphic3d_Layer>>& theSeq)
        : NCollection_List<occ::handle<Graphic3d_Layer>>::Iterator(theSeq),
          myIndex(1)
    {
    }

    int Index() const { return myIndex; }

    void Next()
    {
      NCollection_List<occ::handle<Graphic3d_Layer>>::Iterator::Next();
      ++myIndex;
    }

  private:
    int myIndex;
  };

  class OpenGl_FilteredIndexedLayerIterator
  {
  public:
    OpenGl_FilteredIndexedLayerIterator(
      const NCollection_List<occ::handle<Graphic3d_Layer>>& theSeq,
      bool                                                  theToDrawImmediate,
      OpenGl_LayerFilter                                    theFilterMode,
      Graphic3d_ZLayerId                                    theLayersToProcess)
        : myIter(theSeq),
          myFilterMode(theFilterMode),
          myToDrawImmediate(theToDrawImmediate),
          myLayersToProcess(theLayersToProcess)
    {
      next();
    }

    bool More() const { return myIter.More(); }

    const OpenGl_Layer& Value() const { return *myIter.Value(); }

    int Index() const { return myIter.Index(); }

    void Next()
    {
      myIter.Next();
      next();
    }

  private:
    void next()
    {
      for (; myIter.More(); myIter.Next())
      {
        const occ::handle<Graphic3d_Layer>& aLayer = myIter.Value();
        if (aLayer->IsImmediate() != myToDrawImmediate)
        {
          continue;
        }

        switch (myFilterMode)
        {
          case OpenGl_LF_All:
          {
            if (aLayer->LayerId() >= myLayersToProcess)
            {
              return;
            }
            break;
          }
          case OpenGl_LF_Upper:
          {
            if (aLayer->LayerId() != Graphic3d_ZLayerId_BotOSD
                && (!aLayer->LayerSettings().IsRaytracable() || aLayer->IsImmediate()))
            {
              return;
            }
            break;
          }
          case OpenGl_LF_Bottom:
          {
            if (aLayer->LayerId() == Graphic3d_ZLayerId_BotOSD
                && !aLayer->LayerSettings().IsRaytracable())
            {
              return;
            }
            break;
          }
          case OpenGl_LF_Single:
          {
            if (aLayer->LayerId() == myLayersToProcess)
            {
              return;
            }
            break;
          }
          case OpenGl_LF_RayTracable:
          {
            if (aLayer->LayerSettings().IsRaytracable() && !aLayer->IsImmediate())
            {
              return;
            }
            break;
          }
        }
      }
    }

  private:
    OpenGl_IndexedLayerIterator myIter;
    OpenGl_LayerFilter          myFilterMode;
    bool                        myToDrawImmediate;
    Graphic3d_ZLayerId          myLayersToProcess;
  };

  constexpr int   THE_DRAW_BUFFERS0[]   = {GL_COLOR_ATTACHMENT0};
  constexpr int   THE_DRAW_BUFFERS01[]  = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT0 + 1};
  constexpr int   THE_DRAW_BUFFERS012[] = {GL_COLOR_ATTACHMENT0,
                                           GL_COLOR_ATTACHMENT0 + 1,
                                           GL_COLOR_ATTACHMENT0 + 2};
  constexpr float THE_DEPTH_CLEAR_VALUE = -1e15f;
} // namespace

struct OpenGl_GlobalLayerSettings
{
  GLint     DepthFunc;
  GLboolean DepthMask;
};

OpenGl_LayerList::OpenGl_LayerList()
    : myBVHBuilder(new BVH_LinearBuilder<double, 3>(BVH_Constants_LeafNodeSizeSingle,
                                                    BVH_Constants_MaxTreeDepth)),
      myNbStructures(0),
      myImmediateNbStructures(0),
      myModifStateOfRaytraceable(0)
{
}

OpenGl_LayerList::~OpenGl_LayerList() = default;

void OpenGl_LayerList::SetFrustumCullingBVHBuilder(const occ::handle<BVH_Builder3d>& theBuilder)
{
  myBVHBuilder = theBuilder;
  for (NCollection_List<occ::handle<Graphic3d_Layer>>::Iterator aLayerIter(myLayers);
       aLayerIter.More();
       aLayerIter.Next())
  {
    aLayerIter.ChangeValue()->SetFrustumCullingBVHBuilder(theBuilder);
  }
}

void OpenGl_LayerList::InsertLayerBefore(const Graphic3d_ZLayerId        theNewLayerId,
                                         const Graphic3d_ZLayerSettings& theSettings,
                                         const Graphic3d_ZLayerId        theLayerAfter)
{
  if (myLayerIds.IsBound(theNewLayerId))
  {
    return;
  }

  occ::handle<Graphic3d_Layer> aNewLayer = new Graphic3d_Layer(theNewLayerId, myBVHBuilder);
  aNewLayer->SetLayerSettings(theSettings);

  occ::handle<Graphic3d_Layer> anOtherLayer;
  if (theLayerAfter != Graphic3d_ZLayerId_UNKNOWN && myLayerIds.Find(theLayerAfter, anOtherLayer))
  {
    for (NCollection_List<occ::handle<Graphic3d_Layer>>::Iterator aLayerIter(myLayers);
         aLayerIter.More();
         aLayerIter.Next())
    {
      if (aLayerIter.Value() == anOtherLayer)
      {
        myLayers.InsertBefore(aNewLayer, aLayerIter);
        break;
      }
    }
  }
  else
  {
    myLayers.Prepend(aNewLayer);
  }

  myLayerIds.Bind(theNewLayerId, aNewLayer);
  myTransparentToProcess.Allocate(myLayers.Size());
}

void OpenGl_LayerList::InsertLayerAfter(const Graphic3d_ZLayerId        theNewLayerId,
                                        const Graphic3d_ZLayerSettings& theSettings,
                                        const Graphic3d_ZLayerId        theLayerBefore)
{
  if (myLayerIds.IsBound(theNewLayerId))
  {
    return;
  }

  occ::handle<Graphic3d_Layer> aNewLayer = new Graphic3d_Layer(theNewLayerId, myBVHBuilder);
  aNewLayer->SetLayerSettings(theSettings);

  occ::handle<Graphic3d_Layer> anOtherLayer;
  if (theLayerBefore != Graphic3d_ZLayerId_UNKNOWN && myLayerIds.Find(theLayerBefore, anOtherLayer))
  {
    for (NCollection_List<occ::handle<Graphic3d_Layer>>::Iterator aLayerIter(myLayers);
         aLayerIter.More();
         aLayerIter.Next())
    {
      if (aLayerIter.Value() == anOtherLayer)
      {
        myLayers.InsertAfter(aNewLayer, aLayerIter);
        break;
      }
    }
  }
  else
  {
    myLayers.Append(aNewLayer);
  }

  myLayerIds.Bind(theNewLayerId, aNewLayer);
  myTransparentToProcess.Allocate(myLayers.Size());
}

void OpenGl_LayerList::RemoveLayer(const Graphic3d_ZLayerId theLayerId)
{
  occ::handle<Graphic3d_Layer> aLayerToRemove;
  if (theLayerId <= 0 || !myLayerIds.Find(theLayerId, aLayerToRemove))
  {
    return;
  }

  myLayerIds.Find(Graphic3d_ZLayerId_Default)->Append(*aLayerToRemove);

  myLayers.Remove(aLayerToRemove);
  myLayerIds.UnBind(theLayerId);

  myTransparentToProcess.Allocate(myLayers.Size());
}

void OpenGl_LayerList::AddStructure(const OpenGl_Structure*         theStruct,
                                    const Graphic3d_ZLayerId        theLayerId,
                                    const Graphic3d_DisplayPriority thePriority,
                                    bool                            isForChangePriority)
{

  const occ::handle<Graphic3d_Layer>* aLayerPtr = myLayerIds.Seek(theLayerId);
  const occ::handle<Graphic3d_Layer>& aLayer =
    aLayerPtr != nullptr ? *aLayerPtr : myLayerIds.Find(Graphic3d_ZLayerId_Default);
  aLayer->Add(theStruct, thePriority, isForChangePriority);
  ++myNbStructures;
  if (aLayer->IsImmediate())
  {
    ++myImmediateNbStructures;
  }
}

void OpenGl_LayerList::RemoveStructure(const OpenGl_Structure* theStructure)
{
  const Graphic3d_ZLayerId            aLayerId  = theStructure->ZLayer();
  const occ::handle<Graphic3d_Layer>* aLayerPtr = myLayerIds.Seek(aLayerId);
  const occ::handle<Graphic3d_Layer>& aLayer =
    aLayerPtr != nullptr ? *aLayerPtr : myLayerIds.Find(Graphic3d_ZLayerId_Default);

  Graphic3d_DisplayPriority aPriority = Graphic3d_DisplayPriority_INVALID;

  if (aLayer->Remove(theStructure, aPriority))
  {
    --myNbStructures;
    if (aLayer->IsImmediate())
    {
      --myImmediateNbStructures;
    }

    if (aLayer->LayerSettings().IsRaytracable() && theStructure->IsRaytracable())
    {
      ++myModifStateOfRaytraceable;
    }

    return;
  }

  for (NCollection_List<occ::handle<Graphic3d_Layer>>::Iterator aLayerIter(myLayers);
       aLayerIter.More();
       aLayerIter.Next())
  {
    const occ::handle<Graphic3d_Layer>& aLayerEx = aLayerIter.ChangeValue();
    if (aLayerEx == aLayer)
    {
      continue;
    }

    if (aLayerEx->Remove(theStructure, aPriority))
    {
      --myNbStructures;
      if (aLayerEx->IsImmediate())
      {
        --myImmediateNbStructures;
      }

      if (aLayerEx->LayerSettings().IsRaytracable() && theStructure->IsRaytracable())
      {
        ++myModifStateOfRaytraceable;
      }
      return;
    }
  }
}

void OpenGl_LayerList::InvalidateBVHData(const Graphic3d_ZLayerId theLayerId)
{
  const occ::handle<Graphic3d_Layer>* aLayerPtr = myLayerIds.Seek(theLayerId);
  const occ::handle<Graphic3d_Layer>& aLayer =
    aLayerPtr != nullptr ? *aLayerPtr : myLayerIds.Find(Graphic3d_ZLayerId_Default);
  aLayer->InvalidateBVHData();
}

void OpenGl_LayerList::ChangeLayer(const OpenGl_Structure*  theStructure,
                                   const Graphic3d_ZLayerId theOldLayerId,
                                   const Graphic3d_ZLayerId theNewLayerId)
{
  const occ::handle<Graphic3d_Layer>* aLayerPtr = myLayerIds.Seek(theOldLayerId);
  const occ::handle<Graphic3d_Layer>& aLayer =
    aLayerPtr != nullptr ? *aLayerPtr : myLayerIds.Find(Graphic3d_ZLayerId_Default);

  Graphic3d_DisplayPriority aPriority = Graphic3d_DisplayPriority_INVALID;

  if (aLayer->Remove(theStructure, aPriority, false))
  {
    if (aLayer->LayerSettings().IsRaytracable() && !aLayer->LayerSettings().IsImmediate()
        && theStructure->IsRaytracable())
    {
      ++myModifStateOfRaytraceable;
    }

    --myNbStructures;
    if (aLayer->IsImmediate())
    {
      --myImmediateNbStructures;
    }

    AddStructure(theStructure, theNewLayerId, aPriority);
    return;
  }

  for (NCollection_List<occ::handle<Graphic3d_Layer>>::Iterator aLayerIter(myLayers);
       aLayerIter.More();
       aLayerIter.Next())
  {
    const occ::handle<OpenGl_Layer>& aLayerEx = aLayerIter.ChangeValue();
    if (aLayerEx == aLayer)
    {
      continue;
    }

    if (aLayerEx->Remove(theStructure, aPriority, true))
    {
      if (aLayerEx->LayerSettings().IsRaytracable() && !aLayerEx->LayerSettings().IsImmediate()
          && theStructure->IsRaytracable())
      {
        ++myModifStateOfRaytraceable;
      }

      --myNbStructures;
      if (aLayerEx->IsImmediate())
      {
        --myImmediateNbStructures;
      }

      AddStructure(theStructure, theNewLayerId, aPriority);
      return;
    }
  }
}

void OpenGl_LayerList::ChangePriority(const OpenGl_Structure*         theStructure,
                                      const Graphic3d_ZLayerId        theLayerId,
                                      const Graphic3d_DisplayPriority theNewPriority)
{
  const occ::handle<Graphic3d_Layer>* aLayerPtr = myLayerIds.Seek(theLayerId);
  const occ::handle<Graphic3d_Layer>& aLayer =
    aLayerPtr != nullptr ? *aLayerPtr : myLayerIds.Find(Graphic3d_ZLayerId_Default);

  Graphic3d_DisplayPriority anOldPriority = Graphic3d_DisplayPriority_INVALID;
  if (aLayer->Remove(theStructure, anOldPriority, true))
  {
    --myNbStructures;
    if (aLayer->IsImmediate())
    {
      --myImmediateNbStructures;
    }

    AddStructure(theStructure, theLayerId, theNewPriority, true);
    return;
  }

  for (NCollection_List<occ::handle<Graphic3d_Layer>>::Iterator aLayerIter(myLayers);
       aLayerIter.More();
       aLayerIter.Next())
  {
    const occ::handle<OpenGl_Layer>& aLayerEx = aLayerIter.ChangeValue();
    if (aLayerEx == aLayer)
    {
      continue;
    }

    if (aLayerEx->Remove(theStructure, anOldPriority, true))
    {
      --myNbStructures;
      if (aLayerEx->IsImmediate())
      {
        --myImmediateNbStructures;
      }

      AddStructure(theStructure, theLayerId, theNewPriority, true);
      return;
    }
  }
}

void OpenGl_LayerList::SetLayerSettings(const Graphic3d_ZLayerId        theLayerId,
                                        const Graphic3d_ZLayerSettings& theSettings)
{
  Graphic3d_Layer& aLayer = Layer(theLayerId);
  if (aLayer.LayerSettings().IsRaytracable() != theSettings.IsRaytracable()
      && aLayer.NbStructures() != 0)
  {
    ++myModifStateOfRaytraceable;
  }
  if (aLayer.LayerSettings().IsImmediate() != theSettings.IsImmediate())
  {
    if (theSettings.IsImmediate())
    {
      myImmediateNbStructures += aLayer.NbStructures();
    }
    else
    {
      myImmediateNbStructures -= aLayer.NbStructures();
    }
  }
  aLayer.SetLayerSettings(theSettings);
}

void OpenGl_LayerList::UpdateCulling(const occ::handle<OpenGl_Workspace>& theWorkspace,
                                     const bool                           theToDrawImmediate)
{
  const occ::handle<OpenGl_FrameStats>& aStats = theWorkspace->GetGlContext()->FrameStats();
  OSD_Timer& aTimer = aStats->ActiveDataFrame().ChangeTimer(Graphic3d_FrameStatsTimer_CpuCulling);
  aTimer.Start();

  const int                    aViewId   = theWorkspace->View()->Identification();
  const Graphic3d_CullingTool& aSelector = theWorkspace->View()->BVHTreeSelector();
  for (NCollection_List<occ::handle<Graphic3d_Layer>>::Iterator aLayerIter(myLayers);
       aLayerIter.More();
       aLayerIter.Next())
  {
    const occ::handle<Graphic3d_Layer>& aLayer = aLayerIter.ChangeValue();
    if (aLayer->IsImmediate() != theToDrawImmediate)
    {
      continue;
    }

    aLayer->UpdateCulling(aViewId,
                          aSelector,
                          theWorkspace->View()->RenderingParams().FrustumCullingState);
  }

  aTimer.Stop();
  aStats->ActiveDataFrame()[Graphic3d_FrameStatsTimer_CpuCulling] = aTimer.UserTimeCPU();
}

void OpenGl_LayerList::renderLayer(const occ::handle<OpenGl_Workspace>& theWorkspace,
                                   const OpenGl_GlobalLayerSettings&    theDefaultSettings,
                                   const Graphic3d_Layer&               theLayer) const
{
  const occ::handle<OpenGl_Context>& aCtx = theWorkspace->GetGlContext();

  const Graphic3d_ZLayerSettings& aLayerSettings = theLayer.LayerSettings();

  if (aLayerSettings.ToEnableDepthTest())
  {

    aCtx->core11fwd->glDepthFunc(theDefaultSettings.DepthFunc);
  }
  else
  {
    aCtx->core11fwd->glDepthFunc(GL_ALWAYS);
  }

  occ::handle<OpenGl_TextureSet> anEnvironmentTexture = theWorkspace->EnvironmentTexture();
  if (!aLayerSettings.UseEnvironmentTexture())
  {
    theWorkspace->SetEnvironmentTexture(occ::handle<OpenGl_TextureSet>());
  }

  const Graphic3d_PolygonOffset anAppliedOffsetParams =
    theWorkspace->SetDefaultPolygonOffset(aLayerSettings.PolygonOffset());

  theWorkspace->UseDepthWrite() =
    aLayerSettings.ToEnableDepthWrite() && theDefaultSettings.DepthMask == GL_TRUE;
  aCtx->core11fwd->glDepthMask(theWorkspace->UseDepthWrite() ? GL_TRUE : GL_FALSE);

  const bool hasLocalCS = !aLayerSettings.OriginTransformation().IsNull();
  const occ::handle<OpenGl_ShaderManager>& aManager = aCtx->ShaderManager();
  occ::handle<Graphic3d_LightSet>    aLightsBack    = aManager->LightSourceState().LightSources();
  occ::handle<OpenGl_ShadowMapArray> aShadowMaps    = aManager->LightSourceState().ShadowMaps();
  const bool hasOwnLights = aCtx->ColorMask() && !aLayerSettings.Lights().IsNull()
                            && aLayerSettings.Lights() != aLightsBack;
  if (hasOwnLights)
  {
    aLayerSettings.Lights()->UpdateRevision();
    aManager->UpdateLightSourceStateTo(aLayerSettings.Lights(),
                                       theWorkspace->View()->SpecIBLMapLevels(),
                                       occ::handle<OpenGl_ShadowMapArray>());
  }

  const occ::handle<Graphic3d_Camera>& aWorldCamera = aCtx->Camera();
  if (hasLocalCS)
  {

    theWorkspace->View()->SetLocalOrigin(aLayerSettings.Origin());

    NCollection_Mat4<double> aWorldView = aWorldCamera->OrientationMatrix();
    Graphic3d_TransformUtils::Translate(aWorldView,
                                        aLayerSettings.Origin().X(),
                                        aLayerSettings.Origin().Y(),
                                        aLayerSettings.Origin().Z());

    if (!aManager->LightSourceState().ShadowMaps().IsNull())
    {

      for (OpenGl_ShadowMapArray::Iterator aShadowIter(*aManager->LightSourceState().ShadowMaps());
           aShadowIter.More();
           aShadowIter.Next())
      {
        aShadowIter.Value()->UpdateCamera(*theWorkspace->View(), &aLayerSettings.Origin());
      }
    }

    NCollection_Mat4<float> aWorldViewF;
    aWorldViewF.ConvertFrom(aWorldView);
    aCtx->WorldViewState.SetCurrent(aWorldViewF);
    aCtx->ShaderManager()->UpdateClippingState();
    aCtx->ShaderManager()->UpdateLightSourceState();
  }

  const int aViewId = theWorkspace->View()->Identification();
  for (int aPriorityIter = Graphic3d_DisplayPriority_Bottom;
       aPriorityIter <= Graphic3d_DisplayPriority_Topmost;
       ++aPriorityIter)
  {
    const NCollection_IndexedMap<const Graphic3d_CStructure*>& aStructures =
      theLayer.Structures((Graphic3d_DisplayPriority)aPriorityIter);
    for (OpenGl_Structure::StructIterator aStructIter(aStructures); aStructIter.More();
         aStructIter.Next())
    {
      const OpenGl_Structure* aStruct = aStructIter.Value();
      if (aStruct->IsCulled() || !aStruct->IsVisible(aViewId))
      {
        continue;
      }

      aStruct->Render(theWorkspace);
    }
  }

  if (hasOwnLights)
  {
    aManager->UpdateLightSourceStateTo(aLightsBack,
                                       theWorkspace->View()->SpecIBLMapLevels(),
                                       aShadowMaps);
  }
  if (hasLocalCS)
  {
    if (!aManager->LightSourceState().ShadowMaps().IsNull())
    {

      for (OpenGl_ShadowMapArray::Iterator aShadowIter(*aManager->LightSourceState().ShadowMaps());
           aShadowIter.More();
           aShadowIter.Next())
      {
        aShadowIter.Value()->UpdateCamera(*theWorkspace->View(), &gp::Origin().XYZ());
      }
    }

    aCtx->ShaderManager()->RevertClippingState();
    aCtx->ShaderManager()->UpdateLightSourceState();

    aCtx->WorldViewState.SetCurrent(aWorldCamera->OrientationMatrixF());
    theWorkspace->View()->SetLocalOrigin(gp_XYZ(0.0, 0.0, 0.0));
  }

  theWorkspace->SetDefaultPolygonOffset(anAppliedOffsetParams);

  if (!aLayerSettings.UseEnvironmentTexture())
  {
    theWorkspace->SetEnvironmentTexture(anEnvironmentTexture);
  }
}

void OpenGl_LayerList::Render(const occ::handle<OpenGl_Workspace>& theWorkspace,
                              const bool                           theToDrawImmediate,
                              const OpenGl_LayerFilter             theFilterMode,
                              const Graphic3d_ZLayerId             theLayersToProcess,
                              OpenGl_FrameBuffer*                  theReadDrawFbo,
                              OpenGl_FrameBuffer*                  theOitAccumFbo) const
{

  OpenGl_GlobalLayerSettings aPrevSettings;

  const occ::handle<OpenGl_Context>& aCtx = theWorkspace->GetGlContext();
  aCtx->core11fwd->glGetIntegerv(GL_DEPTH_FUNC, &aPrevSettings.DepthFunc);
  aCtx->core11fwd->glGetBooleanv(GL_DEPTH_WRITEMASK, &aPrevSettings.DepthMask);
  OpenGl_GlobalLayerSettings aDefaultSettings = aPrevSettings;
  const bool isShadowMapPass = theReadDrawFbo != nullptr && !theReadDrawFbo->HasColor();

  const int aPrevFilter =
    theWorkspace->RenderFilter()
    & ~(int)(OpenGl_RenderFilter_OpaqueOnly | OpenGl_RenderFilter_TransparentOnly);
  theWorkspace->SetRenderFilter(aPrevFilter | OpenGl_RenderFilter_OpaqueOnly);

  myTransparentToProcess.Clear();

  OpenGl_LayerStack::iterator aStackIter(myTransparentToProcess.Origin());
  int                         aClearDepthLayerPrev = -1, aClearDepthLayer = -1;
  const bool toPerformDepthPrepass = theWorkspace->View()->RenderingParams().ToEnableDepthPrepass
                                     && aPrevSettings.DepthMask == GL_TRUE && !isShadowMapPass;
  const occ::handle<Graphic3d_LightSet> aLightsBack =
    aCtx->ShaderManager()->LightSourceState().LightSources();
  const occ::handle<OpenGl_ShadowMapArray> aShadowMaps =
    aCtx->ShaderManager()->LightSourceState().ShadowMaps();
  for (OpenGl_FilteredIndexedLayerIterator aLayerIterStart(myLayers,
                                                           theToDrawImmediate,
                                                           theFilterMode,
                                                           theLayersToProcess);
       aLayerIterStart.More();)
  {
    bool hasSkippedDepthLayers = false;
    for (int aPassIter = toPerformDepthPrepass ? 0 : 2; aPassIter < 3; ++aPassIter)
    {
      if (aPassIter == 0)
      {
        aCtx->SetColorMask(false);
        aCtx->ShaderManager()->UpdateLightSourceStateTo(occ::handle<Graphic3d_LightSet>(),
                                                        theWorkspace->View()->SpecIBLMapLevels(),
                                                        occ::handle<OpenGl_ShadowMapArray>());
        aDefaultSettings.DepthFunc = aPrevSettings.DepthFunc;
        aDefaultSettings.DepthMask = GL_TRUE;
      }
      else if (aPassIter == 1)
      {
        if (!hasSkippedDepthLayers)
        {
          continue;
        }
        aCtx->SetColorMask(true);
        aCtx->ShaderManager()->UpdateLightSourceStateTo(aLightsBack,
                                                        theWorkspace->View()->SpecIBLMapLevels(),
                                                        aShadowMaps);
        aDefaultSettings = aPrevSettings;
      }
      else if (aPassIter == 2)
      {
        if (isShadowMapPass)
        {
          aCtx->SetColorMask(false);
          aCtx->ShaderManager()->UpdateLightSourceStateTo(occ::handle<Graphic3d_LightSet>(),
                                                          theWorkspace->View()->SpecIBLMapLevels(),
                                                          occ::handle<OpenGl_ShadowMapArray>());
        }
        else
        {
          aCtx->SetColorMask(true);
          aCtx->ShaderManager()->UpdateLightSourceStateTo(aLightsBack,
                                                          theWorkspace->View()->SpecIBLMapLevels(),
                                                          aShadowMaps);
        }
        if (toPerformDepthPrepass)
        {
          aDefaultSettings.DepthFunc = GL_EQUAL;
          aDefaultSettings.DepthMask = GL_FALSE;
        }
      }

      OpenGl_FilteredIndexedLayerIterator aLayerIter(aLayerIterStart);
      for (; aLayerIter.More(); aLayerIter.Next())
      {
        const OpenGl_Layer& aLayer = aLayerIter.Value();

        if (aLayer.LayerSettings().ToClearDepth())
        {
          aClearDepthLayer = aLayerIter.Index();
        }
        if (aLayer.IsCulled())
        {
          continue;
        }
        else if (aClearDepthLayer > aClearDepthLayerPrev)
        {

          if (aPassIter == 2)
          {
            aLayerIterStart = aLayerIter;
          }
          else
          {
            aClearDepthLayer = -1;
          }
          break;
        }
        else if (aPassIter == 0 && !aLayer.LayerSettings().ToRenderInDepthPrepass())
        {
          hasSkippedDepthLayers = true;
          continue;
        }
        else if (aPassIter == 1 && aLayer.LayerSettings().ToRenderInDepthPrepass())
        {
          continue;
        }

        theWorkspace->ResetSkippedCounter();

        renderLayer(theWorkspace, aDefaultSettings, aLayer);

        if (aPassIter != 0 && theWorkspace->NbSkippedTransparentElements() > 0)
        {
          myTransparentToProcess.Push(&aLayer);
        }
      }
      if (aPassIter == 2 && !aLayerIter.More())
      {
        aLayerIterStart = aLayerIter;
      }
    }

    if (!myTransparentToProcess.IsEmpty())
    {
      renderTransparent(theWorkspace, aStackIter, aPrevSettings, theReadDrawFbo, theOitAccumFbo);
    }
    if (aClearDepthLayer > aClearDepthLayerPrev)
    {
      aClearDepthLayerPrev = aClearDepthLayer;
      aCtx->core11fwd->glDepthMask(GL_TRUE);
      aCtx->core11fwd->glClear(GL_DEPTH_BUFFER_BIT);
    }
  }

  aCtx->ShaderManager()->UpdateLightSourceStateTo(aLightsBack,
                                                  theWorkspace->View()->SpecIBLMapLevels(),
                                                  aShadowMaps);
  aCtx->core11fwd->glDepthMask(aPrevSettings.DepthMask);
  aCtx->core11fwd->glDepthFunc(aPrevSettings.DepthFunc);

  theWorkspace->SetRenderFilter(aPrevFilter);
}

void OpenGl_LayerList::renderTransparent(const occ::handle<OpenGl_Workspace>& theWorkspace,
                                         OpenGl_LayerStack::iterator&         theLayerIter,
                                         const OpenGl_GlobalLayerSettings&    theGlobalSettings,
                                         OpenGl_FrameBuffer*                  theReadDrawFbo,
                                         OpenGl_FrameBuffer*                  theOitAccumFbo) const
{

  if (theLayerIter == myTransparentToProcess.Back())
  {
    return;
  }

  const occ::handle<OpenGl_Context>&       aCtx       = theWorkspace->GetGlContext();
  const occ::handle<OpenGl_ShaderManager>& aManager   = aCtx->ShaderManager();
  const OpenGl_LayerStack::iterator        aLayerFrom = theLayerIter;
  OpenGl_View*                             aView      = theWorkspace->View();

  Graphic3d_RenderTransparentMethod anOitMode =
    aView != nullptr ? aView->RenderingParams().TransparencyMethod : Graphic3d_RTM_BLEND_UNORDERED;

  const int aPrevFilter =
    theWorkspace->RenderFilter()
    & ~(int)(OpenGl_RenderFilter_OpaqueOnly | OpenGl_RenderFilter_TransparentOnly);
  theWorkspace->SetRenderFilter(aPrevFilter | OpenGl_RenderFilter_TransparentOnly);
  aCtx->core11fwd->glEnable(GL_BLEND);

  const occ::handle<OpenGl_FrameBuffer>* aGlDepthPeelFBOs =
    aView->DepthPeelingFbos()->DepthPeelFbosOit();
  const occ::handle<OpenGl_FrameBuffer>* aGlFrontBackColorFBOs =
    aView->DepthPeelingFbos()->FrontBackColorFbosOit();
  const occ::handle<OpenGl_FrameBuffer>& aGlBlendBackFBO =
    aView->DepthPeelingFbos()->BlendBackFboOit();

  if (anOitMode == Graphic3d_RTM_BLEND_OIT)
  {
    if (theOitAccumFbo == nullptr || theOitAccumFbo->NbColorBuffers() < 2
        || !theOitAccumFbo->ColorTexture(0)->IsValid()
        || !theOitAccumFbo->ColorTexture(1)->IsValid())
    {
      anOitMode = Graphic3d_RTM_BLEND_UNORDERED;
    }
  }
  else if (anOitMode == Graphic3d_RTM_DEPTH_PEELING_OIT)
  {
    if (!aGlBlendBackFBO->IsValid())
    {
      anOitMode = Graphic3d_RTM_BLEND_UNORDERED;
    }
  }
  const bool isMSAA              = theReadDrawFbo && theReadDrawFbo->NbSamples() > 0;
  int        aDepthPeelingDrawId = -1;

  switch (anOitMode)
  {
    case Graphic3d_RTM_BLEND_UNORDERED:
    {
      aCtx->core11fwd->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      break;
    }
    case Graphic3d_RTM_BLEND_OIT:
    {
      const float aDepthFactor = aView->RenderingParams().OitDepthFactor;
      aManager->SetWeighedOitState(aDepthFactor);

      theOitAccumFbo->BindBuffer(aCtx);

      aCtx->SetDrawBuffers(2, THE_DRAW_BUFFERS01);

      aCtx->SetColorMaskRGBA(NCollection_Vec4<bool>(true));

      aCtx->core11fwd->glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
      aCtx->core11fwd->glClear(GL_COLOR_BUFFER_BIT);
      aCtx->core15fwd->glBlendFuncSeparate(GL_ONE, GL_ONE, GL_ZERO, GL_ONE_MINUS_SRC_ALPHA);
      break;
    }
    case Graphic3d_RTM_DEPTH_PEELING_OIT:
    {
      static const float THE_MIN_DEPTH = 0.0f;
      static const float THE_MAX_DEPTH = 1.0f;

      aView->DepthPeelingFbos()->AttachDepthTexture(aCtx, theReadDrawFbo->DepthStencilTexture());

      aGlBlendBackFBO->BindDrawBuffer(aCtx);
      aCtx->SetDrawBuffers(1, THE_DRAW_BUFFERS0);

      aCtx->SetColorMaskRGBA(NCollection_Vec4<bool>(true));

      aCtx->core20fwd->glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
      aCtx->core20fwd->glClear(GL_COLOR_BUFFER_BIT);

      aGlDepthPeelFBOs[1]->BindDrawBuffer(aCtx);
      aCtx->SetDrawBuffers(1, THE_DRAW_BUFFERS0);
      aCtx->core20fwd->glClearColor(-THE_MIN_DEPTH, THE_MAX_DEPTH, 0.0f, 0.0f);
      aCtx->core20fwd->glClear(GL_COLOR_BUFFER_BIT);

      aGlFrontBackColorFBOs[0]->BindDrawBuffer(aCtx);
      aCtx->SetDrawBuffers(2, THE_DRAW_BUFFERS01);
      aCtx->core20fwd->glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
      aCtx->core20fwd->glClear(GL_COLOR_BUFFER_BIT);

      aGlFrontBackColorFBOs[1]->BindDrawBuffer(aCtx);
      aCtx->SetDrawBuffers(2, THE_DRAW_BUFFERS01);
      aCtx->core20fwd->glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
      aCtx->core20fwd->glClear(GL_COLOR_BUFFER_BIT);

      aGlDepthPeelFBOs[0]->BindBuffer(aCtx);

      aCtx->SetDrawBuffers(1, THE_DRAW_BUFFERS0);
      aCtx->core20fwd->glClearColor(THE_DEPTH_CLEAR_VALUE, THE_DEPTH_CLEAR_VALUE, 0.0f, 0.0f);
      aCtx->core20fwd->glClear(GL_COLOR_BUFFER_BIT);
      aCtx->core20fwd->glBlendEquation(GL_MAX);

      aManager->SetOitState(Graphic3d_RTM_DEPTH_PEELING_OIT);

      aGlDepthPeelFBOs[1]->ColorTexture(0)->Bind(aCtx, aCtx->DepthPeelingDepthTexUnit());
      aGlDepthPeelFBOs[1]->ColorTexture(1)->Bind(aCtx, aCtx->DepthPeelingFrontColorTexUnit());
      break;
    }
  }

  OpenGl_GlobalLayerSettings aGlobalSettings = theGlobalSettings;
  aGlobalSettings.DepthMask                  = GL_FALSE;
  aCtx->core11fwd->glDepthMask(GL_FALSE);

  for (theLayerIter = aLayerFrom; theLayerIter != myTransparentToProcess.Back(); ++theLayerIter)
  {
    renderLayer(theWorkspace, aGlobalSettings, *(*theLayerIter));
  }

  switch (anOitMode)
  {
    case Graphic3d_RTM_BLEND_UNORDERED:
    {
      break;
    }
    case Graphic3d_RTM_BLEND_OIT:
    {

      aManager->ResetOitState();
      theOitAccumFbo->UnbindBuffer(aCtx);
      if (theReadDrawFbo)
      {
        theReadDrawFbo->BindBuffer(aCtx);
      }

      aCtx->SetDrawBuffers(1, THE_DRAW_BUFFERS0);
      aCtx->SetColorMask(true);
      break;
    }
    case Graphic3d_RTM_DEPTH_PEELING_OIT:
    {

      const int            aNbPasses  = aView->RenderingParams().NbOitDepthPeelingLayers;
      OpenGl_VertexBuffer* aQuadVerts = aView->initBlitQuad(false);

      aGlDepthPeelFBOs[1]->ColorTexture(1)->Unbind(aCtx, aCtx->DepthPeelingFrontColorTexUnit());
      aGlDepthPeelFBOs[1]->ColorTexture(0)->Unbind(aCtx, aCtx->DepthPeelingDepthTexUnit());

      for (int aPass = 0; aPass < aNbPasses; ++aPass)
      {
        const int aReadId   = aPass % 2;
        aDepthPeelingDrawId = 1 - aReadId;

        aGlDepthPeelFBOs[aDepthPeelingDrawId]->BindDrawBuffer(aCtx);
        aCtx->SetDrawBuffers(1, THE_DRAW_BUFFERS0);
        aCtx->core20fwd->glClearColor(THE_DEPTH_CLEAR_VALUE, THE_DEPTH_CLEAR_VALUE, 0.0f, 0.0f);
        aCtx->core20fwd->glClear(GL_COLOR_BUFFER_BIT);

        aGlFrontBackColorFBOs[aDepthPeelingDrawId]->BindDrawBuffer(aCtx);
        aCtx->SetDrawBuffers(2, THE_DRAW_BUFFERS01);
        aCtx->core20fwd->glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        aCtx->core20fwd->glClear(GL_COLOR_BUFFER_BIT);

        aGlDepthPeelFBOs[aDepthPeelingDrawId]->BindBuffer(aCtx);
        aCtx->SetDrawBuffers(3, THE_DRAW_BUFFERS012);
        aCtx->core20fwd->glBlendEquation(GL_MAX);

        aGlDepthPeelFBOs[aReadId]->ColorTexture(0)->Bind(aCtx, aCtx->DepthPeelingDepthTexUnit());
        aGlDepthPeelFBOs[aReadId]->ColorTexture(1)->Bind(aCtx,
                                                         aCtx->DepthPeelingFrontColorTexUnit());

        for (theLayerIter = aLayerFrom; theLayerIter != myTransparentToProcess.Back();
             ++theLayerIter)
        {
          renderLayer(theWorkspace, aGlobalSettings, *(*theLayerIter));
        }

        aGlDepthPeelFBOs[aReadId]->ColorTexture(1)->Unbind(aCtx,
                                                           aCtx->DepthPeelingFrontColorTexUnit());
        aGlDepthPeelFBOs[aReadId]->ColorTexture(0)->Unbind(aCtx, aCtx->DepthPeelingDepthTexUnit());

        aGlBlendBackFBO->BindDrawBuffer(aCtx);
        aCtx->SetDrawBuffers(1, THE_DRAW_BUFFERS0);
        if (aQuadVerts->IsValid() && aManager->BindOitDepthPeelingBlendProgram(isMSAA))
        {
          aCtx->core20fwd->glBlendEquation(GL_FUNC_ADD);
          aCtx->core20fwd->glBlendFuncSeparate(GL_SRC_ALPHA,
                                               GL_ONE_MINUS_SRC_ALPHA,
                                               GL_ONE,
                                               GL_ONE_MINUS_SRC_ALPHA);
          aCtx->core20fwd->glDepthFunc(GL_ALWAYS);

          aQuadVerts->BindVertexAttrib(aCtx, Graphic3d_TOA_POS);

          const occ::handle<OpenGl_TextureSet> aTextureBack =
            aCtx->BindTextures(occ::handle<OpenGl_TextureSet>(),
                               occ::handle<OpenGl_ShaderProgram>());
          aGlDepthPeelFBOs[aDepthPeelingDrawId]->ColorTexture(2)->Bind(aCtx,
                                                                       Graphic3d_TextureUnit_0);

          aCtx->core20fwd->glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

          aQuadVerts->UnbindVertexAttrib(aCtx, Graphic3d_TOA_POS);
          aGlDepthPeelFBOs[aDepthPeelingDrawId]->ColorTexture(2)->Unbind(aCtx,
                                                                         Graphic3d_TextureUnit_0);
          aCtx->BindProgram(nullptr);

          if (!aTextureBack.IsNull())
          {
            aCtx->BindTextures(aTextureBack, occ::handle<OpenGl_ShaderProgram>());
          }

          aCtx->core11fwd->glDepthFunc(theGlobalSettings.DepthFunc);
        }
        else
        {
          aCtx->PushMessage(
            GL_DEBUG_SOURCE_APPLICATION,
            GL_DEBUG_TYPE_ERROR,
            0,
            GL_DEBUG_SEVERITY_HIGH,
            "Initialization of OIT compositing pass has failed.\n"
            "  Depth Peeling order-independent transparency will not be available.\n");
          if (aView != nullptr)
          {
            bool& aOITFlag = isMSAA ? aView->myToDisableOITMSAA : aView->myToDisableOIT;
            aOITFlag       = true;
          }
        }
      }

      aManager->ResetOitState();
      aGlBlendBackFBO->UnbindBuffer(aCtx);
      if (theReadDrawFbo)
      {
        theReadDrawFbo->BindBuffer(aCtx);
      }
      aCtx->SetDrawBuffers(1, THE_DRAW_BUFFERS0);
      aCtx->SetColorMask(true);
      break;
    }
  }

  theWorkspace->SetRenderFilter(aPrevFilter | OpenGl_RenderFilter_OpaqueOnly);
  switch (anOitMode)
  {
    case Graphic3d_RTM_BLEND_UNORDERED:
    {
      break;
    }
    case Graphic3d_RTM_BLEND_OIT:
    {

      OpenGl_VertexBuffer* aVerts = aView->initBlitQuad(false);
      if (aVerts->IsValid() && aManager->BindOitCompositingProgram(isMSAA))
      {
        aCtx->core11fwd->glDepthFunc(GL_ALWAYS);
        aCtx->core11fwd->glDepthMask(GL_FALSE);

        aVerts->BindVertexAttrib(aCtx, Graphic3d_TOA_POS);

        const occ::handle<OpenGl_TextureSet> aTextureBack =
          aCtx->BindTextures(occ::handle<OpenGl_TextureSet>(), occ::handle<OpenGl_ShaderProgram>());
        theOitAccumFbo->ColorTexture(0)->Bind(aCtx, Graphic3d_TextureUnit_0);
        theOitAccumFbo->ColorTexture(1)->Bind(aCtx, Graphic3d_TextureUnit_1);

        aCtx->core11fwd->glBlendFunc(GL_ONE_MINUS_SRC_ALPHA, GL_SRC_ALPHA);
        aCtx->core11fwd->glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        aVerts->UnbindVertexAttrib(aCtx, Graphic3d_TOA_POS);
        theOitAccumFbo->ColorTexture(1)->Unbind(aCtx, Graphic3d_TextureUnit_1);
        theOitAccumFbo->ColorTexture(0)->Unbind(aCtx, Graphic3d_TextureUnit_0);
        aCtx->BindProgram(nullptr);

        if (!aTextureBack.IsNull())
        {
          aCtx->BindTextures(aTextureBack, occ::handle<OpenGl_ShaderProgram>());
        }
      }
      else
      {
        aCtx->PushMessage(GL_DEBUG_SOURCE_APPLICATION,
                          GL_DEBUG_TYPE_ERROR,
                          0,
                          GL_DEBUG_SEVERITY_HIGH,
                          "Initialization of OIT compositing pass has failed.\n"
                          "  Blended order-independent transparency will not be available.\n");
        if (aView != nullptr)
        {
          bool& aOITFlag = isMSAA ? aView->myToDisableOITMSAA : aView->myToDisableOIT;
          aOITFlag       = true;
        }
      }
      break;
    }
    case Graphic3d_RTM_DEPTH_PEELING_OIT:
    {

      OpenGl_VertexBuffer* aVerts = aView->initBlitQuad(false);
      if (aVerts->IsValid() && aManager->BindOitDepthPeelingFlushProgram(isMSAA))
      {
        aCtx->core20fwd->glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
        aCtx->core20fwd->glDepthFunc(GL_ALWAYS);

        aVerts->BindVertexAttrib(aCtx, Graphic3d_TOA_POS);

        const occ::handle<OpenGl_TextureSet> aTextureBack =
          aCtx->BindTextures(occ::handle<OpenGl_TextureSet>(), occ::handle<OpenGl_ShaderProgram>());
        aGlDepthPeelFBOs[aDepthPeelingDrawId]->ColorTexture(1)->Bind(aCtx, Graphic3d_TextureUnit_0);
        aGlBlendBackFBO->ColorTexture(0)->Bind(aCtx, Graphic3d_TextureUnit_1);

        aCtx->core20fwd->glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        aVerts->UnbindVertexAttrib(aCtx, Graphic3d_TOA_POS);
        aGlBlendBackFBO->ColorTexture(0)->Unbind(aCtx, Graphic3d_TextureUnit_1);
        aGlDepthPeelFBOs[aDepthPeelingDrawId]->ColorTexture(1)->Unbind(aCtx,
                                                                       Graphic3d_TextureUnit_0);
        aCtx->BindProgram(nullptr);

        if (!aTextureBack.IsNull())
        {
          aCtx->BindTextures(aTextureBack, occ::handle<OpenGl_ShaderProgram>());
        }

        aCtx->core11fwd->glDepthFunc(theGlobalSettings.DepthFunc);
      }
      else
      {
        aCtx->PushMessage(
          GL_DEBUG_SOURCE_APPLICATION,
          GL_DEBUG_TYPE_ERROR,
          0,
          GL_DEBUG_SEVERITY_HIGH,
          "Initialization of OIT compositing pass has failed.\n"
          "  Depth Peeling order-independent transparency will not be available.\n");
        if (aView != nullptr)
        {
          bool& aOITFlag = isMSAA ? aView->myToDisableOITMSAA : aView->myToDisableOIT;
          aOITFlag       = true;
        }
      }
      aView->DepthPeelingFbos()->DetachDepthTexture(aCtx);

      if (theReadDrawFbo)
      {
        theReadDrawFbo->BindBuffer(aCtx);
      }
      break;
    }
  }

  aCtx->core11fwd->glDisable(GL_BLEND);
  aCtx->core11fwd->glBlendFunc(GL_ONE, GL_ZERO);
  aCtx->core11fwd->glDepthMask(theGlobalSettings.DepthMask);
  aCtx->core11fwd->glDepthFunc(theGlobalSettings.DepthFunc);
}

void OpenGl_LayerList::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_CLASS_BEGIN(theOStream, OpenGl_LayerList)

  for (NCollection_List<occ::handle<Graphic3d_Layer>>::Iterator aLayersIt(myLayers);
       aLayersIt.More();
       aLayersIt.Next())
  {
    const occ::handle<Graphic3d_Layer>& aLayerId = aLayersIt.Value();
    OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, aLayerId.get())
  }

  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myNbStructures)
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myImmediateNbStructures)
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myModifStateOfRaytraceable)
}
