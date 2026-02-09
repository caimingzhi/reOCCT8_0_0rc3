#include <IVtkOCC_ViewerSelector.hpp>

#include <Select3D_SensitiveBox.hpp>
#include <gp_Pnt2d.hpp>
#include <NCollection_Array1.hpp>
#include <Graphic3d_Camera.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IVtkOCC_ViewerSelector, SelectMgr_ViewerSelector)

IVtkOCC_ViewerSelector::IVtkOCC_ViewerSelector()
    : myPixTol(2),
      myToUpdateTol(true)
{
}

IVtkOCC_ViewerSelector::~IVtkOCC_ViewerSelector() = default;

occ::handle<Graphic3d_Camera> IVtkOCC_ViewerSelector::ConvertVtkToOccCamera(
  const IVtk_IView::Handle& theView)
{
  occ::handle<Graphic3d_Camera> aCamera = new Graphic3d_Camera();
  aCamera->SetZeroToOneDepth(true);
  bool isOrthographic = !theView->IsPerspective();
  aCamera->SetProjectionType(isOrthographic ? Graphic3d_Camera::Projection_Orthographic
                                            : Graphic3d_Camera::Projection_Perspective);
  if (isOrthographic)
  {
    aCamera->SetScale(2 * theView->GetParallelScale());
  }
  else
  {
    aCamera->SetFOVy(theView->GetViewAngle());
  }
  double aZNear = 0.0, aZFar = 0.0;
  theView->GetClippingRange(aZNear, aZFar);
  aCamera->SetZRange(aZNear, aZFar);
  aCamera->SetAspect(theView->GetAspectRatio());
  gp_XYZ anAxialScale;
  theView->GetScale(anAxialScale.ChangeCoord(1),
                    anAxialScale.ChangeCoord(2),
                    anAxialScale.ChangeCoord(3));
  aCamera->SetAxialScale(anAxialScale);

  gp_XYZ anUp, aDir, anEyePos;
  theView->GetViewUp(anUp.ChangeCoord(1), anUp.ChangeCoord(2), anUp.ChangeCoord(3));
  theView->GetDirectionOfProjection(aDir.ChangeCoord(1), aDir.ChangeCoord(2), aDir.ChangeCoord(3));
  theView->GetEyePosition(anEyePos.ChangeCoord(1),
                          anEyePos.ChangeCoord(2),
                          anEyePos.ChangeCoord(3));

  aCamera->SetDistance(theView->GetDistance());
  aCamera->SetUp(anUp);
  aCamera->SetDirectionFromEye(aDir.Reversed());
  aCamera->MoveEyeTo(anEyePos);

  return aCamera;
}

void IVtkOCC_ViewerSelector::Pick(const int                 theXPix,
                                  const int                 theYPix,
                                  const IVtk_IView::Handle& theView)
{
  gp_Pnt2d aMousePos(static_cast<double>(theXPix), static_cast<double>(theYPix));
  mySelectingVolumeMgr.InitPointSelectingVolume(aMousePos);

  if (myToUpdateTol)
  {

    mySelectingVolumeMgr.SetPixelTolerance(myPixTol);

    myToUpdateTol = false;
  }

  mySelectingVolumeMgr.SetCamera(ConvertVtkToOccCamera(theView));

  int aWidth = 0, aHeight = 0;
  theView->GetWindowSize(aWidth, aHeight);
  mySelectingVolumeMgr.SetWindowSize(aWidth, aHeight);
  double aX = RealLast(), aY = RealLast();
  double aVpWidth = RealLast(), aVpHeight = RealLast();
  theView->GetViewport(aX, aY, aVpWidth, aVpHeight);
  mySelectingVolumeMgr.SetViewport(aX, aY, aVpWidth, aVpHeight);

  mySelectingVolumeMgr.BuildSelectingVolume();

  TraverseSensitives(-1);
}

