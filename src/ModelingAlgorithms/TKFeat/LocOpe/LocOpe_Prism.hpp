#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDS_Shape.hpp>
#include <gp_Vec.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <Geom_Curve.hpp>
#include <NCollection_Sequence.hpp>
class Geom_Curve;

//! Defines a prism (using Prism from BRepSweep)
//! with modifications provided for the Prism feature.
class LocOpe_Prism
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT LocOpe_Prism();

  Standard_EXPORT LocOpe_Prism(const TopoDS_Shape& Base, const gp_Vec& V);

  Standard_EXPORT LocOpe_Prism(const TopoDS_Shape& Base, const gp_Vec& V, const gp_Vec& Vectra);

  Standard_EXPORT void Perform(const TopoDS_Shape& Base, const gp_Vec& V);

  Standard_EXPORT void Perform(const TopoDS_Shape& Base, const gp_Vec& V, const gp_Vec& Vtra);

  Standard_EXPORT const TopoDS_Shape& FirstShape() const;

  Standard_EXPORT const TopoDS_Shape& LastShape() const;

  Standard_EXPORT const TopoDS_Shape& Shape() const;

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& Shapes(const TopoDS_Shape& S) const;

  Standard_EXPORT void Curves(NCollection_Sequence<occ::handle<Geom_Curve>>& SCurves) const;

  Standard_EXPORT occ::handle<Geom_Curve> BarycCurve() const;

private:
  Standard_EXPORT void IntPerf();

  TopoDS_Shape myBase;
  gp_Vec       myVec;
  gp_Vec       myTra;
  bool         myIsTrans;
  bool         myDone;
  TopoDS_Shape myRes;
  TopoDS_Shape myFirstShape;
  TopoDS_Shape myLastShape;
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher> myMap;
};
