#include <IVtkVTK_View.hpp>

#ifdef _MSC_VER
  #pragma warning(push)
#endif
#include <vtkAutoInit.h>
#include <vtkCamera.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkTransform.h>
#ifdef _MSC_VER
  #pragma warning(pop)
#endif

IMPLEMENT_STANDARD_RTTIEXT(IVtkVTK_View, IVtk_IView)

#ifdef VTK_OPENGL2_BACKEND
VTK_MODULE_INIT(vtkRenderingOpenGL2)
#else
VTK_MODULE_INIT(vtkRenderingOpenGL)
#endif
VTK_MODULE_INIT(vtkInteractionStyle)

IVtkVTK_View::IVtkVTK_View(vtkRenderer* theRenderer)
    : myRenderer(theRenderer)
{
}

IVtkVTK_View::~IVtkVTK_View() = default;

bool IVtkVTK_View::IsPerspective() const
{
  return !myRenderer->GetActiveCamera()->GetParallelProjection();
}

double IVtkVTK_View::GetDistance() const
{
  return myRenderer->GetActiveCamera()->GetDistance();
}

void IVtkVTK_View::GetEyePosition(double& theX, double& theY, double& theZ) const
{
  myRenderer->GetActiveCamera()->GetPosition(theX, theY, theZ);
}

void IVtkVTK_View::GetPosition(double& theX, double& theY, double& theZ) const
{
  myRenderer->GetActiveCamera()->GetFocalPoint(theX, theY, theZ);
}

void IVtkVTK_View::GetViewUp(double& theDx, double& theDy, double& theDz) const
{
  myRenderer->GetActiveCamera()->OrthogonalizeViewUp();
  myRenderer->GetActiveCamera()->GetViewUp(theDx, theDy, theDz);
}

void IVtkVTK_View::GetDirectionOfProjection(double& theDx, double& theDy, double& theDz) const
{
  myRenderer->GetActiveCamera()->GetDirectionOfProjection(theDx, theDy, theDz);
  theDx = -theDx;
  theDy = -theDy;
  theDz = -theDz;
}

void IVtkVTK_View::GetScale(double& theX, double& theY, double& theZ) const
{
  double aScale[3];
  myRenderer->GetActiveCamera()->GetViewTransformObject()->GetScale(aScale);
  theX = aScale[0];
  theY = aScale[1];
  theZ = aScale[2];
}

double IVtkVTK_View::GetParallelScale() const
{
  return myRenderer->GetActiveCamera()->GetParallelScale();
}

double IVtkVTK_View::GetViewAngle() const
{
  return myRenderer->GetActiveCamera()->GetViewAngle();
}

double IVtkVTK_View::GetAspectRatio() const
{
  return myRenderer->GetTiledAspectRatio();
}

void IVtkVTK_View::GetClippingRange(double& theZNear, double& theZFar) const
{
  myRenderer->GetActiveCamera()->GetClippingRange(theZNear, theZFar);
}

void IVtkVTK_View::GetViewCenter(double& theX, double& theY) const
{
  double* aCenter = myRenderer->GetCenter();
  theX            = aCenter[0];
  theY            = aCenter[1];
}

bool IVtkVTK_View::DisplayToWorld(const gp_XY& theDisplayPnt, gp_XYZ& theWorldPnt) const
{

  myRenderer->SetDisplayPoint(theDisplayPnt.X(), theDisplayPnt.Y(), 0.0);
  myRenderer->DisplayToWorld();

  double* const aCoords = myRenderer->GetWorldPoint();
  if (aCoords[3] == 0.0)
  {
    return false;
  }

  theWorldPnt = gp_XYZ(aCoords[0] / aCoords[3], aCoords[1] / aCoords[3], aCoords[2] / aCoords[3]);

  return true;
}

void IVtkVTK_View::GetWindowSize(int& theX, int& theY) const
{
  int* aSize = myRenderer->GetRenderWindow()->GetSize();
  theX       = aSize[0];
  theY       = aSize[1];
}

void IVtkVTK_View::GetCamera(NCollection_Mat4<double>& theProj,
                             NCollection_Mat4<double>& theOrient,
                             bool&                     theIsOrtho) const
{
  theIsOrtho = !IsPerspective();

  vtkMatrix4x4* aCompositeProj =
    myRenderer->GetActiveCamera()->GetCompositeProjectionTransformMatrix(
      myRenderer->GetTiledAspectRatio(),
      0,
      1);
  for (int aRow = 0; aRow < 4; ++aRow)
  {
    for (int aCol = 0; aCol < 4; ++aCol)
    {
      theProj.SetValue(aRow, aCol, aCompositeProj->GetElement(aRow, aCol));
    }
  }

  theOrient.InitIdentity();
}

void IVtkVTK_View::GetViewport(double& theX,
                               double& theY,
                               double& theWidth,
                               double& theHeight) const
{
  double aViewport[4];
  myRenderer->GetViewport(aViewport);
  theX      = aViewport[0];
  theY      = aViewport[1];
  theWidth  = aViewport[2];
  theHeight = aViewport[3];
}
