

#include <Graphic3d_CView.hpp>

#include <Aspect_NeutralWindow.hpp>
#include <Aspect_OpenVRSession.hpp>
#include <Graphic3d_CubeMapPacked.hpp>
#include <Graphic3d_Layer.hpp>
#include <NCollection_Map.hpp>
#include <Graphic3d_StructureManager.hpp>
class Graphic3d_Structure;

IMPLEMENT_STANDARD_RTTIEXT(Graphic3d_CView, Graphic3d_DataStructureManager)

Graphic3d_CView::Graphic3d_CView(const occ::handle<Graphic3d_StructureManager>& theMgr)
    : myId(0),

      myParentView(nullptr),
      myIsSubviewComposer(false),
      mySubviewCorner(Aspect_TOTP_LEFT_UPPER),
      mySubviewSize(1.0, 1.0),

      myStructureManager(theMgr),
      myCamera(new Graphic3d_Camera()),
      myIsInComputedMode(false),
      myIsActive(false),
      myIsRemoved(false),
      myBackfacing(Graphic3d_TypeOfBackfacingModel_Auto),
      myVisualization(Graphic3d_TOV_WIREFRAME),

      myZLayerTarget(Graphic3d_ZLayerId_BotOSD),
      myZLayerRedrawMode(false),

      myBgColor(Quantity_NOC_BLACK),
      myBackgroundType(Graphic3d_TOB_NONE),
      myToUpdateSkydome(false),

      myUnitFactor(1.0)
{
  myId = myStructureManager->Identification(this);
}

Graphic3d_CView::~Graphic3d_CView()
{
  myXRSession.Nullify();
  if (!IsRemoved())
  {
    myStructureManager->UnIdentification(this);
  }
}

void Graphic3d_CView::SetBackgroundSkydome(const Aspect_SkydomeBackground& theAspect,
                                           bool                            theToUpdatePBREnv)
{
  myToUpdateSkydome   = true;
  mySkydomeAspect     = theAspect;
  myCubeMapBackground = new Graphic3d_CubeMapPacked("");
  SetBackgroundType(Graphic3d_TOB_CUBEMAP);
  if (theToUpdatePBREnv && !myCubeMapIBL.IsNull())
  {
    SetImageBasedLighting(false);
    SetImageBasedLighting(true);
  }
}

void Graphic3d_CView::Activate()
{
  if (!IsActive())
  {
    myIsActive = true;

    NCollection_Map<occ::handle<Graphic3d_Structure>> aDisplayedStructs;
    myStructureManager->DisplayedStructures(aDisplayedStructs);
    for (NCollection_Map<occ::handle<Graphic3d_Structure>>::Iterator aStructIter(aDisplayedStructs);
         aStructIter.More();
         aStructIter.Next())
    {
      const occ::handle<Graphic3d_Structure>& aStruct = aStructIter.Key();
      if (IsDisplayed(aStruct))
      {
        continue;
      }

      const Graphic3d_TypeOfAnswer anAnswer = acceptDisplay(aStruct->Visual());
      if (anAnswer == Graphic3d_TOA_YES || anAnswer == Graphic3d_TOA_COMPUTE)
      {
        Display(aStruct);
      }
    }
  }

  Update();
}

void Graphic3d_CView::Deactivate()
{
  if (IsActive())
  {

    NCollection_Map<occ::handle<Graphic3d_Structure>> aDisplayedStructs;
    myStructureManager->DisplayedStructures(aDisplayedStructs);
    for (NCollection_Map<occ::handle<Graphic3d_Structure>>::Iterator aStructIter(aDisplayedStructs);
         aStructIter.More();
         aStructIter.Next())
    {
      const occ::handle<Graphic3d_Structure>& aStruct = aStructIter.Key();
      if (!IsDisplayed(aStruct))
      {
        continue;
      }

      const Graphic3d_TypeOfAnswer anAnswer = acceptDisplay(aStruct->Visual());
      if (anAnswer == Graphic3d_TOA_YES || anAnswer == Graphic3d_TOA_COMPUTE)
      {
        Erase(aStruct);
      }
    }

    Update();
    myIsActive = false;
  }
}

void Graphic3d_CView::Remove()
{
  if (IsRemoved())
  {
    return;
  }

  if (myParentView != nullptr)
  {
    myParentView->RemoveSubview(this);
    myParentView = nullptr;
  }
  {
    NCollection_Sequence<occ::handle<Graphic3d_CView>> aSubviews = mySubviews;
    mySubviews.Clear();
    for (const occ::handle<Graphic3d_CView>& aViewIter : aSubviews)
    {
      aViewIter->Remove();
    }
  }

  NCollection_Map<occ::handle<Graphic3d_Structure>> aDisplayedStructs(myStructsDisplayed);
  for (NCollection_Map<occ::handle<Graphic3d_Structure>>::Iterator aStructIter(aDisplayedStructs);
       aStructIter.More();
       aStructIter.Next())
  {
    Erase(aStructIter.Value());
  }

  myStructsToCompute.Clear();
  myStructsComputed.Clear();
  myStructsDisplayed.Clear();

  if (!myStructureManager.IsNull())
  {
    myStructureManager->UnIdentification(this);
  }

  myIsActive  = false;
  myIsRemoved = true;
}

void Graphic3d_CView::AddSubview(const occ::handle<Graphic3d_CView>& theView)
{
  mySubviews.Append(theView);
}

bool Graphic3d_CView::RemoveSubview(const Graphic3d_CView* theView)
{
  for (NCollection_Sequence<occ::handle<Graphic3d_CView>>::Iterator aViewIter(mySubviews);
       aViewIter.More();
       aViewIter.Next())
  {
    if (aViewIter.Value() == theView)
    {
      mySubviews.Remove(aViewIter);
      return true;
    }
  }
  return false;
}

void Graphic3d_CView::Resized()
{
  if (IsSubview())
  {
    occ::handle<Aspect_NeutralWindow> aWindow = occ::down_cast<Aspect_NeutralWindow>(Window());
    SubviewResized(aWindow);
  }
}

