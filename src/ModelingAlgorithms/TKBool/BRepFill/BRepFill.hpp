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

  //! Computes a ruled surface between two edges.
  Standard_EXPORT static TopoDS_Face Face(const TopoDS_Edge& Edge1, const TopoDS_Edge& Edge2);

  //! Computes a ruled surface between two wires.
  //! The wires must have the same number of edges.
  Standard_EXPORT static TopoDS_Shell Shell(const TopoDS_Wire& Wire1, const TopoDS_Wire& Wire2);

  //! Computes <AxeProf> as Follow. <Location> is
  //! the Position of the nearest vertex V of <Profile>
  //! to <Spine>.<XDirection> is confused with the tangent
  //! to <Spine> at the projected point of V on the Spine.
  //! <Direction> is normal to <Spine>.
  //! <Spine> is a plane wire or a plane face.
  Standard_EXPORT static void Axe(const TopoDS_Shape& Spine,
                                  const TopoDS_Wire&  Profile,
                                  gp_Ax3&             AxeProf,
                                  bool&               ProfOnSpine,
                                  const double        Tol);

  //! Compute ACR on a wire
  Standard_EXPORT static void ComputeACR(const TopoDS_Wire& wire, NCollection_Array1<double>& ACR);

  //! Insert ACR on a wire
  Standard_EXPORT static TopoDS_Wire InsertACR(const TopoDS_Wire&                wire,
                                               const NCollection_Array1<double>& ACRcuts,
                                               const double                      prec);

private:
  //! Computes origins and orientation on a closed wire
  Standard_EXPORT static void SearchOrigin(TopoDS_Wire&  W,
                                           const gp_Pnt& P,
                                           const gp_Vec& V,
                                           const double  Tol);

private:
  friend class BRepFill_PipeShell;
};
