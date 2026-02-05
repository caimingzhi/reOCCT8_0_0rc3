#include <AIS_MediaPlayer.hpp>

#include <AIS_InteractiveContext.hpp>
#include <Media_PlayerContext.hpp>
#include <Message_Messenger.hpp>
#include <Graphic3d_ArrayOfTriangles.hpp>
#include <SelectMgr_EntityOwner.hpp>
#include <Select3D_SensitivePrimitiveArray.hpp>
#include <V3d_Viewer.hpp>

IMPLEMENT_STANDARD_RTTIEXT(AIS_MediaPlayer, AIS_InteractiveObject)

//! Create an array of triangles defining a rectangle.
static occ::handle<Graphic3d_ArrayOfTriangles> createRectangleArray(
  const NCollection_Vec2<int>& theLower,
  const NCollection_Vec2<int>& theUpper,
  Graphic3d_ArrayFlags         theFlags)
{
  occ::handle<Graphic3d_ArrayOfTriangles> aRectTris =
    new Graphic3d_ArrayOfTriangles(4, 6, theFlags);
  aRectTris->AddVertex(gp_Pnt(theLower.x(), theLower.y(), 0.0), gp_Pnt2d(0.0, 1.0));
  aRectTris->AddVertex(gp_Pnt(theLower.x(), theUpper.y(), 0.0), gp_Pnt2d(0.0, 0.0));
  aRectTris->AddVertex(gp_Pnt(theUpper.x(), theUpper.y(), 0.0), gp_Pnt2d(1.0, 0.0));
  aRectTris->AddVertex(gp_Pnt(theUpper.x(), theLower.y(), 0.0), gp_Pnt2d(1.0, 1.0));
  aRectTris->AddEdges(1, 2, 3);
  aRectTris->AddEdges(1, 3, 4);
  return aRectTris;
}

//=================================================================================================

AIS_MediaPlayer::AIS_MediaPlayer()
    : myFramePair(new Graphic3d_MediaTextureSet()),
      myFrameSize(1, 1),
      myToClosePlayer(false)
{
  SetTransformPersistence(new Graphic3d_TransformPers(Graphic3d_TMF_2d, Aspect_TOTP_LEFT_LOWER));
  SetZLayer(Graphic3d_ZLayerId_TopOSD);
  SetInfiniteState(true);

  Graphic3d_MaterialAspect aMat;
  myFrameAspect = new Graphic3d_AspectFillArea3d(Aspect_IS_SOLID,
                                                 Quantity_NOC_WHITE,
                                                 Quantity_NOC_BLACK,
                                                 Aspect_TOL_SOLID,
                                                 1.0f,
                                                 aMat,
                                                 aMat);
  myFrameAspect->SetShadingModel(Graphic3d_TypeOfShadingModel_Unlit);
  myFrameAspect->SetTextureMapOn(true);
  myFrameAspect->SetTextureSet(myFramePair);
}

//=================================================================================================

AIS_MediaPlayer::~AIS_MediaPlayer()
{
  // stop threads
  myFramePair.Nullify();
}

//=================================================================================================

void AIS_MediaPlayer::OpenInput(const TCollection_AsciiString& thePath, bool theToWait)
{
  if (myFramePair->PlayerContext().IsNull() && thePath.IsEmpty())
  {
    return;
  }

  myFramePair->OpenInput(thePath, theToWait);
  SynchronizeAspects();
}

//=================================================================================================

bool AIS_MediaPlayer::PresentFrame(const NCollection_Vec2<int>& theLeftCorner,
                                   const NCollection_Vec2<int>& theMaxSize)
{
  if (myToClosePlayer)
  {
    myToClosePlayer = false;
    if (!HasInteractiveContext())
    {
      return false;
    }

    if (!myFramePair->PlayerContext().IsNull())
    {
      myFramePair->PlayerContext()->Pause();
    }

    occ::handle<AIS_InteractiveContext> aCtx  = GetContext();
    occ::handle<AIS_InteractiveObject>  aThis = this;
    aCtx->Remove(aThis, false);
    aCtx->CurrentViewer()->Invalidate();
    return true;
  }

  if (myFramePair->PlayerContext().IsNull())
  {
    return false;
  }

  bool toRedraw = myFramePair->SwapFrames();
  toRedraw      = updateSize(theLeftCorner, theMaxSize) || toRedraw;
  if (toRedraw)
  {
    myFrameAspect->SetShaderProgram(myFramePair->ShaderProgram());
    SynchronizeAspects();
  }
  return toRedraw;
}

