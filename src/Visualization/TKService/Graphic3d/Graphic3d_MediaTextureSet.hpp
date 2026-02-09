#pragma once

#include <Media_IFrameQueue.hpp>
#include <Graphic3d_MediaTexture.hpp>
#include <Graphic3d_TextureSet.hpp>

#include <mutex>

class Graphic3d_ShaderProgram;
class Media_PlayerContext;

class Graphic3d_MediaTextureSet : public Graphic3d_TextureSet, public Media_IFrameQueue
{
  DEFINE_STANDARD_RTTIEXT(Graphic3d_MediaTextureSet, Graphic3d_TextureSet)
public:
  typedef void (*CallbackOnUpdate_t)(void* theUserPtr);

public:
  Standard_EXPORT Graphic3d_MediaTextureSet();

  Standard_EXPORT void SetCallback(CallbackOnUpdate_t theCallbackFunction,
                                   void*              theCallbackUserPtr);

  Standard_EXPORT void Notify();

  const TCollection_AsciiString& Input() const { return myInput; }

  Standard_EXPORT void OpenInput(const TCollection_AsciiString& thePath, bool theToWait);

  const occ::handle<Media_PlayerContext>& PlayerContext() const { return myPlayerCtx; }

  Standard_EXPORT bool SwapFrames();

  NCollection_Vec2<int> FrameSize() const { return myFrameSize; }

  occ::handle<Graphic3d_ShaderProgram> ShaderProgram() const
  {
    if (myIsPlanarYUV)
    {
      return myIsFullRangeYUV ? myShaderYUVJ : myShaderYUV;
    }
    return occ::handle<Graphic3d_ShaderProgram>();
  }

  bool IsPlanarYUV() const { return myIsPlanarYUV; }

  bool IsFullRangeYUV() const { return myIsFullRangeYUV; }

  double Duration() const { return myDuration; }

  double Progress() const { return myProgress; }

private:
  Standard_EXPORT occ::handle<Media_Frame> LockFrame() override;

  Standard_EXPORT void ReleaseFrame(const occ::handle<Media_Frame>& theFrame) override;

protected:
  occ::handle<Media_PlayerContext>     myPlayerCtx;
  occ::handle<Media_Frame>             myFramePair[2];
  occ::handle<Graphic3d_ShaderProgram> myShaderYUV;
  occ::handle<Graphic3d_ShaderProgram> myShaderYUVJ;
  std::mutex                           myMutex;
  TCollection_AsciiString              myInput;
  CallbackOnUpdate_t                   myCallbackFunction;
  void*                                myCallbackUserPtr;
  NCollection_Vec2<int>                myFrameSize;
  double                               myProgress;
  double                               myDuration;
  int                                  myFront;
  bool                                 myToPresentFrame;

  bool myIsPlanarYUV;
  bool myIsFullRangeYUV;
};
