#pragma once

#include <Graphic3d_TransformPers.hpp>

//! Transformation Zoom persistence with the above boundary of scale.
//! This persistence works only when the camera scale value is below the scale value of this
//! persistence. Otherwise, no persistence is applied.
class Graphic3d_TransformPersScaledAbove : public Graphic3d_TransformPers
{
public:
  //! Create a Zoom transformation persistence with an anchor 3D point and a scale value
  Standard_EXPORT Graphic3d_TransformPersScaledAbove(const double theScale, const gp_Pnt& thePnt);

  //! Destructor
  ~Graphic3d_TransformPersScaledAbove() override = default;

  //! Find scale value based on the camera position and view dimensions
  //! If the camera scale value less than the persistence scale, zoom persistence is not applied.
  //! @param[in] theCamera  camera definition
  //! @param[in] theViewportWidth  the width of viewport.
  //! @param[in] theViewportHeight  the height of viewport.
  Standard_EXPORT double persistentScale(const occ::handle<Graphic3d_Camera>& theCamera,
                                         const int                            theViewportWidth,
                                         const int theViewportHeight) const override;

public:
  DEFINE_STANDARD_RTTIEXT(Graphic3d_TransformPersScaledAbove, Graphic3d_TransformPers)

private:
  double myScale; //!< scale bound value
};
