#pragma once

#include <Graphic3d_Layer.hpp>

typedef Graphic3d_Layer OpenGl_Layer;

#ifndef _OpenGl_LayerFilter_H__
  #define _OpenGl_LayerFilter_H__

enum OpenGl_LayerFilter
{
  OpenGl_LF_All,
  OpenGl_LF_Upper,
  OpenGl_LF_Bottom,
  OpenGl_LF_Single,
  OpenGl_LF_RayTracable
};

#endif

#include <Graphic3d_ZLayerId.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_Handle.hpp>
#include <NCollection_DataMap.hpp>

class OpenGl_FrameBuffer;
class OpenGl_Structure;
class OpenGl_Workspace;
struct OpenGl_GlobalLayerSettings;

class OpenGl_LayerList
{
public:
  Standard_EXPORT OpenGl_LayerList();

  Standard_EXPORT virtual ~OpenGl_LayerList();

  int NbPriorities() const { return Graphic3d_DisplayPriority_NB; }

  int NbStructures() const { return myNbStructures; }

  int NbImmediateStructures() const { return myImmediateNbStructures; }

  Standard_EXPORT void InsertLayerBefore(const Graphic3d_ZLayerId        theNewLayerId,
                                         const Graphic3d_ZLayerSettings& theSettings,
                                         const Graphic3d_ZLayerId        theLayerAfter);

  Standard_EXPORT void InsertLayerAfter(const Graphic3d_ZLayerId        theNewLayerId,
                                        const Graphic3d_ZLayerSettings& theSettings,
                                        const Graphic3d_ZLayerId        theLayerBefore);

  Standard_EXPORT void RemoveLayer(const Graphic3d_ZLayerId theLayerId);

  Standard_EXPORT void AddStructure(const OpenGl_Structure*         theStruct,
                                    const Graphic3d_ZLayerId        theLayerId,
                                    const Graphic3d_DisplayPriority thePriority,
                                    bool                            isForChangePriority = false);

  Standard_EXPORT void RemoveStructure(const OpenGl_Structure* theStructure);

  Standard_EXPORT void ChangeLayer(const OpenGl_Structure*  theStructure,
                                   const Graphic3d_ZLayerId theOldLayerId,
                                   const Graphic3d_ZLayerId theNewLayerId);

  Standard_EXPORT void ChangePriority(const OpenGl_Structure*         theStructure,
                                      const Graphic3d_ZLayerId        theLayerId,
                                      const Graphic3d_DisplayPriority theNewPriority);

  OpenGl_Layer& Layer(const Graphic3d_ZLayerId theLayerId) { return *myLayerIds.Find(theLayerId); }

  const OpenGl_Layer& Layer(const Graphic3d_ZLayerId theLayerId) const
  {
    return *myLayerIds.Find(theLayerId);
  }

  Standard_EXPORT void SetLayerSettings(const Graphic3d_ZLayerId        theLayerId,
                                        const Graphic3d_ZLayerSettings& theSettings);

  Standard_EXPORT void UpdateCulling(const occ::handle<OpenGl_Workspace>& theWorkspace,
                                     const bool                           theToDrawImmediate);

  Standard_EXPORT void Render(const occ::handle<OpenGl_Workspace>& theWorkspace,
                              const bool                           theToDrawImmediate,
                              const OpenGl_LayerFilter             theFilterMode,
                              const Graphic3d_ZLayerId             theLayersToProcess,
                              OpenGl_FrameBuffer*                  theReadDrawFbo,
                              OpenGl_FrameBuffer*                  theOitAccumFbo) const;

  const NCollection_List<occ::handle<Graphic3d_Layer>>& Layers() const { return myLayers; }

  const NCollection_DataMap<Graphic3d_ZLayerId, occ::handle<Graphic3d_Layer>>& LayerIDs() const
  {
    return myLayerIds;
  }

  Standard_EXPORT void InvalidateBVHData(const Graphic3d_ZLayerId theLayerId);

  size_t ModificationStateOfRaytracable() const { return myModifStateOfRaytraceable; }

  const occ::handle<BVH_Builder3d>& FrustumCullingBVHBuilder() const { return myBVHBuilder; }

  Standard_EXPORT void SetFrustumCullingBVHBuilder(const occ::handle<BVH_Builder3d>& theBuilder);

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

protected:
  class OpenGl_LayerStack
  {
  public:
    typedef NCollection_Array1<const Graphic3d_Layer*>::const_iterator const_iterator;
    typedef NCollection_Array1<const Graphic3d_Layer*>::iterator       iterator;

    void Allocate(int theSize)
    {
      if (theSize > 0)
      {
        myStackSpace.Resize(1, theSize, false);
        myStackSpace.Init(nullptr);
        myBackPtr = myStackSpace.begin();
      }
      else
      {
        NCollection_Array1<const Graphic3d_Layer*> aDummy;
        myStackSpace.Move(std::move(aDummy));
        myBackPtr = iterator();
      }
    }

    void Clear()
    {
      myStackSpace.Init(nullptr);
      myBackPtr = myStackSpace.begin();
    }

    void Push(const OpenGl_Layer* theLayer) { (*myBackPtr++) = theLayer; }

    const_iterator Origin() const
    {
      return myStackSpace.IsEmpty() ? const_iterator() : myStackSpace.begin();
    }

    iterator Back() const { return myBackPtr; }

    iterator Origin() { return myStackSpace.IsEmpty() ? iterator() : myStackSpace.begin(); }

    bool IsEmpty() const { return Back() == Origin(); }

  private:
    NCollection_Array1<const OpenGl_Layer*> myStackSpace;
    iterator                                myBackPtr;
  };

  Standard_EXPORT void renderTransparent(const occ::handle<OpenGl_Workspace>& theWorkspace,
                                         OpenGl_LayerStack::iterator&         theLayerIter,
                                         const OpenGl_GlobalLayerSettings&    theGlobalSettings,
                                         OpenGl_FrameBuffer*                  theReadDrawFbo,
                                         OpenGl_FrameBuffer*                  theOitAccumFbo) const;

  Standard_EXPORT void renderLayer(const occ::handle<OpenGl_Workspace>& theWorkspace,
                                   const OpenGl_GlobalLayerSettings&    theDefaultSettings,
                                   const Graphic3d_Layer&               theLayer) const;

protected:
  NCollection_List<occ::handle<Graphic3d_Layer>>                        myLayers;
  NCollection_DataMap<Graphic3d_ZLayerId, occ::handle<Graphic3d_Layer>> myLayerIds;
  occ::handle<BVH_Builder3d>                                            myBVHBuilder;

  int myNbStructures;

  int myImmediateNbStructures;

  mutable size_t myModifStateOfRaytraceable;

  mutable OpenGl_LayerStack myTransparentToProcess;

public:
  DEFINE_STANDARD_ALLOC
};
