#pragma once

#include <Aspect_GenId.hpp>
#include <Graphic3d_CStructure.hpp>
#include <Graphic3d_ZLayerId.hpp>
#include <Graphic3d_ZLayerSettings.hpp>

enum Graphic3d_TypeOfLimit
{
  Graphic3d_TypeOfLimit_MaxNbLights,
  Graphic3d_TypeOfLimit_MaxNbClipPlanes,
  Graphic3d_TypeOfLimit_MaxNbViews,
  Graphic3d_TypeOfLimit_MaxTextureSize,
  Graphic3d_TypeOfLimit_MaxViewDumpSizeX,
  Graphic3d_TypeOfLimit_MaxViewDumpSizeY,
  Graphic3d_TypeOfLimit_MaxCombinedTextureUnits,

  Graphic3d_TypeOfLimit_MaxMsaa,
  Graphic3d_TypeOfLimit_HasPBR,

  Graphic3d_TypeOfLimit_HasRayTracing,
  Graphic3d_TypeOfLimit_HasRayTracingTextures,

  Graphic3d_TypeOfLimit_HasRayTracingAdaptiveSampling,

  Graphic3d_TypeOfLimit_HasRayTracingAdaptiveSamplingAtomic,

  Graphic3d_TypeOfLimit_HasSRGB,
  Graphic3d_TypeOfLimit_HasBlendedOit,

  Graphic3d_TypeOfLimit_HasBlendedOitMsaa,

  Graphic3d_TypeOfLimit_HasFlatShading,

  Graphic3d_TypeOfLimit_HasMeshEdges,

  Graphic3d_TypeOfLimit_IsWorkaroundFBO,

  Graphic3d_TypeOfLimit_NB
};

#include <Standard_Integer.hpp>
#include <NCollection_Sequence.hpp>

class Aspect_DisplayConnection;
class Aspect_Window;
class Graphic3d_CView;
class Graphic3d_Layer;
class Graphic3d_StructureManager;
class TCollection_AsciiString;

class Graphic3d_GraphicDriver : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(Graphic3d_GraphicDriver, Standard_Transient)
public:
  virtual int InquireLimit(const Graphic3d_TypeOfLimit theType) const = 0;

  int InquireLightLimit() const { return InquireLimit(Graphic3d_TypeOfLimit_MaxNbLights); }

  int InquirePlaneLimit() const { return InquireLimit(Graphic3d_TypeOfLimit_MaxNbClipPlanes); }

  int InquireViewLimit() const { return InquireLimit(Graphic3d_TypeOfLimit_MaxNbViews); }

public:
  virtual occ::handle<Graphic3d_CStructure> CreateStructure(
    const occ::handle<Graphic3d_StructureManager>& theManager) = 0;

  virtual void RemoveStructure(occ::handle<Graphic3d_CStructure>& theCStructure) = 0;

  virtual occ::handle<Graphic3d_CView> CreateView(
    const occ::handle<Graphic3d_StructureManager>& theMgr) = 0;

  virtual void RemoveView(const occ::handle<Graphic3d_CView>& theView) = 0;

  virtual void EnableVBO(const bool status) = 0;

  virtual bool IsVerticalSync() const = 0;

  virtual void SetVerticalSync(bool theToEnable) = 0;

  virtual bool MemoryInfo(size_t& theFreeBytes, TCollection_AsciiString& theInfo) const = 0;

  virtual float DefaultTextHeight() const = 0;

  virtual void TextSize(const occ::handle<Graphic3d_CView>& theView,
                        const char*                         theText,
                        const float                         theHeight,
                        float&                              theWidth,
                        float&                              theAscent,
                        float&                              theDescent) const = 0;

  Standard_EXPORT virtual void InsertLayerBefore(const Graphic3d_ZLayerId        theNewLayerId,
                                                 const Graphic3d_ZLayerSettings& theSettings,
                                                 const Graphic3d_ZLayerId        theLayerAfter) = 0;

  Standard_EXPORT virtual void InsertLayerAfter(const Graphic3d_ZLayerId        theNewLayerId,
                                                const Graphic3d_ZLayerSettings& theSettings,
                                                const Graphic3d_ZLayerId        theLayerBefore) = 0;

  Standard_EXPORT virtual void RemoveZLayer(const Graphic3d_ZLayerId theLayerId) = 0;

  Standard_EXPORT virtual void ZLayers(NCollection_Sequence<int>& theLayerSeq) const;

  Standard_EXPORT virtual void SetZLayerSettings(const Graphic3d_ZLayerId        theLayerId,
                                                 const Graphic3d_ZLayerSettings& theSettings) = 0;

  Standard_EXPORT virtual const Graphic3d_ZLayerSettings& ZLayerSettings(
    const Graphic3d_ZLayerId theLayerId) const;

  virtual bool ViewExists(const occ::handle<Aspect_Window>& theWindow,
                          occ::handle<Graphic3d_CView>&     theView) = 0;

  Standard_EXPORT const occ::handle<Aspect_DisplayConnection>& GetDisplayConnection() const;

  Standard_EXPORT int NewIdentification();

  Standard_EXPORT void RemoveIdentification(const int theId);

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

protected:
  Standard_EXPORT Graphic3d_GraphicDriver(const occ::handle<Aspect_DisplayConnection>& theDisp);

protected:
  occ::handle<Aspect_DisplayConnection>                                 myDisplayConnection;
  Aspect_GenId                                                          myStructGenId;
  NCollection_List<occ::handle<Graphic3d_Layer>>                        myLayers;
  NCollection_DataMap<Graphic3d_ZLayerId, occ::handle<Graphic3d_Layer>> myLayerIds;
};
