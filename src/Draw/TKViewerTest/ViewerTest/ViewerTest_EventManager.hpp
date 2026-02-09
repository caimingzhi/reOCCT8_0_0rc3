#pragma once

#include <AIS_ViewController.hpp>
#include <TCollection_AsciiString.hpp>

class AIS_InteractiveContext;
class Aspect_Window;
class V3d_View;

class ViewerTest_EventManager : public Standard_Transient, public AIS_ViewController
{
  DEFINE_STANDARD_RTTIEXT(ViewerTest_EventManager, Standard_Transient)
public:
  static bool& ToCloseViewOnEscape()
  {
    static bool Draw_ToCloseViewOnEsc = false;
    return Draw_ToCloseViewOnEsc;
  }

  static bool& ToExitOnCloseView()
  {
    static bool Draw_ToExitOnCloseView = false;
    return Draw_ToExitOnCloseView;
  }

  Standard_EXPORT static const occ::handle<AIS_AnimationCamera>& GlobalViewAnimation();

public:
  Standard_EXPORT ViewerTest_EventManager(const occ::handle<V3d_View>&               aView,
                                          const occ::handle<AIS_InteractiveContext>& aCtx);

  Standard_EXPORT ~ViewerTest_EventManager() override;

  Standard_EXPORT static void SetupWindowCallbacks(const occ::handle<Aspect_Window>& theWin);

  const occ::handle<AIS_InteractiveContext>& Context() const { return myCtx; }

  bool ToPickPoint() const { return myToPickPnt; }

  void StartPickPoint(const char* theArgX, const char* theArgY, const char* theArgZ)
  {
    myToPickPnt        = true;
    myPickPntArgVec[0] = theArgX;
    myPickPntArgVec[1] = theArgY;
    myPickPntArgVec[2] = theArgZ;
  }

  Standard_EXPORT bool UpdateMouseScroll(const Aspect_ScrollDelta& theDelta) override;

  Standard_EXPORT bool UpdateMouseClick(const NCollection_Vec2<int>& thePoint,
                                        Aspect_VKeyMouse             theButton,
                                        Aspect_VKeyFlags             theModifiers,
                                        bool                         theIsDoubleClick) override;

  Standard_EXPORT bool UpdateMouseButtons(const NCollection_Vec2<int>& thePoint,
                                          Aspect_VKeyMouse             theButtons,
                                          Aspect_VKeyFlags             theModifiers,
                                          bool                         theIsEmulated) override;

  Standard_EXPORT void KeyDown(Aspect_VKey theKey,
                               double      theTime,
                               double      thePressure = 1.0) override;

  Standard_EXPORT void KeyUp(Aspect_VKey theKey, double theTime) override;

  Standard_EXPORT void ProcessExpose() override;

  Standard_EXPORT void handleViewRedraw(const occ::handle<AIS_InteractiveContext>& theCtx,
                                        const occ::handle<V3d_View>& theView) override;

  Standard_EXPORT void ProcessConfigure(bool theIsResized = true) override;

  Standard_EXPORT void ProcessInput() override;

  Standard_EXPORT void ProcessKeyPress(Aspect_VKey theKey);

  Standard_EXPORT void OnSubviewChanged(const occ::handle<AIS_InteractiveContext>& theCtx,
                                        const occ::handle<V3d_View>&               theOldView,
                                        const occ::handle<V3d_View>& theNewView) override;

protected:
  void addActionHotKeys(Aspect_VKey  theAction,
                        unsigned int theHotKey1 = 0,
                        unsigned int theHotKey2 = 0,
                        unsigned int theHotKey3 = 0,
                        unsigned int theHotKey4 = 0,
                        unsigned int theHotKey5 = 0)
  {
    if (theHotKey1 != 0)
    {
      myNavKeyMap.Bind(theHotKey1, theAction);
    }
    if (theHotKey2 != 0)
    {
      myNavKeyMap.Bind(theHotKey2, theAction);
    }
    if (theHotKey3 != 0)
    {
      myNavKeyMap.Bind(theHotKey3, theAction);
    }
    if (theHotKey4 != 0)
    {
      myNavKeyMap.Bind(theHotKey4, theAction);
    }
    if (theHotKey5 != 0)
    {
      myNavKeyMap.Bind(theHotKey5, theAction);
    }
  }

  Standard_EXPORT bool navigationKeyModifierSwitch(unsigned int theModifOld,
                                                   unsigned int theModifNew,
                                                   double       theTimeStamp);

private:
#if defined(__EMSCRIPTEN__)

  static void onWasmRedrawView(void*);
#endif

private:
  occ::handle<AIS_InteractiveContext> myCtx;
  occ::handle<V3d_View>               myView;

  NCollection_DataMap<unsigned int, Aspect_VKey> myNavKeyMap;

  TCollection_AsciiString myPickPntArgVec[3];
  bool                    myToPickPnt;
  bool                    myIsTmpContRedraw;

  unsigned int myNbUpdateRequests;
};
