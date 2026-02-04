#pragma once


#include <gp_Trsf.hpp>
#include <Draw_Window.hpp>

class Draw_Viewer;

class Draw_View : public Draw_Window
{
public:
  //! Constructor
  Draw_View(int             theId,
            Draw_Viewer*    theViewer,
            int             theX,
            int             theY,
            int             theWidth,
            int             theHeight,
            Aspect_Drawable theWindow = 0);

  //! Constructor.
  Draw_View(int theId, Draw_Viewer* theViewer, const char* theTitle);

  //! Destructor.
  ~Draw_View() override;

public: // @name getters and setters
  //! Gets horizontal offset.
  int GetDx() const { return myDx; }

  //! Sets horizontal offset.
  void SetDx(const int theDx) { myDx = theDx; }

  //! Gets vertical offset.
  int GetDy() const { return myDy; }

  //! Sets vertical offset.
  void SetDy(const int theDy) { myDy = theDy; }

  //! Gets parameter of zoom.
  double GetZoom() const { return myZoom; }

  //! Sets parameter of zoom.
  void SetZoom(const double theZoom) { myZoom = theZoom; }

  //! Gets matrix of view.
  const gp_Trsf& GetMatrix() const { return myMatrix; }

  //! Sets view matrix.
  void SetMatrix(const gp_Trsf& theMatrix) { myMatrix = theMatrix; }

  //! Gets focal distance.
  double GetFocalDistance() const { return myFocalDistance; }

  //! Sets focal distance.
  void SetFocalDistance(const double theDistance) { myFocalDistance = theDistance; }

  //! Returns type of view.
  const char* Type() { return myType; }

  //! Returns true value if current view in 2D mode.
  bool Is2D() const { return myIs2D; }

  //! Returns true value if current view in perspective mode.
  double IsPerspective() const { return myIsPers; }

public: //! @name view API
  //! Initialize view by the type.
  bool Init(const char* theType);

  //! Transform view matrix.
  void Transform(const gp_Trsf& theTransformation);

  //! Resets frame of current view.
  void ResetFrame();

  //! Returns parameters of frame corners.
  void GetFrame(int& theX0, int& theY0, int& theX1, int& theY1);

  //! Perform window exposing.
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

