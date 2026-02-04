#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>
#include <Standard_Transient.hpp>

//! Representation of STEP entity SurfaceStyleTransparent
class StepVisual_SurfaceStyleTransparent : public Standard_Transient
{
public:
  //! default constructor
  Standard_EXPORT StepVisual_SurfaceStyleTransparent();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(const double theTransparency);

  //! Returns field Transparency
  Standard_EXPORT double Transparency() const;
  //! Sets field Transparency
  Standard_EXPORT void SetTransparency(const double theTransparency);

  DEFINE_STANDARD_RTTIEXT(StepVisual_SurfaceStyleTransparent, Standard_Transient)

private:
  double myTransparency;
};
