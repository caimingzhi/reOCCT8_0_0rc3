#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_Vec.hpp>
#include <Vrml_SFRotation.hpp>
#include <Standard_OStream.hpp>

//! defines a Transform of VRML specifying transform
//! properties.
//! This node defines a geometric 3D transformation consisting of (in order)
//! a (possibly) non-uniform scale about an arbitrary point, a rotation about
//! an arbitrary point and axis and translation.
//! By default:
//! myTranslation (0,0,0)
//! myRotation  (0,0,1,0)
//! myScaleFactor (1,1,1)
//! myScaleOrientation (0,0,1,0)
//! myCenter (0,0,0)
class Vrml_Transform
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Vrml_Transform();

  Standard_EXPORT Vrml_Transform(const gp_Vec&          aTranslation,
                                 const Vrml_SFRotation& aRotation,
                                 const gp_Vec&          aScaleFactor,
                                 const Vrml_SFRotation& aScaleOrientation,
                                 const gp_Vec&          aCenter);

  Standard_EXPORT void SetTranslation(const gp_Vec& aTranslation);

  Standard_EXPORT gp_Vec Translation() const;

  Standard_EXPORT void SetRotation(const Vrml_SFRotation& aRotation);

  Standard_EXPORT Vrml_SFRotation Rotation() const;

  Standard_EXPORT void SetScaleFactor(const gp_Vec& aScaleFactor);

  Standard_EXPORT gp_Vec ScaleFactor() const;

  Standard_EXPORT void SetScaleOrientation(const Vrml_SFRotation& aScaleOrientation);

  Standard_EXPORT Vrml_SFRotation ScaleOrientation() const;

  Standard_EXPORT void SetCenter(const gp_Vec& aCenter);

  Standard_EXPORT gp_Vec Center() const;

  Standard_EXPORT Standard_OStream& Print(Standard_OStream& anOStream) const;

private:
  gp_Vec          myTranslation;
  Vrml_SFRotation myRotation;
  gp_Vec          myScaleFactor;
  Vrml_SFRotation myScaleOrientation;
  gp_Vec          myCenter;
};

