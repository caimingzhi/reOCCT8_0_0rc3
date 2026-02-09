#pragma once

#include <Graphic3d_GraphicDriver.hpp>

#include <Aspect_DisplayConnection.hpp>
#include <Graphic3d_CView.hpp>
#include <Graphic3d_CStructure.hpp>
#include <NCollection_DataMap.hpp>
#include <OpenGl_Context.hpp>

class Aspect_Window;
class OpenGl_Structure;
class OpenGl_View;
class OpenGl_Window;

class OpenGl_StateCounter
{
public:
  OpenGl_StateCounter()
      : myCounter(0)
  {
  }

  size_t Increment() { return ++myCounter; }

private:
  size_t myCounter;
};

class OpenGl_GraphicDriver : public Graphic3d_GraphicDriver
{
  DEFINE_STANDARD_RTTIEXT(OpenGl_GraphicDriver, Graphic3d_GraphicDriver)
public:
  Standard_EXPORT OpenGl_GraphicDriver(const occ::handle<Aspect_DisplayConnection>& theDisp,
                                       const bool theToInitialize = true);

  Standard_EXPORT ~OpenGl_GraphicDriver() override;

  Standard_EXPORT void ReleaseContext();

  Standard_EXPORT bool InitContext();

  Standard_EXPORT bool InitEglContext(Aspect_Display          theEglDisplay,
                                      Aspect_RenderingContext theEglContext,
                                      void*                   theEglConfig);

  Standard_EXPORT int InquireLimit(const Graphic3d_TypeOfLimit theType) const override;

public:
  Standard_EXPORT occ::handle<Graphic3d_CStructure> CreateStructure(
    const occ::handle<Graphic3d_StructureManager>& theManager) override;

  Standard_EXPORT void RemoveStructure(occ::handle<Graphic3d_CStructure>& theCStructure) override;

  Standard_EXPORT occ::handle<Graphic3d_CView> CreateView(
    const occ::handle<Graphic3d_StructureManager>& theMgr) override;

  Standard_EXPORT void RemoveView(const occ::handle<Graphic3d_CView>& theView) override;

  Standard_EXPORT virtual occ::handle<OpenGl_Window> CreateRenderWindow(
    const occ::handle<Aspect_Window>& theNativeWindow,
    const occ::handle<Aspect_Window>& theSizeWindow,
    const Aspect_RenderingContext     theContext);

public:
  Standard_EXPORT void TextSize(const occ::handle<Graphic3d_CView>& theView,
                                const char*                         theText,
                                const float                         theHeight,
                                float&                              theWidth,
                                float&                              theAscent,
                                float&                              theDescent) const override;

  Standard_EXPORT float DefaultTextHeight() const override;

  Standard_EXPORT bool ViewExists(const occ::handle<Aspect_Window>& theWindow,
                                  occ::handle<Graphic3d_CView>&     theView) override;

public:
  Standard_EXPORT void InsertLayerBefore(const Graphic3d_ZLayerId        theNewLayerId,
                                         const Graphic3d_ZLayerSettings& theSettings,
                                         const Graphic3d_ZLayerId        theLayerAfter) override;

  Standard_EXPORT void InsertLayerAfter(const Graphic3d_ZLayerId        theNewLayerId,
                                        const Graphic3d_ZLayerSettings& theSettings,
                                        const Graphic3d_ZLayerId        theLayerBefore) override;

  Standard_EXPORT void RemoveZLayer(const Graphic3d_ZLayerId theLayerId) override;

  Standard_EXPORT void SetZLayerSettings(const Graphic3d_ZLayerId        theLayerId,
                                         const Graphic3d_ZLayerSettings& theSettings) override;

public:
  inline const OpenGl_Caps& Options() const { return *myCaps.operator->(); }

  inline OpenGl_Caps& ChangeOptions() { return *myCaps.operator->(); }

  Standard_EXPORT void SetBuffersNoSwap(const bool theIsNoSwap);

  Standard_EXPORT void EnableVBO(const bool theToTurnOn) override;

  Standard_EXPORT bool IsVerticalSync() const override;

  Standard_EXPORT void SetVerticalSync(bool theToEnable) override;

  Standard_EXPORT bool MemoryInfo(size_t&                  theFreeBytes,
                                  TCollection_AsciiString& theInfo) const override;

public:
  Standard_EXPORT const occ::handle<OpenGl_Context>& GetSharedContext(bool theBound = false) const;

  Aspect_Display getRawGlDisplay() const { return myEglDisplay; }

  Aspect_RenderingContext getRawGlContext() const { return myEglContext; }

  void* getRawGlConfig() const { return myEglConfig; }

  Standard_EXPORT void setDeviceLost();

public:
  OpenGl_StateCounter* GetStateCounter() const { return &myStateCounter; }

  size_t GetNextPrimitiveArrayUID() const { return myUIDGenerator.Increment(); }

protected:
  Standard_EXPORT void chooseVisualInfo();

protected:
  bool myIsOwnContext;

  Aspect_Display          myEglDisplay;
  Aspect_RenderingContext myEglContext;
  void*                   myEglConfig;

  occ::handle<OpenGl_Caps>                    myCaps;
  NCollection_Map<occ::handle<OpenGl_View>>   myMapOfView;
  NCollection_DataMap<int, OpenGl_Structure*> myMapOfStructure;

  mutable OpenGl_StateCounter myStateCounter;
  mutable OpenGl_StateCounter myUIDGenerator;
};
