#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>
class StepRepr_RepresentationItem;
class Transfer_FinderProcess;
class TopoDS_Shape;
class TopLoc_Location;
class Transfer_TransientProcess;
class Transfer_Binder;
class StepShape_ShapeDefinitionRepresentation;
class StepShape_ContextDependentShapeRepresentation;

//! Defines tools for creation and investigation STEP constructs
//! used for representing various kinds of data, such as product and
//! assembly structure, unit contexts, associated information
//! The creation of these structures is made according to currently
//! active schema (AP203 or AP214 CD2 or DIS)
//! This is taken from parameter write.step.schema
class STEPConstruct
{
public:
  DEFINE_STANDARD_ALLOC

  //! Returns STEP entity of the (sub)type of RepresentationItem
  //! which is a result of the translation of the Shape, or Null if
  //! no result is recorded
  Standard_EXPORT static occ::handle<StepRepr_RepresentationItem> FindEntity(
    const occ::handle<Transfer_FinderProcess>& FinderProcess,
    const TopoDS_Shape&                        Shape);

  //! The same as above, but in the case if item not found, repeats
  //! search on the same shape without location. The Loc corresponds to the
  //! location with which result is found (either location of the Shape,
  //! or Null)
  Standard_EXPORT static occ::handle<StepRepr_RepresentationItem> FindEntity(
    const occ::handle<Transfer_FinderProcess>& FinderProcess,
    const TopoDS_Shape&                        Shape,
    TopLoc_Location&                           Loc);

  //! Returns Shape resulting from given STEP entity (Null if not mapped)
  Standard_EXPORT static TopoDS_Shape FindShape(
    const occ::handle<Transfer_TransientProcess>&   TransientProcess,
    const occ::handle<StepRepr_RepresentationItem>& item);

  //! Find CDSR corresponding to the component in the specified assembly
  Standard_EXPORT static bool FindCDSR(
    const occ::handle<Transfer_Binder>&                         ComponentBinder,
    const occ::handle<StepShape_ShapeDefinitionRepresentation>& AssemblySDR,
    occ::handle<StepShape_ContextDependentShapeRepresentation>& ComponentCDSR);
};