static int getSubViewOffset(double theOffset, int theWinSize)
{
  if (theOffset >= 1.0)
  {
    return int(theOffset);
  }
  else
  {
    return int(theOffset * theWinSize);
  }
}

void Graphic3d_CView::SubviewResized(const occ::handle<Aspect_NeutralWindow>& theWindow)
{
  if (!IsSubview() || theWindow.IsNull())
  {
    return;
  }

  const NCollection_Vec2<int> aWinSize(myParentView->Window()->Dimensions());
  NCollection_Vec2<int>       aViewSize(NCollection_Vec2<double>(aWinSize) * mySubviewSize);
  if (mySubviewSize.x() > 1.0)
  {
    aViewSize.x() = (int)mySubviewSize.x();
  }
  if (mySubviewSize.y() > 1.0)
  {
    aViewSize.y() = (int)mySubviewSize.y();
  }

  NCollection_Vec2<int> anOffset(getSubViewOffset(mySubviewOffset.x(), aWinSize.x()),
                                 getSubViewOffset(mySubviewOffset.y(), aWinSize.y()));
  mySubviewTopLeft = (aWinSize - aViewSize) / 2;
  if ((mySubviewCorner & Aspect_TOTP_LEFT) != 0)
  {
    mySubviewTopLeft.x() = anOffset.x();
  }
  else if ((mySubviewCorner & Aspect_TOTP_RIGHT) != 0)
  {
    mySubviewTopLeft.x() = std::max(aWinSize.x() - anOffset.x() - aViewSize.x(), 0);
  }

  if ((mySubviewCorner & Aspect_TOTP_TOP) != 0)
  {
    mySubviewTopLeft.y() = anOffset.y();
  }
  else if ((mySubviewCorner & Aspect_TOTP_BOTTOM) != 0)
  {
    mySubviewTopLeft.y() = std::max(aWinSize.y() - anOffset.y() - aViewSize.y(), 0);
  }

  mySubviewTopLeft += mySubviewMargins;
  aViewSize -= mySubviewMargins * 2;

  const int aRight = std::min(mySubviewTopLeft.x() + aViewSize.x(), aWinSize.x());
  aViewSize.x()    = aRight - mySubviewTopLeft.x();

  const int aBot = std::min(mySubviewTopLeft.y() + aViewSize.y(), aWinSize.y());
  aViewSize.y()  = aBot - mySubviewTopLeft.y();

  theWindow->SetSize(aViewSize.x(), aViewSize.y());
}

void Graphic3d_CView::SetComputedMode(const bool theMode)
{
  if ((theMode && myIsInComputedMode) || (!theMode && !myIsInComputedMode))
  {
    return;
  }

  myIsInComputedMode = theMode;
  if (!myIsInComputedMode)
  {
    for (NCollection_Map<occ::handle<Graphic3d_Structure>>::Iterator aStructIter(
           myStructsDisplayed);
         aStructIter.More();
         aStructIter.Next())
    {
      const occ::handle<Graphic3d_Structure>& aStruct  = aStructIter.Key();
      const Graphic3d_TypeOfAnswer            anAnswer = acceptDisplay(aStruct->Visual());
      if (anAnswer != Graphic3d_TOA_COMPUTE)
      {
        continue;
      }

      const int anIndex = IsComputed(aStruct);
      if (anIndex != 0)
      {
        const occ::handle<Graphic3d_Structure>& aStructComp = myStructsComputed.Value(anIndex);
        eraseStructure(aStructComp->CStructure());
        displayStructure(aStruct->CStructure(), aStruct->DisplayPriority());
        Update(aStruct->GetZLayer());
      }
    }
    return;
  }

  for (NCollection_Map<occ::handle<Graphic3d_Structure>>::Iterator aDispStructIter(
         myStructsDisplayed);
       aDispStructIter.More();
       aDispStructIter.Next())
  {
    const occ::handle<Graphic3d_Structure>& aStruct  = aDispStructIter.Key();
    const Graphic3d_TypeOfAnswer            anAnswer = acceptDisplay(aStruct->Visual());
    if (anAnswer != Graphic3d_TOA_COMPUTE)
    {
      continue;
    }

    const int anIndex = IsComputed(aStruct);
    if (anIndex != 0)
    {
      eraseStructure(aStruct->CStructure());
      displayStructure(myStructsComputed.Value(anIndex)->CStructure(), aStruct->DisplayPriority());

      Display(aStruct);
      if (aStruct->IsHighlighted())
      {
        const occ::handle<Graphic3d_Structure>& aCompStruct = myStructsComputed.Value(anIndex);
        if (!aCompStruct->IsHighlighted())
        {
          aCompStruct->Highlight(aStruct->HighlightStyle(), false);
        }
      }
    }
    else
    {
      occ::handle<Graphic3d_Structure> aCompStruct;
      aStruct->computeHLR(myCamera, aCompStruct);
      if (aCompStruct.IsNull())
      {
        continue;
      }
      aCompStruct->SetHLRValidation(true);

      const bool toComputeWireframe = myVisualization == Graphic3d_TOV_WIREFRAME
                                      && aStruct->ComputeVisual() != Graphic3d_TOS_SHADING;
      const bool toComputeShading = myVisualization == Graphic3d_TOV_SHADING
                                    && aStruct->ComputeVisual() != Graphic3d_TOS_WIREFRAME;
      if (toComputeWireframe)
        aCompStruct->SetVisual(Graphic3d_TOS_WIREFRAME);
      if (toComputeShading)
        aCompStruct->SetVisual(Graphic3d_TOS_SHADING);

      if (aStruct->IsHighlighted())
      {
        aCompStruct->Highlight(aStruct->HighlightStyle(), false);
      }

      bool      hasResult    = false;
      const int aNbToCompute = myStructsToCompute.Length();
      const int aStructId    = aStruct->Identification();
      for (int aToCompStructIter = 1; aToCompStructIter <= aNbToCompute; ++aToCompStructIter)
      {
        if (myStructsToCompute.Value(aToCompStructIter)->Identification() == aStructId)
        {
          hasResult                                        = true;
          myStructsComputed.ChangeValue(aToCompStructIter) = aCompStruct;
          break;
        }
      }

      if (!hasResult)
      {
        myStructsToCompute.Append(aStruct);
        myStructsComputed.Append(aCompStruct);
      }

      aCompStruct->CalculateBoundBox();
      eraseStructure(aStruct->CStructure());
      displayStructure(aCompStruct->CStructure(), aStruct->DisplayPriority());
    }
  }
  Update();
}

