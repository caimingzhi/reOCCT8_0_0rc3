#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GeomAbs_Shape.hpp>
#include <ShapeUpgrade_ShapeDivide.hpp>
class TopoDS_Shape;
class ShapeUpgrade_FaceDivide;

//! API Tool for converting shapes with C0 geometry into C1 ones
class ShapeUpgrade_ShapeDivideContinuity : public ShapeUpgrade_ShapeDivide
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT ShapeUpgrade_ShapeDivideContinuity();

  //! Initialize by a Shape.
  Standard_EXPORT ShapeUpgrade_ShapeDivideContinuity(const TopoDS_Shape& S);

  //! Sets tolerance.
  Standard_EXPORT void SetTolerance(const double Tol);

  //! Sets tolerance.
  Standard_EXPORT void SetTolerance2d(const double Tol);

  //! Defines a criterion of continuity for the boundary (all the
  //! Wires)
  //!
  //! The possible values are C0, G1, C1, G2, C2, C3, CN The
  //! default is C1 to respect the Cas.Cade Shape Validity.
  //! G1 and G2 are not authorized.
  Standard_EXPORT void SetBoundaryCriterion(const GeomAbs_Shape Criterion = GeomAbs_C1);

  //! Defines a criterion of continuity for the boundary (all the
  //! pcurves of Wires)
  //!
  //! The possible values are C0, G1, C1, G2, C2, C3, CN The
  //! default is C1 to respect the Cas.Cade Shape Validity.
  //! G1 and G2 are not authorized.
  Standard_EXPORT void SetPCurveCriterion(const GeomAbs_Shape Criterion = GeomAbs_C1);

  //! Defines a criterion of continuity for the boundary (all the
  //! Wires)
  //!
  //! The possible values are C0, G1, C1, G2, C2, C3, CN The
  //! default is C1 to respect the Cas.Cade Shape Validity.
  //! G1 and G2 are not authorized.
  Standard_EXPORT void SetSurfaceCriterion(const GeomAbs_Shape Criterion = GeomAbs_C1);

protected:
  //! Returns the tool for dividing faces.
  Standard_EXPORT occ::handle<ShapeUpgrade_FaceDivide> GetSplitFaceTool() const override;

private:
  GeomAbs_Shape myCurve3dCriterion;
  GeomAbs_Shape myCurve2dCriterion;
  GeomAbs_Shape mySurfaceCriterion;
  double        myTolerance3d;
  double        myTolerance2d;
};
