#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>
#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>

class Standard_Transient;
class StepGeom_Curve;
class StepShape_Edge;

//! Representation of STEP SELECT type EdgeOrCurve
class StepVisual_EdgeOrCurve : public StepData_SelectType
{

public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  Standard_EXPORT StepVisual_EdgeOrCurve();

  //! Recognizes a kind of EdgeOrCurve select type
  //! -- 1 -> Curve
  //! -- 2 -> Edge
  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  //! Returns Value as Curve (or Null if another type)
  Standard_EXPORT occ::handle<StepGeom_Curve> Curve() const;

  //! Returns Value as Edge (or Null if another type)
  Standard_EXPORT occ::handle<StepShape_Edge> Edge() const;
};
