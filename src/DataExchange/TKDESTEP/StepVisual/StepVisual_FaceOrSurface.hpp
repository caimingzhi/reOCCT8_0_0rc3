#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>
#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>

class Standard_Transient;
class StepShape_Face;
class StepGeom_Surface;

class StepVisual_FaceOrSurface : public StepData_SelectType
{

public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepVisual_FaceOrSurface();

  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  Standard_EXPORT occ::handle<StepShape_Face> Face() const;

  Standard_EXPORT occ::handle<StepGeom_Surface> Surface() const;
};
