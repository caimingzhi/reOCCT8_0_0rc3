#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDS_Shape.hpp>
#include <gp_Ax1.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <Geom_Curve.hpp>
#include <NCollection_Sequence.hpp>
class Geom_Curve;

class LocOpe_Revol
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT LocOpe_Revol();

  Standard_EXPORT LocOpe_Revol(const TopoDS_Shape& Base,
                               const gp_Ax1&       Axis,
                               const double        Angle,
                               const double        angledec);

  Standard_EXPORT LocOpe_Revol(const TopoDS_Shape& Base, const gp_Ax1& Axis, const double Angle);

  Standard_EXPORT void Perform(const TopoDS_Shape& Base,
                               const gp_Ax1&       Axis,
                               const double        Angle,
                               const double        angledec);

  Standard_EXPORT void Perform(const TopoDS_Shape& Base, const gp_Ax1& Axis, const double Angle);

  Standard_EXPORT const TopoDS_Shape& FirstShape() const;

  Standard_EXPORT const TopoDS_Shape& LastShape() const;

  Standard_EXPORT const TopoDS_Shape& Shape() const;

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& Shapes(const TopoDS_Shape& S) const;

  Standard_EXPORT void Curves(NCollection_Sequence<occ::handle<Geom_Curve>>& SCurves) const;

  Standard_EXPORT occ::handle<Geom_Curve> BarycCurve() const;

private:
  Standard_EXPORT void IntPerf();

  TopoDS_Shape myBase;
  gp_Ax1       myAxis;
  double       myAngle;
  double       myAngTra;
  bool         myIsTrans;
  bool         myDone;
  TopoDS_Shape myRes;
  TopoDS_Shape myFirstShape;
  TopoDS_Shape myLastShape;
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher> myMap;
};
