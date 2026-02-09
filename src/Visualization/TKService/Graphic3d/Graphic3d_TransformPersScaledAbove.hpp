#pragma once

#include <Graphic3d_TransformPers.hpp>

class Graphic3d_TransformPersScaledAbove : public Graphic3d_TransformPers
{
public:
  Standard_EXPORT Graphic3d_TransformPersScaledAbove(const double theScale, const gp_Pnt& thePnt);

  ~Graphic3d_TransformPersScaledAbove() override = default;

  Standard_EXPORT double persistentScale(const occ::handle<Graphic3d_Camera>& theCamera,
                                         const int                            theViewportWidth,
                                         const int theViewportHeight) const override;

public:
  DEFINE_STANDARD_RTTIEXT(Graphic3d_TransformPersScaledAbove, Graphic3d_TransformPers)

private:
  double myScale;
};
