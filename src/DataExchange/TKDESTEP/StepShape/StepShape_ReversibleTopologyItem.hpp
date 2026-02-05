#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class StepShape_Edge;
class StepShape_Path;
class StepShape_Face;
class StepShape_FaceBound;
class StepShape_ClosedShell;
class StepShape_OpenShell;

class StepShape_ReversibleTopologyItem : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  //! Returns a ReversibleTopologyItem SelectType
  Standard_EXPORT StepShape_ReversibleTopologyItem();

  //! Recognizes a ReversibleTopologyItem Kind Entity that is :
  //! 1 -> Edge
  //! 2 -> Path
  //! 3 -> Face
  //! 4 -> FaceBound
  //! 5 -> ClosedShell
  //! 6 -> OpenShell
  //! 0 else
  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  //! returns Value as a Edge (Null if another type)
  Standard_EXPORT occ::handle<StepShape_Edge> Edge() const;

  //! returns Value as a Path (Null if another type)
  Standard_EXPORT occ::handle<StepShape_Path> Path() const;

  //! returns Value as a Face (Null if another type)
  Standard_EXPORT occ::handle<StepShape_Face> Face() const;

  //! returns Value as a FaceBound (Null if another type)
  Standard_EXPORT occ::handle<StepShape_FaceBound> FaceBound() const;

  //! returns Value as a ClosedShell (Null if another type)
  Standard_EXPORT occ::handle<StepShape_ClosedShell> ClosedShell() const;

  //! returns Value as a OpenShell (Null if another type)
  Standard_EXPORT occ::handle<StepShape_OpenShell> OpenShell() const;
};
