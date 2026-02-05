#pragma once

#include <Standard.hpp>
#include <StepKinematics_SurfacePair.hpp>

#include <TCollection_HAsciiString.hpp>
#include <StepRepr_RepresentationItem.hpp>
#include <StepKinematics_KinematicJoint.hpp>
#include <StepGeom_Surface.hpp>
#include <StepGeom_RectangularTrimmedSurface.hpp>

//! Representation of STEP entity SurfacePairWithRange
class StepKinematics_SurfacePairWithRange : public StepKinematics_SurfacePair
{
public:
  //! default constructor
  Standard_EXPORT StepKinematics_SurfacePairWithRange();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&      theRepresentationItem_Name,
    const occ::handle<TCollection_HAsciiString>&      theItemDefinedTransformation_Name,
    const bool                                        hasItemDefinedTransformation_Description,
    const occ::handle<TCollection_HAsciiString>&      theItemDefinedTransformation_Description,
    const occ::handle<StepRepr_RepresentationItem>&   theItemDefinedTransformation_TransformItem1,
    const occ::handle<StepRepr_RepresentationItem>&   theItemDefinedTransformation_TransformItem2,
    const occ::handle<StepKinematics_KinematicJoint>& theKinematicPair_Joint,
    const occ::handle<StepGeom_Surface>&              theSurfacePair_Surface1,
    const occ::handle<StepGeom_Surface>&              theSurfacePair_Surface2,
    const bool                                        theSurfacePair_Orientation,
    const occ::handle<StepGeom_RectangularTrimmedSurface>& theRangeOnSurface1,
    const occ::handle<StepGeom_RectangularTrimmedSurface>& theRangeOnSurface2,
    const bool                                             hasLowerLimitActualRotation,
    const double                                           theLowerLimitActualRotation,
    const bool                                             hasUpperLimitActualRotation,
    const double                                           theUpperLimitActualRotation);

  //! Returns field RangeOnSurface1
  Standard_EXPORT occ::handle<StepGeom_RectangularTrimmedSurface> RangeOnSurface1() const;
  //! Sets field RangeOnSurface1
  Standard_EXPORT void SetRangeOnSurface1(
    const occ::handle<StepGeom_RectangularTrimmedSurface>& theRangeOnSurface1);

  //! Returns field RangeOnSurface2
  Standard_EXPORT occ::handle<StepGeom_RectangularTrimmedSurface> RangeOnSurface2() const;
  //! Sets field RangeOnSurface2
  Standard_EXPORT void SetRangeOnSurface2(
    const occ::handle<StepGeom_RectangularTrimmedSurface>& theRangeOnSurface2);

  //! Returns field LowerLimitActualRotation
  Standard_EXPORT double LowerLimitActualRotation() const;
  //! Sets field LowerLimitActualRotation
  Standard_EXPORT void SetLowerLimitActualRotation(const double theLowerLimitActualRotation);
  //! Returns True if optional field LowerLimitActualRotation is defined
  Standard_EXPORT bool HasLowerLimitActualRotation() const;

  //! Returns field UpperLimitActualRotation
  Standard_EXPORT double UpperLimitActualRotation() const;
  //! Sets field UpperLimitActualRotation
  Standard_EXPORT void SetUpperLimitActualRotation(const double theUpperLimitActualRotation);
  //! Returns True if optional field UpperLimitActualRotation is defined
  Standard_EXPORT bool HasUpperLimitActualRotation() const;

  DEFINE_STANDARD_RTTIEXT(StepKinematics_SurfacePairWithRange, StepKinematics_SurfacePair)

private:
  occ::handle<StepGeom_RectangularTrimmedSurface> myRangeOnSurface1;
  occ::handle<StepGeom_RectangularTrimmedSurface> myRangeOnSurface2;
  double                                          myLowerLimitActualRotation; //!< optional
  double                                          myUpperLimitActualRotation; //!< optional
  bool defLowerLimitActualRotation; //!< flag "is LowerLimitActualRotation defined"
  bool defUpperLimitActualRotation; //!< flag "is UpperLimitActualRotation defined"
};
