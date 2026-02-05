#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class StepGeom_Vector;
class StepGeom_Direction;

class StepGeom_VectorOrDirection : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  //! Returns a VectorOrDirection SelectType
  Standard_EXPORT StepGeom_VectorOrDirection();

  //! Recognizes a VectorOrDirection Kind Entity that is :
  //! 1 -> Vector
  //! 2 -> Direction
  //! 0 else
  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  //! returns Value as a Vector (Null if another type)
  Standard_EXPORT occ::handle<StepGeom_Vector> Vector() const;

  //! returns Value as a Direction (Null if another type)
  Standard_EXPORT occ::handle<StepGeom_Direction> Direction() const;
};
