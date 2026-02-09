#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <BRepFill_Pipe.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <Geom_Curve.hpp>
#include <NCollection_Sequence.hpp>
#include <gp_Pnt.hpp>
class TopoDS_Wire;
class Geom_Curve;

class LocOpe_Pipe
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT LocOpe_Pipe(const TopoDS_Wire& Spine, const TopoDS_Shape& Profile);

  const TopoDS_Shape& Spine() const;

  const TopoDS_Shape& Profile() const;

  const TopoDS_Shape& FirstShape() const;

  const TopoDS_Shape& LastShape() const;

  Standard_EXPORT const TopoDS_Shape& Shape() const;

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& Shapes(const TopoDS_Shape& S);

  Standard_EXPORT const NCollection_Sequence<occ::handle<Geom_Curve>>& Curves(
    const NCollection_Sequence<gp_Pnt>& Spt);

  Standard_EXPORT occ::handle<Geom_Curve> BarycCurve();

private:
  BRepFill_Pipe                                                                              myPipe;
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher> myMap;
  TopoDS_Shape                                                                               myRes;
  NCollection_List<TopoDS_Shape>                myGShap;
  NCollection_Sequence<occ::handle<Geom_Curve>> myCrvs;
  TopoDS_Shape                                  myFirstShape;
  TopoDS_Shape                                  myLastShape;
};

inline const TopoDS_Shape& LocOpe_Pipe::Spine() const
{
  return myPipe.Spine();
}

inline const TopoDS_Shape& LocOpe_Pipe::Profile() const
{
  return myPipe.Profile();
}

inline const TopoDS_Shape& LocOpe_Pipe::FirstShape() const
{
  return myPipe.FirstShape();
}

inline const TopoDS_Shape& LocOpe_Pipe::LastShape() const
{
  return myPipe.LastShape();
}
