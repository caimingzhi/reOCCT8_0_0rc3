#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <TopoDS_Shape.hpp>
#include <gp_Vec.hpp>
#include <gp_Ax1.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <gp_Pnt.hpp>

//! Defines a revolution form (using Revol from BRepSweep)
//! with modifications provided for the RevolutionForm feature.
class LocOpe_RevolutionForm
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT LocOpe_RevolutionForm();

  Standard_EXPORT LocOpe_RevolutionForm(const TopoDS_Shape& Base,
                                        const gp_Ax1&       Axe,
                                        const double        Angle);

  Standard_EXPORT void Perform(const TopoDS_Shape& Base, const gp_Ax1& Axe, const double Angle);

  Standard_EXPORT const TopoDS_Shape& FirstShape() const;

  Standard_EXPORT const TopoDS_Shape& LastShape() const;

  Standard_EXPORT const TopoDS_Shape& Shape() const;

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& Shapes(const TopoDS_Shape& S) const;

private:
  Standard_EXPORT void IntPerf();

  TopoDS_Shape myBase;
  gp_Vec       myVec;
  gp_Vec       myTra;
  double       myAngle;
  gp_Ax1       myAxis;
  double       myAngTra;
  bool         myDone;
  bool         myIsTrans;
  TopoDS_Shape myRes;
  TopoDS_Shape myFirstShape;
  TopoDS_Shape myLastShape;
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher> myMap;
  gp_Pnt                                                                                     myPnt1;
  gp_Pnt                                                                                     myPnt2;
};