void Graphic3d_CView::ReCompute(const occ::handle<Graphic3d_Structure>& theStruct)
{
  theStruct->CalculateBoundBox();
  if (!theStruct->IsMutable() && !theStruct->CStructure()->IsForHighlight
      && !theStruct->CStructure()->IsInfinite)
  {
    const Graphic3d_ZLayerId aLayerId = theStruct->GetZLayer();
    InvalidateBVHData(aLayerId);
  }

  if (!ComputedMode() || !IsActive() || !theStruct->IsDisplayed())
  {
    return;
  }

  theStruct->RecomputeTransformation(myCamera);

  const Graphic3d_TypeOfAnswer anAnswer = acceptDisplay(theStruct->Visual());
  if (anAnswer != Graphic3d_TOA_COMPUTE)
  {
    return;
  }

  const int anIndex = IsComputed(theStruct);
  if (anIndex == 0)
  {
    return;
  }

  occ::handle<Graphic3d_Structure> aCompStructOld = myStructsComputed.ChangeValue(anIndex);
  occ::handle<Graphic3d_Structure> aCompStruct    = aCompStructOld;
  aCompStruct->SetTransformation(occ::handle<TopLoc_Datum3D>());
  theStruct->computeHLR(myCamera, aCompStruct);
  if (aCompStruct.IsNull())
  {
    return;
  }

  aCompStruct->SetHLRValidation(true);
  aCompStruct->CalculateBoundBox();

  const bool toComputeWireframe = myVisualization == Graphic3d_TOV_WIREFRAME
                                  && theStruct->ComputeVisual() != Graphic3d_TOS_SHADING;
  const bool toComputeShading = myVisualization == Graphic3d_TOV_SHADING
                                && theStruct->ComputeVisual() != Graphic3d_TOS_WIREFRAME;
  if (toComputeWireframe)
  {
    aCompStruct->SetVisual(Graphic3d_TOS_WIREFRAME);
  }
  else if (toComputeShading)
  {
    aCompStruct->SetVisual(Graphic3d_TOS_SHADING);
  }

  if (theStruct->IsHighlighted())
  {
    aCompStruct->Highlight(theStruct->HighlightStyle(), false);
  }

  eraseStructure(aCompStructOld->CStructure());
  displayStructure(aCompStruct->CStructure(), theStruct->DisplayPriority());

  myStructsToCompute.Append(theStruct);
  myStructsComputed.Append(aCompStruct);

  myStructsToCompute.Remove(anIndex);
  myStructsComputed.Remove(anIndex);
}

void Graphic3d_CView::Update(const Graphic3d_ZLayerId theLayerId)
{
  InvalidateZLayerBoundingBox(theLayerId);
}

void Graphic3d_CView::InvalidateZLayerBoundingBox(const Graphic3d_ZLayerId theLayerId)
{
  if (occ::handle<Graphic3d_Layer> aLayer = Layer(theLayerId))
  {
    aLayer->InvalidateBoundingBox();
    return;
  }

  for (NCollection_List<occ::handle<Graphic3d_Layer>>::Iterator aLayerIter(Layers());
       aLayerIter.More();
       aLayerIter.Next())
  {
    const occ::handle<Graphic3d_Layer>& aLayer = aLayerIter.Value();
    if (aLayer->NbOfTransformPersistenceObjects() > 0)
    {
      aLayer->InvalidateBoundingBox();
    }
  }
}

void Graphic3d_CView::DisplayedStructures(
  NCollection_Map<occ::handle<Graphic3d_Structure>>& theStructures) const
{
  for (NCollection_Map<occ::handle<Graphic3d_Structure>>::Iterator aStructIter(myStructsDisplayed);
       aStructIter.More();
       aStructIter.Next())
  {
    theStructures.Add(aStructIter.Key());
  }
}

Bnd_Box Graphic3d_CView::MinMaxValues(const bool theToIncludeAuxiliary) const
{
  if (!IsDefined())
  {
    return Bnd_Box();
  }

  const occ::handle<Graphic3d_Camera>& aCamera = Camera();
  NCollection_Vec2<int>                aWinSize;
  Window()->Size(aWinSize.x(), aWinSize.y());

  Bnd_Box aResult;
  for (NCollection_List<occ::handle<Graphic3d_Layer>>::Iterator aLayerIter(Layers());
       aLayerIter.More();
       aLayerIter.Next())
  {
    const occ::handle<Graphic3d_Layer>& aLayer = aLayerIter.Value();
    Bnd_Box                             aBox   = aLayer->BoundingBox(Identification(),
                                       aCamera,
                                       aWinSize.x(),
                                       aWinSize.y(),
                                       theToIncludeAuxiliary);
    aResult.Add(aBox);
  }
  return aResult;
}

double Graphic3d_CView::ConsiderZoomPersistenceObjects()
{
  if (!IsDefined())
  {
    return 1.0;
  }

  const occ::handle<Graphic3d_Camera>& aCamera = Camera();
  NCollection_Vec2<int>                aWinSize;
  Window()->Size(aWinSize.x(), aWinSize.y());

  double aMaxCoef = 1.0;
  for (NCollection_List<occ::handle<Graphic3d_Layer>>::Iterator aLayerIter(Layers());
       aLayerIter.More();
       aLayerIter.Next())
  {
    const occ::handle<Graphic3d_Layer>& aLayer = aLayerIter.Value();
    aMaxCoef                                   = std::max(aMaxCoef,
                        aLayer->considerZoomPersistenceObjects(Identification(),
                                                               aCamera,
                                                               aWinSize.x(),
                                                               aWinSize.y()));
  }

  return aMaxCoef;
}

