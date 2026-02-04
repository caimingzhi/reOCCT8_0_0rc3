#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Boolean.hpp>
#include <StepGeom_Surface.hpp>
class TCollection_HAsciiString;

//! Representation of STEP entity OrientedSurface
class StepGeom_OrientedSurface : public StepGeom_Surface
{

public:
  //! Empty constructor
  Standard_EXPORT StepGeom_OrientedSurface();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aRepresentationItem_Name,
                            const bool                                   aOrientation);

  //! Returns field Orientation
  Standard_EXPORT bool Orientation() const;

  //! Set field Orientation
  Standard_EXPORT void SetOrientation(const bool Orientation);

  DEFINE_STANDARD_RTTIEXT(StepGeom_OrientedSurface, StepGeom_Surface)

private:
  bool theOrientation;
};

