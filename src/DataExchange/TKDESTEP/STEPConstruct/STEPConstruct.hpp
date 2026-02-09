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

class STEPConstruct
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static occ::handle<StepRepr_RepresentationItem> FindEntity(
    const occ::handle<Transfer_FinderProcess>& FinderProcess,
    const TopoDS_Shape&                        Shape);

  Standard_EXPORT static occ::handle<StepRepr_RepresentationItem> FindEntity(
    const occ::handle<Transfer_FinderProcess>& FinderProcess,
    const TopoDS_Shape&                        Shape,
    TopLoc_Location&                           Loc);

  Standard_EXPORT static TopoDS_Shape FindShape(
    const occ::handle<Transfer_TransientProcess>&   TransientProcess,
    const occ::handle<StepRepr_RepresentationItem>& item);

  Standard_EXPORT static bool FindCDSR(
    const occ::handle<Transfer_Binder>&                         ComponentBinder,
    const occ::handle<StepShape_ShapeDefinitionRepresentation>& AssemblySDR,
    occ::handle<StepShape_ContextDependentShapeRepresentation>& ComponentCDSR);
};
