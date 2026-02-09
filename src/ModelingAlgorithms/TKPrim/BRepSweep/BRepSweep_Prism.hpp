#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <BRepSweep_Translation.hpp>
#include <Standard_Boolean.hpp>
class TopoDS_Shape;
class gp_Vec;
class gp_Dir;
class Sweep_NumShape;
class TopLoc_Location;

class BRepSweep_Prism
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepSweep_Prism(const TopoDS_Shape& S,
                                  const gp_Vec&       V,
                                  const bool          Copy     = false,
                                  const bool          Canonize = true);

  Standard_EXPORT BRepSweep_Prism(const TopoDS_Shape& S,
                                  const gp_Dir&       D,
                                  const bool          Inf      = true,
                                  const bool          Copy     = false,
                                  const bool          Canonize = true);

  Standard_EXPORT TopoDS_Shape Shape();

  Standard_EXPORT TopoDS_Shape Shape(const TopoDS_Shape& aGenS);

  Standard_EXPORT TopoDS_Shape FirstShape();

  Standard_EXPORT TopoDS_Shape FirstShape(const TopoDS_Shape& aGenS);

  Standard_EXPORT TopoDS_Shape LastShape();

  Standard_EXPORT TopoDS_Shape LastShape(const TopoDS_Shape& aGenS);

  Standard_EXPORT gp_Vec Vec() const;

  Standard_EXPORT bool IsUsed(const TopoDS_Shape& aGenS) const;

  Standard_EXPORT bool GenIsUsed(const TopoDS_Shape& theS) const;

private:
  Standard_EXPORT Sweep_NumShape NumShape() const;

  Standard_EXPORT Sweep_NumShape NumShape(const bool Inf) const;

  Standard_EXPORT TopLoc_Location Location(const gp_Vec& V) const;

  BRepSweep_Translation myTranslation;
};