Bnd_Box Graphic3d_CView::MinMaxValues(
  const NCollection_Map<occ::handle<Graphic3d_Structure>>& theSet,
  const bool                                               theToIgnoreInfiniteFlag) const
{
  Bnd_Box   aResult;
  const int aViewId = Identification();

  occ::handle<Graphic3d_Camera> aCamera    = Camera();
  int                           aWinWidth  = 0;
  int                           aWinHeight = 0;
  if (IsDefined())
  {
    Window()->Size(aWinWidth, aWinHeight);
  }

  for (NCollection_Map<occ::handle<Graphic3d_Structure>>::Iterator aStructIter(theSet);
       aStructIter.More();
       aStructIter.Next())
  {
    const occ::handle<Graphic3d_Structure>& aStructure = aStructIter.Key();
    if (aStructure->IsEmpty() || !aStructure->CStructure()->IsVisible(aViewId))
    {
      continue;
    }

    if (!aStructure->TransformPersistence().IsNull())
    {

      if (!theToIgnoreInfiniteFlag || aStructure->TransformPersistence()->IsTrihedronOr2d())
      {
        continue;
      }
    }

    Bnd_Box aBox = aStructure->MinMaxValues(theToIgnoreInfiniteFlag);

    if (aBox.IsWhole() || aBox.IsVoid())
    {
      continue;
    }

    if (!aStructure->TransformPersistence().IsNull())
    {
      const NCollection_Mat4<double>& aProjectionMat = aCamera->ProjectionMatrix();
      const NCollection_Mat4<double>& aWorldViewMat  = aCamera->OrientationMatrix();
      aStructure->TransformPersistence()
        ->Apply(aCamera, aProjectionMat, aWorldViewMat, aWinWidth, aWinHeight, aBox);
    }

    if (std::abs(aBox.CornerMax().X()) >= ShortRealLast()
        || std::abs(aBox.CornerMax().Y()) >= ShortRealLast()
        || std::abs(aBox.CornerMax().Z()) >= ShortRealLast()
        || std::abs(aBox.CornerMin().X()) >= ShortRealLast()
        || std::abs(aBox.CornerMin().Y()) >= ShortRealLast()
        || std::abs(aBox.CornerMin().Z()) >= ShortRealLast())
    {
      continue;
    }

    aResult.Add(aBox);
  }
  return aResult;
}

Graphic3d_TypeOfAnswer Graphic3d_CView::acceptDisplay(
  const Graphic3d_TypeOfStructure theStructType) const
{
  switch (theStructType)
  {
    case Graphic3d_TOS_ALL:
    {
      return Graphic3d_TOA_YES;
    }
    case Graphic3d_TOS_SHADING:
    {
      return myVisualization == Graphic3d_TOV_SHADING ? Graphic3d_TOA_YES : Graphic3d_TOA_NO;
    }
    case Graphic3d_TOS_WIREFRAME:
    {
      return myVisualization == Graphic3d_TOV_WIREFRAME ? Graphic3d_TOA_YES : Graphic3d_TOA_NO;
    }
    case Graphic3d_TOS_COMPUTED:
    {
      return (myVisualization == Graphic3d_TOV_SHADING
              || myVisualization == Graphic3d_TOV_WIREFRAME)
               ? Graphic3d_TOA_COMPUTE
               : Graphic3d_TOA_NO;
    }
  }
  return Graphic3d_TOA_NO;
}

void Graphic3d_CView::Compute()
{

  for (NCollection_Sequence<occ::handle<Graphic3d_Structure>>::Iterator aStructIter(
         myStructsComputed);
       aStructIter.More();
       aStructIter.Next())
  {
    aStructIter.Value()->SetHLRValidation(false);
  }

  for (NCollection_Map<occ::handle<Graphic3d_Structure>>::Iterator aStructIter(myStructsDisplayed);
       aStructIter.More();
       aStructIter.Next())
  {
    aStructIter.Value()->RecomputeTransformation(myCamera);
  }

  if (!ComputedMode())
  {
    return;
  }

  NCollection_Sequence<occ::handle<Graphic3d_Structure>> aStructsSeq;
  for (NCollection_Map<occ::handle<Graphic3d_Structure>>::Iterator aStructIter(myStructsDisplayed);
       aStructIter.More();
       aStructIter.Next())
  {
    const Graphic3d_TypeOfAnswer anAnswer = acceptDisplay(aStructIter.Key()->Visual());
    if (anAnswer == Graphic3d_TOA_COMPUTE)
    {

      aStructsSeq.Append(aStructIter.Key());
    }
  }

  for (NCollection_Sequence<occ::handle<Graphic3d_Structure>>::Iterator aStructIter(aStructsSeq);
       aStructIter.More();
       aStructIter.Next())
  {
    Display(aStructIter.ChangeValue());
  }
}

void Graphic3d_CView::Clear(Graphic3d_Structure* theStructure, const bool theWithDestruction)
{
  const int anIndex = IsComputed(theStructure);
  if (anIndex != 0)
  {
    const occ::handle<Graphic3d_Structure>& aCompStruct = myStructsComputed.Value(anIndex);
    aCompStruct->GraphicClear(theWithDestruction);
    aCompStruct->SetHLRValidation(false);
  }
}

void Graphic3d_CView::Connect(const Graphic3d_Structure* theMother,
                              const Graphic3d_Structure* theDaughter)
{
  int anIndexM = IsComputed(theMother);
  int anIndexD = IsComputed(theDaughter);
  if (anIndexM != 0 && anIndexD != 0)
  {
    const occ::handle<Graphic3d_Structure>& aStructM = myStructsComputed.Value(anIndexM);
    const occ::handle<Graphic3d_Structure>& aStructD = myStructsComputed.Value(anIndexD);
    aStructM->GraphicConnect(aStructD);
  }
}

void Graphic3d_CView::Disconnect(const Graphic3d_Structure* theMother,
                                 const Graphic3d_Structure* theDaughter)
{
  int anIndexM = IsComputed(theMother);
  int anIndexD = IsComputed(theDaughter);
  if (anIndexM != 0 && anIndexD != 0)
  {
    const occ::handle<Graphic3d_Structure>& aStructM = myStructsComputed.Value(anIndexM);
    const occ::handle<Graphic3d_Structure>& aStructD = myStructsComputed.Value(anIndexD);
    aStructM->GraphicDisconnect(aStructD);
  }
}

