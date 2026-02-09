#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <ShapeAnalysis_WireVertex.hpp>
#include <Standard_Integer.hpp>
class TopoDS_Wire;
class ShapeExtend_WireData;

class ShapeFix_WireVertex
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT ShapeFix_WireVertex();

  Standard_EXPORT void Init(const TopoDS_Wire& wire, const double preci);

  Standard_EXPORT void Init(const occ::handle<ShapeExtend_WireData>& sbwd, const double preci);

  Standard_EXPORT void Init(const ShapeAnalysis_WireVertex& sawv);

  Standard_EXPORT const ShapeAnalysis_WireVertex& Analyzer() const;

  Standard_EXPORT const occ::handle<ShapeExtend_WireData>& WireData() const;

  Standard_EXPORT TopoDS_Wire Wire() const;

  Standard_EXPORT int FixSame();

  Standard_EXPORT int Fix();

private:
  ShapeAnalysis_WireVertex myAnalyzer;
};
