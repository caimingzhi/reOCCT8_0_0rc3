#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <BRepFill_Evolved.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Wire.hpp>
#include <TopoDS_Edge.hpp>
#include <Geom_Curve.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
class Geom_Curve;

//! Defines a pipe (near from Pipe from BRepFill),
//! with modifications provided for the Pipe feature.
class LocOpe_DPrism
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT LocOpe_DPrism(const TopoDS_Face& Spine,
                                const double       Height1,
                                const double       Height2,
                                const double       Angle);

  Standard_EXPORT LocOpe_DPrism(const TopoDS_Face& Spine, const double Height, const double Angle);

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT const TopoDS_Shape& Spine() const;

  Standard_EXPORT const TopoDS_Shape& Profile() const;

  Standard_EXPORT const TopoDS_Shape& FirstShape() const;

  Standard_EXPORT const TopoDS_Shape& LastShape() const;

  Standard_EXPORT const TopoDS_Shape& Shape() const;

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& Shapes(const TopoDS_Shape& S) const;

  Standard_EXPORT void Curves(NCollection_Sequence<occ::handle<Geom_Curve>>& SCurves) const;

  Standard_EXPORT occ::handle<Geom_Curve> BarycCurve() const;

private:
  Standard_EXPORT void IntPerf();

  BRepFill_Evolved                              myDPrism;
  TopoDS_Shape                                  myRes;
  TopoDS_Face                                   mySpine;
  TopoDS_Wire                                   myProfile;
  TopoDS_Edge                                   myProfile1;
  TopoDS_Edge                                   myProfile2;
  TopoDS_Edge                                   myProfile3;
  double                                        myHeight;
  TopoDS_Shape                                  myFirstShape;
  TopoDS_Shape                                  myLastShape;
  NCollection_Sequence<occ::handle<Geom_Curve>> myCurvs;
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher> myMap;
};