void Graphic3d_CView::Display(const occ::handle<Graphic3d_Structure>& theStructure)
{
  if (!IsActive())
  {
    return;
  }

  int anIndex = IsComputed(theStructure);
  if (anIndex != 0 && theStructure->Visual() != Graphic3d_TOS_COMPUTED)
  {
    myStructsToCompute.Remove(anIndex);
    myStructsComputed.Remove(anIndex);
    anIndex = 0;
  }

  theStructure->RecomputeTransformation(myCamera);

  Graphic3d_TypeOfAnswer anAnswer = acceptDisplay(theStructure->Visual());
  if (anAnswer == Graphic3d_TOA_NO)
  {
    return;
  }

  if (!ComputedMode())
  {
    anAnswer = Graphic3d_TOA_YES;
  }

  if (anAnswer == Graphic3d_TOA_YES)
  {
    if (!myStructsDisplayed.Add(theStructure))
    {
      return;
    }

    theStructure->CalculateBoundBox();
    displayStructure(theStructure->CStructure(), theStructure->DisplayPriority());
    Update(theStructure->GetZLayer());
    return;
  }
  else if (anAnswer != Graphic3d_TOA_COMPUTE)
  {
    return;
  }

  if (anIndex != 0)
  {

    const occ::handle<Graphic3d_Structure>& anOldStruct = myStructsComputed.Value(anIndex);
    if (anOldStruct->HLRValidation())
    {

      if (!myStructsDisplayed.Add(theStructure))
      {
        return;
      }

      displayStructure(anOldStruct->CStructure(), theStructure->DisplayPriority());
      Update(anOldStruct->GetZLayer());
      return;
    }
    else
    {

      const int aNewIndex = HaveTheSameOwner(theStructure);
      if (aNewIndex != 0)
      {

        if (!myStructsDisplayed.Add(theStructure))
        {
          return;
        }

        const occ::handle<Graphic3d_Structure>& aNewStruct = myStructsComputed.Value(aNewIndex);
        myStructsComputed.SetValue(anIndex, aNewStruct);
        displayStructure(aNewStruct->CStructure(), theStructure->DisplayPriority());
        Update(aNewStruct->GetZLayer());
        return;
      }
      else
      {

        if (myStructsDisplayed.Contains(theStructure))
        {
          eraseStructure(anOldStruct->CStructure());
        }
      }
    }
  }

  occ::handle<Graphic3d_Structure> aStruct;
  if (anIndex != 0)
  {
    aStruct = myStructsComputed.Value(anIndex);
    aStruct->SetTransformation(occ::handle<TopLoc_Datum3D>());
  }
  theStructure->computeHLR(myCamera, aStruct);
  if (aStruct.IsNull())
  {
    return;
  }
  aStruct->SetHLRValidation(true);

  myStructsToCompute.Append(theStructure);
  myStructsComputed.Append(aStruct);

  if (anIndex != 0)
  {
    myStructsToCompute.Remove(anIndex);
    myStructsComputed.Remove(anIndex);
  }

  const bool toComputeWireframe = myVisualization == Graphic3d_TOV_WIREFRAME
                                  && theStructure->ComputeVisual() != Graphic3d_TOS_SHADING;
  const bool toComputeShading = myVisualization == Graphic3d_TOV_SHADING
                                && theStructure->ComputeVisual() != Graphic3d_TOS_WIREFRAME;
  if (!toComputeShading && !toComputeWireframe)
  {
    anAnswer = Graphic3d_TOA_NO;
  }
  else
  {
    aStruct->SetVisual(toComputeWireframe ? Graphic3d_TOS_WIREFRAME : Graphic3d_TOS_SHADING);
    anAnswer = acceptDisplay(aStruct->Visual());
  }

  if (theStructure->IsHighlighted())
  {
    aStruct->Highlight(theStructure->HighlightStyle(), false);
  }

  if (anAnswer == Graphic3d_TOA_NO)
  {
    return;
  }

  myStructsDisplayed.Add(theStructure);
  displayStructure(aStruct->CStructure(), theStructure->DisplayPriority());

  Update(aStruct->GetZLayer());
}

void Graphic3d_CView::Erase(const occ::handle<Graphic3d_Structure>& theStructure)
{
  if (!IsDisplayed(theStructure))
  {
    return;
  }

  const Graphic3d_TypeOfAnswer anAnswer =
    myIsInComputedMode ? acceptDisplay(theStructure->Visual()) : Graphic3d_TOA_YES;
  if (anAnswer != Graphic3d_TOA_COMPUTE)
  {
    eraseStructure(theStructure->CStructure());
  }

  const int anIndex = !myStructsToCompute.IsEmpty() ? IsComputed(theStructure) : 0;
  if (anIndex != 0)
  {
    if (anAnswer == Graphic3d_TOA_COMPUTE && myIsInComputedMode)
    {
      const occ::handle<Graphic3d_Structure>& aCompStruct = myStructsComputed.ChangeValue(anIndex);
      eraseStructure(aCompStruct->CStructure());
    }
    myStructsComputed.Remove(anIndex);
    myStructsToCompute.Remove(anIndex);
  }

  myStructsDisplayed.Remove(theStructure);
  Update(theStructure->GetZLayer());
}

void Graphic3d_CView::Highlight(const occ::handle<Graphic3d_Structure>& theStructure)
{
  const int anIndex = IsComputed(theStructure);
  if (anIndex != 0)
  {
    const occ::handle<Graphic3d_Structure>& aCompStruct = myStructsComputed.ChangeValue(anIndex);
    aCompStruct->Highlight(theStructure->HighlightStyle(), false);
  }
}

