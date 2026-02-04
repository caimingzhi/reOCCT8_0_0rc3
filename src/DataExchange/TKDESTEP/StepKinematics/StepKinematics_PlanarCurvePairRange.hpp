#pragma once


#include <Standard.hpp>
#include <StepKinematics_PlanarCurvePair.hpp>

#include <TCollection_HAsciiString.hpp>
#include <StepRepr_RepresentationItem.hpp>
#include <StepKinematics_KinematicJoint.hpp>
#include <StepGeom_Curve.hpp>
#include <StepGeom_TrimmedCurve.hpp>

//! Representation of STEP entity PlanarCurvePairRange
class StepKinematics_PlanarCurvePairRange : public StepKinematics_PlanarCurvePair
{
public:
  //! default constructor
  Standard_EXPORT StepKinematics_PlanarCurvePairRange();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&      theRepresentationItem_Name,
    const occ::handle<TCollection_HAsciiString>&      theItemDefinedTransformation_Name,
    const bool                                        hasItemDefinedTransformation_Description,
    const occ::handle<TCollection_HAsciiString>&      theItemDefinedTransformation_Description,
    const occ::handle<StepRepr_RepresentationItem>&   theItemDefinedTransformation_TransformItem1,
    const occ::handle<StepRepr_RepresentationItem>&   theItemDefinedTransformation_TransformItem2,
    const occ::handle<StepKinematics_KinematicJoint>& theKinematicPair_Joint,
    const occ::handle<StepGeom_Curve>&                thePlanarCurvePair_Curve1,
    const occ::handle<StepGeom_Curve>&                thePlanarCurvePair_Curve2,
    const bool                                        thePlanarCurvePair_Orientation,
    const occ::handle<StepGeom_TrimmedCurve>&         theRangeOnCurve1,
    const occ::handle<StepGeom_TrimmedCurve>&         theRangeOnCurve2);

  //! Returns field RangeOnCurve1
  Standard_EXPORT occ::handle<StepGeom_TrimmedCurve> RangeOnCurve1() const;
  //! Sets field RangeOnCurve1
  Standard_EXPORT void SetRangeOnCurve1(const occ::handle<StepGeom_TrimmedCurve>& theRangeOnCurve1);

  //! Returns field RangeOnCurve2
  Standard_EXPORT occ::handle<StepGeom_TrimmedCurve> RangeOnCurve2() const;
  //! Sets field RangeOnCurve2
  Standard_EXPORT void SetRangeOnCurve2(const occ::handle<StepGeom_TrimmedCurve>& theRangeOnCurve2);

  DEFINE_STANDARD_RTTIEXT(StepKinematics_PlanarCurvePairRange, StepKinematics_PlanarCurvePair)

private:
  occ::handle<StepGeom_TrimmedCurve> myRangeOnCurve1;
  occ::handle<StepGeom_TrimmedCurve> myRangeOnCurve2;
};