void IVtkOCC_ViewerSelector::Pick(const int                 theXMin,
                                  const int                 theYMin,
                                  const int                 theXMax,
                                  const int                 theYMax,
                                  const IVtk_IView::Handle& theView)
{
  gp_Pnt2d aMinMousePos(static_cast<double>(theXMin), static_cast<double>(theYMin));
  gp_Pnt2d aMaxMousePos(static_cast<double>(theXMax), static_cast<double>(theYMax));
  mySelectingVolumeMgr.InitBoxSelectingVolume(aMinMousePos, aMaxMousePos);

  if (myToUpdateTol)
  {

    mySelectingVolumeMgr.SetPixelTolerance(myPixTol);

    myToUpdateTol = false;
  }

  int    aWidth = 0, aHeight = 0;
  double aX = RealLast(), aY = RealLast();
  double aVpWidth = RealLast(), aVpHeight = RealLast();

  mySelectingVolumeMgr.SetCamera(ConvertVtkToOccCamera(theView));

  theView->GetWindowSize(aWidth, aHeight);
  mySelectingVolumeMgr.SetWindowSize(aWidth, aHeight);

  theView->GetViewport(aX, aY, aVpWidth, aVpHeight);
  mySelectingVolumeMgr.SetViewport(aX, aY, aVpWidth, aVpHeight);

  mySelectingVolumeMgr.BuildSelectingVolume();

  TraverseSensitives(-1);
}

void IVtkOCC_ViewerSelector::Pick(double**                  thePoly,
                                  const int                 theNbPoints,
                                  const IVtk_IView::Handle& theView)
{

  NCollection_Array1<gp_Pnt2d> aPolyline(1, theNbPoints);
  for (int anIt = 0; anIt < theNbPoints; anIt++)
  {
    gp_XY aDispPnt = thePoly[anIt][2] != 0 ? gp_XY(thePoly[anIt][0] / thePoly[anIt][2],
                                                   thePoly[anIt][1] / thePoly[anIt][2])
                                           : gp_XY(thePoly[anIt][0], thePoly[anIt][1]);
    aPolyline.SetValue(anIt + 1, aDispPnt);
  }
  mySelectingVolumeMgr.InitPolylineSelectingVolume(aPolyline);

  if (myToUpdateTol)
  {

    mySelectingVolumeMgr.SetPixelTolerance(myPixTol);

    myToUpdateTol = false;
  }

  int    aWidth = 0, aHeight = 0;
  double aX = RealLast(), aY = RealLast();
  double aVpWidth = RealLast(), aVpHeight = RealLast();

  mySelectingVolumeMgr.SetCamera(ConvertVtkToOccCamera(theView));

  theView->GetWindowSize(aWidth, aHeight);
  mySelectingVolumeMgr.SetWindowSize(aWidth, aHeight);

  theView->GetViewport(aX, aY, aVpWidth, aVpHeight);
  mySelectingVolumeMgr.SetViewport(aX, aY, aVpWidth, aVpHeight);

  mySelectingVolumeMgr.BuildSelectingVolume();

  TraverseSensitives(-1);
}

void IVtkOCC_ViewerSelector::Activate(const occ::handle<SelectMgr_Selection>& theSelection)
{
  for (NCollection_Vector<occ::handle<SelectMgr_SensitiveEntity>>::Iterator aSelEntIter(
         theSelection->Entities());
       aSelEntIter.More();
       aSelEntIter.Next())
  {
    aSelEntIter.Value()->SetActiveForSelection();
  }

  if (theSelection->GetSelectionState() != SelectMgr_SOS_Activated)
  {
    theSelection->SetSelectionState(SelectMgr_SOS_Activated);
    myTolerances.Add(theSelection->Sensitivity());
  }
}

void IVtkOCC_ViewerSelector::Deactivate(const occ::handle<SelectMgr_Selection>& theSelection)
{
  for (NCollection_Vector<occ::handle<SelectMgr_SensitiveEntity>>::Iterator aSelEntIter(
         theSelection->Entities());
       aSelEntIter.More();
       aSelEntIter.Next())
  {
    aSelEntIter.Value()->ResetSelectionActiveStatus();
  }

  if (theSelection->GetSelectionState() == SelectMgr_SOS_Activated)
  {
    theSelection->SetSelectionState(SelectMgr_SOS_Deactivated);
    myTolerances.Decrement(theSelection->Sensitivity());
  }
}
