#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <ShapeAnalysis_WireVertex.hpp>
#include <Standard_Integer.hpp>
class TopoDS_Wire;
class ShapeExtend_WireData;

//! Fixing disconnected edges in the wire
//! Fixes vertices in the wire on the basis of pre-analysis
//! made by ShapeAnalysis_WireVertex (given as argument).
//! The Wire has formerly been loaded in a ShapeExtend_WireData.
class ShapeFix_WireVertex
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT ShapeFix_WireVertex();

  //! Loads the wire, ininializes internal analyzer
  //! (ShapeAnalysis_WireVertex) with the given precision,
  //! and performs analysis
  Standard_EXPORT void Init(const TopoDS_Wire& wire, const double preci);

  //! Loads the wire, ininializes internal analyzer
  //! (ShapeAnalysis_WireVertex) with the given precision,
  //! and performs analysis
  Standard_EXPORT void Init(const occ::handle<ShapeExtend_WireData>& sbwd, const double preci);

  //! Loads all the data on wire, already analysed by
  //! ShapeAnalysis_WireVertex
  Standard_EXPORT void Init(const ShapeAnalysis_WireVertex& sawv);

  //! returns internal analyzer
  Standard_EXPORT const ShapeAnalysis_WireVertex& Analyzer() const;

  //! returns data on wire (fixed)
  Standard_EXPORT const occ::handle<ShapeExtend_WireData>& WireData() const;

  //! returns resulting wire (fixed)
  Standard_EXPORT TopoDS_Wire Wire() const;

  //! Fixes "Same" or "Close" status (same vertex may be set,
  //! without changing parameters)
  //! Returns the count of fixed vertices, 0 if none
  Standard_EXPORT int FixSame();

  //! Fixes all statuses except "Disjoined", i.e. the cases in which a
  //! common value has been set, with or without changing parameters
  //! Returns the count of fixed vertices, 0 if none
  Standard_EXPORT int Fix();

private:
  ShapeAnalysis_WireVertex myAnalyzer;
};

