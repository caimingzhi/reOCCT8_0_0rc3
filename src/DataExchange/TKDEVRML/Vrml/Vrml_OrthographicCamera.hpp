#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_Vec.hpp>
#include <Vrml_SFRotation.hpp>
#include <Standard_OStream.hpp>

class Vrml_OrthographicCamera
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Vrml_OrthographicCamera();

  Standard_EXPORT Vrml_OrthographicCamera(const gp_Vec&          aPosition,
                                          const Vrml_SFRotation& aOrientation,
                                          const double           aFocalDistance,
                                          const double           aHeight);

  Standard_EXPORT void SetPosition(const gp_Vec& aPosition);

  Standard_EXPORT gp_Vec Position() const;

  Standard_EXPORT void SetOrientation(const Vrml_SFRotation& aOrientation);

  Standard_EXPORT Vrml_SFRotation Orientation() const;

  Standard_EXPORT void SetFocalDistance(const double aFocalDistance);

  Standard_EXPORT double FocalDistance() const;

  Standard_EXPORT void SetHeight(const double aHeight);

  Standard_EXPORT double Height() const;

  Standard_EXPORT Standard_OStream& Print(Standard_OStream& anOStream) const;

private:
  gp_Vec          myPosition;
  Vrml_SFRotation myOrientation;
  double          myFocalDistance;
  double          myHeight;
};
