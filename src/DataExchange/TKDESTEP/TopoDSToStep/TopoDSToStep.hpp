#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDSToStep_BuilderError.hpp>
#include <TopoDSToStep_MakeFaceError.hpp>
#include <TopoDSToStep_MakeWireError.hpp>
#include <TopoDSToStep_MakeEdgeError.hpp>
#include <TopoDSToStep_MakeVertexError.hpp>
class TCollection_HAsciiString;
class Transfer_FinderProcess;
class TopoDS_Shape;
class Standard_Transient;
class TopoDSToStep_Tool;

//! This package implements the mapping between CAS.CAD
//! Shape representation and AP214 Shape Representation.
//! The target schema is pms_c4 (a subset of AP214)
//!
//! How to use this Package :
//!
//! Entry point are context dependent. It can be :
//! MakeManifoldSolidBrep
//! MakeBrepWithVoids
//! MakeFacetedBrep
//! MakeFacetedBrepAndBrepWithVoids
//! MakeShellBasedSurfaceModel
//! Each of these classes call the Builder
//! The class tool centralizes some common information.
class TopoDSToStep
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static occ::handle<TCollection_HAsciiString> DecodeBuilderError(
    const TopoDSToStep_BuilderError E);

  Standard_EXPORT static occ::handle<TCollection_HAsciiString> DecodeFaceError(
    const TopoDSToStep_MakeFaceError E);

  Standard_EXPORT static occ::handle<TCollection_HAsciiString> DecodeWireError(
    const TopoDSToStep_MakeWireError E);

  Standard_EXPORT static occ::handle<TCollection_HAsciiString> DecodeEdgeError(
    const TopoDSToStep_MakeEdgeError E);

  //! Returns a new shape without undirect surfaces.
  Standard_EXPORT static occ::handle<TCollection_HAsciiString> DecodeVertexError(
    const TopoDSToStep_MakeVertexError E);

  //! Adds an entity into the list of results (binders) for
  //! shape stored in FinderProcess
  Standard_EXPORT static void AddResult(const occ::handle<Transfer_FinderProcess>& FP,
                                        const TopoDS_Shape&                        Shape,
                                        const occ::handle<Standard_Transient>&     entity);

  //! Adds all entities recorded in Tool into the map of results
  //! (binders) stored in FinderProcess
  Standard_EXPORT static void AddResult(const occ::handle<Transfer_FinderProcess>& FP,
                                        const TopoDSToStep_Tool&                   Tool);
};
