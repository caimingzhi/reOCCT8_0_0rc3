#pragma once

#include <Media_IFrameQueue.hpp>
#include <Media_Timer.hpp>
#include <OSD_Thread.hpp>
#include <Standard_Condition.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

#include <mutex>

class Media_BufferPool;
class Media_CodecContext;
class Media_FormatContext;
class Media_Scaler;

class Media_PlayerContext : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(Media_PlayerContext, Standard_Transient)
public:
  Standard_EXPORT static occ::handle<Media_Frame> DumpFirstFrame(
    const TCollection_AsciiString& theSrcVideo,
    TCollection_AsciiString&       theMediaInfo);

  Standard_EXPORT static bool DumpFirstFrame(const TCollection_AsciiString& theSrcVideo,
                                             const TCollection_AsciiString& theOutImage,
                                             TCollection_AsciiString&       theMediaInfo,
                                             int                            theMaxSize = 0);

public:
  Standard_EXPORT Media_PlayerContext(Media_IFrameQueue* theFrameQueue);

  Standard_EXPORT ~Media_PlayerContext() override;

public:
  Standard_EXPORT void SetInput(const TCollection_AsciiString& theInputPath, bool theToWait);

  Standard_EXPORT void PlaybackState(bool& theIsPaused, double& theProgress, double& theDuration);

  Standard_EXPORT void PlayPause(bool& theIsPaused, double& theProgress, double& theDuration);

  Standard_EXPORT void Seek(double thePosSec);

  Standard_EXPORT void Pause();

  Standard_EXPORT void Resume();

  bool ToForceRgb() const { return myToForceRgb; }

  void SetForceRgb(bool theToForce) { myToForceRgb = theToForce; }

private:
  enum Media_PlayerEvent
  {
    Media_PlayerEvent_NONE = 0,
    Media_PlayerEvent_PAUSE,
    Media_PlayerEvent_RESUME,
    Media_PlayerEvent_SEEK,
    Media_PlayerEvent_NEXT,
  };

private:
  Standard_EXPORT void doThreadLoop();

  Standard_EXPORT void pushPlayEvent(Media_PlayerEvent thePlayEvent);

  Standard_EXPORT bool popPlayEvent(Media_PlayerEvent&                      thePlayEvent,
                                    const occ::handle<Media_FormatContext>& theFormatCtx,
                                    const occ::handle<Media_CodecContext>&  theVideoCtx,
                                    const occ::handle<Media_Frame>&         theFrame);

  bool receiveFrame(const occ::handle<Media_Frame>&        theFrame,
                    const occ::handle<Media_CodecContext>& theVideoCtx);

  static void* doThreadWrapper(void* theData)
  {
    Media_PlayerContext* aThis = (Media_PlayerContext*)theData;
    aThis->doThreadLoop();
    return nullptr;
  }

private:
  Media_IFrameQueue* myFrameQueue;
  OSD_Thread         myThread;
  std::mutex         myMutex;

  Standard_Condition myWakeEvent;
  Standard_Condition myNextEvent;
  Media_Timer        myTimer;
  double             myDuration;

  occ::handle<Media_BufferPool> myBufferPools[4];
  occ::handle<Media_Frame>      myFrameTmp;
  occ::handle<Media_Scaler>     myScaler;
  bool                          myToForceRgb;

  volatile bool              myToShutDown;
  TCollection_AsciiString    myInputPath;
  volatile double            mySeekTo;
  volatile Media_PlayerEvent myPlayEvent;
};
