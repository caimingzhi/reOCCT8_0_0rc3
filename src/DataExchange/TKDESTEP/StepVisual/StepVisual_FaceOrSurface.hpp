#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>
#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>

class Standard_Transient;
class StepShape_Face;
class StepGeom_Surface;

//! Representation of STEP SELECT type FaceOrSurface
class StepVisual_FaceOrSurface : public StepData_SelectType
{

public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  Standard_EXPORT StepVisual_FaceOrSurface();

  //! Recognizes a kind of FaceOrSurface select type
  //! -- 1 -> Face
  //! -- 2 -> Surface
  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  //! Returns Value as Face (or Null if another type)
  Standard_EXPORT occ::handle<StepShape_Face> Face() const;

  //! Returns Value as Surface (or Null if another type)
  Standard_EXPORT occ::handle<StepGeom_Surface> Surface() const;
};
