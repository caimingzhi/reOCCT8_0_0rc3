#pragma once


#include <Standard.hpp>
#include <StepKinematics_HighOrderKinematicPair.hpp>

#include <TCollection_HAsciiString.hpp>
#include <StepRepr_RepresentationItem.hpp>
#include <StepKinematics_KinematicJoint.hpp>
#include <StepGeom_Surface.hpp>

//! Representation of STEP entity PointOnSurfacePair
class StepKinematics_PointOnSurfacePair : public StepKinematics_HighOrderKinematicPair
{
public:
  //! default constructor
  Standard_EXPORT StepKinematics_PointOnSurfacePair();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&      theRepresentationItem_Name,
    const occ::handle<TCollection_HAsciiString>&      theItemDefinedTransformation_Name,
    const bool                                        hasItemDefinedTransformation_Description,
    const occ::handle<TCollection_HAsciiString>&      theItemDefinedTransformation_Description,
    const occ::handle<StepRepr_RepresentationItem>&   theItemDefinedTransformation_TransformItem1,
    const occ::handle<StepRepr_RepresentationItem>&   theItemDefinedTransformation_TransformItem2,
    const occ::handle<StepKinematics_KinematicJoint>& theKinematicPair_Joint,
    const occ::handle<StepGeom_Surface>&              thePairSurface);

  //! Returns field PairSurface
  Standard_EXPORT occ::handle<StepGeom_Surface> PairSurface() const;
  //! Sets field PairSurface
  Standard_EXPORT void SetPairSurface(const occ::handle<StepGeom_Surface>& thePairSurface);

  DEFINE_STANDARD_RTTIEXT(StepKinematics_PointOnSurfacePair, StepKinematics_HighOrderKinematicPair)

private:
  occ::handle<StepGeom_Surface> myPairSurface;
};
