#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Real.hpp>
#include <Standard_Boolean.hpp>
class TDataXtd_Constraint;
class AIS_InteractiveObject;
class TCollection_ExtendedString;
class TopoDS_Shape;
class Geom_Geometry;

class TPrsStd_ConstraintTools
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void UpdateOnlyValue(const occ::handle<TDataXtd_Constraint>&   aConst,
                                              const occ::handle<AIS_InteractiveObject>& anAIS);

  Standard_EXPORT static void ComputeDistance(const occ::handle<TDataXtd_Constraint>& aConst,
                                              occ::handle<AIS_InteractiveObject>&     anAIS);

  Standard_EXPORT static void ComputeParallel(const occ::handle<TDataXtd_Constraint>& aConst,
                                              occ::handle<AIS_InteractiveObject>&     anAIS);

  Standard_EXPORT static void ComputeTangent(const occ::handle<TDataXtd_Constraint>& aConst,
                                             occ::handle<AIS_InteractiveObject>&     anAIS);

  Standard_EXPORT static void ComputePerpendicular(const occ::handle<TDataXtd_Constraint>& aConst,
                                                   occ::handle<AIS_InteractiveObject>&     anAIS);

  Standard_EXPORT static void ComputeConcentric(const occ::handle<TDataXtd_Constraint>& aConst,
                                                occ::handle<AIS_InteractiveObject>&     anAIS);

  Standard_EXPORT static void ComputeSymmetry(const occ::handle<TDataXtd_Constraint>& aConst,
                                              occ::handle<AIS_InteractiveObject>&     anAIS);

  Standard_EXPORT static void ComputeMidPoint(const occ::handle<TDataXtd_Constraint>& aConst,
                                              occ::handle<AIS_InteractiveObject>&     anAIS);

  Standard_EXPORT static void ComputeAngle(const occ::handle<TDataXtd_Constraint>& aConst,
                                           occ::handle<AIS_InteractiveObject>&     anAIS);

  Standard_EXPORT static void ComputeRadius(const occ::handle<TDataXtd_Constraint>& aConst,
                                            occ::handle<AIS_InteractiveObject>&     anAIS);

  Standard_EXPORT static void ComputeMinRadius(const occ::handle<TDataXtd_Constraint>& aConst,
                                               occ::handle<AIS_InteractiveObject>&     anAIS);

  Standard_EXPORT static void ComputeMaxRadius(const occ::handle<TDataXtd_Constraint>& aConst,
                                               occ::handle<AIS_InteractiveObject>&     anAIS);

  Standard_EXPORT static void ComputeEqualDistance(const occ::handle<TDataXtd_Constraint>& aConst,
                                                   occ::handle<AIS_InteractiveObject>&     anAIS);

  Standard_EXPORT static void ComputeEqualRadius(const occ::handle<TDataXtd_Constraint>& aConst,
                                                 occ::handle<AIS_InteractiveObject>&     anAIS);

  Standard_EXPORT static void ComputeFix(const occ::handle<TDataXtd_Constraint>& aConst,
                                         occ::handle<AIS_InteractiveObject>&     anAIS);

  Standard_EXPORT static void ComputeDiameter(const occ::handle<TDataXtd_Constraint>& aConst,
                                              occ::handle<AIS_InteractiveObject>&     anAIS);

  Standard_EXPORT static void ComputeOffset(const occ::handle<TDataXtd_Constraint>& aConst,
                                            occ::handle<AIS_InteractiveObject>&     anAIS);

  Standard_EXPORT static void ComputePlacement(const occ::handle<TDataXtd_Constraint>& aConst,
                                               occ::handle<AIS_InteractiveObject>&     anAIS);

  Standard_EXPORT static void ComputeCoincident(const occ::handle<TDataXtd_Constraint>& aConst,
                                                occ::handle<AIS_InteractiveObject>&     anAIS);

  Standard_EXPORT static void ComputeRound(const occ::handle<TDataXtd_Constraint>& aConst,
                                           occ::handle<AIS_InteractiveObject>&     anAIS);

  Standard_EXPORT static void ComputeOthers(const occ::handle<TDataXtd_Constraint>& aConst,
                                            occ::handle<AIS_InteractiveObject>&     anAIS);

  Standard_EXPORT static void ComputeTextAndValue(const occ::handle<TDataXtd_Constraint>& aConst,
                                                  double&                                 aValue,
                                                  TCollection_ExtendedString&             aText,
                                                  const bool anIsAngle);

  Standard_EXPORT static void ComputeAngleForOneFace(const occ::handle<TDataXtd_Constraint>& aConst,
                                                     occ::handle<AIS_InteractiveObject>&     anAIS);

private:
  Standard_EXPORT static void GetOneShape(const occ::handle<TDataXtd_Constraint>& aConst,
                                          TopoDS_Shape&                           aShape);

  Standard_EXPORT static void GetGeom(const occ::handle<TDataXtd_Constraint>& aConst,
                                      occ::handle<Geom_Geometry>&             aGeom);

  Standard_EXPORT static void GetTwoShapes(const occ::handle<TDataXtd_Constraint>& aConst,
                                           TopoDS_Shape&                           aShape1,
                                           TopoDS_Shape&                           aShape2);

  Standard_EXPORT static void GetShapesAndGeom(const occ::handle<TDataXtd_Constraint>& aConst,
                                               TopoDS_Shape&                           aShape1,
                                               TopoDS_Shape&                           aShape2,
                                               occ::handle<Geom_Geometry>&             aGeom);

  Standard_EXPORT static void GetShapesAndGeom(const occ::handle<TDataXtd_Constraint>& aConst,
                                               TopoDS_Shape&                           aShape1,
                                               TopoDS_Shape&                           aShape2,
                                               TopoDS_Shape&                           aShape3,
                                               occ::handle<Geom_Geometry>&             aGeom);

  Standard_EXPORT static void GetShapesAndGeom(const occ::handle<TDataXtd_Constraint>& aConst,
                                               TopoDS_Shape&                           aShape1,
                                               TopoDS_Shape&                           aShape2,
                                               TopoDS_Shape&                           aShape3,
                                               TopoDS_Shape&                           aShape4,
                                               occ::handle<Geom_Geometry>&             aGeom);
};

