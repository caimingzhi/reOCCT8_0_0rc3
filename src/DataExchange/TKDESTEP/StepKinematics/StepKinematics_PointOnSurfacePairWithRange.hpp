#pragma once


#include <Standard.hpp>
#include <StepKinematics_PointOnSurfacePair.hpp>

#include <TCollection_HAsciiString.hpp>
#include <StepRepr_RepresentationItem.hpp>
#include <StepKinematics_KinematicJoint.hpp>
#include <StepGeom_Surface.hpp>
#include <StepGeom_RectangularTrimmedSurface.hpp>

//! Representation of STEP entity PointOnSurfacePairWithRange
class StepKinematics_PointOnSurfacePairWithRange : public StepKinematics_PointOnSurfacePair
{
public:
  //! default constructor
  Standard_EXPORT StepKinematics_PointOnSurfacePairWithRange();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&      theRepresentationItem_Name,
    const occ::handle<TCollection_HAsciiString>&      theItemDefinedTransformation_Name,
    const bool                                        hasItemDefinedTransformation_Description,
    const occ::handle<TCollection_HAsciiString>&      theItemDefinedTransformation_Description,
    const occ::handle<StepRepr_RepresentationItem>&   theItemDefinedTransformation_TransformItem1,
    const occ::handle<StepRepr_RepresentationItem>&   theItemDefinedTransformation_TransformItem2,
    const occ::handle<StepKinematics_KinematicJoint>& theKinematicPair_Joint,
    const occ::handle<StepGeom_Surface>&              thePointOnSurfacePair_PairSurface,
    const occ::handle<StepGeom_RectangularTrimmedSurface>& theRangeOnPairSurface,
    const bool                                             hasLowerLimitYaw,
    const double                                           theLowerLimitYaw,
    const bool                                             hasUpperLimitYaw,
    const double                                           theUpperLimitYaw,
    const bool                                             hasLowerLimitPitch,
    const double                                           theLowerLimitPitch,
    const bool                                             hasUpperLimitPitch,
    const double                                           theUpperLimitPitch,
    const bool                                             hasLowerLimitRoll,
    const double                                           theLowerLimitRoll,
    const bool                                             hasUpperLimitRoll,
    const double                                           theUpperLimitRoll);

  //! Returns field RangeOnPairSurface
  Standard_EXPORT occ::handle<StepGeom_RectangularTrimmedSurface> RangeOnPairSurface() const;
  //! Sets field RangeOnPairSurface
  Standard_EXPORT void SetRangeOnPairSurface(
    const occ::handle<StepGeom_RectangularTrimmedSurface>& theRangeOnPairSurface);

  //! Returns field LowerLimitYaw
  Standard_EXPORT double LowerLimitYaw() const;
  //! Sets field LowerLimitYaw
  Standard_EXPORT void SetLowerLimitYaw(const double theLowerLimitYaw);
  //! Returns True if optional field LowerLimitYaw is defined
  Standard_EXPORT bool HasLowerLimitYaw() const;

  //! Returns field UpperLimitYaw
  Standard_EXPORT double UpperLimitYaw() const;
  //! Sets field UpperLimitYaw
  Standard_EXPORT void SetUpperLimitYaw(const double theUpperLimitYaw);
  //! Returns True if optional field UpperLimitYaw is defined
  Standard_EXPORT bool HasUpperLimitYaw() const;

  //! Returns field LowerLimitPitch
  Standard_EXPORT double LowerLimitPitch() const;
  //! Sets field LowerLimitPitch
  Standard_EXPORT void SetLowerLimitPitch(const double theLowerLimitPitch);
  //! Returns True if optional field LowerLimitPitch is defined
  Standard_EXPORT bool HasLowerLimitPitch() const;

  //! Returns field UpperLimitPitch
  Standard_EXPORT double UpperLimitPitch() const;
  //! Sets field UpperLimitPitch
  Standard_EXPORT void SetUpperLimitPitch(const double theUpperLimitPitch);
  //! Returns True if optional field UpperLimitPitch is defined
  Standard_EXPORT bool HasUpperLimitPitch() const;

  //! Returns field LowerLimitRoll
  Standard_EXPORT double LowerLimitRoll() const;
  //! Sets field LowerLimitRoll
  Standard_EXPORT void SetLowerLimitRoll(const double theLowerLimitRoll);
  //! Returns True if optional field LowerLimitRoll is defined
  Standard_EXPORT bool HasLowerLimitRoll() const;

  //! Returns field UpperLimitRoll
  Standard_EXPORT double UpperLimitRoll() const;
  //! Sets field UpperLimitRoll
  Standard_EXPORT void SetUpperLimitRoll(const double theUpperLimitRoll);
  //! Returns True if optional field UpperLimitRoll is defined
  Standard_EXPORT bool HasUpperLimitRoll() const;

  DEFINE_STANDARD_RTTIEXT(StepKinematics_PointOnSurfacePairWithRange,
                          StepKinematics_PointOnSurfacePair)

private:
  occ::handle<StepGeom_RectangularTrimmedSurface> myRangeOnPairSurface;
  double                                          myLowerLimitYaw;   //!< optional
  double                                          myUpperLimitYaw;   //!< optional
  double                                          myLowerLimitPitch; //!< optional
  double                                          myUpperLimitPitch; //!< optional
  double                                          myLowerLimitRoll;  //!< optional
  double                                          myUpperLimitRoll;  //!< optional
  bool defLowerLimitYaw;   //!< flag "is LowerLimitYaw defined"
  bool defUpperLimitYaw;   //!< flag "is UpperLimitYaw defined"
  bool defLowerLimitPitch; //!< flag "is LowerLimitPitch defined"
  bool defUpperLimitPitch; //!< flag "is UpperLimitPitch defined"
  bool defLowerLimitRoll;  //!< flag "is LowerLimitRoll defined"
  bool defUpperLimitRoll;  //!< flag "is UpperLimitRoll defined"
};