void Graphic3d_CView::SetTransform(const occ::handle<Graphic3d_Structure>& theStructure,
                                   const occ::handle<TopLoc_Datum3D>&      theTrsf)
{
  const int anIndex = IsComputed(theStructure);
  if (anIndex != 0)
  {

    if (!theTrsf.IsNull()
        && (theTrsf->Form() == gp_Translation || theTrsf->Form() == gp_Scale
            || theTrsf->Form() == gp_CompoundTrsf))
    {
      ReCompute(theStructure);
    }
    else
    {
      const occ::handle<Graphic3d_Structure>& aCompStruct = myStructsComputed.ChangeValue(anIndex);
      aCompStruct->GraphicTransform(theTrsf);
    }
  }

  theStructure->CalculateBoundBox();
  if (!theStructure->IsMutable() && !theStructure->CStructure()->IsForHighlight
      && !theStructure->CStructure()->IsInfinite)
  {
    const Graphic3d_ZLayerId aLayerId = theStructure->GetZLayer();
    InvalidateBVHData(aLayerId);
  }
}

void Graphic3d_CView::UnHighlight(const occ::handle<Graphic3d_Structure>& theStructure)
{
  int anIndex = IsComputed(theStructure);
  if (anIndex != 0)
  {
    const occ::handle<Graphic3d_Structure>& aCompStruct = myStructsComputed.ChangeValue(anIndex);
    aCompStruct->CStructure()->GraphicUnhighlight();
  }
}

bool Graphic3d_CView::IsComputed(const int                         theStructId,
                                 occ::handle<Graphic3d_Structure>& theComputedStruct) const
{
  theComputedStruct.Nullify();
  if (!ComputedMode())
    return false;

  const int aNbStructs = myStructsToCompute.Length();
  for (int aStructIter = 1; aStructIter <= aNbStructs; ++aStructIter)
  {
    if (myStructsToCompute.Value(aStructIter)->Identification() == theStructId)
    {
      theComputedStruct = myStructsComputed(aStructIter);
      return true;
    }
  }
  return false;
}

int Graphic3d_CView::IsComputed(const Graphic3d_Structure* theStructure) const
{
  const int aStructId    = theStructure->Identification();
  int       aStructIndex = 1;
  for (NCollection_Sequence<occ::handle<Graphic3d_Structure>>::Iterator aStructIter(
         myStructsToCompute);
       aStructIter.More();
       aStructIter.Next(), ++aStructIndex)
  {
    const occ::handle<Graphic3d_Structure>& aStruct = aStructIter.Value();
    if (aStruct->Identification() == aStructId)
    {
      return aStructIndex;
    }
  }
  return 0;
}

bool Graphic3d_CView::IsDisplayed(const occ::handle<Graphic3d_Structure>& theStructure) const
{
  return myStructsDisplayed.Contains(theStructure);
}

void Graphic3d_CView::ChangePriority(const occ::handle<Graphic3d_Structure>& theStructure,
                                     const Graphic3d_DisplayPriority,
                                     const Graphic3d_DisplayPriority theNewPriority)
{
  if (!IsActive() || !IsDisplayed(theStructure))
  {
    return;
  }

  if (!myIsInComputedMode)
  {
    changePriority(theStructure->CStructure(), theNewPriority);
    return;
  }

  const int                                anIndex = IsComputed(theStructure);
  const occ::handle<Graphic3d_CStructure>& aCStruct =
    anIndex != 0 ? myStructsComputed.Value(anIndex)->CStructure() : theStructure->CStructure();

  changePriority(aCStruct, theNewPriority);
}

void Graphic3d_CView::ChangeZLayer(const occ::handle<Graphic3d_Structure>& theStructure,
                                   const Graphic3d_ZLayerId                theLayerId)
{
  if (!IsActive() || !IsDisplayed(theStructure))
  {
    return;
  }

  if (!myIsInComputedMode)
  {
    changeZLayer(theStructure->CStructure(), theLayerId);
    return;
  }

  const int                         anIndex = IsComputed(theStructure);
  occ::handle<Graphic3d_CStructure> aCStruct =
    anIndex != 0 ? myStructsComputed.Value(anIndex)->CStructure() : theStructure->CStructure();

  changeZLayer(aCStruct, theLayerId);
}

int Graphic3d_CView::HaveTheSameOwner(const occ::handle<Graphic3d_Structure>& theStructure) const
{

  const int aNbToCompStructs = myStructsToCompute.Length();
  for (int aStructIter = 1; aStructIter <= aNbToCompStructs; ++aStructIter)
  {
    const occ::handle<Graphic3d_Structure>& aStructToComp = myStructsToCompute.Value(aStructIter);
    if (aStructToComp->Owner() == theStructure->Owner()
        && aStructToComp->Identification() != theStructure->Identification())
    {
      const occ::handle<Graphic3d_Structure>& aStructComp = myStructsComputed.Value(aStructIter);
      if (aStructComp->HLRValidation())
      {
        return aStructIter;
      }
    }
  }
  return 0;
}

void Graphic3d_CView::CopySettings(const occ::handle<Graphic3d_CView>& theOther)
{
  ChangeRenderingParams() = theOther->RenderingParams();
  SetBackground(theOther->Background());
  SetGradientBackground(theOther->GradientBackground());
  SetBackgroundImage(theOther->BackgroundImage());
  SetBackgroundImageStyle(theOther->BackgroundImageStyle());
  SetTextureEnv(theOther->TextureEnv());
  SetShadingModel(theOther->ShadingModel());
  SetBackfacingModel(theOther->BackfacingModel());
  SetCamera(new Graphic3d_Camera(theOther->Camera()));
  SetLights(theOther->Lights());
  SetClipPlanes(theOther->ClipPlanes());
}

void Graphic3d_CView::SetShadingModel(Graphic3d_TypeOfShadingModel theModel)
{
  if (theModel == Graphic3d_TypeOfShadingModel_DEFAULT)
  {
    throw Standard_ProgramError(
      "Graphic3d_CView::SetShadingModel() - attempt to set invalid Shading Model!");
  }

  myRenderParams.ShadingModel = theModel;
}

void Graphic3d_CView::SetUnitFactor(double theFactor)
{
  if (theFactor <= 0.0)
  {
    throw Standard_ProgramError("Graphic3d_CView::SetUnitFactor() - invalid unit factor");
  }
  myUnitFactor = theFactor;
  if (!myXRSession.IsNull())
  {
    myXRSession->SetUnitFactor(theFactor);
  }
}

bool Graphic3d_CView::IsActiveXR() const
{
  return !myXRSession.IsNull() && myXRSession->IsOpen();
}

