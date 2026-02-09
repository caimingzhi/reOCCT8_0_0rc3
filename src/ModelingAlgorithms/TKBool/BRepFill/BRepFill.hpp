#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>
#include <NCollection_Array1.hpp>
class TopoDS_Face;
class TopoDS_Edge;
class TopoDS_Shell;
class TopoDS_Wire;
class TopoDS_Shape;
class gp_Ax3;
class gp_Pnt;
class gp_Vec;

class BRepFill
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static TopoDS_Face Face(const TopoDS_Edge& Edge1, const TopoDS_Edge& Edge2);

  Standard_EXPORT static TopoDS_Shell Shell(const TopoDS_Wire& Wire1, const TopoDS_Wire& Wire2);

  Standard_EXPORT static void Axe(const TopoDS_Shape& Spine,
                                  const TopoDS_Wire&  Profile,
                                  gp_Ax3&             AxeProf,
                                  bool&               ProfOnSpine,
                                  const double        Tol);

  Standard_EXPORT static void ComputeACR(const TopoDS_Wire& wire, NCollection_Array1<double>& ACR);

  Standard_EXPORT static TopoDS_Wire InsertACR(const TopoDS_Wire&                wire,
                                               const NCollection_Array1<double>& ACRcuts,
                                               const double                      prec);

private:
  Standard_EXPORT static void SearchOrigin(TopoDS_Wire&  W,
                                           const gp_Pnt& P,
                                           const gp_Vec& V,
                                           const double  Tol);

private:
  friend class BRepFill_PipeShell;
};
