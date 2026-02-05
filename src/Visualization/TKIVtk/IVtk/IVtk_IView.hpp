#pragma once

#include <IVtk_Interface.hpp>
#include <gp_XY.hpp>
#include <gp_XYZ.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Mat4.hpp>
#include <Standard_TypeDef.hpp>

//! @class IVtk_IView
//! @brief Interface for obtaining view transformation parameters.
//!
//! These parameters are used by selection algorithm to compute
//! projections of selectable (active) 3D shapes.
class IVtk_IView : public IVtk_Interface
{

public:
  typedef occ::handle<IVtk_IView> Handle;

  //! Destructor
  ~IVtk_IView() override = default;

  //! @return true if this is a perspective view, and false otherwise.
  virtual bool IsPerspective() const = 0;

  //! @return The focal distance of the view
  virtual double GetDistance() const = 0;

  //! @return The world coordinates of the camera position
  virtual void GetEyePosition(double& theX, double& theY, double& theZ) const = 0;

  //! @return The world coordinates of the view position
  virtual void GetPosition(double& theX, double& theY, double& theZ) const = 0;

  //! @return The "view up" direction of the view
  virtual void GetViewUp(double& theDx, double& theDy, double& theDz) const = 0;

  //! @return The projection direction vector of this view
  virtual void GetDirectionOfProjection(double& theDx, double& theDy, double& theDz) const = 0;

  //! @return Three doubles containing scale components of the view transformation
  virtual void GetScale(double& theX, double& theY, double& theZ) const = 0;

  //! @return The current view's zoom factor (for parallel projection)
  virtual double GetParallelScale() const = 0;

  //! @return The current view angle (for perspective projection)
  virtual double GetViewAngle() const = 0;

  //! @return The location of the near and far clipping planes along the direction of projection
  virtual void GetClippingRange(double& theZNear, double& theZFar) const = 0;

  //! @return The current view the aspect ratio
  virtual double GetAspectRatio() const = 0;

  //! @return Two doubles containing the display coordinates of the view window center
  virtual void GetViewCenter(double& theX, double& theY) const = 0;

  //! Gets window size in screen coordinates in pixels
  virtual void GetWindowSize(int& theX, int& theY) const = 0;

  //! Gets camera projection and orientation matrices
  virtual void GetCamera(NCollection_Mat4<double>& theProj,
                         NCollection_Mat4<double>& theOrient,
                         bool&                     theIsOrtho) const = 0;

  //! Converts 3D display coordinates into 3D world coordinates.
  //! @param[in]  theDisplayPnt 2d point of display coordinates
  //! @param[out]  theWorldPnt 3d point of world coordinates
  //! @return true if conversion was successful, false otherwise
  virtual bool DisplayToWorld(const gp_XY& theDisplayPnt, gp_XYZ& theWorldPnt) const = 0;

  //! Gets viewport coordinates
  virtual void GetViewport(double& theX,
                           double& theY,
                           double& theWidth,
                           double& theHeight) const = 0;

  DEFINE_STANDARD_RTTIEXT(IVtk_IView, IVtk_Interface)
};