bool Graphic3d_CView::InitXR()
{
  if (myXRSession.IsNull())
  {
    myXRSession = new Aspect_OpenVRSession();
    myXRSession->SetUnitFactor(myUnitFactor);
  }
  if (!myXRSession->IsOpen())
  {
    myXRSession->Open();
    if (myBackXRCamera.IsNull())
    {

      myBackXRCamera = new Graphic3d_Camera(myCamera);
    }
  }
  return myXRSession->IsOpen();
}

void Graphic3d_CView::ReleaseXR()
{
  if (!myXRSession.IsNull())
  {
    if (myXRSession->IsOpen() && !myBackXRCamera.IsNull())
    {

      myCamera->SetFOV2d(myBackXRCamera->FOV2d());
      myCamera->SetFOVy(myBackXRCamera->FOVy());
      myCamera->SetAspect(myBackXRCamera->Aspect());
      myCamera->SetIOD(myBackXRCamera->GetIODType(), myBackXRCamera->IOD());
      myCamera->SetZFocus(myBackXRCamera->ZFocusType(), myBackXRCamera->ZFocus());
      myCamera->ResetCustomProjection();
      myBackXRCamera.Nullify();
    }
    myXRSession->Close();
  }
}

void Graphic3d_CView::ProcessXRInput()
{
  if (myRenderParams.StereoMode == Graphic3d_StereoMode_OpenVR
      && myCamera->ProjectionType() == Graphic3d_Camera::Projection_Stereo)
  {
    InitXR();
  }
  else
  {
    ReleaseXR();
  }

  if (!IsActiveXR())
  {
    myBaseXRCamera.Nullify();
    myPosedXRCamera.Nullify();
    return;
  }

  myXRSession->ProcessEvents();
  Invalidate();

  myCamera->SetFOV2d(myRenderParams.HmdFov2d);
  myCamera->SetAspect(myXRSession->Aspect());
  myCamera->SetFOVy(myXRSession->FieldOfView());
  myCamera->SetIOD(Graphic3d_Camera::IODType_Absolute, myXRSession->IOD());
  myCamera->SetZFocus(Graphic3d_Camera::FocusType_Absolute, 1.0 * myUnitFactor);

  if (myXRSession->HasProjectionFrustums())
  {

    myCamera->SetCustomStereoFrustums(myXRSession->ProjectionFrustum(Aspect_Eye_Left),
                                      myXRSession->ProjectionFrustum(Aspect_Eye_Right));
  }
  else
  {
    const NCollection_Mat4<double> aPoseL = myXRSession->HeadToEyeTransform(Aspect_Eye_Left);
    const NCollection_Mat4<double> aPoseR = myXRSession->HeadToEyeTransform(Aspect_Eye_Right);
    const NCollection_Mat4<double> aProjL =
      myXRSession->ProjectionMatrix(Aspect_Eye_Left, myCamera->ZNear(), myCamera->ZFar());
    const NCollection_Mat4<double> aProjR =
      myXRSession->ProjectionMatrix(Aspect_Eye_Right, myCamera->ZNear(), myCamera->ZFar());
    myCamera->SetCustomStereoProjection(aProjL, aPoseL, aProjR, aPoseR);
  }
  myBaseXRCamera = myCamera;
  if (myPosedXRCamera.IsNull())
  {
    myPosedXRCamera = new Graphic3d_Camera();
  }
  SynchronizeXRBaseToPosedCamera();
}

void Graphic3d_CView::SynchronizeXRBaseToPosedCamera()
{
  if (!myPosedXRCamera.IsNull())
  {
    ComputeXRPosedCameraFromBase(*myPosedXRCamera, myXRSession->HeadPose());
  }
}

void Graphic3d_CView::ComputeXRPosedCameraFromBase(Graphic3d_Camera& theCam,
                                                   const gp_Trsf&    theXRTrsf) const
{
  theCam.Copy(myBaseXRCamera);

  const gp_Ax3 anAxVr(gp::Origin(), gp::DZ(), gp::DX());
  const gp_Ax3 aCameraCS(gp::Origin(), -myBaseXRCamera->Direction(), -myBaseXRCamera->SideRight());
  gp_Trsf      aTrsfCS;
  aTrsfCS.SetTransformation(aCameraCS, anAxVr);
  const gp_Trsf aTrsfToCamera = aTrsfCS * theXRTrsf * aTrsfCS.Inverted();
  gp_Trsf       aTrsfToEye;
  aTrsfToEye.SetTranslation(myBaseXRCamera->Eye().XYZ());

  const gp_Trsf aTrsf    = aTrsfToEye * aTrsfToCamera;
  const gp_Dir  anUpNew  = myBaseXRCamera->Up().Transformed(aTrsf);
  const gp_Dir  aDirNew  = myBaseXRCamera->Direction().Transformed(aTrsf);
  const gp_Pnt  anEyeNew = gp::Origin().Translated(aTrsf.TranslationPart());
  theCam.SetUp(anUpNew);
  theCam.SetDirectionFromEye(aDirNew);
  theCam.MoveEyeTo(anEyeNew);
}

void Graphic3d_CView::SynchronizeXRPosedToBaseCamera()
{
  if (myPosedXRCameraCopy.IsNull() || myPosedXRCamera.IsNull() || myBaseXRCamera.IsNull()
      || myCamera != myPosedXRCamera)
  {
    return;
  }

  if (myPosedXRCameraCopy->Eye().IsEqual(myPosedXRCamera->Eye(), gp::Resolution())
      && (myPosedXRCameraCopy->Distance() - myPosedXRCamera->Distance()) <= gp::Resolution()
      && myPosedXRCameraCopy->Direction().IsEqual(myPosedXRCamera->Direction(), gp::Resolution())
      && myPosedXRCameraCopy->Up().IsEqual(myPosedXRCamera->Up(), gp::Resolution()))
  {

    return;
  }

  ComputeXRBaseCameraFromPosed(myPosedXRCamera, myXRSession->HeadPose());
  myPosedXRCameraCopy->Copy(myPosedXRCamera);
}

