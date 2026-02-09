#pragma once

#include <OSD_Thread.hpp>
#include <Standard_Condition.hpp>
#include <Standard_Type.hpp>

#include <mutex>

class V3d_View;

class ViewerTest_ContinuousRedrawer
{
public:
  Standard_EXPORT static ViewerTest_ContinuousRedrawer& Instance();

public:
  Standard_EXPORT ~ViewerTest_ContinuousRedrawer();

  bool IsStarted() const { return myThread.GetId() != 0; }

  Standard_EXPORT void Start(const occ::handle<V3d_View>& theView, double theTargetFps);

  Standard_EXPORT void Stop(const occ::handle<V3d_View>& theView = nullptr);

  bool IsPaused() const { return myToPause; }

  Standard_EXPORT void Pause();

private:
  void doThreadLoop();

  static void* doThreadWrapper(void* theData)
  {
    ViewerTest_ContinuousRedrawer* aThis = (ViewerTest_ContinuousRedrawer*)theData;
    aThis->doThreadLoop();
    return nullptr;
  }

  ViewerTest_ContinuousRedrawer();

private:
  occ::handle<V3d_View> myView;
  OSD_Thread            myThread;
  std::mutex            myMutex;
  Standard_Condition    myWakeEvent;
  double                myTargetFps;
  volatile bool         myToStop;
  volatile bool         myToPause;
};
