#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <IGESToBRep_CurveAndSurface.hpp>
class TopoDS_Shape;
class IGESData_IGESEntity;
class IGESGeom_RuledSurface;
class IGESGeom_SurfaceOfRevolution;
class IGESGeom_TabulatedCylinder;
class IGESGeom_OffsetSurface;
class IGESGeom_TrimmedSurface;
class IGESGeom_BoundedSurface;
class IGESGeom_Plane;
class IGESSolid_PlaneSurface;
class IGESBasic_SingleParent;
class gp_Pln;
class gp_Trsf;
class gp_Trsf2d;

//! Provides methods to transfer topologic surfaces entities
//! from IGES to CASCADE.
class IGESToBRep_TopoSurface : public IGESToBRep_CurveAndSurface
{
public:
  DEFINE_STANDARD_ALLOC

  //! Creates a tool TopoSurface ready to run, with
  //! epsilons set to 1.E-04, TheModeTopo to True, the
  //! optimization of the continuity to False.
  Standard_EXPORT IGESToBRep_TopoSurface();

  //! Creates a tool TopoSurface ready to run and sets its
  //! fields as CS's.
  Standard_EXPORT IGESToBRep_TopoSurface(const IGESToBRep_CurveAndSurface& CS);

  //! Creates a tool TopoSurface ready to run.
  Standard_EXPORT IGESToBRep_TopoSurface(const double eps,
                                         const double epsGeom,
                                         const double epsCoeff,
                                         const bool   mode,
                                         const bool   modeapprox,
                                         const bool   optimized);

  Standard_EXPORT TopoDS_Shape TransferTopoSurface(const occ::handle<IGESData_IGESEntity>& start);

  Standard_EXPORT TopoDS_Shape
    TransferTopoBasicSurface(const occ::handle<IGESData_IGESEntity>& start);

  Standard_EXPORT TopoDS_Shape
    TransferRuledSurface(const occ::handle<IGESGeom_RuledSurface>& start);

  Standard_EXPORT TopoDS_Shape
    TransferSurfaceOfRevolution(const occ::handle<IGESGeom_SurfaceOfRevolution>& start);

  Standard_EXPORT TopoDS_Shape
    TransferTabulatedCylinder(const occ::handle<IGESGeom_TabulatedCylinder>& start);

  Standard_EXPORT TopoDS_Shape
    TransferOffsetSurface(const occ::handle<IGESGeom_OffsetSurface>& start);

  Standard_EXPORT TopoDS_Shape
    TransferTrimmedSurface(const occ::handle<IGESGeom_TrimmedSurface>& start);

  Standard_EXPORT TopoDS_Shape
    TransferBoundedSurface(const occ::handle<IGESGeom_BoundedSurface>& start);

  Standard_EXPORT TopoDS_Shape TransferPlane(const occ::handle<IGESGeom_Plane>& start);

  Standard_EXPORT TopoDS_Shape
    TransferPlaneSurface(const occ::handle<IGESSolid_PlaneSurface>& start);

  Standard_EXPORT TopoDS_Shape TransferPerforate(const occ::handle<IGESBasic_SingleParent>& start);

  Standard_EXPORT TopoDS_Shape ParamSurface(const occ::handle<IGESData_IGESEntity>& start,
                                            gp_Trsf2d&                              trans,
                                            double&                                 uFact);

private:
  Standard_EXPORT TopoDS_Shape TransferPlaneParts(const occ::handle<IGESGeom_Plane>& start,
                                                  gp_Pln&                            gplan,
                                                  gp_Trsf&                           locat,
                                                  const bool                         first);

  double TheULength;
};

