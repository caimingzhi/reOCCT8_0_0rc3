#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <IGESToBRep_CurveAndSurface.hpp>
class Geom_Curve;
class IGESData_IGESEntity;
class Geom2d_Curve;
class IGESGeom_BSplineCurve;
class IGESGeom_CircularArc;
class IGESGeom_ConicArc;
class Geom_BSplineCurve;
class IGESGeom_CopiousData;
class Geom2d_BSplineCurve;
class IGESGeom_Line;
class IGESGeom_SplineCurve;
class Geom_Transformation;
class IGESGeom_TransformationMatrix;

//! Provides methods to transfer basic geometric curves entities
//! from IGES to CASCADE.
//! These can be:
//! * Circular arc
//! * Conic arc
//! * Spline curve
//! * BSpline curve
//! * Line
//! * Copious data
//! * Point
//! * Transformation matrix
class IGESToBRep_BasicCurve : public IGESToBRep_CurveAndSurface
{
public:
  DEFINE_STANDARD_ALLOC

  //! Creates a tool BasicCurve ready to run, with
  //! epsilons set to 1.E-04, TheModeTopo to True, the
  //! optimization of the continuity to False.
  Standard_EXPORT IGESToBRep_BasicCurve();

  //! Creates a tool BasicCurve ready to run and sets its
  //! fields as CS's.
  Standard_EXPORT IGESToBRep_BasicCurve(const IGESToBRep_CurveAndSurface& CS);

  //! Creates a tool BasicCurve ready to run.
  Standard_EXPORT IGESToBRep_BasicCurve(const double eps,
                                        const double epsGeom,
                                        const double epsCoeff,
                                        const bool   mode,
                                        const bool   modeapprox,
                                        const bool   optimized);

  //! Transfer a IGESEntity which answer True to the
  //! member : IGESToBRep::IsBasicCurve(IGESEntity). If this
  //! Entity could not be converted, this member returns a NullEntity.
  Standard_EXPORT occ::handle<Geom_Curve> TransferBasicCurve(
    const occ::handle<IGESData_IGESEntity>& start);

  //! Transfert a IGESEntity which answer True to the
  //! member : IGESToBRep::IsBasicCurve(IGESEntity).
  //! The IGESEntity must be a curve UV and its associed TRSF must
  //! be planar. If this Entity could not be converted, this member
  //! returns a NullEntity.
  Standard_EXPORT occ::handle<Geom2d_Curve> Transfer2dBasicCurve(
    const occ::handle<IGESData_IGESEntity>& start);

  Standard_EXPORT occ::handle<Geom_Curve> TransferBSplineCurve(
    const occ::handle<IGESGeom_BSplineCurve>& start);

  Standard_EXPORT occ::handle<Geom2d_Curve> Transfer2dBSplineCurve(
    const occ::handle<IGESGeom_BSplineCurve>& start);

  Standard_EXPORT occ::handle<Geom_Curve> TransferCircularArc(
    const occ::handle<IGESGeom_CircularArc>& start);

  Standard_EXPORT occ::handle<Geom2d_Curve> Transfer2dCircularArc(
    const occ::handle<IGESGeom_CircularArc>& start);

  Standard_EXPORT occ::handle<Geom_Curve> TransferConicArc(
    const occ::handle<IGESGeom_ConicArc>& start);

  Standard_EXPORT occ::handle<Geom2d_Curve> Transfer2dConicArc(
    const occ::handle<IGESGeom_ConicArc>& start);

  Standard_EXPORT occ::handle<Geom_BSplineCurve> TransferCopiousData(
    const occ::handle<IGESGeom_CopiousData>& start);

  Standard_EXPORT occ::handle<Geom2d_BSplineCurve> Transfer2dCopiousData(
    const occ::handle<IGESGeom_CopiousData>& start);

  Standard_EXPORT occ::handle<Geom_Curve> TransferLine(const occ::handle<IGESGeom_Line>& start);

  Standard_EXPORT occ::handle<Geom2d_Curve> Transfer2dLine(const occ::handle<IGESGeom_Line>& start);

  Standard_EXPORT occ::handle<Geom_BSplineCurve> TransferSplineCurve(
    const occ::handle<IGESGeom_SplineCurve>& start);

  Standard_EXPORT occ::handle<Geom2d_BSplineCurve> Transfer2dSplineCurve(
    const occ::handle<IGESGeom_SplineCurve>& start);

  Standard_EXPORT occ::handle<Geom_Transformation> TransferTransformation(
    const occ::handle<IGESGeom_TransformationMatrix>& start);
};
