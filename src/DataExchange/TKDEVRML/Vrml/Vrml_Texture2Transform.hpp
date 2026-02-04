#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_Vec2d.hpp>
#include <Standard_OStream.hpp>

//! defines a Texture2Transform node of VRML specifying properties of geometry
//! and its appearance.
//! This node defines a 2D transformation applied to texture coordinates.
//! This affect the way textures are applied to the surfaces of subsequent
//! shapes.
//! Transformation consisits of (in order) a non-uniform scale about an
//! arbitrary center point, a rotation about that same point, and
//! a translation. This allows a user to change the size and position of
//! the textures on the shape.
//! By default:
//! myTranslation (0 0)
//! myRotation (0)
//! myScaleFactor (1 1)
//! myCenter (0 0)
class Vrml_Texture2Transform
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Vrml_Texture2Transform();

  Standard_EXPORT Vrml_Texture2Transform(const gp_Vec2d& aTranslation,
                                         const double    aRotation,
                                         const gp_Vec2d& aScaleFactor,
                                         const gp_Vec2d& aCenter);

  Standard_EXPORT void SetTranslation(const gp_Vec2d& aTranslation);

  Standard_EXPORT gp_Vec2d Translation() const;

  Standard_EXPORT void SetRotation(const double aRotation);

  Standard_EXPORT double Rotation() const;

  Standard_EXPORT void SetScaleFactor(const gp_Vec2d& aScaleFactor);

  Standard_EXPORT gp_Vec2d ScaleFactor() const;

  Standard_EXPORT void SetCenter(const gp_Vec2d& aCenter);

  Standard_EXPORT gp_Vec2d Center() const;

  Standard_EXPORT Standard_OStream& Print(Standard_OStream& anOStream) const;

private:
  gp_Vec2d myTranslation;
  double   myRotation;
  gp_Vec2d myScaleFactor;
  gp_Vec2d myCenter;
};

