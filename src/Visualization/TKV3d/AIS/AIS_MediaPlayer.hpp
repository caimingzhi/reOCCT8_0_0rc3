#pragma once

#include <AIS_InteractiveObject.hpp>
#include <Graphic3d_MediaTextureSet.hpp>

class Media_PlayerContext;

class AIS_MediaPlayer : public AIS_InteractiveObject
{
  DEFINE_STANDARD_RTTIEXT(AIS_MediaPlayer, AIS_InteractiveObject)
public:
  Standard_EXPORT AIS_MediaPlayer();

  Standard_EXPORT ~AIS_MediaPlayer() override;

  void SetCallback(Graphic3d_MediaTextureSet::CallbackOnUpdate_t theCallbackFunction,
                   void*                                         theCallbackUserPtr)
  {
    myFramePair->SetCallback(theCallbackFunction, theCallbackUserPtr);
  }

  Standard_EXPORT void OpenInput(const TCollection_AsciiString& thePath, bool theToWait);

  Standard_EXPORT bool PresentFrame(const NCollection_Vec2<int>& theLeftCorner,
                                    const NCollection_Vec2<int>& theMaxSize);

  const occ::handle<Media_PlayerContext>& PlayerContext() const
  {
    return myFramePair->PlayerContext();
  }

  Standard_EXPORT void PlayPause();

  void SetClosePlayer()
  {
    myToClosePlayer = true;
    myFramePair->Notify();
  }

  double Duration() const { return myFramePair->Duration(); }

protected:
  bool AcceptDisplayMode(const int theMode) const override { return theMode == 0; }

  Standard_EXPORT void Compute(const occ::handle<PrsMgr_PresentationManager>& thePrsMgr,
                               const occ::handle<Prs3d_Presentation>&         thePrs,
                               const int                                      theMode) override;

  Standard_EXPORT void ComputeSelection(const occ::handle<SelectMgr_Selection>& theSel,
                                        const int                               theMode) override;

protected:
  Standard_EXPORT bool updateSize(const NCollection_Vec2<int>& theLeftCorner,
                                  const NCollection_Vec2<int>& theMaxSize);

protected:
  occ::handle<Graphic3d_MediaTextureSet>  myFramePair;
  occ::handle<Graphic3d_AspectFillArea3d> myFrameAspect;
  NCollection_Vec2<int>                   myFrameBottomLeft;
  NCollection_Vec2<int>                   myFrameSize;
  bool                                    myToClosePlayer;
};
