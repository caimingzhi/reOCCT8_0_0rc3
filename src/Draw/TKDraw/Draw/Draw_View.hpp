#pragma once

#include <gp_Trsf.hpp>
#include <Draw_Window.hpp>

class Draw_Viewer;

class Draw_View : public Draw_Window
{
public:
  Draw_View(int             theId,
            Draw_Viewer*    theViewer,
            int             theX,
            int             theY,
            int             theWidth,
            int             theHeight,
            Aspect_Drawable theWindow = 0);

  Draw_View(int theId, Draw_Viewer* theViewer, const char* theTitle);

  ~Draw_View() override;

public:
  int GetDx() const { return myDx; }

  void SetDx(const int theDx) { myDx = theDx; }

  int GetDy() const { return myDy; }

  void SetDy(const int theDy) { myDy = theDy; }

  double GetZoom() const { return myZoom; }

  void SetZoom(const double theZoom) { myZoom = theZoom; }

  const gp_Trsf& GetMatrix() const { return myMatrix; }

  void SetMatrix(const gp_Trsf& theMatrix) { myMatrix = theMatrix; }

  double GetFocalDistance() const { return myFocalDistance; }

  void SetFocalDistance(const double theDistance) { myFocalDistance = theDistance; }

  const char* Type() { return myType; }

  bool Is2D() const { return myIs2D; }

  double IsPerspective() const { return myIsPers; }

public:
  bool Init(const char* theType);

  void Transform(const gp_Trsf& theTransformation);

  void ResetFrame();

  void GetFrame(int& theX0, int& theY0, int& theX1, int& theY1);

  void WExpose() override;

protected:
  int          myId;
  Draw_Viewer* myViewer;
  char         myType[5];
  bool         myIsPers;
  bool         myIs2D;
  double       myFocalDistance;
  double       myZoom;
  gp_Trsf      myMatrix;
  int          myDx;
  int          myDy;
  int          myFrameX0;
  int          myFrameY0;
  int          myFrameX1;
  int          myFrameY1;
};