//=================================================================================================

bool AIS_MediaPlayer::updateSize(const NCollection_Vec2<int>& theLeftCorner,
                                 const NCollection_Vec2<int>& theMaxSize)
{
  const NCollection_Vec2<int> aFrameSize = myFramePair->FrameSize();
  NCollection_Vec2<int>       aNewPos    = theLeftCorner;
  NCollection_Vec2<int>       aNewSize   = myFrameSize;
  if (aFrameSize.x() > 0 && aFrameSize.y() > 0)
  {
    const double anAspect   = double(theMaxSize.x()) / double(theMaxSize.y());
    const double aFitAspect = double(aFrameSize.x()) / double(aFrameSize.y());
    aNewSize                = aFrameSize;
    if (aFitAspect >= anAspect)
    {
      aNewSize.y() = int(double(aFrameSize.x()) / aFitAspect);
    }
    else
    {
      aNewSize.x() = int(double(aFrameSize.y()) * aFitAspect);
    }

    for (int aCoord = 0; aCoord < 2; ++aCoord)
    {
      if (aNewSize[aCoord] > theMaxSize[aCoord])
      {
        const double aScale = double(theMaxSize[aCoord]) / double(aNewSize[aCoord]);
        aNewSize.x()        = int(double(aNewSize.x()) * aScale);
        aNewSize.y()        = int(double(aNewSize.y()) * aScale);
      }
    }

    aNewPos = theLeftCorner + theMaxSize / 2 - aNewSize / 2;
  }
  else if (myFrameSize.x() < 2 || myFrameSize.y() < 2)
  {
    aNewSize = theMaxSize;
  }

  if (myFrameSize == aNewSize && myFrameBottomLeft == aNewPos)
  {
    return false;
  }

  myFrameSize       = aNewSize;
  myFrameBottomLeft = aNewPos;
  if (HasInteractiveContext())
  {
    SetToUpdate();
    GetContext()->Redisplay(this, false);
    GetContext()->CurrentViewer()->Invalidate();
  }
  return true;
}

//=================================================================================================

void AIS_MediaPlayer::PlayPause()
{
  if (myFramePair->PlayerContext().IsNull())
  {
    return;
  }

  double aProgress = 0.0, aDuration = 0.0;
  bool   isPaused = false;
  myFramePair->PlayerContext()->PlayPause(isPaused, aProgress, aDuration);
}

//=================================================================================================

void AIS_MediaPlayer::Compute(const occ::handle<PrsMgr_PresentationManager>&,
                              const occ::handle<Prs3d_Presentation>& thePrs,
                              const int                              theMode)
{
  thePrs->SetInfiniteState(IsInfinite());
  if (theMode != 0)
  {
    return;
  }

  // main frame
  {
    occ::handle<Graphic3d_ArrayOfTriangles> aTris =
      createRectangleArray(myFrameBottomLeft,
                           myFrameBottomLeft + myFrameSize,
                           Graphic3d_ArrayFlags_VertexTexel);
    occ::handle<Graphic3d_Group> aMainGroup = thePrs->NewGroup();
    aMainGroup->SetGroupPrimitivesAspect(myFrameAspect);
    aMainGroup->AddPrimitiveArray(aTris);
  }
}

//=================================================================================================

void AIS_MediaPlayer::ComputeSelection(const occ::handle<SelectMgr_Selection>& theSel,
                                       const int                               theMode)
{
  if (theMode != 0)
  {
    return;
  }

  occ::handle<Graphic3d_ArrayOfTriangles> aTris =
    createRectangleArray(myFrameBottomLeft,
                         myFrameBottomLeft + myFrameSize,
                         Graphic3d_ArrayFlags_None);

  occ::handle<SelectMgr_EntityOwner>            anOwner = new SelectMgr_EntityOwner(this, 5);
  occ::handle<Select3D_SensitivePrimitiveArray> aSens =
    new Select3D_SensitivePrimitiveArray(anOwner);
  aSens->InitTriangulation(aTris->Attributes(), aTris->Indices(), TopLoc_Location());
  theSel->Add(aSens);
}
