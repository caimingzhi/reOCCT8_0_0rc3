#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class StepShape_ShellBasedSurfaceModel;

class StepShape_SurfaceModel : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  //! Returns a SurfaceModel SelectType
  Standard_EXPORT StepShape_SurfaceModel();

  //! Recognizes a SurfaceModel Kind Entity that is :
  //! 1 -> ShellBasedSurfaceModel
  //! 2 -> FaceBasedSurfaceModel
  //! 0 else
  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  //! returns Value as a ShellBasedSurfaceModel (Null if another type)
  Standard_EXPORT occ::handle<StepShape_ShellBasedSurfaceModel> ShellBasedSurfaceModel() const;
};

