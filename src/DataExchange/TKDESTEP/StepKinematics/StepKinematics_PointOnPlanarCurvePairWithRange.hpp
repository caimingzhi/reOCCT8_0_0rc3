#pragma once

#include <Standard.hpp>
#include <StepKinematics_PointOnPlanarCurvePair.hpp>

#include <TCollection_HAsciiString.hpp>
#include <StepRepr_RepresentationItem.hpp>
#include <StepKinematics_KinematicJoint.hpp>
#include <StepGeom_Curve.hpp>
#include <StepGeom_TrimmedCurve.hpp>

class StepKinematics_PointOnPlanarCurvePairWithRange : public StepKinematics_PointOnPlanarCurvePair
{
public:
  Standard_EXPORT StepKinematics_PointOnPlanarCurvePairWithRange();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&      theRepresentationItem_Name,
    const occ::handle<TCollection_HAsciiString>&      theItemDefinedTransformation_Name,
    const bool                                        hasItemDefinedTransformation_Description,
    const occ::handle<TCollection_HAsciiString>&      theItemDefinedTransformation_Description,
    const occ::handle<StepRepr_RepresentationItem>&   theItemDefinedTransformation_TransformItem1,
    const occ::handle<StepRepr_RepresentationItem>&   theItemDefinedTransformation_TransformItem2,
    const occ::handle<StepKinematics_KinematicJoint>& theKinematicPair_Joint,
    const occ::handle<StepGeom_Curve>&                thePointOnPlanarCurvePair_PairCurve,
    const bool                                        thePointOnPlanarCurvePair_Orientation,
    const occ::handle<StepGeom_TrimmedCurve>&         theRangeOnPairCurve,
    const bool                                        hasLowerLimitYaw,
    const double                                      theLowerLimitYaw,
    const bool                                        hasUpperLimitYaw,
    const double                                      theUpperLimitYaw,
    const bool                                        hasLowerLimitPitch,
    const double                                      theLowerLimitPitch,
    const bool                                        hasUpperLimitPitch,
    const double                                      theUpperLimitPitch,
    const bool                                        hasLowerLimitRoll,
    const double                                      theLowerLimitRoll,
    const bool                                        hasUpperLimitRoll,
    const double                                      theUpperLimitRoll);

  Standard_EXPORT occ::handle<StepGeom_TrimmedCurve> RangeOnPairCurve() const;

  Standard_EXPORT void SetRangeOnPairCurve(
    const occ::handle<StepGeom_TrimmedCurve>& theRangeOnPairCurve);

  Standard_EXPORT double LowerLimitYaw() const;

  Standard_EXPORT void SetLowerLimitYaw(const double theLowerLimitYaw);

  Standard_EXPORT bool HasLowerLimitYaw() const;

  Standard_EXPORT double UpperLimitYaw() const;

  Standard_EXPORT void SetUpperLimitYaw(const double theUpperLimitYaw);

  Standard_EXPORT bool HasUpperLimitYaw() const;

  Standard_EXPORT double LowerLimitPitch() const;

  Standard_EXPORT void SetLowerLimitPitch(const double theLowerLimitPitch);

  Standard_EXPORT bool HasLowerLimitPitch() const;

  Standard_EXPORT double UpperLimitPitch() const;

  Standard_EXPORT void SetUpperLimitPitch(const double theUpperLimitPitch);

  Standard_EXPORT bool HasUpperLimitPitch() const;

  Standard_EXPORT double LowerLimitRoll() const;

  Standard_EXPORT void SetLowerLimitRoll(const double theLowerLimitRoll);

  Standard_EXPORT bool HasLowerLimitRoll() const;

  Standard_EXPORT double UpperLimitRoll() const;

  Standard_EXPORT void SetUpperLimitRoll(const double theUpperLimitRoll);

  Standard_EXPORT bool HasUpperLimitRoll() const;

  DEFINE_STANDARD_RTTIEXT(StepKinematics_PointOnPlanarCurvePairWithRange,
                          StepKinematics_PointOnPlanarCurvePair)

private:
  occ::handle<StepGeom_TrimmedCurve> myRangeOnPairCurve;
  double                             myLowerLimitYaw;
  double                             myUpperLimitYaw;
  double                             myLowerLimitPitch;
  double                             myUpperLimitPitch;
  double                             myLowerLimitRoll;
  double                             myUpperLimitRoll;
  bool                               defLowerLimitYaw;
  bool                               defUpperLimitYaw;
  bool                               defLowerLimitPitch;
  bool                               defUpperLimitPitch;
  bool                               defLowerLimitRoll;
  bool                               defUpperLimitRoll;
};
