#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>
#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>

class Standard_Transient;
class StepGeom_CompositeCurve;
class StepShape_Path;

//! Representation of STEP SELECT type PathOrCompositeCurve
class StepVisual_PathOrCompositeCurve : public StepData_SelectType
{

public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  Standard_EXPORT StepVisual_PathOrCompositeCurve();

  //! Recognizes a kind of PathOrCompositeCurve select type
  //! -- 1 -> CompositeCurve
  //! -- 2 -> Path
  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  //! Returns Value as CompositeCurve (or Null if another type)
  Standard_EXPORT occ::handle<StepGeom_CompositeCurve> CompositeCurve() const;

  //! Returns Value as Path (or Null if another type)
  Standard_EXPORT occ::handle<StepShape_Path> Path() const;
};
