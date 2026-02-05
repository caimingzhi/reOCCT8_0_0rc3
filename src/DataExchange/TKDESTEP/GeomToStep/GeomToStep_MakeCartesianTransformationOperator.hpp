#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GeomToStep_Root.hpp>
#include <StepData_StepModel.hpp>
#include <StepGeom_CartesianTransformationOperator3d.hpp>

class gp_Trsf;

//! This class creates a cartesian_transformation_operator from gp_Trsf.
//! This entity is used in OCCT to implement a transformation with scaling.
//! In case of other inputs without scaling use Axis2Placement3d.
class GeomToStep_MakeCartesianTransformationOperator : public GeomToStep_Root
{
public:
  DEFINE_STANDARD_ALLOC

  //! Main constructor.
  //! @param[in] theTrsf Transformation to create the operator from it.
  //! @param[in] theLocalFactors Unit scale factors
  Standard_EXPORT GeomToStep_MakeCartesianTransformationOperator(
    const gp_Trsf&          theTrsf,
    const StepData_Factors& theLocalFactors = StepData_Factors());

  //! Returns the created entity.
  //! @return The created value.
  inline const occ::handle<StepGeom_CartesianTransformationOperator3d>& Value() const
  {
    return myTrsfOp;
  }

private:
  occ::handle<StepGeom_CartesianTransformationOperator3d> myTrsfOp;
};
