#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <BRepSweep_Rotation.hpp>
#include <Standard_Boolean.hpp>
class TopoDS_Shape;
class gp_Ax1;
class Sweep_NumShape;
class TopLoc_Location;

class BRepSweep_Revol
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepSweep_Revol(const TopoDS_Shape& S,
                                  const gp_Ax1&       A,
                                  const double        D,
                                  const bool          C = false);

  Standard_EXPORT BRepSweep_Revol(const TopoDS_Shape& S, const gp_Ax1& A, const bool C = false);

  Standard_EXPORT TopoDS_Shape Shape();

  Standard_EXPORT TopoDS_Shape Shape(const TopoDS_Shape& aGenS);

  Standard_EXPORT TopoDS_Shape FirstShape();

  Standard_EXPORT TopoDS_Shape FirstShape(const TopoDS_Shape& aGenS);

  Standard_EXPORT TopoDS_Shape LastShape();

  Standard_EXPORT TopoDS_Shape LastShape(const TopoDS_Shape& aGenS);

  Standard_EXPORT gp_Ax1 Axe() const;

  Standard_EXPORT double Angle() const;

  Standard_EXPORT bool IsUsed(const TopoDS_Shape& aGenS) const;

private:
  Standard_EXPORT Sweep_NumShape NumShape(const double D) const;

  Standard_EXPORT TopLoc_Location Location(const gp_Ax1& Ax, const double D) const;

  Standard_EXPORT gp_Ax1 Axe(const gp_Ax1& Ax, const double D) const;

  Standard_EXPORT double Angle(const double D) const;

  BRepSweep_Rotation myRotation;
};