void Graphic3d_CView::ComputeXRBaseCameraFromPosed(const Graphic3d_Camera& theCamPosed,
                                                   const gp_Trsf&          thePoseTrsf)
{
  const gp_Ax3 anAxVr(gp::Origin(), gp::DZ(), gp::DX());
  const gp_Ax3 aCameraCS(gp::Origin(), -myBaseXRCamera->Direction(), -myBaseXRCamera->SideRight());
  gp_Trsf      aTrsfCS;
  aTrsfCS.SetTransformation(aCameraCS, anAxVr);
  const gp_Trsf aTrsfToCamera  = aTrsfCS * thePoseTrsf * aTrsfCS.Inverted();
  const gp_Trsf aTrsfCamToHead = aTrsfToCamera.Inverted();
  const gp_Dir  anUpNew        = theCamPosed.Up().Transformed(aTrsfCamToHead);
  const gp_Dir  aDirNew        = theCamPosed.Direction().Transformed(aTrsfCamToHead);
  const gp_Pnt  anEyeNew = theCamPosed.Eye().Translated(aTrsfToCamera.TranslationPart().Reversed());
  myBaseXRCamera->SetUp(anUpNew);
  myBaseXRCamera->SetDirectionFromEye(aDirNew);
  myBaseXRCamera->MoveEyeTo(anEyeNew);
}

void Graphic3d_CView::TurnViewXRCamera(const gp_Trsf& theTrsfTurn)
{

  const occ::handle<Graphic3d_Camera>& aCamBase = myBaseXRCamera;
  gp_Trsf                              aHeadTrsfLocal;
  aHeadTrsfLocal.SetTranslationPart(myXRSession->HeadPose().TranslationPart());
  const gp_Pnt anEyeAnchor = PoseXRToWorld(aHeadTrsfLocal).TranslationPart();

  aCamBase->SetDirectionFromEye(aCamBase->Direction().Transformed(theTrsfTurn));

  const gp_Ax3 anAxVr(gp::Origin(), gp::DZ(), gp::DX());
  const gp_Ax3 aCameraCS(gp::Origin(), -aCamBase->Direction(), -aCamBase->SideRight());
  gp_Trsf      aTrsfCS;
  aTrsfCS.SetTransformation(aCameraCS, anAxVr);
  const gp_Trsf aTrsfToCamera = aTrsfCS * aHeadTrsfLocal * aTrsfCS.Inverted();
  const gp_Pnt  anEyeNew      = anEyeAnchor.Translated(aTrsfToCamera.TranslationPart().Reversed());
  aCamBase->MoveEyeTo(anEyeNew);

  SynchronizeXRBaseToPosedCamera();
}

void Graphic3d_CView::SetupXRPosedCamera()
{
  if (!myPosedXRCamera.IsNull())
  {
    myCamera = myPosedXRCamera;
    if (myPosedXRCameraCopy.IsNull())
    {
      myPosedXRCameraCopy = new Graphic3d_Camera();
    }
    myPosedXRCameraCopy->Copy(myPosedXRCamera);
  }
}

void Graphic3d_CView::UnsetXRPosedCamera()
{
  if (myCamera == myPosedXRCamera && !myBaseXRCamera.IsNull())
  {
    SynchronizeXRPosedToBaseCamera();
    myCamera = myBaseXRCamera;
  }
}

void Graphic3d_CView::DiagnosticInformation(
  NCollection_IndexedDataMap<TCollection_AsciiString, TCollection_AsciiString>& theDict,
  Graphic3d_DiagnosticInfo                                                      theFlags) const
{
  if ((theFlags & Graphic3d_DiagnosticInfo_Device) != 0 && !myXRSession.IsNull())
  {
    TCollection_AsciiString aVendor  = myXRSession->GetString(Aspect_XRSession::InfoString_Vendor);
    TCollection_AsciiString aDevice  = myXRSession->GetString(Aspect_XRSession::InfoString_Device);
    TCollection_AsciiString aTracker = myXRSession->GetString(Aspect_XRSession::InfoString_Tracker);
    TCollection_AsciiString aSerial =
      myXRSession->GetString(Aspect_XRSession::InfoString_SerialNumber);
    TCollection_AsciiString aDisplay =
      TCollection_AsciiString() + myXRSession->RecommendedViewport().x() + "x"
      + myXRSession->RecommendedViewport().y() + "@"
      + (int)std::round(myXRSession->DisplayFrequency())
      + " [FOVy: " + (int)std::round(myXRSession->FieldOfView()) + "]";

    theDict.ChangeFromIndex(theDict.Add("VRvendor", aVendor))   = aVendor;
    theDict.ChangeFromIndex(theDict.Add("VRdevice", aDevice))   = aDevice;
    theDict.ChangeFromIndex(theDict.Add("VRtracker", aTracker)) = aTracker;
    theDict.ChangeFromIndex(theDict.Add("VRdisplay", aDisplay)) = aDisplay;
    theDict.ChangeFromIndex(theDict.Add("VRserial", aSerial))   = aSerial;
  }
}

void Graphic3d_CView::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)

  OCCT_DUMP_BASE_CLASS(theOStream, theDepth, Graphic3d_DataStructureManager);

  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myId)
  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, &myRenderParams)
  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, &myBgColor)
  OCCT_DUMP_FIELD_VALUE_POINTER(theOStream, myStructureManager)
  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, myCamera.get())

  for (NCollection_Sequence<occ::handle<Graphic3d_Structure>>::Iterator anIter(myStructsToCompute);
       anIter.More();
       anIter.Next())
  {
    const occ::handle<Graphic3d_Structure>& aStructToCompute = anIter.Value();
    OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, aStructToCompute.get())
  }

  for (NCollection_Sequence<occ::handle<Graphic3d_Structure>>::Iterator anIter(myStructsComputed);
       anIter.More();
       anIter.Next())
  {
    const occ::handle<Graphic3d_Structure>& aStructComputed = anIter.Value();
    OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, aStructComputed.get())
  }

  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myIsInComputedMode)
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myIsActive)
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myIsRemoved)

  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myVisualization)

  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, myBackXRCamera.get())
  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, myBaseXRCamera.get())
  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, myPosedXRCamera.get())
  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, myPosedXRCameraCopy.get())

  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myUnitFactor)
}
